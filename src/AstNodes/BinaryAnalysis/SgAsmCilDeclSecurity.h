/** CIL DeclSecurity node (II.22.11). */
class SgAsmCilDeclSecurity: public SgAsmCilMetadata {
public:
    /** Property: Action.
     *
     *  A 2-byte value. */
    [[using Rosebud: rosetta]]
    uint16_t Action = 0;

    /** Property: Parent.
     *
     *  An index into the TypeDef, MethodDef, or Assembly table. */
    [[using Rosebud: rosetta]]
    uint32_t Parent = 0;

    /** Property: PermissionSet.
     *
     *  An index into the Blob heap. */
    [[using Rosebud: rosetta]]
    uint32_t PermissionSet = 0;

public:
    void parse(std::vector<uint8_t>& buf, size_t& index, uint64_t uses4byteIndexing);

    const SgAsmCilMetadata* get_Parent_object() const;
    const std::uint8_t* get_PermissionSet_blob() const;
};
