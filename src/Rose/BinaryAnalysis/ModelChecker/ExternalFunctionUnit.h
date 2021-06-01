#ifndef ROSE_BinaryAnalysis_ModelChecker_ExternalFunctionUnit_H
#define ROSE_BinaryAnalysis_ModelChecker_ExternalFunctionUnit_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS

#include <Rose/BinaryAnalysis/ModelChecker/ExecutionUnit.h>
#include <Rose/BinaryAnalysis/CallingConvention.h>
#include <Rose/BinaryAnalysis/Partitioner2/BasicTypes.h>

namespace Rose {
namespace BinaryAnalysis {
namespace ModelChecker {

/** An execution unit for an externally linked function.
 *
 *  This execution unit represents a call to an external function which is not loaded as part of the memory image
 *  for the specimen under consideration. Executing such a call uses the calling conventions to set certain locations
 *  to undefined values. At some point in the future we might provide a more precise way of executing these functions,
 *  but this will do for now. */
class ExternalFunctionUnit: public ExecutionUnit {
public:
    using Ptr = ExternalFunctionUnitPtr;

private:
    Partitioner2::FunctionPtr function_;

protected:
    ExternalFunctionUnit() = delete;
    ExternalFunctionUnit(const Partitioner2::FunctionPtr&, const SourceLocation&);
public:
    ~ExternalFunctionUnit();

public:
    /** Allocating constructor.
     *
     *  Constructs a new execution unit that holds the specified function, which must not be null.
     *
     *  Thread safety: This constructor is thread safe. */
    static Ptr instance(const Partitioner2::FunctionPtr&, const SourceLocation&);

public:
    /** Property: Function.
     *
     *  This is the function associated with the execution unit. This property is read-only and initialized when this
     *  execution object is created.
     *
     *  Thread safety: This property accessor is thread safe. */
    Partitioner2::FunctionPtr function() const;

public:
    virtual std::string printableName() const override;
    virtual void printSteps(const SettingsPtr&, std::ostream&, const std::string &prefix,
                            size_t stepOrigin, size_t maxSteps) const override;
    virtual void toYaml(const SettingsPtr&, std::ostream&, const std::string &prefix,
                        size_t stepOrigin, size_t maxSteps) const override;
    virtual size_t nSteps() const override;
    virtual Sawyer::Optional<rose_addr_t> address() const override;
    virtual std::vector<TagPtr> execute(const SettingsPtr&, const SemanticCallbacksPtr&,
                                        const InstructionSemantics2::BaseSemantics::RiscOperatorsPtr&) override;

private:
    // Read a calling convention parameter location
    InstructionSemantics2::BaseSemantics::SValuePtr
    readLocation(const InstructionSemantics2::BaseSemantics::DispatcherPtr&,
                 const CallingConvention::ParameterLocation&,
                 const InstructionSemantics2::BaseSemantics::SValuePtr &dfltValue);

    // Write to a calling convention parameter location
    void
    writeLocation(const InstructionSemantics2::BaseSemantics::DispatcherPtr&,
                 const CallingConvention::ParameterLocation&,
                 const InstructionSemantics2::BaseSemantics::SValuePtr &value);

    // Set function return values to free variables
    void clearReturnValues(const InstructionSemantics2::BaseSemantics::DispatcherPtr&);

    // Simulate a function return
    void simulateReturn(const InstructionSemantics2::BaseSemantics::DispatcherPtr&);
};


} // namespace
} // namespace
} // namespace

#endif
#endif
