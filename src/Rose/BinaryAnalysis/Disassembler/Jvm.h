#ifndef ROSE_BinaryAnalysis_Disassembler_Jvm_H
#define ROSE_BinaryAnalysis_Disassembler_Jvm_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS

#include <Rose/BinaryAnalysis/Disassembler/Base.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

namespace Rose {
namespace BinaryAnalysis {
namespace Disassembler {

/** JVM Disassembler.
 *
 *  This disassembler decodes JVM instructions.
 */
class Jvm: public Base {
public:
    /** Reference counting pointer. */
    using Ptr = Sawyer::SharedPointer<Jvm>;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
    // Default constructor for serialization
    Jvm();

public:
  /** Allocating constructor. */
  static Ptr instance();

  virtual ~Jvm();

  virtual Base::Ptr clone() const override;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Public methods
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    virtual bool canDisassemble(SgAsmGenericHeader*) const override;

    virtual Unparser::BasePtr unparser() const override;

    virtual SgAsmInstruction* disassembleOne(const MemoryMap::Ptr&, rose_addr_t va,
                                             AddressSet* successors=nullptr) override;

    virtual SgAsmInstruction* makeUnknownInstruction(const Disassembler::Exception&) override;

private:
    size_t appendTableswitch(const MemoryMap::Ptr &map, rose_addr_t start,
                             SgUnsignedCharList &chars, SgAsmOperandList* operands);
    template <class T>
      size_t appendOperand(const MemoryMap::Ptr &map, rose_addr_t va,
                           SgUnsignedCharList &chars, SgAsmOperandList* operands);

    /* beginning offset to code segment being processed */
    rose_addr_t codeOffset_;

public:
    rose_addr_t codeOffset();
    void codeOffset(rose_addr_t offset);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Serialization
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ROSE_HAVE_BOOST_SERIALIZATION_LIB
private:
    friend class boost::serialization::access;

    template<class S>
    void serialize(S &s, const unsigned /*version*/) {
        s & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Disassembler::Base);
    }
#endif
};

} // namespace
} // namespace
} // namespace

#endif
#endif
