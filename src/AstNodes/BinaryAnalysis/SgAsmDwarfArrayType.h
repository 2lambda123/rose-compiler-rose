class SgAsmDwarfArrayType: public SgAsmDwarfConstruct {
    [[using Rosebud: rosetta, traverse]]
    SgAsmDwarfConstructList* body = nullptr;

public:
    SgAsmDwarfConstructList* get_children() override;
};
