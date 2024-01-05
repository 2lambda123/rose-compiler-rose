/** CIL PropertyMap tables. */
class SgAsmCilPropertyMapTable: public SgAsmCilMetadata {
public:
    [[using Rosebud: rosetta, traverse, mutators(), large]]
    std::vector<SgAsmCilPropertyMap*> elements;

public:
    using CilMetadataType = SgAsmCilPropertyMap;
};
