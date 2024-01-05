#ifndef ROSE_BinaryAnalysis_Architecture_Powerpc_H
#define ROSE_BinaryAnalysis_Architecture_Powerpc_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS
#include <Rose/BinaryAnalysis/Architecture/Base.h>

namespace Rose {
namespace BinaryAnalysis {
namespace Architecture {

/** Base class for PowerPC architectures. */
class Powerpc: public Base {
public:
    using Ptr = PowerpcPtr;

protected:
    explicit Powerpc(size_t bytesPerWord, ByteOrder::Endianness);
public:
    ~Powerpc();

public:
    virtual const CallingConvention::Dictionary& callingConventions() const override;
    std::string instructionDescription(const SgAsmInstruction*) const override;
    bool terminatesBasicBlock(SgAsmInstruction*) const override;
    bool isFunctionCallFast(const std::vector<SgAsmInstruction*>&, rose_addr_t *target, rose_addr_t *ret) const override;
    bool isFunctionReturnFast(const std::vector<SgAsmInstruction*>&) const override;
    Disassembler::BasePtr newInstructionDecoder() const override;
    Unparser::BasePtr newUnparser() const override;

    virtual InstructionSemantics::BaseSemantics::DispatcherPtr
    newInstructionDispatcher(const InstructionSemantics::BaseSemantics::RiscOperatorsPtr&) const override;

    std::vector<Partitioner2::FunctionPrologueMatcherPtr>
    functionPrologueMatchers(const Partitioner2::EnginePtr&) const override;

protected:
    // IBM calling convention
    CallingConvention::DefinitionPtr cc_ibm(size_t bitsPerWord) const;
};

} // namespace
} // namespace
} // namespace

#endif
#endif
