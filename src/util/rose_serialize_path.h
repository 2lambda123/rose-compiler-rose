#ifndef ROSE_serialize_path_H
#define ROSE_serialize_path_H
#include <featureTests.h>

#include <boost/filesystem/path.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Boost
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cereal
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ROSE_HAVE_CEREAL

namespace cereal {

template<class Archive>
void
CEREAL_SAVE_FUNCTION_NAME(Archive &archive, const boost::filesystem::path &x) {
    std::string s = x.string();
    archive(cereal::make_nvp("path", s));
}

template<class Archive>
void
CEREAL_LOAD_FUNCTION_NAME(Archive &archive, boost::filesystem::path &x) {
    std::string s;
    archive(cereal::make_nvp("path", s));
    x = s;
}

} // namespace

#endif
#endif