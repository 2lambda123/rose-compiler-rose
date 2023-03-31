/** CIL Constant node. */
class SgAsmCilConstant: public SgAsmCilMetadata {
    /** Property: Type.
     *
     *  A 1-byte constant. */
    [[using Rosebud: rosetta]]
    uint8_t Type;

    /** Property: Padding.
     *
     *  A 1-byte zero padding. */
    [[using Rosebud: rosetta]]
    uint8_t Padding;

    /** Property: Parent.
     *
     *  An index into the Param, Field, or Property table. */
    [[using Rosebud: rosetta]]
    uint32_t Parent;

    /** Property: Value.
     *
     *  An index into the Blob heap. */
    [[using Rosebud: rosetta]]
    uint32_t Value;

public:
    void parse(std::vector<uint8_t>& buf, size_t& index, uint64_t uses4byteIndexing);

    const SgAsmCilMetadata* get_Parent_object() const;
    const std::uint8_t* get_Value_blob() const;
};
