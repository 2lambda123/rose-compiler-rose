#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define PTR_SIZE 100
#define PTR2_SIZE 10
#define PTR3_SIZE 10
#define OUT_OF_BOUNDS_EXCESS 1
#define LINKED_LIST_SIZE 10
#define ARRAY_SIZE 10
//#define USE_NEW
#if 1

struct User 
{
  float *user_ptr1;
}
;

class Base 
{
  private: unsigned int *ptr1;
  unsigned int *ptr2;
  unsigned int var1;
  char var2;
  float var3;
  float *ptr3;
  unsigned int *ptr4;
  struct User *str_ptr1;
  

  public: virtual inline void print()
{
    int *print_ptr1;
    printf("This is base class\n");
  }
  

  virtual inline void set_var1(unsigned int val)
{
    (this) -> var1 = val;
  }
  

  inline unsigned int get_var1()
{
    return (this) -> var1;
  }
}
;

class Derived1 : public Base
{
  private: unsigned int *der1_ptr1;
  float *der1_ptr2;
  

  public: virtual inline void print()
{
    int *print_ptr1;
    printf("This is Derived1 class\n");
  }
}
;

struct __Pb__v__Pe___Type 
{
  void *ptr;
  unsigned long long addr;
}
;
static struct __Pb__v__Pe___Type __Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(unsigned long );

struct __Pb__Base__Pe___Type 
{
  class Base *ptr;
  unsigned long long addr;
}
;
static struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type );
static struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(struct __Pb__Base__Pe___Type *,struct __Pb__Base__Pe___Type );
static void v_Ret_create_entry_UL_Arg_UL_Arg(unsigned long long ,unsigned long long );
static struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(class Base *,unsigned long long );
static struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Ret_Add___Pb__Base__Pe___Type_Arg_Ui_Arg(struct __Pb__Base__Pe___Type ,unsigned int );

struct __Pb__Ui__Pe___Type 
{
  unsigned int *ptr;
  unsigned long long addr;
}
;
static struct __Pb__Ui__Pe___Type __Pb__Ui__Pe___Type_Ret_create_struct___Pb__Ui__Pe___Arg_UL_Arg(unsigned int *,unsigned long long );
static struct __Pb__Ui__Pe___Type __Pb__Ui__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type );
static struct __Pb__Ui__Pe___Type __Pb__Ui__Pe___Type_Ret_Assign___Pb____Pb__Ui__Pe___Type__Pe___Arg___Pb__Ui__Pe___Type_Arg(struct __Pb__Ui__Pe___Type *,struct __Pb__Ui__Pe___Type );

struct __Pb__f__Pe___Type 
{
  float *ptr;
  unsigned long long addr;
}
;
static struct __Pb__f__Pe___Type __Pb__f__Pe___Type_Ret_create_struct___Pb__f__Pe___Arg_UL_Arg(float *,unsigned long long );
static struct __Pb__Ui__Pe___Type __Pb__Ui__Pe___Type_Ret_Increment___Pb____Pb__Ui__Pe___Type__Pe___Arg(struct __Pb__Ui__Pe___Type *);
static struct __Pb__f__Pe___Type __Pb__f__Pe___Type_Ret_Cast___Pb__Ui__Pe___Type_Arg(struct __Pb__Ui__Pe___Type );
static struct __Pb__f__Pe___Type __Pb__f__Pe___Type_Ret_Assign___Pb____Pb__f__Pe___Type__Pe___Arg___Pb__f__Pe___Type_Arg(struct __Pb__f__Pe___Type *,struct __Pb__f__Pe___Type );

class Derived2 : public Derived1
{
  private: unsigned int *der2_ptr1;
  float *der2_ptr2;
  class Base *der2_base_ptr1;
  class Derived1 der2_der1_obj;
  

  public: virtual inline void print()
{
    int *print_ptr1;
    printf("This is Derived2 class\n");
  }
  

  inline void set_base_ptr(unsigned int size)
{
        #ifdef USE_NEW
        #else
    class Base *temp;
    struct __Pb__Base__Pe___Type temp_str;
    ((temp_str.__Pb__Base__Pe___Type::ptr = temp , temp_str.__Pb__Base__Pe___Type::addr = ((unsigned long long )(&temp))) , ((__Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(&temp_str,__Pb__Base__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )(size * 64ULL))))) , temp = temp_str.__Pb__Base__Pe___Type::ptr)));
        #endif
    struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Var_ovl_0;
    (((__Pb__Base__Pe___Type_Var_ovl_0 = __Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg((this) -> der2_base_ptr1,((unsigned long long )(&(this) -> der2_base_ptr1))) , __Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(&__Pb__Base__Pe___Type_Var_ovl_0,__Pb__Base__Pe___Type_Ret_Add___Pb__Base__Pe___Type_Arg_Ui_Arg(__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(temp,((unsigned long long )(&temp))),(size - 1U)))) ,  *((class Base **)__Pb__Base__Pe___Type_Var_ovl_0.__Pb__Base__Pe___Type::addr) = __Pb__Base__Pe___Type_Var_ovl_0.__Pb__Base__Pe___Type::ptr) , __Pb__Base__Pe___Type_Var_ovl_0);
  }
  

  inline void set_two_pointers(unsigned int size)
{
    struct __Pb__Ui__Pe___Type __Pb__Ui__Pe___Type_Var_ovl_1;
    (((__Pb__Ui__Pe___Type_Var_ovl_1 = __Pb__Ui__Pe___Type_Ret_create_struct___Pb__Ui__Pe___Arg_UL_Arg((this) -> der2_ptr1,((unsigned long long )(&(this) -> der2_ptr1))) , __Pb__Ui__Pe___Type_Ret_Assign___Pb____Pb__Ui__Pe___Type__Pe___Arg___Pb__Ui__Pe___Type_Arg(&__Pb__Ui__Pe___Type_Var_ovl_1,__Pb__Ui__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )(size * 4ULL)))))) ,  *((unsigned int **)__Pb__Ui__Pe___Type_Var_ovl_1.__Pb__Ui__Pe___Type::addr) = __Pb__Ui__Pe___Type_Var_ovl_1.__Pb__Ui__Pe___Type::ptr) , __Pb__Ui__Pe___Type_Var_ovl_1);
    struct __Pb__Ui__Pe___Type __Pb__Ui__Pe___Type_Var_ovl_2;
    struct __Pb__f__Pe___Type __Pb__f__Pe___Type_Var_ovl_3;
    (((__Pb__f__Pe___Type_Var_ovl_3 = __Pb__f__Pe___Type_Ret_create_struct___Pb__f__Pe___Arg_UL_Arg((this) -> der2_ptr2,((unsigned long long )(&(this) -> der2_ptr2))) , __Pb__f__Pe___Type_Ret_Assign___Pb____Pb__f__Pe___Type__Pe___Arg___Pb__f__Pe___Type_Arg(&__Pb__f__Pe___Type_Var_ovl_3,__Pb__f__Pe___Type_Ret_Cast___Pb__Ui__Pe___Type_Arg(((((__Pb__Ui__Pe___Type_Var_ovl_2 = __Pb__Ui__Pe___Type_Ret_create_struct___Pb__Ui__Pe___Arg_UL_Arg((this) -> der2_ptr1,((unsigned long long )(&(this) -> der2_ptr1))) , __Pb__Ui__Pe___Type_Ret_Increment___Pb____Pb__Ui__Pe___Type__Pe___Arg(&__Pb__Ui__Pe___Type_Var_ovl_2)) ,  *((unsigned int **)__Pb__Ui__Pe___Type_Var_ovl_2.__Pb__Ui__Pe___Type::addr) = __Pb__Ui__Pe___Type_Var_ovl_2.__Pb__Ui__Pe___Type::ptr) , __Pb__Ui__Pe___Type_Var_ovl_2))))) ,  *((float **)__Pb__f__Pe___Type_Var_ovl_3.__Pb__f__Pe___Type::addr) = __Pb__f__Pe___Type_Var_ovl_3.__Pb__f__Pe___Type::ptr) , __Pb__f__Pe___Type_Var_ovl_3);
    (this) ->  set_base_ptr ((size * 2U));
  }
}
;

