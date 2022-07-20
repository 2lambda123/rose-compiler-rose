#ifndef ROSE_BinaryAnalysis_ConcreteLocation_H
#define ROSE_BinaryAnalysis_ConcreteLocation_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS

#include <Rose/BinaryAnalysis/RegisterDescriptor.h>
#include <Rose/BinaryAnalysis/Registers.h>
#include <Rose/Location.h>

#include <boost/serialization/access.hpp>
#include <ostream>
#include <Sawyer/Optional.h>
#include <string>

namespace Rose {
namespace BinaryAnalysis {

/** Concrete location of data.
 *
 *  A concrete location is a machine register, a concrete memory address, or a memory address calculated
 *  from a register's current value and a signed byte offset.
 *
 *  Concrete locations are immutable objects.
 *
 *  See also, @ref AbstractLocation. */
class ConcreteLocation: public Location {
public:
    /** Type of location. */
    enum Type {
        NO_LOCATION,                                    /**< Used by default-constructed locations. */
        REGISTER,                                       /**< Parameter is in a register. */
        RELATIVE,                                       /**< Parameter in memory relative to a register. E.g., stack. */
        ABSOLUTE                                        /**< Parameter is at a fixed memory address. */
    };

private:
    RegisterDescriptor reg_;
    Sawyer::Optional<uint64_t> va_;
    const RegisterDictionary *regdict_ = nullptr;

#ifdef ROSE_HAVE_BOOST_SERIALIZATION_LIB
private:
    friend class boost::serialization::access;

    template<class S>
    void serialize(S &s, const unsigned /*version*/) {
        s & BOOST_SERIALIZATION_NVP(reg_);
        s & BOOST_SERIALIZATION_NVP(va_);
        s & BOOST_SERIALIZATION_NVP(regdict_);
    }
#endif

public:
    /** Default constructor.
     *
     * Constructs a concrete location that does not refer to any location. The @ref isEmpty method return true for such
     * objects. */
    ConcreteLocation();
    virtual ~ConcreteLocation();

    /** Copy constructor. */
    ConcreteLocation(const ConcreteLocation&);
    ConcreteLocation& operator=(const ConcreteLocation&);

    /** Register location.
     *
     *  Construct a concrete location that refers to a register.  The optional register dictionary can be associated with the
     *  location and is only used when printing the location.
     *
     *  FIXME[Robb Matzke 2022-07-15]: The second argument is temporary and unused. It's only purpose is to disambiguate the
     *  call to ConcreteLocation(RegisterDescriptor,int64_t) without the user having to add int64_t casts at all such calls
     *  when the offset is zero. Doing it this way will be easier to change in the future when register dictionaries are
     *  changed to use smart pointers since the compiler will be able to help us. */
    explicit ConcreteLocation(RegisterDescriptor,
                              const Sawyer::Nothing& = Sawyer::Nothing(), // delete this when regdict uses smart pointers
                              const RegisterDictionary *regdict = nullptr);

    /** Address location.
     *
     *  Construct a concrete location that refers to an address in memory. */
    explicit ConcreteLocation(rose_addr_t);

    /** Register and offset location.
     *
     *  Construct a concrete location that refers to an address in memory calculated by adding a register's value and a signed
     *  byte offset. */
    ConcreteLocation(RegisterDescriptor, int64_t offset);

    /** Parse a concrete location from a string. */
    static ConcreteLocation parse(const std::string&);

    // Inherited methods
    virtual bool isValid() const override;
    virtual std::string toString() const override;
    virtual void print(std::ostream&) const override;
    virtual std::string printableName() const override;
    virtual bool isEqual(const Location&) const override;
    virtual bool operator<(const Location&) const override;
    virtual bool operator<=(const Location&) const override;
    virtual bool operator>(const Location&) const override;
    virtual bool operator>=(const Location&) const override;

    /** Print using the specified register dictionary.
     *
     *  Concrete locations have an optional internal register dictionary pointer that's usually used for printing, but this
     *  method provides a way to use some other register dictionary. */
    void print(std::ostream&, const RegisterDictionary*) const;

    /** Compare two concrete locations.
     *
     *  Returns negative if this location is less than the @p other, positive if this location is greater than the @p other, or
     *  zero if this and the @p other location are equal. */
    int compare(const ConcreteLocation&) const;

    /** Type of location. */
    Type type() const;

    /** Property: Register dictionary.
     *
     *  This is the optional register dictionary associated with this location and used when printing the location.
     *
     * @{ */
    const RegisterDictionary* registerDictionary() const;
    void registerDictionary(const RegisterDictionary*);
    /** @} */

    /** Register part of the location.
     *
     *  Returns the register part of the location. This returns a valid register descriptor if the location is either a register
     *  or an indirect (register plus offset) memory address. Otherwise it returns the empty register descriptor. */
    RegisterDescriptor reg() const;

    /** Address part of the location.
     *
     *  Returns the address of the location if the location is a simple memory address. Otherwise, if the address is formed
     *  from a base register and an offset, or if the location is a register, then zero is returned. */
    rose_addr_t address() const;

    /** Offset part of the location.
     *
     *  Returns the signed offset when the location is a memory address formed from a register base value and an
     *  offset. Otherwise it returns zero. */
    int64_t offset() const;
};

} // namespace
} // namespace

#endif
#endif
