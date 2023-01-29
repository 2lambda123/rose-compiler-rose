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

#ifdef ROSE_HAVE_BOOST_SERIALIZATION_LIB
private:
  friend class boost::serialization::access;

  template<class S>
  void serialize(S &s, const unsigned /*version*/) {
      s & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Disassembler::Base);
  }
#endif

protected:
  Jvm();

public:
  /** Allocating constructor. */
  static Ptr instance();

  virtual ~Jvm();
  virtual Base::Ptr clone() const override;
  virtual bool canDisassemble(SgAsmGenericHeader*) const override;
  virtual Unparser::BasePtr unparser() const override;
  virtual SgAsmInstruction* makeUnknownInstruction(const Disassembler::Exception&) override;
  virtual SgAsmInstruction* disassembleOne(const MemoryMap::Ptr&, rose_addr_t va, AddressSet *successors = NULL) override;

private:
  size_t append_tableswitch(const MemoryMap::Ptr &map, rose_addr_t start,
                            SgUnsignedCharList &chars, SgAsmOperandList* operands);
  template <class T>
  size_t append_operand(const MemoryMap::Ptr &map, rose_addr_t va,
                        SgUnsignedCharList &chars, SgAsmOperandList* operands);

  /* beginning offset to code segment being processed */
  rose_addr_t code_offset_;
public:
  rose_addr_t code_offset() {return code_offset_;}
  void code_offset(rose_addr_t offset) {code_offset_ = offset;}
};

} // namespace
} // namespace
} // namespace

#endif
#endif