struct node 
{
  class Base *base_ptr;
  unsigned int node_ctr;
  struct node *next;
  struct node *prev;
}
;
#endif
//#include "decls.h"

struct __Pb__i__Pe___Type 
{
  int *ptr;
  unsigned long long addr;
}
;

struct __Pb__Derived1__Pe___Type 
{
  class Derived1 *ptr;
  unsigned long long addr;
}
;

class Base fn2(struct __Pb__i__Pe___Type input1_str,struct __Pb__f__Pe___Type input2_str,struct __Pb__Derived1__Pe___Type input3_str,struct __Pb__Derived1__Pe___Type input4_str,class Base input5,struct __Pb__Base__Pe___Type input6_str)
{
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&input6_str.__Pb__Base__Pe___Type::ptr)),input6_str.__Pb__Base__Pe___Type::addr) , input6_str.__Pb__Base__Pe___Type::addr = ((unsigned long long )(&input6_str.__Pb__Base__Pe___Type::ptr)));
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&input4_str.__Pb__Derived1__Pe___Type::ptr)),input4_str.__Pb__Derived1__Pe___Type::addr) , input4_str.__Pb__Derived1__Pe___Type::addr = ((unsigned long long )(&input4_str.__Pb__Derived1__Pe___Type::ptr)));
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&input3_str.__Pb__Derived1__Pe___Type::ptr)),input3_str.__Pb__Derived1__Pe___Type::addr) , input3_str.__Pb__Derived1__Pe___Type::addr = ((unsigned long long )(&input3_str.__Pb__Derived1__Pe___Type::ptr)));
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&input2_str.__Pb__f__Pe___Type::ptr)),input2_str.__Pb__f__Pe___Type::addr) , input2_str.__Pb__f__Pe___Type::addr = ((unsigned long long )(&input2_str.__Pb__f__Pe___Type::ptr)));
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&input1_str.__Pb__i__Pe___Type::ptr)),input1_str.__Pb__i__Pe___Type::addr) , input1_str.__Pb__i__Pe___Type::addr = ((unsigned long long )(&input1_str.__Pb__i__Pe___Type::ptr)));
  return (input5);
}

struct __Pb__Derived2__Pe___Type 
{
  class Derived2 *ptr;
  unsigned long long addr;
}
;
static class Derived2 *__Pb__Derived2__Pe___Ret_Deref___Pb__Derived2__Pe___Type_Arg(struct __Pb__Derived2__Pe___Type );
static int *__Pb__i__Pe___Ret_Deref___Pb__i__Pe___Type_Arg(struct __Pb__i__Pe___Type );
static struct __Pb__Derived1__Pe___Type __Pb__Derived1__Pe___Type_Ret_Cast___Pb__Derived2__Pe___Type_Arg(struct __Pb__Derived2__Pe___Type );
static struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Ret_Cast___Pb__Derived1__Pe___Type_Arg(struct __Pb__Derived1__Pe___Type );

struct __Pb__Base__Pe___Type fn1(struct __Pb__i__Pe___Type input1_str,char input4,struct __Pb__f__Pe___Type input2_str,struct __Pb__Derived2__Pe___Type input3_str,class Base input5)
{
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&input3_str.__Pb__Derived2__Pe___Type::ptr)),input3_str.__Pb__Derived2__Pe___Type::addr) , input3_str.__Pb__Derived2__Pe___Type::addr = ((unsigned long long )(&input3_str.__Pb__Derived2__Pe___Type::ptr)));
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&input2_str.__Pb__f__Pe___Type::ptr)),input2_str.__Pb__f__Pe___Type::addr) , input2_str.__Pb__f__Pe___Type::addr = ((unsigned long long )(&input2_str.__Pb__f__Pe___Type::ptr)));
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&input1_str.__Pb__i__Pe___Type::ptr)),input1_str.__Pb__i__Pe___Type::addr) , input1_str.__Pb__i__Pe___Type::addr = ((unsigned long long )(&input1_str.__Pb__i__Pe___Type::ptr)));
  __Pb__Derived2__Pe___Ret_Deref___Pb__Derived2__Pe___Type_Arg(input3_str) ->  set_two_pointers (( *__Pb__i__Pe___Ret_Deref___Pb__i__Pe___Type_Arg(input1_str)));
  return __Pb__Base__Pe___Type_Ret_Cast___Pb__Derived1__Pe___Type_Arg(__Pb__Derived1__Pe___Type_Ret_Cast___Pb__Derived2__Pe___Type_Arg(input3_str));
}

struct __Pb__node__Pe___Type 
{
  struct node *ptr;
  unsigned long long addr;
}
;
static struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type );
static struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(struct __Pb__node__Pe___Type *,struct __Pb__node__Pe___Type );
static struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(struct node *,unsigned long long );
static struct node *__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(struct __Pb__node__Pe___Type );
static struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Ret_Cast_i_Arg(int );

struct __Pb__node__Pe___Type insert_node(struct __Pb__Base__Pe___Type ptr_str,struct __Pb__node__Pe___Type pos_str)
{
    #ifdef USE_NEW
    #else
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&pos_str.__Pb__node__Pe___Type::ptr)),pos_str.__Pb__node__Pe___Type::addr) , pos_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&pos_str.__Pb__node__Pe___Type::ptr)));
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&ptr_str.__Pb__Base__Pe___Type::ptr)),ptr_str.__Pb__Base__Pe___Type::addr) , ptr_str.__Pb__Base__Pe___Type::addr = ((unsigned long long )(&ptr_str.__Pb__Base__Pe___Type::ptr)));
  struct node *new_node;
  struct __Pb__node__Pe___Type new_node_str;
  ((new_node_str.__Pb__node__Pe___Type::ptr = new_node , new_node_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&new_node))) , ((__Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&new_node_str,__Pb__node__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )32UL)))) , new_node = new_node_str.__Pb__node__Pe___Type::ptr)));
    #endif
  struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Var_ovl_4;
  (((__Pb__Base__Pe___Type_Var_ovl_4 = __Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node)))) -> node::base_ptr,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node)))) -> node::base_ptr))) , __Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(&__Pb__Base__Pe___Type_Var_ovl_4,ptr_str)) ,  *((class Base **)__Pb__Base__Pe___Type_Var_ovl_4.__Pb__Base__Pe___Type::addr) = __Pb__Base__Pe___Type_Var_ovl_4.__Pb__Base__Pe___Type::ptr) , __Pb__Base__Pe___Type_Var_ovl_4);
  __Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node)))) -> node::node_ctr = ++__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(pos_str) -> node::node_ctr;
  struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_5;
  (((__Pb__node__Pe___Type_Var_ovl_5 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node)))) -> node::next,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node)))) -> node::next))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_5,__Pb__node__Pe___Type_Ret_Cast_i_Arg(0))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_5.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_5.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_5);
  struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_6;
  (((__Pb__node__Pe___Type_Var_ovl_6 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node)))) -> node::prev,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node)))) -> node::prev))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_6,pos_str)) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_6.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_6.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_6);
  struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_7;
  (((__Pb__node__Pe___Type_Var_ovl_7 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(pos_str) -> node::next,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(pos_str) -> node::next))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_7,__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node))))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_7.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_7.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_7);
  return __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node)));
}
static struct __Pb__v__Pe___Type __Pb__v__Pe___Type_Ret_Cast___Pb__Base__Pe___Type_Arg(struct __Pb__Base__Pe___Type );
static void v_Ret_free_overload___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type );
static struct __Pb__v__Pe___Type __Pb__v__Pe___Type_Ret_Cast___Pb__node__Pe___Type_Arg(struct __Pb__node__Pe___Type );

