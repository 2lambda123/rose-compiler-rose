#ifndef Rosebud_RosettaGenerator_H
#define Rosebud_RosettaGenerator_H
#include <Rosebud/Generator.h>

namespace Rosebud {

/** Generator that produces ROSETTA output. */
class RosettaGenerator: public Generator {
    size_t outputWidth = 130;                           // nominal width of the generated code
    boost::filesystem::path rosettaFileName;            // optional name of file into which ROSETTA source code is written
    boost::filesystem::path implDirectoryName;          // optional name of directory where node implementation files are created
    boost::filesystem::path nodeListFileName;           // optional name of file that contains list of all node types
public:
    virtual void adjustParser(Sawyer::CommandLine::Parser&) override;
    virtual void generate(const Ast::ProjectPtr&) override;
    std::string propertyDataMemberName(const Ast::PropertyPtr&p) const override;
    std::vector<std::string> propertyAccessorNames(const Ast::PropertyPtr&) const override;
    std::vector<std::string> propertyMutatorNames(const Ast::PropertyPtr&) const override;

private:
    std::string shortName(const Ast::ClassPtr&);
    std::string rosettaBaseClass(const Ast::ClassPtr&);
    void genRosettaFileBegin(std::ostream &rosetta);
    void genRosettaFileEnd(std::ostream &rosetta);
    void genRosettaFunctionBegin(std::ostream &rosetta);
    void genRosettaFunctionEnd(std::ostream &rosetta);
    void genImplFileBegin(std::ostream &impl, const Ast::ClassPtr&);
    void genImplFileEnd(std::ostream &impl, const Ast::ClassPtr&);
    void genClassDefinition(std::ostream&, const Ast::ClassPtr&, const Hierarchy&);
    void genNonterminalMacros(std::ostream &rosetta, const Ast::ClassPtr&, const Hierarchy&);
    void genNewNonterminalMacro(std::ostream &rosetta, const Ast::ClassPtr&, const Hierarchy&);
    void genLeafMacros(std::ostream &rosetta, const Ast::ClassPtr&);
    void genClassBegin(std::ostream &rosetta, const Ast::ClassPtr&);
    void genClassEnd(std::ostream &rosetta, const Ast::ClassPtr&);
    void genClassDeclarations(std::ostream &rosetta, const Classes&);
    void genProperty(std::ostream &rosetta, std::ostream &header, std::ostream &impl, const Ast::PropertyPtr&);
    void genCppConditions(std::ostream &out, const Ast::FilePtr&, const std::string &text);
    void genClassDestructor(std::ostream &header, std::ostream &impl, const Ast::ClassPtr&);
    void genClassConstructors(std::ostream &header, std::ostream &impl, const Ast::ClassPtr&, const Hierarchy&);
    void genInitProperties(std::ostream &header, std::ostream &impl, const Ast::ClassPtr&);
    void genOtherContent(std::ostream &rosetta, const Ast::ClassPtr&, const std::string &content);
    std::vector<std::string> implementationFileNames(const Classes&);
    void adjustNodeList(const std::shared_ptr<Ast::Project>&);
    void genTupFile(const std::vector<std::string> &implFileNames);
    void genMakeFile(const std::vector<std::string> &implFileNames);
    void genCmakeFile(const std::vector<std::string> &implFileNames);
};

} // namespace
#endif
