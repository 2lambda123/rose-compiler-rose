#ifndef ROSE_Sarif_Rule_H
#define ROSE_Sarif_Rule_H
#include <Rose/Sarif/Node.h>

#include <boost/uuid/uuid.hpp>

namespace Rose {
namespace Sarif {

/** Information that describes a tool analysis result.
 *
 *  This object represents meta data about an analysis result. An analysis result may refer to a particular rule in order to impart
 *  additional meta information to the result.
 *
 *  In the SARIF standard, this object is called a "reportingDescriptor" object and is more general than how we use it here.  The
 *  standard says "A 'reportingDescriptor' object contains information that describes a 'reporting item' generated by a tool. A
 *  reporting item is either a result produced by the tool's analysis, or a notification of a condition encountered by the tool. We
 *  refer to this descriptive information as 'reporting item metadata'. When referring to the metadata that describes a result, we
 *  use the more specific term 'rule metadata'. Some of the properties of the reportingDescriptor object are interpreted differently
 *  depending on whether the object represents a rule or a notification. The description of each property will specify any such
 *  differences." */
class Rule: public Node {
public:
    /** Shared ownership pointer to a @ref Rule object.
     *
     *  @{ */
    using Ptr = RulePtr;
    using ConstPtr = RuleConstPtr;
    /** @} */

private:
    std::string id_;                                    // this should be short and stable over time; may be opaque
    std::string name_;                                  // optional, short, non-stable, human readable
    std::string description_;                           // optional multi-line description
    std::string helpUri_;                               // URI pointing to more detailed information
    boost::uuids::uuid uuid_;                           // generated at construction time

public:
    ~Rule();
protected:
    Rule(const std::string &id, const std::string &description);
public:
    /** Allocating constructor.
     *
     *  The @p id should be a unique, short, stable string that identifies the rule. If the @p id is an empty string then an ID will
     *  be generated by hashing the description. An analysis result will link to the rule by using this @p id. The @p description
     *  can be multi-line descriptive text. */
    static Ptr instance(const std::string &id, const std::string &description);

    /** Property: Identification string.
     *
     *  The identification string should be a short, stable string that identifies the rule. This string is set by the constructor
     *  and not modifiable thereafter. Identifiers may be opaque to the user. */
    const std::string& id() const;

    /** Property: Optional name.
     *
     *  A rule may contain a non-null name that is understandable to the user. If the name of a rule contains implementation details
     *  that change over time, a tool author might alter a rule's name while leaving the stable ID property unchanged. A rule name
     *  is suitable in contexts where a readable identifier is preferable and where the lack of stability is not a concern.
     *
     * @{ */
    const std::string& name() const;
    void name(const std::string&);
    /** @} */

    /** Property: Full description.
     *
     *  The full description is a multi-line, multi-paragraph string describing the rule in detail. It is initially set during
     *  construction but can be changed later.
     *
     * @{ */
    const std::string& description() const;
    void description(const std::string&);
    /** @} */

    /** Property: Help URI.
     *
     *  A URI pointing to the primary documentation for the reporting item. The documentation might include examples, author contact
     *  information, and links to additional information.
     *
     * @{ */
    const std::string& helpUri() const;
    void helpUri(const std::string&);
    /** @} */

    /** Property: Universally unique identifier.
     *
     *  The universally unique identification. This is assigned during construction, but can be changed later.
     *
     * @{ */
    boost::uuids::uuid uuid() const;
    void uuid(boost::uuids::uuid);
    /** @} */

public:
    void emitYaml(std::ostream&, const std::string&) override;
    std::string emissionPrefix() override;

private:
    void emitId(std::ostream&, const std::string&);
    void emitUuid(std::ostream&, const std::string&);
    void emitName(std::ostream&, const std::string&);
    void emitDescription(std::ostream&, const std::string&);
    void emitHelpUri(std::ostream&, const std::string&);
};

} // namespace
} // namespace
#endif
