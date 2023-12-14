/** CIL AssemblyRefProcessor node (II.22.7). */
class SgAsmCilAssemblyRefProcessor: public SgAsmCilMetadata {
public:
    /** Property: Processor.
     *
     *  A 4-byte constant. */
    [[using Rosebud: rosetta]]
    uint32_t Processor = 0;

    /** Property: AssemblyRef.
     *
     *  An index into the AssemblyRef table. */
    [[using Rosebud: rosetta]]
    uint32_t AssemblyRef = 0;

public:
    void parse(std::vector<uint8_t>& buf, size_t& index, uint64_t uses4byteIndexing);

    const SgAsmCilMetadata* get_AssemblyRef_object() const;
};