struct __Pb__node__Pe___Type delete_node(struct __Pb__node__Pe___Type pos_str)
{
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&pos_str.__Pb__node__Pe___Type::ptr)),pos_str.__Pb__node__Pe___Type::addr) , pos_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&pos_str.__Pb__node__Pe___Type::ptr)));
  struct node *prev;
  struct __Pb__node__Pe___Type prev_str;
  ((prev_str.__Pb__node__Pe___Type::ptr = prev , prev_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&prev))) , ((__Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&prev_str,__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(pos_str) -> node::prev,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(pos_str) -> node::prev)))) , prev = prev_str.__Pb__node__Pe___Type::ptr)));
  struct node *next;
  struct __Pb__node__Pe___Type next_str;
  ((next_str.__Pb__node__Pe___Type::ptr = next , next_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&next))) , ((__Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&next_str,__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(pos_str) -> node::next,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(pos_str) -> node::next)))) , next = next_str.__Pb__node__Pe___Type::ptr)));
  struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_8;
  (((__Pb__node__Pe___Type_Var_ovl_8 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev,((unsigned long long )(&prev)))) -> node::next,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev,((unsigned long long )(&prev)))) -> node::next))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_8,__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(next,((unsigned long long )(&next))))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_8.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_8.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_8);
  struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_9;
  (((__Pb__node__Pe___Type_Var_ovl_9 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(next,((unsigned long long )(&next)))) -> node::prev,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(next,((unsigned long long )(&next)))) -> node::prev))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_9,__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev,((unsigned long long )(&prev))))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_9.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_9.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_9);
  v_Ret_free_overload___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_Cast___Pb__Base__Pe___Type_Arg(__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(pos_str) -> node::base_ptr,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(pos_str) -> node::base_ptr)))));
  v_Ret_free_overload___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_Cast___Pb__node__Pe___Type_Arg(pos_str));
  return __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev,((unsigned long long )(&prev)));
}
#if 1
static struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Ret_Add___Pb__node__Pe___Type_Arg_Ui_Arg(struct __Pb__node__Pe___Type ,unsigned int );
static class Base *__Pb__Base__Pe___Ret_Deref___Pb__Base__Pe___Type_Arg(struct __Pb__Base__Pe___Type );

void fn3(struct __Pb__node__Pe___Type array_str)
{
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&array_str.__Pb__node__Pe___Type::ptr)),array_str.__Pb__node__Pe___Type::addr) , array_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&array_str.__Pb__node__Pe___Type::ptr)));
  for (unsigned int index = 0U; index < 10U; index++) {
    struct node *element;
    struct __Pb__node__Pe___Type element_str;
    ((element_str.__Pb__node__Pe___Type::ptr = element , element_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&element))) , ((__Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&element_str,__Pb__node__Pe___Type_Ret_Add___Pb__node__Pe___Type_Arg_Ui_Arg(array_str,index)) , element = element_str.__Pb__node__Pe___Type::ptr)));
    printf("%d\n",( *__Pb__Base__Pe___Ret_Deref___Pb__Base__Pe___Type_Arg(__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(element,((unsigned long long )(&element)))) -> node::base_ptr,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(element,((unsigned long long )(&element)))) -> node::base_ptr))))). get_var1 ());
  }
}
#endif
static int i_Ret_NotEqual___Pb__node__Pe___Type_Arg___Pb__node__Pe___Type_Arg(struct __Pb__node__Pe___Type ,struct __Pb__node__Pe___Type );

void fn4_ext(struct __Pb__node__Pe___Type head_str)
{
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&head_str.__Pb__node__Pe___Type::ptr)),head_str.__Pb__node__Pe___Type::addr) , head_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&head_str.__Pb__node__Pe___Type::ptr)));
  printf("fn4_ext: Printing linked list\n");
  unsigned int index = 0U;
  struct node *start;
  struct __Pb__node__Pe___Type start_str;
  ((start_str.__Pb__node__Pe___Type::ptr = start , start_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&start))) , ((__Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&start_str,head_str) , start = start_str.__Pb__node__Pe___Type::ptr)));
  while(i_Ret_NotEqual___Pb__node__Pe___Type_Arg___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(start,((unsigned long long )(&start))),__Pb__node__Pe___Type_Ret_Cast_i_Arg(0))){
    printf("%d: %d\n",++index,__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(start,((unsigned long long )(&start)))) -> node::node_ctr);
    struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_10;
    (((__Pb__node__Pe___Type_Var_ovl_10 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(start,((unsigned long long )(&start))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_10,__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(start,((unsigned long long )(&start)))) -> node::next,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(start,((unsigned long long )(&start)))) -> node::next))))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_10.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_10.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_10);
  };
  printf("Done with linked list\n");
}
#if 1
static struct node *__Pb__node__Pe___Ret_PntrArrRef___Pb__node__Pe___Type_Arg_Ui_Arg(struct __Pb__node__Pe___Type ,unsigned int );

