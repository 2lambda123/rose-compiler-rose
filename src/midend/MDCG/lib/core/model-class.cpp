
#include "sage3basic.h"

#include "MDCG/Core/model-class.hpp"
#include "MDCG/Core/model-field.hpp"

#include <cassert>

namespace MDCG {

namespace Model {

field_t scope_t<e_model_class>::getField(const std::string & name) const {
  std::vector<field_t>::const_iterator it;
  for (it = field_children.begin(); it != field_children.end(); it++)
    if ((*it)->node->symbol->get_name().getString() == name) break;
  assert(it != field_children.end());
  return *it;
}

}

}

