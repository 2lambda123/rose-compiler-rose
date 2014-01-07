
#ifndef __KLT_MFB_KLT_HPP__
#define __KLT_MFB_KLT_HPP__

#include "KLT/kernel.hpp"

#include "MFB/Sage/driver.hpp"
#include "MFB/Sage/function-declaration.hpp"

namespace MFB {

/*!
 * \addtogroup grp_klt_mfb
 * @{
*/

template <class Object>
class KLT {};

template <>
class Driver<KLT> {
  public:
    template <class Object>
    typename KLT<Object>::build_result_t build(typename KLT<Object>::object_desc_t const & object);
};

class KLT_Driver : public Driver<Sage>, public Driver<KLT> {
  public:
    KLT_Driver(SgProject * project_ = NULL);
};

template <class Annotation, class Language, class Runtime>
SgBasicBlock * createLocalDeclarations(
  Driver<Sage> & driver,
  SgFunctionDefinition * kernel_defn,
  typename ::KLT::Kernel<Annotation, Language, Runtime>::local_symbol_maps_t & local_symbol_maps,
  const typename ::KLT::Kernel<Annotation, Language, Runtime>::arguments_t & arguments,
  const std::map<
    typename ::KLT::LoopTrees<Annotation>::loop_t *,
    typename Runtime::loop_shape_t *
  > & loop_shapes
);

template <class Object>
typename KLT<Object>::build_result_t Driver<KLT>::build(typename KLT<Object>::object_desc_t const & object) {
  typename KLT<Object>::build_result_t result = 
    new typename ::KLT::Kernel<
      typename KLT<Object>::Annotation,
      typename KLT<Object>::Language,
      typename KLT<Object>::Runtime
    >::a_kernel();

  std::map<SgVariableSymbol *, SgVariableSymbol *> param_to_field_map;
  std::map<SgVariableSymbol *, SgVariableSymbol *> coef_to_field_map;
  std::map< ::KLT::Data<typename KLT<Object>::Annotation> *, SgVariableSymbol *> data_to_field_map;

  typename std::list<typename ::KLT::LoopTrees<typename KLT<Object>::Annotation>::loop_t *>::const_iterator it_nested_loop;
  typename std::list<typename ::KLT::LoopTrees<typename KLT<Object>::Annotation>::node_t *>::const_iterator it_body_branch;

  // * Function Declaration *

  std::ostringstream kernel_function_name;
  kernel_function_name << "kernel_" << object.kernel << "_" << object.id;
  result->kernel_name = kernel_function_name.str();

  SgFunctionParameterList * kernel_function_params =
    ::KLT::createParameterList<
      typename KLT<Object>::Annotation,
      typename KLT<Object>::Language,
      typename KLT<Object>::Runtime
    >(object.kernel);

  MFB::Sage<SgFunctionDeclaration>::object_desc_t kernel_function_desc(
    result->kernel_name,
    SageBuilder::buildVoidType(),
    kernel_function_params,
    NULL,
    object.file_id
  );

  MFB::Sage<SgFunctionDeclaration>::build_result_t kernel_result = 
    ((Driver<Sage> *)this)->build<SgFunctionDeclaration>(kernel_function_desc);

  {
    SgFunctionDeclaration * kernel_decl = kernel_result.symbol->get_declaration();
    assert(kernel_decl != NULL);

    SgFunctionDeclaration * first_kernel_decl = isSgFunctionDeclaration(kernel_decl->get_firstNondefiningDeclaration());
    assert(first_kernel_decl != NULL);
    first_kernel_decl->get_functionModifier().setOpenclKernel();

    SgFunctionDeclaration * defn_kernel_decl = isSgFunctionDeclaration(kernel_decl->get_definingDeclaration());
    assert(defn_kernel_decl != NULL);
    defn_kernel_decl->get_functionModifier().setOpenclKernel();
  }

  // * Local Declarations *

  typename ::KLT::Kernel<typename KLT<Object>::Annotation, typename KLT<Object>::Language, typename KLT<Object>::Runtime>::local_symbol_maps_t local_symbol_maps;

  SgBasicBlock * body = createLocalDeclarations<
    typename KLT<Object>::Annotation,
    typename KLT<Object>::Language,
    typename KLT<Object>::Runtime
  > (
    *(Driver<Sage> *)this,
    kernel_result.definition,
    local_symbol_maps,
    object.kernel->getArguments(),
    object.shapes
  );

  /// \todo add loops descriptor to 'result'

  unsigned loop_id = 0;
  const std::list<typename ::KLT::LoopTrees<typename KLT<Object>::Annotation>::node_t *> & kernel_roots = object.kernel->getRoots();
  typename std::list<typename ::KLT::LoopTrees<typename KLT<Object>::Annotation>::node_t *>::const_iterator it_root;
  for (it_root = kernel_roots.begin(); it_root != kernel_roots.end(); it_root++)
    ::KLT::generateKernelBody<typename KLT<Object>::Annotation, typename KLT<Object>::Language, typename KLT<Object>::Runtime>(
      *it_root, loop_id, result->loops, KLT<Object>::Runtime::default_execution_mode, object.shapes, local_symbol_maps, body
    );

  return result;
}

/** @} */

}

#endif /* __KLT__MFB_KLT_HPP__ */
