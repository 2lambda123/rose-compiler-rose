#ifndef ROSE_BinaryAnalysis_ModelChecker_SemanticCallbacks_H
#define ROSE_BinaryAnalysis_ModelChecker_SemanticCallbacks_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS

#include <BinaryAnalysis/ModelChecker/Types.h>

#include <BaseSemanticsTypes.h>
#include <Partitioner2/Partitioner.h>

namespace Rose {
namespace BinaryAnalysis {
namespace ModelChecker {

/** User-defined functions for model checking semantics.
 *
 *  This class contains functions that are called by the model checker engine and which are meant to be overridden by
 *  users. This base class provides some reasonable defaults for some of the functions, but some of the others are
 *  pure virtual. */
class SemanticCallbacks {
public:
    using Ptr = SemanticCallbacksPtr;

private:
    const SettingsPtr mcSettings_;                      // model checker settings

protected:
    SemanticCallbacks() = delete;
    explicit SemanticCallbacks(const SettingsPtr&);
public:
    virtual ~SemanticCallbacks();

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Functions for creating the semantics framework
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /** Reset internal data.
     *
     *  This is called when the model checker framework is reset. It should reset most internal data associated with the model
     *  checking process itself, but should not reset settings that control how the model checker works.
     *
     *  Thread safety: This method is not thread safe. */
    virtual void reset() {}

    /** Property: Model checker settings.
     *
     *  Returns a pointer to the model checker settings.
     *
     *  Thread safety: This method is thread safe. */
    SettingsPtr mcSettings() const;

    /** Create a prototypical semantic value.
     *
     *  The prototypical value is used to instantiate other parts of the semantic framework and is what defines the semantic
     *  domain in conjunction with the @ref Rose::BinaryAnalysis::InstructionSemantics2::BaseSemantics::RiscOperators "RISC
     *  operators". The default implementation returns a prototypical value of the @ref
     *  Rose::BinaryAnalysis::InstructionSemantics2::SymbolicSemantics "symbolic domain".
     *
     *  Thread safety: The implementation must be thread safe, but the object it returns does not need to have a thread safe
     *  API. */
    virtual InstructionSemantics2::BaseSemantics::SValuePtr protoval();

    /** Create an initial register state.
     *
     *  Creates the initial register state for paths. The registers can be initialize here or in @ref initializeState.
     *
     *  Thread safety: The implementation must be thread safe, but the object it returns does not need to have a thread safe
     *  API. */
    virtual InstructionSemantics2::BaseSemantics::RegisterStatePtr createInitialRegisters() = 0;

    /** Create an initial memory state.
     *
     *  Creates the initial memory state for paths. The memory can be initialized here or in @ref initializeState.
     *
     *  Thread safety: The implementation must be thread safe, but the object it returns does not need to have a thread safe
     *  API. */
    virtual InstructionSemantics2::BaseSemantics::MemoryStatePtr createInitialMemory() = 0;

    /** Create an initial state.
     *
     *  Creates the initial state for paths beginning at the specified execution unit. The default implementation
     *  uses the @ref Rose::BinaryAnalysis::InstructionSemantics2::BaseSemantics::State "base semantics state".
     *
     *  Thread safety: The implementation must be thread safe, but the object it returns does not need to have a thread safe
     *  API. */
    virtual InstructionSemantics2::BaseSemantics::StatePtr createInitialState();

    /** Create RISC operators.
     *
     *  Creates a new RISC operators object which, together with the @ref protoval, defines the semantic domain.
     *
     *  The returned operators must have a null initial state and null current state. This is to prevent implementations of
     *  this function from accidentally thinking they can initialize the path's state this way -- they can't. Instead, states
     *  are initialized either when they're created (@ref createInitialRegisters, @ref createInitialMemory, @ref
     *  createInitialState) or when they're first associated with a path (@ref initializeState). The latter is the easiest
     *  since it allows one to initialize the state through the RISC operators.  The model checker framework will swap states
     *  into and out of the RISC operators object as necessary.
     *
     *  The RISC operators may refer to an SMT solver if desired. This solver will remain attached to the operators for the
     *  duration of its existence and will be used for operations but not for the model checking. The SMT solver for the model
     *  checker is created by the @ref createSolver method.
     *
     *  Thread safety: The implementation must be thread safe, but the object it returns does not need to have a thread safe
     *  API. */
    virtual InstructionSemantics2::BaseSemantics::RiscOperatorsPtr createRiscOperators() = 0;

    /** Create model checker solver.
     *
     *  This solver will be used for model checker operations, but not for RISC operations (see @ref createRiscOperators). The
     *  The model checker will insert various path assertions when necessary. Whenever the model checker calls user code that
     *  might modify the solver, it will protect the call with a solver transaction. If user code needs to permanently add
     *  assertions, there are other mechanisms to do so. Namely, one needs to add the assertion through a model checker API so
     *  that the model checker knows about it.
     *
     *  Thread safety: The implementation must be thread safe, but the object it returns will be used only by the calling
     *  thread. */
    virtual SmtSolver::Ptr createSolver() = 0;

