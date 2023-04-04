/* Base class for symbol tables. */
[[Rosebud::abstract]]
class SgAsmGenericSymbol: public SgAsmExecutableFileFormat {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Local types
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /** Symbol definition state. */
    enum SymbolDefState {
        SYM_UNDEFINED,          /**< Symbol has not been defined yet. */
        SYM_TENTATIVE,          /**< Does not have size/value yet. E.g., uninitialized C or Fortran common blks. */
        SYM_DEFINED             /**< Created and assigned storage. */
    };

    /** Symbol type. */
    enum SymbolType {
        SYM_NO_TYPE,            /**< No type or type is unknown. */
        SYM_DATA,               /**< Normal variable definitions. */
        SYM_FUNC,               /**< Function or other code. */
        SYM_SECTION,            /**< Section of a file. */
        SYM_FILE,               /**< Name of a file. */
        SYM_ARRAY,              /**< Array of some other type. */
        SYM_TLS,                /**< Thread-local storage. */
        SYM_REGISTER,           /**< CPU register value. See Sparc. */
        SYM_COMMON,             /**< Common block. */
        SYM_IFUNC               /**< Indirection function. */
    };

    /** Symbol binding. */
    enum SymbolBinding {
        SYM_NO_BINDING,         /**< Unknown binding. */
        SYM_LOCAL,              /**< Local binding. */
        SYM_GLOBAL,             /**< Global binding. */
        SYM_WEAK                /**< Weak binding. */
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /** Property: Definition state. */
    [[using Rosebud: rosetta]]
    SgAsmGenericSymbol::SymbolDefState def_state = SgAsmGenericSymbol::SYM_UNDEFINED;

    /** Property: Symbol binding. */
    [[using Rosebud: rosetta]]
    SgAsmGenericSymbol::SymbolBinding binding = SgAsmGenericSymbol::SYM_NO_BINDING;

    /** Property: Symbol type. */
    [[using Rosebud: rosetta]]
    SgAsmGenericSymbol::SymbolType type = SgAsmGenericSymbol::SYM_NO_TYPE;

    /** Property: Symbol value. */
    [[using Rosebud: rosetta]]
    rose_addr_t value = 0;

    /** Property: Symbol size in bytes. */
    [[using Rosebud: rosetta]]
    rose_addr_t size = 0;

    /** Property: Associated file section. */
    [[using Rosebud: rosetta]]
    SgAsmGenericSection* bound = nullptr;

    /** Property: Name.
     *
     * @{ */
    [[using Rosebud: rosetta, traverse, accessors(), mutators()]]
    SgAsmGenericString* name = nullptr;

    SgAsmGenericString* get_name() const;
    void set_name(SgAsmGenericString*);
    /** @} */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /** Print some debugging info. */
    virtual void dump(FILE*, const char *prefix, ssize_t idx) const;
};
