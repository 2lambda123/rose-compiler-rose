/** CIL MethodDef node (II.22.26). */
class SgAsmCilMethodDef: public SgAsmCilMetadata {
public:
    /** Property: RVA.
     *
     *  A 4-byte constant. */
    [[using Rosebud: rosetta]]
    uint32_t RVA = 0;

    /** Property: ImplFlags.
     *
     *  A 2-byte bitmask of type MethodImplAttributes. */
    [[using Rosebud: rosetta]]
    uint32_t ImplFlags = 0;

    /** Property: Flags.
     *
     *  A 2-byte bitmask of type MethodAttributes. */
    [[using Rosebud: rosetta]]
    uint16_t Flags = 0;

    /** Property: Name.
     *
     *  An index into the String heap. */
    [[using Rosebud: rosetta]]
    uint32_t Name = 0;

    /** Property: Signature.
     *
     *  An index into the Blob heap. */
    [[using Rosebud: rosetta]]
    uint32_t Signature = 0;

    /** Property: ParamList.
     *
     *  An index into the Param table. */
    [[using Rosebud: rosetta]]
    uint32_t ParamList = 0;


    /** Property: body.
     *
     *  A block containing an instruction sequence (either x86 or CIL). */
    [[using Rosebud: rosetta]]
    SgAsmBlock* body = 0;

    /** Property: initLocals.
     *
     *  Returns true if locals are initialized. */
    [[using Rosebud: rosetta]]
    bool initLocals = 0;

    /** Property: stackSize.
     *
     *  Returns the max stack size required for this method. */
    [[using Rosebud: rosetta]]
    uint32_t stackSize = 0;

    /** Property: hasMoreSections.
     *
     *  Returns true if this method has more sections in addition to the body. */
    [[using Rosebud: rosetta]]
    bool hasMoreSections = 0;
public:
    void parse(std::vector<uint8_t>& buf, size_t& index, uint64_t uses4byteIndexing);

    const std::uint8_t* get_Name_string() const;
    const std::uint8_t* get_Signature_blob() const;
    const SgAsmCilMetadata* get_ParamList_object() const;
};
