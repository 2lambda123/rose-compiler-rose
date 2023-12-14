#ifndef ROSE_BinaryAnalysis_SymbolicExpressionParser_H
#define ROSE_BinaryAnalysis_SymbolicExpressionParser_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS

#include <Rose/BinaryAnalysis/BasicTypes.h>
#include <Rose/BinaryAnalysis/InstructionSemantics/BaseSemantics.h>
#include <Rose/BinaryAnalysis/SymbolicExpression.h>
#include <Rose/Exception.h>
#include <Sawyer/BiMap.h>
#include <Sawyer/CommandLine.h>
#include <Sawyer/Message.h>
#include <Sawyer/SharedPointer.h>

namespace Rose {
namespace BinaryAnalysis {

/** Parses symbolic expressions from text.
 *
 *  Parses symbolic expressions using a simple LISP-like syntax, the same syntax used by the unparser.  An expression can be a
 *  numeric constant with an optional negative sign, a hexadecimal bit vector, a numbered variable like "v123", a named
 *  variable, or an operator with arguments.  Operators are expressed as an operator name and space-separated arguments; the
 *  operator and arguments are both inside the parentheses like in LISP.  A width in bits can be appended to any constant,
 *  variable, or operator name and is a positive number inside square brackets.  Inline comments are enclosed in angle brackets
 *  (less than and greater than signs) and can be nested. Backslashes are used to escape parentheses, square brackets, and
 *  angle brackets to remove their special meaning. The normal C/C++ backslash escapes are also understood.
 *
 *  @todo Symbolic expressions were originally intended to be used only within ROSE and therefore many of the
 *        operations assert that their arguments are correct. Now that users can easily construct their own symbolic
 *        expressions from text, we need to make the failure modes less extreme. [Robb P. Matzke 2015-09-22]. */
class SymbolicExpressionParser {
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Syntax errors that are thrown. */
    class SyntaxError: public Rose::Exception {
    public:
        std::string inputName;                          /**< Name of input, usually a file name. */
        unsigned lineNumber;                            /**< Line number (1-origin). Zero if position info is not available. */
        unsigned columnNumber;                          /**< Column number (0-origin). Unused when @c lineNumber is zero. */
        SyntaxError(const std::string &mesg, const std::string &inputName, unsigned lineNumber, unsigned columnNumber);
        ~SyntaxError() throw () {}
        void print(std::ostream&) const;                /**< Print error message to stream. */
    };

    /** Substitution error during expansion. */
    class SubstitutionError: public Rose::Exception {
    public:
        SubstitutionError(const std::string &mesg)
            : Rose::Exception(mesg) {}
        ~SubstitutionError() throw () {}
        void print(std::ostream&) const;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Tokens generated by the lexical analysis. */
    class Token {
    public:
        /** Token types. */
        enum Type {
            NONE = 0,                                   /**< End of input. */
            LTPAREN,                                    /**< Left parenthesis. */
            RTPAREN,                                    /**< Right parenthesis. */
            BITVECTOR,                                  /**< Numeric constant. */
            SYMBOL                                      /**< Symbol. Symbols are basically anything but white space, comments,
                                                         *   and the other token types. */
        };

    private:
        Type tokenType_;
        std::string lexeme_;                            // lexeme
        SymbolicExpression::Type exprType_;             // type for expression
        Sawyer::Container::BitVector bits_;             // bits representing constant terms
        unsigned lineNumber_, columnNumber_;            // for start of token

    public:
        /** Constructs an end-of-input token with no position information. */
        Token()
            : tokenType_(NONE), lineNumber_(0), columnNumber_(0) {}

        /** Constructs a specific token from a string. Do not use this to construct numeric tokens. */
        Token(Type tokenType, const SymbolicExpression::Type &exprType, const std::string &lexeme,
              unsigned lineNumber, unsigned columnNumber)
            : tokenType_(tokenType), lexeme_(lexeme), exprType_(exprType),
              lineNumber_(lineNumber), columnNumber_(columnNumber) {
            ASSERT_forbid(BITVECTOR == tokenType);
        }

        /** Construct a token for a numeric constant. */
        Token(const Sawyer::Container::BitVector &bv, const SymbolicExpression::Type &exprType, const std::string &lexeme,
              unsigned lineNumber, unsigned columnNumber)
            : tokenType_(BITVECTOR), lexeme_(lexeme), exprType_(exprType), bits_(bv),
              lineNumber_(lineNumber), columnNumber_(columnNumber) {
            ASSERT_require(exprType.nBits() == bv.size());
        }

