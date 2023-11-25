#ifndef ROSE_BinaryAnalysis_Disassembler_Base_H
#define ROSE_BinaryAnalysis_Disassembler_Base_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS

#include <Rose/BinaryAnalysis/Architecture/BasicTypes.h>
#include <Rose/BinaryAnalysis/CallingConvention.h>
#include <Rose/BinaryAnalysis/Disassembler/BasicTypes.h>
#include <Rose/BinaryAnalysis/Disassembler/Exception.h>
#include <Rose/BinaryAnalysis/InstructionSemantics/BaseSemantics.h>
#include <Rose/BinaryAnalysis/MemoryMap.h>
#include <Rose/BinaryAnalysis/Unparser/Settings.h>
#include <Rose/Diagnostics.h>

#include "integerOps.h"
#include "Map.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>

// REG_SP possibly defined on __sun
// REG_LINK possibly defined on Windows
#undef REG_SP
#undef REG_LINK

namespace Rose {
namespace BinaryAnalysis {
namespace Disassembler {

/** The InstructionMap is a mapping from (absolute) virtual address to disassembled instruction. */
typedef Map<rose_addr_t, SgAsmInstruction*> InstructionMap;

/** Virtual base class for instruction disassemblers.
 *
 *  The @ref Disassembler::Base class is a virtual class providing all non-architecture-specific functionality for
 *  disassembling instructions; architecture-specific components are in subclasses @ref Aarch64, @ref Powerpc, @ref X86, and
 *  others. In general, there is no need to explicitly instantiate or call functions in any of these subclasses.  A @ref
 *  Disassembler::Base is responsible for disassembling a single instruction at a time at some specified address, whereas the
 *  classes in @ref Rose::BinaryAnalysis::Partitioner2 are responsible for deciding what addresses should be disassembled.
 *
 *  The main interface to a @ref Disassembler::Base is the @ref disassembleOne method. It tries to disassemble one instruction
 *  at the specified address from a supplied @ref MemoryMap.  A @ref MemoryMap object represents the data in a virtual address
 *  space. On success, it returns an instance of a subclass of @ref SgAsmInstruction, which serves as the root of an abstract
 *  syntax tree (AST) that containins information about the instruction.  The instruction operands are represented by the
 *  subclasses of @ref SgAsmExpression. If an error occurs during the disassembly of a single instruction, the disassembler
 *  will throw an exception.
 *
 *  New architectures can be added to ROSE without modifying any ROSE source code. One does this through the @ref
 *  Rose::Architecture API. */
class Base: public Sawyer::SharedObject {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                  Types
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    using Ptr = BasePtr;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                  Data members
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    Architecture::BaseConstPtr architecture_;
    CallingConvention::Dictionary callingConventions_;

protected:
    RegisterDescriptor REG_IP, REG_SP, REG_SS, REG_SF, REG_LINK; /**< Register descriptors initialized during construction. */
    ByteOrder::Endianness p_byteOrder = ByteOrder::ORDER_LSB;    /**< Byte order of instructions in memory. */
    size_t instructionAlignment_ = 1;                            /**< Positive alignment constraint for instruction addresses. */

    /** Prototypical dispatcher for creating real dispatchers */
    InstructionSemantics::BaseSemantics::DispatcherPtr p_proto_dispatcher;

public:


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                  Serialization
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ROSE_HAVE_BOOST_SERIALIZATION_LIB
private:
    friend class boost::serialization::access;

    template<class S>
    void serialize(S &s, const unsigned version) {
        s & BOOST_SERIALIZATION_NVP(REG_IP);
        s & BOOST_SERIALIZATION_NVP(REG_SS);
        if (version >= 1)
            s & BOOST_SERIALIZATION_NVP(REG_SF);
        s & BOOST_SERIALIZATION_NVP(p_byteOrder);
        if (version >= 2)
            s & BOOST_SERIALIZATION_NVP(instructionAlignment_);
    }
#endif


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                  Constructors
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
    explicit Base(const Architecture::BaseConstPtr&);

public:
    virtual ~Base();

    /** Creates a new copy of a disassembler. The new copy has all the same settings as the original.
     *
     *  Thread safety: The thread safety of this virtual method depends on the implementation in the subclass. */
    virtual Ptr clone() const = 0;


    /***************************************************************************************************************************
     *                                          Disassembler properties and settings
     ***************************************************************************************************************************/
public:
    /** Property: Architecture. */
    Architecture::BaseConstPtr architecture() const;

    /** Property: Name. */
    const std::string& name() const;

    /** Unparser.
     *
     *  Returns an unparser suitable for unparsing the same instruction set architecture as recognized and produced by this
     *  disassembler. */
    virtual Unparser::BasePtr unparser() const = 0;

    /** Property: Byte order of instructions in memory.
     *
     * @{ */
    ByteOrder::Endianness byteOrder() const { return p_byteOrder; }
    void byteOrder(ByteOrder::Endianness sex) { p_byteOrder = sex; }
    /** @} */

    /** Property: Instruction alignment requirement.
     *
     *  The alignment that's required for instruction addresses. The return value is a positive number of bytes. */
    size_t instructionAlignment() const;
    
