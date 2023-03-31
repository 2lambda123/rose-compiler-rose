/** Represents static data in an executable.
 *
 *  For now, we don't associate any type with the data because ROSE's data type infrastructure (source or binary) is not
 *  capable of representing the information we need: multiple interpretations of overlapping parts of memory (i.e., two or
 *  more types for the same bytes); arbitrary offsets and padding in structured types; size-specific integers and
 *  floating-point types; regions of unknown type; ease of improving type information by filling in more details as the
 *  type is discovered; etc. */
class SgAsmStaticData: public SgAsmStatement {
    /** Property: Raw bytes.
     *
     *  These are the raw memory bytes of static data that appear in the binary specimen. Type information is painted onto
     *  these bytes. */
    [[using Rosebud: rosetta]]
    SgUnsignedCharList raw_bytes;

public:
    /** Property: Size of static data in bytes.
     *
     *  This returns the number of raw data bytes rather than the size of any data type painted onto those bytes. */
    size_t get_size() const { return p_raw_bytes.size(); }
};
