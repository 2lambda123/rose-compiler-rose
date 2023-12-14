/** CIL MethodSpec tables. */
class SgAsmCilMethodSpecTable: public SgAsmCilMetadata {
public:
    [[using Rosebud: rosetta, traverse, mutators(), large]]
    std::vector<SgAsmCilMethodSpec*> elements;

public:
    using CilMetadataType = SgAsmCilMethodSpec;
};
