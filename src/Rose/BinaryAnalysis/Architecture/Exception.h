#ifndef ROSE_BinaryAnalysis_Architecture_Exception_H
#define ROSE_BinaryAnalysis_Architecture_Exception_H
#include <featureTests.h>
#ifdef ROSE_ENABLE_BINARY_ANALYSIS

#include <Rose/Exception.h>

#include <string>

namespace Rose {
namespace BinaryAnalysis {
namespace Architecture {

/** Base class for exceptions thrown by architecture definitions. */
class Exception: public Rose::Exception {
public:
    /** Constructs exception with message. */
    Exception(const std::string &message);
    ~Exception() throw();
};

/** Error when an architecture is not found. */
class NotFound: public Exception {
public:
    /** Constructs exception with message. */
    NotFound(const std::string &message);
    ~NotFound() throw();
};

} // namespace
} // namespace
} // namespace

#endif
#endif
