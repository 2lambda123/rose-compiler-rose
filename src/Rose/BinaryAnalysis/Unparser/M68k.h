#ifndef ROSE_BinaryAnalysis_Unparser_M68k_H
#define ROSE_BinaryAnalysis_Unparser_M68k_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS
#include <Rose/BinaryAnalysis/Unparser/Base.h>

namespace Rose {
namespace BinaryAnalysis {
namespace Unparser {

std::string unparseM68kMnemonic(SgAsmM68kInstruction*);
std::string unparseM68kExpression(SgAsmExpression*, const LabelMap*, const RegisterDictionary*);

struct M68kSettings: public Settings {};

class M68k: public Base {
    M68kSettings settings_;

protected:
    explicit M68k(const M68kSettings &settings)
        : settings_(settings) {}

public:
    static Ptr instance(const M68kSettings &settings = M68kSettings()) {
        return Ptr(new M68k(settings));
    }

    Ptr copy() const ROSE_OVERRIDE {
        return instance(settings());
    }
    
    const M68kSettings& settings() const ROSE_OVERRIDE { return settings_; }
    M68kSettings& settings() ROSE_OVERRIDE { return settings_; }

protected:
    void emitInstruction(std::ostream&, SgAsmInstruction*, State&) const ROSE_OVERRIDE;
    void emitOperandBody(std::ostream&, SgAsmExpression*, State&) const ROSE_OVERRIDE;

private:
    void outputExpr(std::ostream&, SgAsmExpression*, State&) const;
};

} // namespace
} // namespace
} // namespace

#endif
#endif