    /** Associate solver with semantics.
     *
     *  Given the semantics RISC operators for a thread, and the SMT solver used by the model checking for that thread,
     *  associate the model checker solver with the operators.  This only needs to do anything if the semantics need access
     *  to the solver. For instance, a null address checker would evaluate the address during memoryRead and memoryWrite
     *  RISC operations and would therefore benefit from being able to use the model checker's current solver state.
     *
     *  The model checker solver can be completely independent of the SMT solver that's sometimes associated with symbolic RISC
     *  operators, or they can be the same solver.
     *
     *  Thread safety: The implementation must be thread safe, but the provided RISC operators and solver will be thread
     *  local. */
    virtual void attachModelCheckerSolver(const InstructionSemantics2::BaseSemantics::RiscOperatorsPtr&,
                                          const SmtSolver::Ptr&) {}

    /** Initialize the initial state.
     *
     *  This is useful if initializations were not done in @ref createInitialRegisters, @ref createInitialMemory, or @ref
     *  createInitialState.  The benefit of doing it here si that the same code can be used for different semantic domains,
     *  leaving the other functions to choose the domains.  Doing the initialization here also allows you to use the RISC
     *  operators to initialize the states.
     *
     *  Thread safety: The implementation must be thread safe. However, the RISC operators object is thread-local. */
    virtual void initializeState(const InstructionSemantics2::BaseSemantics::RiscOperatorsPtr&);

    /** Create an instruction dispatcher.
     *
     *  The instruction dispatcher is used to transition from one state to another when "executing" an instruction.
     *
     *  Thread safety: The implementation must be thread safe, but the object it returns does not need to have a thread safe
     *  API. */
    virtual InstructionSemantics2::BaseSemantics::DispatcherPtr
    createDispatcher(const InstructionSemantics2::BaseSemantics::RiscOperatorsPtr&) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // State query functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /** Address of the next instruction.
     *
     *  Given a state, return the address of the instruction that would be executed next. It should not modify the current
     *  state associated with the supplied RISC operators.
     *
     *  Thread safety: The implementation must be thread safe, but the provided state will be thread local. */
    virtual InstructionSemantics2::BaseSemantics::SValuePtr
    instructionPointer(const InstructionSemantics2::BaseSemantics::RiscOperatorsPtr&) = 0;

    /** Addresses and completeness.
     *
     *  This is the return value for @ref codeAddresses. */
    struct CodeAddresses {
        InstructionSemantics2::BaseSemantics::SValuePtr ip; /**< Instruction pointer value. */
        std::set<rose_addr_t> addresses;                    /**< The concrete addresses. */
        bool isComplete = true;                             /**< Whether additional non-concrete addresses were found. */
    };

    /** Possible next code addresses.
     *
     *  This method looks at the instruction pointer register (see @ref instructionPointer) and returns whatever concrete
     *  addresses it can find.  It should not modify the current state associated with the RISC operators.
     *
     *  Thread safety: The implementation must be thread safe, but the provided arguments are all thread local. */
    virtual CodeAddresses nextCodeAddresses(const InstructionSemantics2::BaseSemantics::RiscOperatorsPtr&);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Execution tree functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /** Called before execution starts.
     *
     *  This method is called before the execution unit is executed. It is allowed to change the state prior to the execution.
     *  It is also a convenient place at which to create tags to be later attached to the node.
     *
     *  The default implementation does nothing.
     *
     *  Thread safety: The implementation must be thread safe, but the provided RISC operators will be thread local. The
     *  current state to which the RISC operators pointsw ill have been copied by this thread. */
    virtual std::vector<TagPtr>
    preExecute(const ExecutionUnitPtr&, const InstructionSemantics2::BaseSemantics::RiscOperatorsPtr&);

    /** Called after execution ends.
     *
     *  This method is called after the execution unit is executed. It is allowed to change the execution's resulting state.
     *  It is also a convenient place at which to create tags to be later attached to the node.
     *
     *  The default implementation does nothing.
     *
     *  Thread safety: The implementation must be thread safe, but the provided RISC operators will be thread local. The
     *  current state to which the RISC operators pointsw ill have been copied by this thread. */
    virtual std::vector<TagPtr>
    postExecute(const ExecutionUnitPtr&, const InstructionSemantics2::BaseSemantics::RiscOperatorsPtr&);

    /** Return value for @ref nextUnits. */
    struct NextUnit {
        ExecutionUnitPtr unit;                          /**< Unit to be executed. */
        SymbolicExpr::Ptr assertion;                    /**< Path assertion for this unit. */
    };

    /** Discover next execution units.
     *
     *  Given a semantic state of an execution path, determine how the path should be extended by returning the list of next
     *  execution units.  For instance, a conditional branch instruction would likely result in two new execution units: the
     *  target basic block for when the branch is taken, and the fall-through basic block for when the branch is not taken.
     *
     *  All returned execution units should be feasible. That is, this function should check that the address of a candidate
     *  execution unit satisfies the path constraints that are already represented in the supplied solver.
     *
     *  The order of the returned execution units is irrelevant because they will be sorted within the work list according to
     *  the work list priority function. However, since the user defines both the priority and the execution unit types, this
     *  method can communicate to the priority function via data it stores in the execution unit.
     *
     *  Thread safety: The implementation must be thread safe, but the provided RISC operators will be thread local. The
     *  current state to which the RISC operators points will have been copied by this thread. */
    virtual std::vector<NextUnit>
    nextUnits(const PathPtr&, const InstructionSemantics2::BaseSemantics::RiscOperatorsPtr&, const SmtSolver::Ptr&) = 0;
};

} // namespace
} // namespace
} // namespace

#endif
#endif
