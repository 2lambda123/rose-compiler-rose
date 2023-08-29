/** CIL ManifestResource node (II.22.24). */
class SgAsmCilManifestResource: public SgAsmCilMetadata {

    /** Property: Offset.
     *
     *  A 4-byte constant. */
    [[using Rosebud: rosetta]]
    uint32_t Offset = 0;

    /** Property: Flags.
     *
     *  A 4-byte constant of type ManifestResourceAttributes. */
    [[using Rosebud: rosetta]]
    uint32_t Flags = 0;

    /** Property: Name.
     *
     *  An index into the String heap. */
    [[using Rosebud: rosetta]]
    uint32_t Name = 0;

    /** Property: Implementation.
     *
     *  An index into a File table, a AssemblyRef table, or null. */
    [[using Rosebud: rosetta]]
    uint32_t Implementation = 0;

public:
    void parse(std::vector<uint8_t>& buf, size_t& index, uint64_t uses4byteIndexing);

    const std::uint8_t* get_Name_string() const;
    const SgAsmCilMetadata* get_Implementation_object() const;
};
