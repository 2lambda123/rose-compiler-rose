#ifndef ROSE_BinaryAnalysis_Partitioner2_ModulesX86_H
#define ROSE_BinaryAnalysis_Partitioner2_ModulesX86_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS
#include <Rose/BinaryAnalysis/Partitioner2/BasicTypes.h>

#include <Rose/BinaryAnalysis/Partitioner2/Modules.h>

namespace Rose {
namespace BinaryAnalysis {
namespace Partitioner2 {

/** Disassembly and partitioning utilities for Intel x86 and amd64. */
namespace ModulesX86 {

/** Matches an x86 function prologue.
 *
 *  The standard x86 function prologue is:
 *
 * @code
 *  push ebp
 *  mov ebp, esp
 * @endcode
 *
 *  The width of ebp and esp must match the word size for the architecture (i.e., they must be EBP and ESP for the i386 family,
 *  and RBP, RSP for the amd64 family). */
class MatchStandardPrologue: public FunctionPrologueMatcher {
protected:
    FunctionPtr function_;
protected:
    MatchStandardPrologue();
public:
    ~MatchStandardPrologue();

public:
    static Ptr instance();                              /**< Allocating constructor. */
    virtual std::vector<FunctionPtr> functions() const override;
    virtual bool match(const PartitionerConstPtr&, rose_addr_t anchor) override;
};

/** Matches an x86 function prologue with hot patch.
 *
 *  A hot-patch prologue is a MOV EDI, EDI instruction followed by a standard prologue. These are generated by Microsoft
 *  compilers.
 *
 *  @todo: FIXME[Robb P. Matzke 2014-08-24]: this function should also check for and attach the bytes prior to the MOV EDI,
 *  EDI. We should also have a version that matches after a patch is activated in case we're disassembling the memory of a
 *  process. */
class MatchHotPatchPrologue: public MatchStandardPrologue {
public:
    static Ptr instance() { return Ptr(new MatchHotPatchPrologue); } /**< Allocating constructor. */
    virtual std::vector<FunctionPtr> functions() const override { return std::vector<FunctionPtr>(1, function_); }
    virtual bool match(const PartitionerConstPtr&, rose_addr_t anchor) override;
};

/** Matches an x86 <code>MOV EDI,EDI; PUSH ESI</code> function prologe. */
class MatchAbbreviatedPrologue: public FunctionPrologueMatcher {
protected:
    FunctionPtr function_;
protected:
    MatchAbbreviatedPrologue();
public:
    ~MatchAbbreviatedPrologue();

public:
    static Ptr instance();                              /**< Allocating constructor. */
    virtual std::vector<FunctionPtr> functions() const override;
    virtual bool match(const PartitionerConstPtr&, rose_addr_t anchor) override;
};

/** Matches an x86 "ENTER xxx, 0" prologue. */
class MatchEnterPrologue: public FunctionPrologueMatcher {
protected:
    FunctionPtr function_;
public:
    static Ptr instance() { return Ptr(new MatchEnterPrologue); } /**< Allocating constructor. */
    virtual std::vector<FunctionPtr> functions() const override { return std::vector<FunctionPtr>(1, function_); }
    virtual bool match(const PartitionerConstPtr&, rose_addr_t anchor) override;
};

/** Match RET followed by PUSH with intervening no-op padding. */
class MatchRetPadPush: public FunctionPrologueMatcher {
protected:
    FunctionPtr function_;
public:
    static Ptr instance() { return Ptr(new MatchRetPadPush); } /**< Allocating constructor. */
    virtual std::vector<FunctionPtr> functions() const override { return std::vector<FunctionPtr>(1, function_); }
    virtual bool match(const PartitionerConstPtr&, rose_addr_t anchor) override;
};

/** Basic block callback to detect function returns.
 *
 *  The architecture agnostic isFunctionReturn test for basic blocks does not detect x86 "RET N" (N!=0) instructions as
 *  returning from a function because such instructions have side effects that apply after the return-to address is popped from
 *  the stack.  Therefore this basic block callback looks for such instructions and sets the isFunctionReturn property for the
 *  basic block. */
class FunctionReturnDetector: public BasicBlockCallback {
public:
    static Ptr instance() { return Ptr(new FunctionReturnDetector); } /**< Allocating constructor. */
    virtual bool operator()(bool chain, const Args&) override;
};

/** Basic block callback to detect "switch" statements.
 *
 *  Examines the instructions of a basic block to determine if they are from a C "switch"-like statement and attempts to find
 *  the "case" labels, adding them as successors to this basic block. */
class SwitchSuccessors: public BasicBlockCallback {
public:
    enum EntryType { ABSOLUTE, RELATIVE };

private:
    Sawyer::Optional<rose_addr_t> tableVa_;             // possible address for jump table
    EntryType entryType_;                               // type of table entries
    size_t entrySizeBytes_;                             // size of each table entry

public:
    SwitchSuccessors()
        : entryType_(ABSOLUTE), entrySizeBytes_(4) {}
    static Ptr instance() { return Ptr(new SwitchSuccessors); } /**< Allocating constructor. */
    virtual bool operator()(bool chain, const Args&) override;
private:
    bool matchPattern1(SgAsmExpression *jmpArg);
    bool matchPattern2(const BasicBlockPtr&, SgAsmInstruction *jmp);
    bool matchPattern3(const PartitionerConstPtr&, const BasicBlockPtr&, SgAsmInstruction *jmp);
    bool matchPatterns(const PartitionerConstPtr&, const BasicBlockPtr&);
};

/** Matches "ENTER x, 0" */
bool matchEnterAnyZero(const PartitionerConstPtr&, SgAsmX86Instruction*);

/** Matches "JMP constant".
 *
 *  Returns the constant if matched, nothing otherwise. */
Sawyer::Optional<rose_addr_t> matchJmpConst(const PartitionerConstPtr&, SgAsmX86Instruction*);

/** Matches "LEA ECX, [EBP + constant]" or variant. */
bool matchLeaCxMemBpConst(const PartitionerConstPtr&, SgAsmX86Instruction*);

/** Matches "JMP [address]" or variant. */
bool matchJmpMem(const PartitionerConstPtr&, SgAsmX86Instruction*);

/** Matches "MOV EBP, ESP" or variant. */
bool matchMovBpSp(const PartitionerConstPtr&, SgAsmX86Instruction*);

/** Matches "MOV EDI, EDI" or variant. */
bool matchMovDiDi(const PartitionerConstPtr&, SgAsmX86Instruction*);

/** Matches "PUSH EBP" or variant. */
bool matchPushBp(const PartitionerConstPtr&, SgAsmX86Instruction*);

/** Matches "PUSH SI" or variant. */
bool matchPushSi(const PartitionerConstPtr&, SgAsmX86Instruction*);

/** Reads a table of code addresses.
 *
 *  Reads a table of code addresses from within the @p tableLimits memory range starting at either the specified @p
 *  probableStartVa or the beginning of the @ref tableLimits. If @p nSkippable is positive, up to that many invalid entries can
 *  be skipped before actual valid entries are found.  If no entries are skipped and the @p probableStartVa is larger than the
 *  minimum @p tableLimits then we also look backward from the @p probableStartVa to consume as many valid table entries as
 *  possible within the @p tableLimits.  An entry is valid if it exists in read-only memory and its value (the target address)
 *  falls within @p targetLimits.
 *
 *  If valid table entries are found, and the table is some arbitrarily small number of entries, then it can be followed by
 *  zero or more single-byte indexes into the table entries.
 *
 *  Upon return, the @p tableLimits is adjusted to be the addresses where valid table entries were found unioned with the
 *  addresses of the optional post-table indexes.  The return value is the valid table entries in the order they occur in the
 *  table. */
std::vector<rose_addr_t> scanCodeAddressTable(const PartitionerConstPtr&, AddressInterval &tableLimits /*in,out*/,
                                              const AddressInterval &targetLimits,
                                              SwitchSuccessors::EntryType tableEntryType, size_t tableEntrySizeBytes,
                                              Sawyer::Optional<rose_addr_t> probableStartVa = Sawyer::Nothing(),
                                              size_t nSkippable = 0);

/** Try to match a base+offset expression.
 *
 *  Matches expressions like:
 *
 * @li base + register
 * @li base + register * size
 * @li [ base + register ]
 * @li [ base + register * size ]
 *
 * Returns the numeric value of @c base or nothing if the expression is not a recognized form. */
Sawyer::Optional<rose_addr_t> findTableBase(SgAsmExpression*);


} // namespace
} // namespace
} // namespace
} // namespace

#endif
#endif