void fn3_ext(struct __Pb__node__Pe___Type node_array_str)
{
  (v_Ret_create_entry_UL_Arg_UL_Arg(((unsigned long long )(&node_array_str.__Pb__node__Pe___Type::ptr)),node_array_str.__Pb__node__Pe___Type::addr) , node_array_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&node_array_str.__Pb__node__Pe___Type::ptr)));
  printf("fn3_ext: Printing array\n");
  for (unsigned int index = 0U; index < 10U; index++) {
    printf("%d:%d\n",index,( *__Pb__Base__Pe___Ret_Deref___Pb__Base__Pe___Type_Arg(__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(( *__Pb__node__Pe___Ret_PntrArrRef___Pb__node__Pe___Type_Arg_Ui_Arg(node_array_str,index)).node::base_ptr,((unsigned long long )(&( *__Pb__node__Pe___Ret_PntrArrRef___Pb__node__Pe___Type_Arg_Ui_Arg(node_array_str,index)).node::base_ptr))))). get_var1 ());
  }
  printf("Done with array\n");
}
#endif
static struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type );
static struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Ret_Assign___Pb____Pb__i__Pe___Type__Pe___Arg___Pb__i__Pe___Type_Arg(struct __Pb__i__Pe___Type *,struct __Pb__i__Pe___Type );
static struct __Pb__Derived1__Pe___Type __Pb__Derived1__Pe___Type_Ret_AddressOf_UL_Arg_Ui_Arg(unsigned long long ,unsigned int );
static void v_Ret_create_entry_UL_Arg_UL_Arg_Ul_Arg(unsigned long long ,unsigned long long ,unsigned long );
static struct __Pb__Derived1__Pe___Type __Pb__Derived1__Pe___Type_Ret_Cast___Pb__Base__Pe___Type_Arg(struct __Pb__Base__Pe___Type );
static class Derived1 *__Pb__Derived1__Pe___Ret_Deref___Pb__Derived1__Pe___Type_Arg(struct __Pb__Derived1__Pe___Type );
static struct __Pb__Derived2__Pe___Type __Pb__Derived2__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type );
static struct __Pb__Derived2__Pe___Type __Pb__Derived2__Pe___Type_Ret_Assign___Pb____Pb__Derived2__Pe___Type__Pe___Arg___Pb__Derived2__Pe___Type_Arg(struct __Pb__Derived2__Pe___Type *,struct __Pb__Derived2__Pe___Type );
static struct __Pb__Derived2__Pe___Type __Pb__Derived2__Pe___Type_Ret_create_struct___Pb__Derived2__Pe___Arg_UL_Arg(class Derived2 *,unsigned long long );
static struct __Pb__Derived2__Pe___Type __Pb__Derived2__Pe___Type_Ret_Cast___Pb__Base__Pe___Type_Arg(struct __Pb__Base__Pe___Type );
static struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(int *,unsigned long long );
static struct __Pb__f__Pe___Type __Pb__f__Pe___Type_Ret_Cast___Pb__i__Pe___Type_Arg(struct __Pb__i__Pe___Type );
static struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Ret_Increment___Pb____Pb__i__Pe___Type__Pe___Arg(struct __Pb__i__Pe___Type *);

int main()
{
  printf("begin... \n");
  int *ptr;
  struct __Pb__i__Pe___Type ptr_str;
  ((ptr_str.__Pb__i__Pe___Type::ptr = ptr , ptr_str.__Pb__i__Pe___Type::addr = ((unsigned long long )(&ptr))) , ((__Pb__i__Pe___Type_Ret_Assign___Pb____Pb__i__Pe___Type__Pe___Arg___Pb__i__Pe___Type_Arg(&ptr_str,__Pb__i__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )400UL)))) , ptr = ptr_str.__Pb__i__Pe___Type::ptr)));
  int *ptr2;
  struct __Pb__i__Pe___Type ptr2_str;
  ((ptr2_str.__Pb__i__Pe___Type::ptr = ptr2 , ptr2_str.__Pb__i__Pe___Type::addr = ((unsigned long long )(&ptr2))) , ((__Pb__i__Pe___Type_Ret_Assign___Pb____Pb__i__Pe___Type__Pe___Arg___Pb__i__Pe___Type_Arg(&ptr2_str,__Pb__i__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )40UL)))) , ptr2 = ptr2_str.__Pb__i__Pe___Type::ptr)));
  printf("ptr and ptr2 malloc\'ed\n");
  class Base base_obj;
    #ifdef USE_NEW
    #else
  class Base *base_ptr;
  struct __Pb__Base__Pe___Type base_ptr_str;
  ((base_ptr_str.__Pb__Base__Pe___Type::ptr = base_ptr , base_ptr_str.__Pb__Base__Pe___Type::addr = ((unsigned long long )(&base_ptr))) , ((__Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(&base_ptr_str,__Pb__Base__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )64UL)))) , base_ptr = base_ptr_str.__Pb__Base__Pe___Type::ptr)));
    #endif
  printf("base_obj and ptr created.. \n");
  __Pb__Base__Pe___Ret_Deref___Pb__Base__Pe___Type_Arg(__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(base_ptr,((unsigned long long )(&base_ptr)))) ->  print ();
  printf("base_ptr print done\n");
  class Base *base_ptr2;
  struct __Pb__Base__Pe___Type base_ptr2_str;
  ((base_ptr2_str.__Pb__Base__Pe___Type::ptr = base_ptr2 , base_ptr2_str.__Pb__Base__Pe___Type::addr = ((unsigned long long )(&base_ptr2))) , ((__Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(&base_ptr2_str,__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(base_ptr,((unsigned long long )(&base_ptr)))) , base_ptr2 = base_ptr2_str.__Pb__Base__Pe___Type::ptr)));
  printf("base_ptr2 created\n");
  __Pb__Base__Pe___Ret_Deref___Pb__Base__Pe___Type_Arg(__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(base_ptr,((unsigned long long )(&base_ptr)))) ->  print ();
  printf("base_ptr print 2 done\n");
  class Derived1 der1_obj;
  struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Var_ovl_11;
  (((__Pb__Base__Pe___Type_Var_ovl_11 = __Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(base_ptr,((unsigned long long )(&base_ptr))) , __Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(&__Pb__Base__Pe___Type_Var_ovl_11,__Pb__Base__Pe___Type_Ret_Cast___Pb__Derived1__Pe___Type_Arg(__Pb__Derived1__Pe___Type_Ret_AddressOf_UL_Arg_Ui_Arg(((unsigned long long )(&der1_obj)),sizeof(der1_obj))))) ,  *((class Base **)__Pb__Base__Pe___Type_Var_ovl_11.__Pb__Base__Pe___Type::addr) = __Pb__Base__Pe___Type_Var_ovl_11.__Pb__Base__Pe___Type::ptr) , __Pb__Base__Pe___Type_Var_ovl_11);
  ( *__Pb__Derived1__Pe___Ret_Deref___Pb__Derived1__Pe___Type_Arg(__Pb__Derived1__Pe___Type_Ret_Cast___Pb__Base__Pe___Type_Arg(__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(base_ptr,((unsigned long long )(&base_ptr)))))). print ();
    #ifdef USE_NEW
    #else
  class Derived2 *der2_ptr;
  struct __Pb__Derived2__Pe___Type der2_ptr_str;
  ((der2_ptr_str.__Pb__Derived2__Pe___Type::ptr = der2_ptr , der2_ptr_str.__Pb__Derived2__Pe___Type::addr = ((unsigned long long )(&der2_ptr))) , ((__Pb__Derived2__Pe___Type_Ret_Assign___Pb____Pb__Derived2__Pe___Type__Pe___Arg___Pb__Derived2__Pe___Type_Arg(&der2_ptr_str,__Pb__Derived2__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )184UL)))) , der2_ptr = der2_ptr_str.__Pb__Derived2__Pe___Type::ptr)));
    #endif
  struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Var_ovl_12;
  (((__Pb__Base__Pe___Type_Var_ovl_12 = __Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(base_ptr,((unsigned long long )(&base_ptr))) , __Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(&__Pb__Base__Pe___Type_Var_ovl_12,__Pb__Base__Pe___Type_Ret_Cast___Pb__Derived1__Pe___Type_Arg(__Pb__Derived1__Pe___Type_Ret_Cast___Pb__Derived2__Pe___Type_Arg(__Pb__Derived2__Pe___Type_Ret_create_struct___Pb__Derived2__Pe___Arg_UL_Arg(der2_ptr,((unsigned long long )(&der2_ptr))))))) ,  *((class Base **)__Pb__Base__Pe___Type_Var_ovl_12.__Pb__Base__Pe___Type::addr) = __Pb__Base__Pe___Type_Var_ovl_12.__Pb__Base__Pe___Type::ptr) , __Pb__Base__Pe___Type_Var_ovl_12);
  ( *__Pb__Derived2__Pe___Ret_Deref___Pb__Derived2__Pe___Type_Arg(__Pb__Derived2__Pe___Type_Ret_Cast___Pb__Base__Pe___Type_Arg(__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(base_ptr,((unsigned long long )(&base_ptr)))))). print ();
  struct __Pb__Derived2__Pe___Type __Pb__Derived2__Pe___Type_Var_ovl_13;
  (((__Pb__Derived2__Pe___Type_Var_ovl_13 = __Pb__Derived2__Pe___Type_Ret_create_struct___Pb__Derived2__Pe___Arg_UL_Arg(der2_ptr,((unsigned long long )(&der2_ptr))) , __Pb__Derived2__Pe___Type_Ret_Assign___Pb____Pb__Derived2__Pe___Type__Pe___Arg___Pb__Derived2__Pe___Type_Arg(&__Pb__Derived2__Pe___Type_Var_ovl_13,__Pb__Derived2__Pe___Type_Ret_Cast___Pb__Base__Pe___Type_Arg(::fn1(__Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(ptr,((unsigned long long )(&ptr))),'a',__Pb__f__Pe___Type_Ret_Cast___Pb__i__Pe___Type_Arg(__Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(ptr2,((unsigned long long )(&ptr2)))),__Pb__Derived2__Pe___Type_Ret_create_struct___Pb__Derived2__Pe___Arg_UL_Arg(der2_ptr,((unsigned long long )(&der2_ptr))),(base_obj))))) ,  *((class Derived2 **)__Pb__Derived2__Pe___Type_Var_ovl_13.__Pb__Derived2__Pe___Type::addr) = __Pb__Derived2__Pe___Type_Var_ovl_13.__Pb__Derived2__Pe___Type::ptr) , __Pb__Derived2__Pe___Type_Var_ovl_13);
  int *start_ptr;
  struct __Pb__i__Pe___Type start_ptr_str;
  ((start_ptr_str.__Pb__i__Pe___Type::ptr = start_ptr , start_ptr_str.__Pb__i__Pe___Type::addr = ((unsigned long long )(&start_ptr))) , ((__Pb__i__Pe___Type_Ret_Assign___Pb____Pb__i__Pe___Type__Pe___Arg___Pb__i__Pe___Type_Arg(&start_ptr_str,__Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(ptr,((unsigned long long )(&ptr)))) , start_ptr = start_ptr_str.__Pb__i__Pe___Type::ptr)));
  int *start_ptr2;
  struct __Pb__i__Pe___Type start_ptr2_str;
  ((start_ptr2_str.__Pb__i__Pe___Type::ptr = start_ptr2 , start_ptr2_str.__Pb__i__Pe___Type::addr = ((unsigned long long )(&start_ptr2))) , ((__Pb__i__Pe___Type_Ret_Assign___Pb____Pb__i__Pe___Type__Pe___Arg___Pb__i__Pe___Type_Arg(&start_ptr2_str,__Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(ptr2,((unsigned long long )(&ptr2)))) , start_ptr2 = start_ptr2_str.__Pb__i__Pe___Type::ptr)));
