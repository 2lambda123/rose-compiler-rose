
#ifndef Rose_CodeGen_API_h
#define Rose_CodeGen_API_h

#include "Rose/CodeGen/Driver.h"
#include "Rose/CodeGen/Object.h"

#include <vector>
#include <map>
#include <string>

namespace Rose { namespace CodeGen {

/**
 * \brief permits to gather types and symbols to extract an API from a set of headers.
 */
template <typename CRT>
class API {
  public:
    using a_namespace = symbol_t<Object::a_namespace> *;
    using a_class     = symbol_t<Object::a_class> *;
    using a_typedef   = symbol_t<Object::a_typedef> *;
    using a_variable  = symbol_t<Object::a_variable> *;
    using a_function  = symbol_t<Object::a_function> *;

    void load(Driver & driver);

    void add_nodes_for_namequal(Driver & driver, SgSourceFile * srcfile) const;

    void display(std::ostream & out) const;

  private: // Static fields provided by user code
    static std::string const name;

    // Static fields used to locate and open the header files
    static std::string const cache;
    static std::vector<std::string> const paths;
    static std::vector<std::string> const files;
    static std::vector<std::string> const flags;

    // Object maps used to load API elements into the CRT "sub-class" (introspection of sort)
    static std::map<std::string, a_namespace CRT::* > const namespaces;
    static std::map<std::string, a_class     CRT::* > const classes;
    static std::map<std::string, a_typedef   CRT::* > const typedefs;
    static std::map<std::string, a_variable  CRT::* > const variables;
    static std::map<std::string, a_function  CRT::* > const functions;

  private:
    std::set<size_t> file_ids;

    void build_command_line(std::vector<std::string> & cmdline) const;
    void load_headers(Driver & driver);
    void load_api(Driver & driver);

  template <typename API>
  friend struct SymbolScanner;
};

} }

#include "Rose/CodeGen/API.txx"

#endif /* Rose_CodeGen_API_h */

