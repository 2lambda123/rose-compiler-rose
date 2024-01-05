/** CIL AssemblyRef tables. */
class SgAsmCilAssemblyRefTable: public SgAsmCilMetadata {
public:
    [[using Rosebud: rosetta, traverse, mutators(), large]]
    std::vector<SgAsmCilAssemblyRef*> elements;

public:
    using CilMetadataType = SgAsmCilAssemblyRef;
};
