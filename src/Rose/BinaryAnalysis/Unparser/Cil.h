#ifndef ROSE_BinaryAnalysis_Unparser_Cil_H
#define ROSE_BinaryAnalysis_Unparser_Cil_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS
#include <Rose/BinaryAnalysis/Unparser/Base.h>

#include <Rose/BinaryAnalysis/BasicTypes.h>

namespace Rose {
namespace BinaryAnalysis {
namespace Unparser {

std::string unparseCilMnemonic(SgAsmCilInstruction*);
std::string unparseCilExpression(SgAsmExpression*, const LabelMap*);

/** %Settings specific to the Cil unaprser. */
struct CilSettings: public Settings {};

/** %Unparser for CIL. */
class Cil: public Base {
    CilSettings settings_;

protected:
    explicit Cil(const Architecture::BaseConstPtr&, const CilSettings&);

public:
    ~Cil();

    static Ptr instance(const Architecture::BaseConstPtr&, const CilSettings& = CilSettings());

    Ptr copy() const override;

    const CilSettings& settings() const override { return settings_; }
    CilSettings& settings() override { return settings_; }

protected:
    void emitInstruction(std::ostream&, SgAsmInstruction*, State&) const override;
    void emitOperandBody(std::ostream&, SgAsmExpression*, State&) const override;

private:
    void outputExpr(std::ostream&, SgAsmExpression*, State&) const;
};

} // namespace
} // namespace
} // namespace

#endif
#endif
