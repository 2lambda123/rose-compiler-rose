/** Base class for string tables. */
[[Rosebud::abstract]]
class SgAsmGenericStrtab: public SgAsmExecutableFileFormat {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Local types
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    typedef std::vector<class SgAsmStringStorage*> referenced_t;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /** Property: Section storing this string table. */
    [[using Rosebud: rosetta]]
    SgAsmGenericSection* container = nullptr;

    /** Property: String storage list. */
    [[using Rosebud: rosetta]]
    SgAsmGenericStrtab::referenced_t storage_list;

    /** Property: Free space list.
     *
     *  This list stores space which is available for new strings.
     *
     *  @{ */
    [[using Rosebud: rosetta, accessors(), mutators()]]
    AddressIntervalSet freelist;

    const AddressIntervalSet& get_freelist() const;
    AddressIntervalSet& get_freelist();
    /** @} */

    /** Property: Space that should never be freed. */
    [[using Rosebud: rosetta]]
    SgAsmStringStorage* dont_free = nullptr;

    /** Property: Number of strings freed thus far. */
    [[using Rosebud: rosetta]]
    size_t num_freed = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    /** Constructs table inside file section. */
    explicit SgAsmGenericStrtab(SgAsmGenericSection *container);

    /** Parse a string table. */
    virtual SgAsmGenericStrtab* parse() {return this;}

    /** Print some debugging info. */
    virtual void dump(FILE*, const char *prefix, ssize_t idx) const;

    /** Constructs an SgAsmStoredString from an offset into this string table. */
    SgAsmStoredString *create_string(rose_addr_t offset, bool shared);

    /** Free area of this string table that corresponds to the string currently stored.
     *
     *  Use this in preference to the offset/size version of free() when possible. */
    void free(SgAsmStringStorage*);

    /** Add a range of bytes to the free list after subtracting areas that are referenced by other strings.
     *
     *  For instance, an ELF string table can have "main" and "domain" sharing storage. If we free the "domain" string then
     *  only "do" should be added to the free list. */
    void free(rose_addr_t offset, rose_addr_t size); /*mark part of table as free*/

    /** Free all strings so they will be reallocated later.
     *
     *  This is more efficient than calling @ref free for each storage object. If @p blow_away_holes is true then any areas
     *  that are unreferenced in the string table will be marked as referenced and added to the free list. */
    void free_all_strings(bool blow_away_holes=false);

    virtual void allocate_overlap(SgAsmStringStorage*) {};

    /** Allocates storage for strings that have been modified but not allocated.
     *
     *  First try to fit unallocated strings into free space. Any that are left will cause the string table to be
     *  extended. Returns true if the reallocation would potentially affect some other section. If @p shrink is true then
     *  release address space that's no longer needed at the end of the table. */
    bool reallocate(bool shrink);


    //These should be pure virtual but ROSETTA apparently doesn't support that (RPM 2008-10-03)
    virtual SgAsmStringStorage *create_storage(rose_addr_t /*offset*/, bool /*shared*/) {abort(); return NULL;}
    virtual rose_addr_t get_storage_size(const SgAsmStringStorage*) {abort(); return 0;}
    virtual void rebind(SgAsmStringStorage*, rose_addr_t) {abort();}
};
