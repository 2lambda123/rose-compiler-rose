/** RVA/size pair. */
class SgAsmPERVASizePair: public SgAsmExecutableFileFormat {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Local types
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
#ifdef _MSC_VER
# pragma pack (1)
#endif
    /** File format for an RVA/Size pair.
     *
     *  Such pairs are considered to be part of the PE file header.  All fields are little endian. */
    struct RVASizePair_disk {
        uint32_t    e_rva;
        uint32_t    e_size;
    }
#if !defined(SWIG) && !defined(_MSC_VER)
    __attribute__((packed))
#endif
    ;
#ifdef _MSC_VER
# pragma pack ()
#endif

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /** Property: RVA.
     *
     *  See PE specification. */
    [[using Rosebud: rosetta, large]]
    rose_rva_t e_rva = 0;

    /** Property: Size.
     *
     *  See PE specification. */
    [[using Rosebud: rosetta]]
    rose_addr_t e_size = 0;

    /** Property: Section.
     *
     *  See PE specification. */
    [[using Rosebud: rosetta, accessors(), mutators()]]
    SgAsmGenericSection* section = nullptr;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    SgAsmPERVASizePair(SgAsmPERVASizePairList *parent, const SgAsmPERVASizePair::RVASizePair_disk*);
    SgAsmPERVASizePair(SgAsmPERVASizePairList *parent, rose_addr_t rva, rose_addr_t size);

    /** Sets or removes the section associated with an RVA/size pair.
     *
     *  Setting or removing the section also updates the RVA and size according to the preferred mapping address and mapped
     *  size of the section. */
    void set_section(SgAsmGenericSection *section);

    /** Returns the section associated with an RVA/size pair.
     *
     *  This is the same as the ROSETTA-generated accessor, but we need a custom version of set_section(). */
    SgAsmGenericSection *get_section() const;

    void *encode(SgAsmPERVASizePair::RVASizePair_disk *disk) const;
};
