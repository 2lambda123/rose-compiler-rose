/** CIL NestedClass tables. */
class SgAsmCilNestedClassTable: public SgAsmCilMetadata {
public:
    [[using Rosebud: rosetta, traverse, mutators(), large]]
    std::vector<SgAsmCilNestedClass*> elements;

public:
    using CilMetadataType = SgAsmCilNestedClass;
};
