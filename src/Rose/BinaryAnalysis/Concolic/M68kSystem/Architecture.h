#ifndef ROSE_BinaryAnalysis_Concolic_M68kSystem_Architecture_H
#define ROSE_BinaryAnalysis_Concolic_M68kSystem_Architecture_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_CONCOLIC_TESTING

#include <Rose/BinaryAnalysis/Concolic/Architecture.h>
#include <Rose/BinaryAnalysis/Partitioner2/BasicTypes.h>
#include <Rose/Yaml.h>

#include <boost/process/child.hpp>

namespace Rose {
namespace BinaryAnalysis {
namespace Concolic {
namespace M68kSystem {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bare Motorola 68000 system using QEMU
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Architecture: public Concolic::Architecture {
    using Super = Concolic::Architecture;

public:
    /** Reference counting pointer. */
    using Ptr = ArchitecturePtr;

private:
    boost::process::child qemu_;

protected:
    Architecture(const std::string&);                   // for factories
    Architecture(const DatabasePtr&, TestCaseId);
public:
    ~Architecture();

public:
    /** Allocating constructor for test case.
     *
     *  Constructs a new executor for the specified test case.
     *
     * @{ */
    static Ptr instance(const DatabasePtr&, TestCaseId, const Yaml::Node &config);
    static Ptr instance(const DatabasePtr&, const TestCasePtr&, const Yaml::Node &config);
    /** @} */

    /** Allocating constructor to create a factory. */
    static Ptr factory();

public:
    // These are documented in the base class.
    virtual bool matchFactory(const Yaml::Node&) const override;
    virtual Super::Ptr instanceFromFactory(const DatabasePtr&, TestCaseId, const Yaml::Node &config) const override;
    virtual Partitioner2::PartitionerPtr partition(Partitioner2::Engine*, const std::string &specimen) override;
    virtual void configureSystemCalls() override;
    virtual void load(const boost::filesystem::path&) override;
    virtual ByteOrder::Endianness memoryByteOrder() override;
    virtual std::vector<ExecutionEventPtr> createMemoryHashEvents() override;
    virtual std::vector<ExecutionEventPtr> createMemoryAdjustEvents(const MemoryMap::Ptr&, rose_addr_t insnVa) override;
    virtual std::vector<ExecutionEventPtr> createMemoryRestoreEvents() override;
    virtual void mapMemory(const AddressInterval&, unsigned permissions) override;
    virtual void unmapMemory(const AddressInterval&) override;
    virtual void createInputVariables(const Partitioner2::PartitionerConstPtr&, const Emulation::RiscOperatorsPtr&,
                                      const SmtSolver::Ptr&) override;
    virtual void systemCall(const Partitioner2::PartitionerConstPtr&,
                            const InstructionSemantics::BaseSemantics::RiscOperatorsPtr&) override;
    virtual InstructionSemantics::BaseSemantics::DispatcherPtr
        makeDispatcher(const InstructionSemantics::BaseSemantics::RiscOperatorsPtr&) override;
};

} // namespace
} // namespace
} // namespace
} // namespace

#endif
#endif