// Crossing the boundary of ptr. The condition should
// be less than, not less than or equal to
// ptr[PTR_SIZE] is an out-of-bounds access
  for (int index = 0; index <= 101; index++) {
     *__Pb__i__Pe___Ret_Deref___Pb__i__Pe___Type_Arg(__Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(ptr,((unsigned long long )(&ptr)))) = index;
    struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Var_ovl_14;
    (((__Pb__i__Pe___Type_Var_ovl_14 = __Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(ptr,((unsigned long long )(&ptr))) , __Pb__i__Pe___Type_Ret_Increment___Pb____Pb__i__Pe___Type__Pe___Arg(&__Pb__i__Pe___Type_Var_ovl_14)) ,  *((int **)__Pb__i__Pe___Type_Var_ovl_14.__Pb__i__Pe___Type::addr) = __Pb__i__Pe___Type_Var_ovl_14.__Pb__i__Pe___Type::ptr) , __Pb__i__Pe___Type_Var_ovl_14);
  }
// Resetting ptr to start_ptr, so that it points to the beginning
// of the allocation
  struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Var_ovl_15;
  (((__Pb__i__Pe___Type_Var_ovl_15 = __Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(ptr,((unsigned long long )(&ptr))) , __Pb__i__Pe___Type_Ret_Assign___Pb____Pb__i__Pe___Type__Pe___Arg___Pb__i__Pe___Type_Arg(&__Pb__i__Pe___Type_Var_ovl_15,__Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(start_ptr,((unsigned long long )(&start_ptr))))) ,  *((int **)__Pb__i__Pe___Type_Var_ovl_15.__Pb__i__Pe___Type::addr) = __Pb__i__Pe___Type_Var_ovl_15.__Pb__i__Pe___Type::ptr) , __Pb__i__Pe___Type_Var_ovl_15);
// Printing what we wrote above
  for (int index = 0; index <= 101; index++) {
    printf("ptr[%d]=%d\n",index, *__Pb__i__Pe___Ret_Deref___Pb__i__Pe___Type_Arg(__Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(ptr,((unsigned long long )(&ptr)))));
    struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Var_ovl_16;
    (((__Pb__i__Pe___Type_Var_ovl_16 = __Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(ptr,((unsigned long long )(&ptr))) , __Pb__i__Pe___Type_Ret_Increment___Pb____Pb__i__Pe___Type__Pe___Arg(&__Pb__i__Pe___Type_Var_ovl_16)) ,  *((int **)__Pb__i__Pe___Type_Var_ovl_16.__Pb__i__Pe___Type::addr) = __Pb__i__Pe___Type_Var_ovl_16.__Pb__i__Pe___Type::ptr) , __Pb__i__Pe___Type_Var_ovl_16);
  }
  printf("Linked list\n");
  printf("Head\n");
// Linked list traversal
//struct node* head = new struct node;
  struct node *head;
  struct __Pb__node__Pe___Type head_str;
  ((head_str.__Pb__node__Pe___Type::ptr = head , head_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&head))) , ((__Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&head_str,__Pb__node__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )32UL)))) , head = head_str.__Pb__node__Pe___Type::ptr)));
  struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Var_ovl_17;
  (((__Pb__Base__Pe___Type_Var_ovl_17 = __Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head)))) -> node::base_ptr,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head)))) -> node::base_ptr))) , __Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(&__Pb__Base__Pe___Type_Var_ovl_17,__Pb__Base__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )80UL))))) ,  *((class Base **)__Pb__Base__Pe___Type_Var_ovl_17.__Pb__Base__Pe___Type::addr) = __Pb__Base__Pe___Type_Var_ovl_17.__Pb__Base__Pe___Type::ptr) , __Pb__Base__Pe___Type_Var_ovl_17);
  __Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head)))) -> node::node_ctr = 0U;
  struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_18;
  (((__Pb__node__Pe___Type_Var_ovl_18 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head)))) -> node::next,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head)))) -> node::next))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_18,__Pb__node__Pe___Type_Ret_Cast_i_Arg(0))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_18.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_18.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_18);
  struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_19;
  (((__Pb__node__Pe___Type_Var_ovl_19 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head)))) -> node::prev,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head)))) -> node::prev))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_19,__Pb__node__Pe___Type_Ret_Cast_i_Arg(0))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_19.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_19.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_19);
  printf("Insert Node\n");
  struct node *new_node;
  struct __Pb__node__Pe___Type new_node_str;
  ((new_node_str.__Pb__node__Pe___Type::ptr = new_node , new_node_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&new_node))) , ((__Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&new_node_str,::insert_node(__Pb__Base__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )184UL))),__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head))))) , new_node = new_node_str.__Pb__node__Pe___Type::ptr)));
  struct node *prev_node;
  struct __Pb__node__Pe___Type prev_node_str;
  ((prev_node_str.__Pb__node__Pe___Type::ptr = prev_node , prev_node_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&prev_node))) , ((__Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&prev_node_str,__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node)))) , prev_node = prev_node_str.__Pb__node__Pe___Type::ptr)));
  printf("Insert Node Loop\n");
