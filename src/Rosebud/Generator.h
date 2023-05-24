#ifndef Rosebud_Generator_H
#define Rosebud_Generator_H
#include <Rosebud/Utility.h>

#include <Sawyer/CommandLine.h>

namespace Rosebud {

/** Base class for backend code generators. */
class Generator {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Nested types
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    using Ptr = GeneratorPtr;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Data members
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    static std::vector<Ptr> registry_;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Construction related stuff
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    virtual ~Generator() {}

protected:
    Generator() {}

public:
    /** Register a backend for use later. */
    static void registerGenerator(const Ptr&);

    /** Return all registered backends. */
    static const std::vector<Ptr>& registeredGenerators();

    /** Return the registered generator with the specified name. */
    static Ptr lookup(const std::string&);

    /** Add command-line switches and documentation to a parser.
     *
     *  Any command-line switches and documentation that is specific to the backend are added to the specified parser. In order to
     *  not conflict with other backends that might also be adding switch parsers, the backend should create a switch group and give
     *  it a unique prefix. */
    virtual void adjustParser(Sawyer::CommandLine::Parser&) {}

    /** Add all known generator switches to parser. */
    static void addAllToParser(Sawyer::CommandLine::Parser&);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /** Every generator should have a unique name. */
    virtual std::string name() const = 0;

    /** Single-line description for documentation. */
    virtual std::string purpose() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Code generation
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /** Generate code.
     *
     *  The specified project AST is used to generate code. */
    virtual void generate(const Ast::ProjectPtr&) = 0;

    /** Data member name for a property.
     *
     *  Returns the name of the class data member that stores the value of the property. The returned value must be a valid C++ name
     *  for the property data member. Each property has exactly one data member. */
    virtual std::string propertyDataMemberName(const Ast::PropertyPtr&) const;

    /** Accessor names for a property.
     *
     *  Returns a list of zero or more C++ member function names to use as accessor names. If no names are returned, then no
     *  accessor functions are declared or defined. */
    virtual std::vector<std::string> propertyAccessorNames(const Ast::PropertyPtr&) const;

    /** Mutator names for a property.
     *
     *  Returns a list of zero or more C++ member function names to use as mutator names. If no names are returned, then no mutator
     *  functions are declared or defined. */
    virtual std::vector<std::string> propertyMutatorNames(const Ast::PropertyPtr&) const;

private:
    static void initRegistry();
};

} // namespace
#endif