    /** Property: Calling convention dictionary.
     *
     *  This is a dictionary of the common calling conventions for this architecture.
     *
     * @{ */
    const CallingConvention::Dictionary& callingConventions() const { return callingConventions_; }
    CallingConvention::Dictionary& callingConventions() { return callingConventions_; }
    void callingConventions(const CallingConvention::Dictionary &d) { callingConventions_ = d; }
    /** @} */

    /** Returns the register that points to instructions. */
    virtual RegisterDescriptor instructionPointerRegister() const {
        ASSERT_forbid(REG_IP.isEmpty());
        return REG_IP;
    }

    /** Returns the register that points to the stack. */
    virtual RegisterDescriptor stackPointerRegister() const {
        ASSERT_forbid(REG_SP.isEmpty());
        return REG_SP;
    }

    /** Returns the register that ponts to the stack frame. */
    virtual RegisterDescriptor stackFrameRegister() const {
        return REG_SF;                                  // need not be valid
    }

    /** Returns the segment register for accessing the stack.  Not all architectures have this register, in which case the
     * default-constructed register descriptor is returned. */
    virtual RegisterDescriptor stackSegmentRegister() const {
        return REG_SS;                                  // need not be valid
    }

    /** Returns the register that holds the return address for a function.
     *
     *  If the architecture doesn't have such a register then a default constructed descriptor is returned. */
    virtual RegisterDescriptor callReturnRegister() const {
        return REG_LINK;                                // need not be valid
    }

    /** Return an instruction semantics dispatcher if possible.
     *
     *  If instruction semantics are implemented for this architecure then return a pointer to a dispatcher. The dispatcher
     *  will have no attached RISC operators and can only be used to create a new dispatcher via its virtual constructor.  If
     *  instruction semantics are not implemented then the null pointer is returned. */
    const Rose::BinaryAnalysis::InstructionSemantics::BaseSemantics::DispatcherPtr& dispatcher() const {
        return p_proto_dispatcher;
    }

    /***************************************************************************************************************************
     *                                          Instruction disassembly functions
     ***************************************************************************************************************************/
public:
    /** This is the lowest level disassembly function and is implemented in the architecture-specific subclasses. It
     *  disassembles one instruction at the specified virtual address. The @p map is a mapping from virtual addresses to
     *  buffer and enables instructions to span file segments that are mapped contiguously in virtual memory by the loader but
     *  which might not be contiguous in the file.  The instruction's successor virtual addresses are added to the optional
     *  successor set (note that successors of an individual instruction can also be obtained via
     *  SgAsmInstruction::getSuccessors). If the instruction cannot be disassembled then an exception is thrown and the
     *  successors set is not modified.
     *
     *  Thread safety:  The safety of this method depends on its implementation in the subclass. In any case, no other thread
     *  can be modifying the MemoryMap or successors set at the same time. */
    virtual SgAsmInstruction *disassembleOne(const MemoryMap::Ptr &map, rose_addr_t start_va, AddressSet *successors=NULL) = 0;

    /** Similar in functionality to the disassembleOne method that takes a MemoryMap argument, except the content buffer is
     *  mapped 1:1 to virtual memory beginning at the specified address.
     *
     *  Thread safety:  The safety of this method depends on the implementation of the disassembleOne() defined in the
     *  subclass. If the subclass is thread safe then this method can be called in multiple threads as long as the supplied
     *  buffer and successors set are not being modified by another thread. */
    SgAsmInstruction *disassembleOne(const unsigned char *buf, rose_addr_t buf_va, size_t buf_size, rose_addr_t start_va,
                                     AddressSet *successors=NULL);


    /***************************************************************************************************************************
     *                                          Miscellaneous methods
     ***************************************************************************************************************************/
public:
    /** Makes an unknown instruction from an exception.
     *
     *  Thread safety: The safety of this method depends on its implementation in the subclass. */
    virtual SgAsmInstruction* makeUnknownInstruction(const Exception&) = 0;

    /** Marks parts of the file that correspond to instructions as having been referenced.
     *
     *  Thread safety: This method is not thread safe. */
    void mark_referenced_instructions(SgAsmInterpretation*, const MemoryMap::Ptr&, const InstructionMap&);

    /** Calculates the successor addresses of a basic block and adds them to a successors set. The successors is always
     *  non-null when called. If the function is able to determine the complete set of successors then it should set @p
     *  complete to true before returning.
     *
     *  Thread safety: Thread safe provided no other thread is modifying the specified instruction map. */
    AddressSet get_block_successors(const InstructionMap&, bool &complete/*out*/);

    /** Finds the highest-address instruction that contains the byte at the specified virtual address. Returns null if no such
     *  instruction exists.
     *
     *  Thread safety: This class method is thread safe provided no other thread is modifying the instruction map nor the
     *  instructions to which the map points, particularly the instructions' virtual address and raw bytes. */
    static SgAsmInstruction *find_instruction_containing(const InstructionMap &insns, rose_addr_t va);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Deprecated [Robb Matzke 2023-11-24]
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    size_t wordSizeBytes() const ROSE_DEPRECATED("use architecture()->bytesPerWord()");
    RegisterDictionaryPtr registerDictionary() const ROSE_DEPRECATED("use architecture()->registerDictionary()");
};

} // namespace
} // namespace
} // namespace

// Class versions must be at global scope
BOOST_CLASS_VERSION(Rose::BinaryAnalysis::Disassembler::Base, 3);

#endif
#endif