// Create a linked list of size LINKED_LIST_SIZE -- already has two nodes -- so total size
// would be LINKED_LIST_SIZE + 2
  for (unsigned int index = 0U; index < 10U; index++) {
    class Base *temp;
    struct __Pb__Base__Pe___Type temp_str;
    ((temp_str.__Pb__Base__Pe___Type::ptr = temp , temp_str.__Pb__Base__Pe___Type::addr = ((unsigned long long )(&temp))) , ((__Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(&temp_str,__Pb__Base__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )80UL)))) , temp = temp_str.__Pb__Base__Pe___Type::ptr)));
    printf("sizeof(temp): %u\n",64ULL);
    struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_20;
    (((__Pb__node__Pe___Type_Var_ovl_20 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_20,::insert_node(__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(temp,((unsigned long long )(&temp))),__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev_node,((unsigned long long )(&prev_node)))))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_20.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_20.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_20);
        #if 0
        #endif
    struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_21;
    (((__Pb__node__Pe___Type_Var_ovl_21 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev_node,((unsigned long long )(&prev_node))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_21,__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(new_node,((unsigned long long )(&new_node))))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_21.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_21.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_21);
  }
// prev_node now points to the last node
// lets delete from one before the last node
//struct node* to_delete = prev_node->prev;
  struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_22;
  (((__Pb__node__Pe___Type_Var_ovl_22 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev_node,((unsigned long long )(&prev_node))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_22,__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev_node,((unsigned long long )(&prev_node)))) -> node::prev,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev_node,((unsigned long long )(&prev_node)))) -> node::prev))))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_22.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_22.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_22);
  fn4_ext(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head))));
  printf("Delete Node Loop\n");
  for (unsigned int index = 0U; index < 10U; index++) {
        #if 0
        #endif
    struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Var_ovl_23;
    (((__Pb__node__Pe___Type_Var_ovl_23 = __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev_node,((unsigned long long )(&prev_node))) , __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&__Pb__node__Pe___Type_Var_ovl_23,::delete_node(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(prev_node,((unsigned long long )(&prev_node)))))) ,  *((struct node **)__Pb__node__Pe___Type_Var_ovl_23.__Pb__node__Pe___Type::addr) = __Pb__node__Pe___Type_Var_ovl_23.__Pb__node__Pe___Type::ptr) , __Pb__node__Pe___Type_Var_ovl_23);
  }
  printf("Asserting\n");
// Should be left with two nodes
// Verifying that
    #if 0
    #endif
  printf("Prints\n");
  printf("head: ctr: %d\n",__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head)))) -> node::node_ctr);
  printf("next: ctr: %d\n",( *__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head)))) -> node::next,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(head,((unsigned long long )(&head)))) -> node::next))))).node::node_ctr);
    #if 0
// Array ref
//base_index = (class Base*)malloc(sizeof(class Base));
    #endif
    #if 1
  struct node *node_array;
  struct __Pb__node__Pe___Type node_array_str;
  ((node_array_str.__Pb__node__Pe___Type::ptr = node_array , node_array_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&node_array))) , ((__Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&node_array_str,__Pb__node__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )80UL)))) , node_array = node_array_str.__Pb__node__Pe___Type::ptr)));
  printf("Setting node array\n");
  for (unsigned int index = 0U; index < 10U; index++) {
    struct node *element;
    struct __Pb__node__Pe___Type element_str;
    ((element_str.__Pb__node__Pe___Type::ptr = element , element_str.__Pb__node__Pe___Type::addr = ((unsigned long long )(&element))) , ((__Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(&element_str,__Pb__node__Pe___Type_Ret_Add___Pb__node__Pe___Type_Arg_Ui_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(node_array,((unsigned long long )(&node_array))),index)) , element = element_str.__Pb__node__Pe___Type::ptr)));
        #ifdef USE_NEW
        #else
    struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Var_ovl_24;
    (((__Pb__Base__Pe___Type_Var_ovl_24 = __Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(element,((unsigned long long )(&element)))) -> node::base_ptr,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(element,((unsigned long long )(&element)))) -> node::base_ptr))) , __Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(&__Pb__Base__Pe___Type_Var_ovl_24,__Pb__Base__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(__Pb__v__Pe___Type_Ret_malloc_overload_Ul_Arg(((unsigned long )64UL))))) ,  *((class Base **)__Pb__Base__Pe___Type_Var_ovl_24.__Pb__Base__Pe___Type::addr) = __Pb__Base__Pe___Type_Var_ovl_24.__Pb__Base__Pe___Type::ptr) , __Pb__Base__Pe___Type_Var_ovl_24);
        #endif
    ( *__Pb__Base__Pe___Ret_Deref___Pb__Base__Pe___Type_Arg(__Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(element,((unsigned long long )(&element)))) -> node::base_ptr,((unsigned long long )(&__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(element,((unsigned long long )(&element)))) -> node::base_ptr))))). set_var1 (index);
  }
  printf("Printing node array\n");
  fn3_ext(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(node_array,((unsigned long long )(&node_array))));
  fn3(__Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(node_array,((unsigned long long )(&node_array))));
    #endif
  return 1;
}

static struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type input1)
{
  struct __Pb__Base__Pe___Type output;
  output.__Pb__Base__Pe___Type::ptr = ((class Base *)input1.__Pb__v__Pe___Type::ptr);
  output.__Pb__Base__Pe___Type::addr = input1.__Pb__v__Pe___Type::addr;
  return output;
}

static struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Ret_Assign___Pb____Pb__Base__Pe___Type__Pe___Arg___Pb__Base__Pe___Type_Arg(struct __Pb__Base__Pe___Type *input1,struct __Pb__Base__Pe___Type input2)
{
  input1 -> __Pb__Base__Pe___Type::ptr = input2.__Pb__Base__Pe___Type::ptr;
  v_Ret_create_entry_UL_Arg_UL_Arg(input1 -> __Pb__Base__Pe___Type::addr,input2.__Pb__Base__Pe___Type::addr);
  return  *input1;
}

static struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Ret_create_struct___Pb__Base__Pe___Arg_UL_Arg(class Base *input1,unsigned long long input2)
{
  struct __Pb__Base__Pe___Type output;
  output.__Pb__Base__Pe___Type::ptr = input1;
  output.__Pb__Base__Pe___Type::addr = input2;
  return output;
}

static struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Ret_Add___Pb__Base__Pe___Type_Arg_Ui_Arg(struct __Pb__Base__Pe___Type input1,unsigned int input2)
{
  input1.__Pb__Base__Pe___Type::ptr += input2;
  return input1;
}

static struct __Pb__Ui__Pe___Type __Pb__Ui__Pe___Type_Ret_create_struct___Pb__Ui__Pe___Arg_UL_Arg(unsigned int *input1,unsigned long long input2)
{
  struct __Pb__Ui__Pe___Type output;
  output.__Pb__Ui__Pe___Type::ptr = input1;
  output.__Pb__Ui__Pe___Type::addr = input2;
  return output;
}

static struct __Pb__Ui__Pe___Type __Pb__Ui__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type input1)
{
  struct __Pb__Ui__Pe___Type output;
  output.__Pb__Ui__Pe___Type::ptr = ((unsigned int *)input1.__Pb__v__Pe___Type::ptr);
  output.__Pb__Ui__Pe___Type::addr = input1.__Pb__v__Pe___Type::addr;
  return output;
}

static struct __Pb__Ui__Pe___Type __Pb__Ui__Pe___Type_Ret_Assign___Pb____Pb__Ui__Pe___Type__Pe___Arg___Pb__Ui__Pe___Type_Arg(struct __Pb__Ui__Pe___Type *input1,struct __Pb__Ui__Pe___Type input2)
{
  input1 -> __Pb__Ui__Pe___Type::ptr = input2.__Pb__Ui__Pe___Type::ptr;
  v_Ret_create_entry_UL_Arg_UL_Arg(input1 -> __Pb__Ui__Pe___Type::addr,input2.__Pb__Ui__Pe___Type::addr);
  return  *input1;
}

static struct __Pb__f__Pe___Type __Pb__f__Pe___Type_Ret_create_struct___Pb__f__Pe___Arg_UL_Arg(float *input1,unsigned long long input2)
{
  struct __Pb__f__Pe___Type output;
  output.__Pb__f__Pe___Type::ptr = input1;
  output.__Pb__f__Pe___Type::addr = input2;
  return output;
}

static struct __Pb__Ui__Pe___Type __Pb__Ui__Pe___Type_Ret_Increment___Pb____Pb__Ui__Pe___Type__Pe___Arg(struct __Pb__Ui__Pe___Type *input1)
{
  ++input1 -> __Pb__Ui__Pe___Type::ptr;
  return  *input1;
}

static struct __Pb__f__Pe___Type __Pb__f__Pe___Type_Ret_Cast___Pb__Ui__Pe___Type_Arg(struct __Pb__Ui__Pe___Type input1)
{
  struct __Pb__f__Pe___Type output;
  output.__Pb__f__Pe___Type::ptr = ((float *)input1.__Pb__Ui__Pe___Type::ptr);
  output.__Pb__f__Pe___Type::addr = input1.__Pb__Ui__Pe___Type::addr;
  return output;
}

static struct __Pb__f__Pe___Type __Pb__f__Pe___Type_Ret_Assign___Pb____Pb__f__Pe___Type__Pe___Arg___Pb__f__Pe___Type_Arg(struct __Pb__f__Pe___Type *input1,struct __Pb__f__Pe___Type input2)
{
  input1 -> __Pb__f__Pe___Type::ptr = input2.__Pb__f__Pe___Type::ptr;
  v_Ret_create_entry_UL_Arg_UL_Arg(input1 -> __Pb__f__Pe___Type::addr,input2.__Pb__f__Pe___Type::addr);
  return  *input1;
}

static class Derived2 *__Pb__Derived2__Pe___Ret_Deref___Pb__Derived2__Pe___Type_Arg(struct __Pb__Derived2__Pe___Type input1)
{
  return input1.__Pb__Derived2__Pe___Type::ptr;
}

static int *__Pb__i__Pe___Ret_Deref___Pb__i__Pe___Type_Arg(struct __Pb__i__Pe___Type input1)
{
  return input1.__Pb__i__Pe___Type::ptr;
}

static struct __Pb__Derived1__Pe___Type __Pb__Derived1__Pe___Type_Ret_Cast___Pb__Derived2__Pe___Type_Arg(struct __Pb__Derived2__Pe___Type input1)
{
  struct __Pb__Derived1__Pe___Type output;
  output.__Pb__Derived1__Pe___Type::ptr = ((class Derived1 *)input1.__Pb__Derived2__Pe___Type::ptr);
  output.__Pb__Derived1__Pe___Type::addr = input1.__Pb__Derived2__Pe___Type::addr;
  return output;
}

static struct __Pb__Base__Pe___Type __Pb__Base__Pe___Type_Ret_Cast___Pb__Derived1__Pe___Type_Arg(struct __Pb__Derived1__Pe___Type input1)
{
  struct __Pb__Base__Pe___Type output;
  output.__Pb__Base__Pe___Type::ptr = ((class Base *)input1.__Pb__Derived1__Pe___Type::ptr);
  output.__Pb__Base__Pe___Type::addr = input1.__Pb__Derived1__Pe___Type::addr;
  return output;
}

static struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type input1)
{
  struct __Pb__node__Pe___Type output;
  output.__Pb__node__Pe___Type::ptr = ((struct node *)input1.__Pb__v__Pe___Type::ptr);
  output.__Pb__node__Pe___Type::addr = input1.__Pb__v__Pe___Type::addr;
  return output;
}

static struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Ret_Assign___Pb____Pb__node__Pe___Type__Pe___Arg___Pb__node__Pe___Type_Arg(struct __Pb__node__Pe___Type *input1,struct __Pb__node__Pe___Type input2)
{
  input1 -> __Pb__node__Pe___Type::ptr = input2.__Pb__node__Pe___Type::ptr;
  v_Ret_create_entry_UL_Arg_UL_Arg(input1 -> __Pb__node__Pe___Type::addr,input2.__Pb__node__Pe___Type::addr);
  return  *input1;
}

static struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Ret_create_struct___Pb__node__Pe___Arg_UL_Arg(struct node *input1,unsigned long long input2)
{
  struct __Pb__node__Pe___Type output;
  output.__Pb__node__Pe___Type::ptr = input1;
  output.__Pb__node__Pe___Type::addr = input2;
  return output;
}

static struct node *__Pb__node__Pe___Ret_Deref___Pb__node__Pe___Type_Arg(struct __Pb__node__Pe___Type input1)
{
  return input1.__Pb__node__Pe___Type::ptr;
}

static struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Ret_Cast_i_Arg(int input1)
{
  struct __Pb__node__Pe___Type output;
  output.__Pb__node__Pe___Type::ptr = ((struct node *)input1);
  output.__Pb__node__Pe___Type::addr = ((unsigned long long )(&output.__Pb__node__Pe___Type::ptr));
  return output;
}

static struct __Pb__v__Pe___Type __Pb__v__Pe___Type_Ret_Cast___Pb__Base__Pe___Type_Arg(struct __Pb__Base__Pe___Type input1)
{
  struct __Pb__v__Pe___Type output;
  output.__Pb__v__Pe___Type::ptr = ((void *)input1.__Pb__Base__Pe___Type::ptr);
  output.__Pb__v__Pe___Type::addr = input1.__Pb__Base__Pe___Type::addr;
  return output;
}

