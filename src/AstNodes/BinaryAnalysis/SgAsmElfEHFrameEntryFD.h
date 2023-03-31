/** ELF error handling frame entry frame description entry. */
class SgAsmElfEHFrameEntryFD: public SgAsmExecutableFileFormat {
    /** Property: Beginning relative virtual address.
     *
     *  See official ELF specification. */
    [[using Rosebud: rosetta, large]]
    rose_rva_t begin_rva = 0;

    /** Property: Size in bytes.
     *
     *  See official ELF specification. */
    [[using Rosebud: rosetta]]
    rose_addr_t size = 0;

    /** Property: Augmentation data.
     *
     *  See official ELF specification. */
    [[using Rosebud: rosetta, large]]
    SgUnsignedCharList augmentation_data;

    /** Property: Instructions.
     *
     *  See official ELF specification. */
    [[using Rosebud: rosetta, large]]
    SgUnsignedCharList instructions;

public:
    /** Non-parsing constructor */
    explicit SgAsmElfEHFrameEntryFD(SgAsmElfEHFrameEntryCI*);

    /** Print some debugging info */
    virtual void dump(FILE*, const char *prefix, ssize_t idx) const;

    /** Unparse to string.
     *
     *  Unparses the frame description entry (FDE) into a string but do not include the leading length field(s) or the CIE
     *  back pointer. */
    std::string unparse(const SgAsmElfEHFrameSection*, SgAsmElfEHFrameEntryCI*) const;
};