        /** Creates a syntax error from a token plus message. */
        SymbolicExpressionParser::SyntaxError syntaxError(const std::string &mesg, const std::string &name="input") const {
            return SymbolicExpressionParser::SyntaxError(mesg, name, lineNumber_, columnNumber_);
        }

        /** Token type. */
        Type tokenType() const { return tokenType_; }

        /** Lexeme from which token was parsed. */
        const std::string &lexeme() const { return lexeme_; }

        /** Type of expression. */
        SymbolicExpression::Type exprType() const { return exprType_; }

        /** Bit vector for numeric constants. The bit vector will be empty for non-numeric tokens. */
        const Sawyer::Container::BitVector& bits() const { return bits_; }

        /** Line number for start of token. */
        unsigned lineNumber() const { return lineNumber_; }

        /** Column number for start of token. */
        unsigned columnNumber() const { return columnNumber_; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** A stream of tokens.
     *
     *  This container is conceptually infinite size padded with EOF tokens, although in practice it usually holds only one or
     *  two tokens at a time.  Tokens are consumed by shifting them off the beginning of the stream. */
    class TokenStream {
        std::istream &input_;
        std::string name_;
        unsigned lineNumber_, columnNumber_;
        const Token endToken_;
        std::vector<Token> tokens_;
        int readAhead_;

    public:
        /** Scan tokens from a character stream.
         *
         *  The @p name parameter is the name to use for this stream in error messages (usually a file name), and the @p
         *  lineNumber and @p columnNumber are the position of the first character in the stream. */
        explicit TokenStream(std::istream &input, const std::string &name="input",
                             unsigned lineNumber=1, unsigned columnNumber=0)
            : input_(input), name_(name), lineNumber_(lineNumber), columnNumber_(columnNumber), readAhead_(EOF) {
            init();
        }

        /** Name of this input stream. */
        const std::string& name() const { return name_; }

        /** Current line number. */
        unsigned lineNumber() const { return lineNumber_; }

        /** Current column number. */
        unsigned columnNumber() const { return columnNumber_; }

        /** Returns the specified token without consuming it. */
        const Token& operator[](size_t idx);

        /** Consume the specified number of tokens. */
        void shift(size_t n=1);

        /** Returns the next character.  Returns the next character of input or EOF without consuming it. */
        int nextCharacter();

        /** Consume the next character. Advances over the next character, adjusting line and column information.  Returns the
         * character consumed, or EOF. */
        int consumeCharacter();

        /** Skip over characters until a non-white-space character is encountered. */
        void consumeWhiteSpace();

        /** Skip over an escape sequence and return the escaped character. */
        int consumeEscapeSequence();

        /** Skip over angle-bracket comments. Consumes angle bracket comments like "<this is a comment>". Any right angle
         *  brackets that are part of the comment must be escaped. Unescaped angle brackets can be nested like parentheses. */
        void consumeInlineComment();

        /** Skip over white space and/or inline comments. */
        void consumeWhiteSpaceAndComments();

        /** Parse and consume a term.
         *
         *  A term is a numeric constant or a symbol.  Symbols that start with a letter or underscore contain only letters,
         *  underscores, and decimal digits.  Symbols that start with other than a letter or underscore end at the first
         *  unescaped white-space, comment, parenthesis, angle bracket, or square bracket. Escaping the special character with
         *  a backslash will cause it to become part of the symbol. */
        std::string consumeTerm();

        /** Parse and consume a type specification.
         *
         *  A type specification is a type name in square brackets. If the square brackets contain only an integer then the
         *  type is an integer type with the specified width. */
        SymbolicExpression::Type consumeType();

        /** Parse and consume the next token. Parses and consumes the next token and return it. Returns the special NONE token
         * at end-of-input. */
        Token scan();

    private:
        void init();

        // Try to fill the token vector so it contains tokens up through at least [idx]
        void fillTokenList(size_t idx);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Virtual base class for atom and operator expansion. */
    class Expansion: public Sawyer::SharedObject {
        std::string title_;
        std::string docString_;
    public:
        virtual ~Expansion() {}

        /** Shared-ownership pointer to an @ref Expansion. See @ref heap_object_shared_ownership. */
        typedef Sawyer::SharedPointer<Expansion> Ptr;

        /** Property: Title to use for documentation.
         *
         * @{ */
        const std::string& title() const { return title_; }
        void title(const std::string &s) { title_ = s; }
        /** @} */

        /** Property: Documentation string.
         *
         *  The string uses the simple markup language from Sawyer's command-line processing.
         *
         * @{ */
        const std::string& docString() const { return docString_; }
        void docString(const std::string &s) { docString_ = s; }
        /** @} */

        /** Substitute one expression with another.
         *
         *  This second phase of expansion occurs after parsing (perhaps much later) and is able to dynamically replace the
         *  given expression with some other expression. For instance, if this object recognizes register names, it it might
         *  replace the register names with variables in the first phase, and during the second phase read register values from
         *  a provided state.
         *
         *  If the input expression does not need to be substituted, then this function should return the original
         *  expression. */
        virtual SymbolicExpression::Ptr delayedExpansion(const SymbolicExpression::Ptr &src, const SymbolicExpressionParser*) {
            return src;
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Virtual base class for expanding atoms. */
    class AtomExpansion: public Expansion {
    public:
        /** Shared-ownership pointer to an @ref AtomExpansion. See @ref heap_object_shared_ownership. */
        typedef Sawyer::SharedPointer<AtomExpansion> Ptr;

        /** Expand a parsed atom into some other expression.
         *
         *  This method takes a token parsed from the input and optionally replaces it with some other expression. For
         *  instance, a subclass that recognizes the token "true" would replace it with a single-bit constant 1.  If this
         *  object does not recognize the token, it should return a null pointer. This phase of expansion occurs immediately
         *  during parsing; a second phase may occur later. */
        virtual SymbolicExpression::Ptr immediateExpansion(const Token &name) = 0;
    };

    /** Ordered atom table. */
    typedef std::vector<AtomExpansion::Ptr> AtomTable;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Virtual base class for expanding operators. */
    class OperatorExpansion: public Expansion {
    public:
        /** Shared-ownership pointer. See @ref heap_object_shared_ownership. */
        typedef Sawyer::SharedPointer<OperatorExpansion> Ptr;

    protected:
        SmtSolverPtr solver;                            // may be null

        explicit OperatorExpansion(const SmtSolverPtr &solver);

    public:
        virtual ~OperatorExpansion();

        /** Operator to expand a list into an expression tree. The width in bits is either the width specified in
         *  square brackets for the function symbol, or zero.  Functors are all called for each symbol, and the first one to
         *  return non-null is the one that's used to generate the symbolic expression. */
        virtual SymbolicExpression::Ptr immediateExpansion(const Token &name, const SymbolicExpression::Nodes &operands) = 0;
    };

    /** Ordered operator table. */
    typedef std::vector<OperatorExpansion::Ptr> OperatorTable;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Expand register names to register values.
     *
     *  This expansion uses a @ref BinaryAnalysis::InstructionSemantics::BaseSemantics::RiscOperators "RiscOperators" object to
     *  convert register names in the parse string into register values. The values are substituted at the time the string is
     *  parsed. At this time (2018-08) only the symbolic semantic domain is supported since this is the one usually used with SMT
     *  solvers. */
    class RegisterToValue: public AtomExpansion {
    public:
        /** Shared-ownership pointer. See @ref heap_object_shared_ownership. */
        typedef Sawyer::SharedPointer<RegisterToValue> Ptr;

    private:
        InstructionSemantics::BaseSemantics::RiscOperatorsPtr ops_;

    protected:
        RegisterToValue(const InstructionSemantics::BaseSemantics::RiscOperatorsPtr &ops)
            : ops_(ops) {}

    public:
        /** Allocating constructor. */
        static Ptr instance(const InstructionSemantics::BaseSemantics::RiscOperatorsPtr&);

        // internal
        SymbolicExpression::Ptr immediateExpansion(const SymbolicExpressionParser::Token&) override;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Expand register name to placeholder variables.
     *
     *  The problem with @ref RegisterToValue is that the expansion from register name to register value occurs at parsing
     *  time, and parsing is a relatively slow operation.  Therefore, this class takes a slightly different approach: at
     *  parsing time, register names are replaced by symbolic variables (placeholders), and information is returned about how
     *  these placeholders map to register names. Then, at a later time, a substition can be run to replace the placeholders
     *  with the register values. */
    class RegisterSubstituter: public AtomExpansion {
    public:
        /** Shared-ownership pointer. See @ref heap_object_shared_ownership. */
        typedef Sawyer::SharedPointer<RegisterSubstituter> Ptr;

        // internal
        typedef Sawyer::Container::BiMap<RegisterDescriptor, SymbolicExpression::Ptr> RegToVarMap;

    private:
        RegisterDictionaryPtr regdict_;
        RegToVarMap reg2var_;
        InstructionSemantics::BaseSemantics::RiscOperatorsPtr ops_;

    protected:
        RegisterSubstituter(const RegisterDictionaryPtr &regdict)
            : regdict_(regdict) {}

    public:
        /** Allocating constructor. */
        static Ptr instance(const RegisterDictionaryPtr&);

        /** Property: Semantic state used during delayed expansion.
         *
         *  This property holds a pointer to the semantic operators and its current state that's used during the second phase of expansion
         *  (@ref delayedExpansion).
         *
         * @{ */
        InstructionSemantics::BaseSemantics::RiscOperatorsPtr riscOperators() const {
            return ops_;
        }
        void riscOperators(const InstructionSemantics::BaseSemantics::RiscOperatorsPtr &ops) {
            ops_ = ops;
        }
        /** @} */

        // internal
        SymbolicExpression::Ptr immediateExpansion(const SymbolicExpressionParser::Token&) override;
        SymbolicExpression::Ptr delayedExpansion(const SymbolicExpression::Ptr&, const SymbolicExpressionParser*) override;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Expand "memory" function to placeholder.
     *
     *  This parser replaces functions of the form (memory[NBYTES] ADDRESS) to placeholders that are later substituted with
     *  the actual value read from ROSE's semantic memory state. */
    class MemorySubstituter: public OperatorExpansion {
    public:
        /** Shared-ownership pointer. See @ref heap_object_shared_ownership. */
        typedef Sawyer::SharedPointer<MemorySubstituter> Ptr;

        // internal
        typedef Sawyer::Container::Map<SymbolicExpression::Ptr /*placeholder*/, SymbolicExpression::Ptr /*address*/> ExprToMem;

    private:
        ExprToMem exprToMem_;
        InstructionSemantics::BaseSemantics::RiscOperatorsPtr ops_;

    protected:
        MemorySubstituter(const SmtSolver::Ptr &solver /*=NULL*/)
            : OperatorExpansion(solver) {}

    public:
        /** Allocating constructor */
        static Ptr instance(const SmtSolver::Ptr &solver /*=NULL*/);

        /** Property: Semantic state used during delayed expansion.
         *
         *  This property holds a pointer to the semantic operators and its current state that's used during the second phase of expansion
         *  (@ref delayedExpansion).
         *
         * @{ */
        InstructionSemantics::BaseSemantics::RiscOperatorsPtr riscOperators() const {
            return ops_;
        }
        void riscOperators(const InstructionSemantics::BaseSemantics::RiscOperatorsPtr &ops) {
            ops_ = ops;
        }
        /** @} */

        // internal
        virtual SymbolicExpression::Ptr immediateExpansion(const Token &name, const SymbolicExpression::Nodes &operands) override;
        virtual SymbolicExpression::Ptr delayedExpansion(const SymbolicExpression::Ptr&, const SymbolicExpressionParser*) override;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Expand unrecognized terms to placholder variables.
     *
     *  When parsing a symbolic expression, any unrecognized variable names such as "foo" will be replaced with a new
     *  symbolic variable such as "v48722" and a record of the substitution is saved in this object. The same name is always
     *  substituted with the same placeholder. */
    class TermPlaceholders: public AtomExpansion {
    public:
        /** Shared-ownership pointer. See @ref heap_object_shared_ownership. */
        typedef Sawyer::SharedPointer<TermPlaceholders> Ptr;

        /** Mapping between term names and placeholder variables. */
        typedef Sawyer::Container::BiMap<std::string, SymbolicExpression::Ptr> NameToVarMap;

    private:
        NameToVarMap name2var_;

    protected:
        TermPlaceholders() {}

    public:
        /** Allocating constructor. */
        static Ptr instance();

        /** Mapping between terms and variables. */
        const NameToVarMap& map() const { return name2var_; }

        // internal
        SymbolicExpression::Ptr immediateExpansion(const SymbolicExpressionParser::Token&) override;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Parse a symbolic expression from the command-line.
     *
     *  This class implements a functor for parsing a symbolic expression from a command-line switch argument using the parser
     *  from @ref Sawyer::CommandLine. */
    class SymbolicExprCmdlineParser: public Sawyer::CommandLine::ValueParser {
    protected:
        SymbolicExprCmdlineParser() {}
        SymbolicExprCmdlineParser(const Sawyer::CommandLine::ValueSaver::Ptr &valueSaver)
            : Sawyer::CommandLine::ValueParser(valueSaver) {}

    public:
        /** Shared-ownership pointer. See @ref heap_object_shared_ownership. */
        typedef Sawyer::SharedPointer<SymbolicExprCmdlineParser> Ptr;

        static Ptr instance() {
            return Ptr(new SymbolicExprCmdlineParser);
        }

        static Ptr instance(const Sawyer::CommandLine::ValueSaver::Ptr &valueSaver) {
            return Ptr(new SymbolicExprCmdlineParser(valueSaver));
        }

        static std::string docString();

    private:
        virtual Sawyer::CommandLine::ParsedValue operator()(const char *input, const char **rest,
                                                            const Sawyer::CommandLine::Location &loc) override;
    };

    static SymbolicExprCmdlineParser::Ptr symbolicExprParser(SymbolicExpression::Ptr &storage);
    static SymbolicExprCmdlineParser::Ptr symbolicExprParser(std::vector<SymbolicExpression::Ptr> &storage);
    static SymbolicExprCmdlineParser::Ptr symbolicExprParser();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    AtomTable atomTable_;
    OperatorTable operatorTable_;
    SmtSolverPtr solver_;                               // optional solver for simplifications

public:
    static Sawyer::Message::Facility mlog;

public:
    /** Default constructor. */
    SymbolicExpressionParser();

    /** Parser using a specific SMT solver for simplifications.
     *
     *  The solver may be null in which case ROSE's default simplifications are the only ones used. */
    explicit SymbolicExpressionParser(const SmtSolverPtr &solver);

    ~SymbolicExpressionParser();

    // used internally to initialize the diagnostics system
    static void initDiagnostics();

    /** Create a symbolic expression by parsing a string.
     *
     *  Parses an expression from a string. Throws a @ref SyntaxError if problems are encountered, including when the string
     *  contains additional non-white-space following the expression. */
    SymbolicExpression::Ptr parse(const std::string&, const std::string &inputName="string");

    /** Create a symbolic expression by parsing a file.
     *
     *  Parses the file and returns the first expression in the file. Throws a @ref SyntaxError if problems are encountered. */
    SymbolicExpression::Ptr parse(std::istream &input, const std::string &filename,
                                  unsigned lineNumber=1, unsigned columnNumber=0);

    /** Create a symbolic expression by parsing a token stream.
     *
     *  Parses the token stream and returns its first expression. Throws a @ref SyntaxError if problems are encountered. */
    SymbolicExpression::Ptr parse(TokenStream&);

    /** Append a new functor for expanding atoms into symbolic expressions. */
    void appendAtomExpansion(const AtomExpansion::Ptr&);

    /** Append a new functor for expanding operators into symbolic expressions. */
    void appendOperatorExpansion(const OperatorExpansion::Ptr&);

    /** Return all atom expansion functors.
     *
     * @{ */
    const AtomTable& atomTable() const { return atomTable_; }
    AtomTable& atomTable() { return atomTable_; }
    /** @} */

    /** Return all operator expansion functors.
     *
     * @{ */
    const OperatorTable& operatorTable() const { return operatorTable_; }
    OperatorTable& operatorTable() { return operatorTable_; }
    /** @} */

    /** Documentation string.
     *
     *  Returns the documentation string for this parser. The documentation string is a a simple markup language that can be
     *  used by command-line parsers. */
    std::string docString() const;

    /** Add definitions for registers.
     *
     *  If register definitions are specified, then whenever a register name appears as a token during parsing, it will be
     *  immediately replaced with the value of the register queried from the specified operator state.  If a @ref
     *  Rose::BinaryAnalysis::InstructionSemantics::BaseSemantics::RiscOperators "RiscOperators" object is specified, then the
     *  replacement is the register's current value; if a register dictionary is specified, then the replacement is a new
     *  symbolic variable and an internal table is updated to associate the variable with a register name so that the register
     *  value can be substituted later.
     *
     * @{ */
    void defineRegisters(const InstructionSemantics::BaseSemantics::RiscOperatorsPtr&);
    RegisterSubstituter::Ptr defineRegisters(const RegisterDictionaryPtr&);
    /** @} */

    /** Perform delayed expansion.
     *
     *  This runs the @ref Expansion::delayedExpansion "delayedExpansion" method for each of the registerd expansion functors. */
    SymbolicExpression::Ptr delayedExpansion(const SymbolicExpression::Ptr&) const;

private:
    void init();
};

std::ostream& operator<<(std::ostream&, const SymbolicExpressionParser::SyntaxError&);
std::ostream& operator<<(std::ostream&, const SymbolicExpressionParser::SubstitutionError&);

} // namespace
} // namespace

#endif
#endif