static struct __Pb__v__Pe___Type __Pb__v__Pe___Type_Ret_Cast___Pb__node__Pe___Type_Arg(struct __Pb__node__Pe___Type input1)
{
  struct __Pb__v__Pe___Type output;
  output.__Pb__v__Pe___Type::ptr = ((void *)input1.__Pb__node__Pe___Type::ptr);
  output.__Pb__v__Pe___Type::addr = input1.__Pb__node__Pe___Type::addr;
  return output;
}

static struct __Pb__node__Pe___Type __Pb__node__Pe___Type_Ret_Add___Pb__node__Pe___Type_Arg_Ui_Arg(struct __Pb__node__Pe___Type input1,unsigned int input2)
{
  input1.__Pb__node__Pe___Type::ptr += input2;
  return input1;
}

static class Base *__Pb__Base__Pe___Ret_Deref___Pb__Base__Pe___Type_Arg(struct __Pb__Base__Pe___Type input1)
{
  return input1.__Pb__Base__Pe___Type::ptr;
}

static int i_Ret_NotEqual___Pb__node__Pe___Type_Arg___Pb__node__Pe___Type_Arg(struct __Pb__node__Pe___Type input1,struct __Pb__node__Pe___Type input2)
{
  return input1.__Pb__node__Pe___Type::ptr != input2.__Pb__node__Pe___Type::ptr;
}

static struct node *__Pb__node__Pe___Ret_PntrArrRef___Pb__node__Pe___Type_Arg_Ui_Arg(struct __Pb__node__Pe___Type input1,unsigned int input2)
{
  return input1.__Pb__node__Pe___Type::ptr + input2;
}

static struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type input1)
{
  struct __Pb__i__Pe___Type output;
  output.__Pb__i__Pe___Type::ptr = ((int *)input1.__Pb__v__Pe___Type::ptr);
  output.__Pb__i__Pe___Type::addr = input1.__Pb__v__Pe___Type::addr;
  return output;
}

static struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Ret_Assign___Pb____Pb__i__Pe___Type__Pe___Arg___Pb__i__Pe___Type_Arg(struct __Pb__i__Pe___Type *input1,struct __Pb__i__Pe___Type input2)
{
  input1 -> __Pb__i__Pe___Type::ptr = input2.__Pb__i__Pe___Type::ptr;
  v_Ret_create_entry_UL_Arg_UL_Arg(input1 -> __Pb__i__Pe___Type::addr,input2.__Pb__i__Pe___Type::addr);
  return  *input1;
}

static struct __Pb__Derived1__Pe___Type __Pb__Derived1__Pe___Type_Ret_AddressOf_UL_Arg_Ui_Arg(unsigned long long input1,unsigned int input2)
{
  struct __Pb__Derived1__Pe___Type output;
  output.__Pb__Derived1__Pe___Type::ptr = ((class Derived1 *)input1);
  output.__Pb__Derived1__Pe___Type::addr = ((unsigned long long )(&output.__Pb__Derived1__Pe___Type::ptr));
  v_Ret_create_entry_UL_Arg_UL_Arg_Ul_Arg(output.__Pb__Derived1__Pe___Type::addr,((unsigned long long )output.__Pb__Derived1__Pe___Type::ptr),((unsigned long )input2));
  return output;
}

static struct __Pb__Derived1__Pe___Type __Pb__Derived1__Pe___Type_Ret_Cast___Pb__Base__Pe___Type_Arg(struct __Pb__Base__Pe___Type input1)
{
  struct __Pb__Derived1__Pe___Type output;
  output.__Pb__Derived1__Pe___Type::ptr = ((class Derived1 *)input1.__Pb__Base__Pe___Type::ptr);
  output.__Pb__Derived1__Pe___Type::addr = input1.__Pb__Base__Pe___Type::addr;
  return output;
}

static class Derived1 *__Pb__Derived1__Pe___Ret_Deref___Pb__Derived1__Pe___Type_Arg(struct __Pb__Derived1__Pe___Type input1)
{
  return input1.__Pb__Derived1__Pe___Type::ptr;
}

static struct __Pb__Derived2__Pe___Type __Pb__Derived2__Pe___Type_Ret_Cast___Pb__v__Pe___Type_Arg(struct __Pb__v__Pe___Type input1)
{
  struct __Pb__Derived2__Pe___Type output;
  output.__Pb__Derived2__Pe___Type::ptr = ((class Derived2 *)input1.__Pb__v__Pe___Type::ptr);
  output.__Pb__Derived2__Pe___Type::addr = input1.__Pb__v__Pe___Type::addr;
  return output;
}

static struct __Pb__Derived2__Pe___Type __Pb__Derived2__Pe___Type_Ret_Assign___Pb____Pb__Derived2__Pe___Type__Pe___Arg___Pb__Derived2__Pe___Type_Arg(struct __Pb__Derived2__Pe___Type *input1,struct __Pb__Derived2__Pe___Type input2)
{
  input1 -> __Pb__Derived2__Pe___Type::ptr = input2.__Pb__Derived2__Pe___Type::ptr;
  v_Ret_create_entry_UL_Arg_UL_Arg(input1 -> __Pb__Derived2__Pe___Type::addr,input2.__Pb__Derived2__Pe___Type::addr);
  return  *input1;
}

static struct __Pb__Derived2__Pe___Type __Pb__Derived2__Pe___Type_Ret_create_struct___Pb__Derived2__Pe___Arg_UL_Arg(class Derived2 *input1,unsigned long long input2)
{
  struct __Pb__Derived2__Pe___Type output;
  output.__Pb__Derived2__Pe___Type::ptr = input1;
  output.__Pb__Derived2__Pe___Type::addr = input2;
  return output;
}

static struct __Pb__Derived2__Pe___Type __Pb__Derived2__Pe___Type_Ret_Cast___Pb__Base__Pe___Type_Arg(struct __Pb__Base__Pe___Type input1)
{
  struct __Pb__Derived2__Pe___Type output;
  output.__Pb__Derived2__Pe___Type::ptr = ((class Derived2 *)input1.__Pb__Base__Pe___Type::ptr);
  output.__Pb__Derived2__Pe___Type::addr = input1.__Pb__Base__Pe___Type::addr;
  return output;
}

static struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Ret_create_struct___Pb__i__Pe___Arg_UL_Arg(int *input1,unsigned long long input2)
{
  struct __Pb__i__Pe___Type output;
  output.__Pb__i__Pe___Type::ptr = input1;
  output.__Pb__i__Pe___Type::addr = input2;
  return output;
}

static struct __Pb__f__Pe___Type __Pb__f__Pe___Type_Ret_Cast___Pb__i__Pe___Type_Arg(struct __Pb__i__Pe___Type input1)
{
  struct __Pb__f__Pe___Type output;
  output.__Pb__f__Pe___Type::ptr = ((float *)input1.__Pb__i__Pe___Type::ptr);
  output.__Pb__f__Pe___Type::addr = input1.__Pb__i__Pe___Type::addr;
  return output;
}

static struct __Pb__i__Pe___Type __Pb__i__Pe___Type_Ret_Increment___Pb____Pb__i__Pe___Type__Pe___Arg(struct __Pb__i__Pe___Type *input1)
{
  ++input1 -> __Pb__i__Pe___Type::ptr;
  return  *input1;
}
