#ifndef __FORTRANPARSERSTATE_H_
#define __FORTRANPARSERSTATE_H_


#include "fortran_support.h"

#define astScopeStack              (*(FortranParserState::getCurrentScopeStack()))
#define astExpressionStack         (*(FortranParserState::getCurrentExpressionStack()))
#define astNodeStack               (*(FortranParserState::getCurrentNodeStack()))
#define astNameStack               (*(FortranParserState::getCurrentNameStack()))
#define astTypeStack               (*(FortranParserState::getCurrentTypeStack()))
#define astBaseTypeStack           (*(FortranParserState::getCurrentBaseTypeStack()))
#define astIntentSpecStack         (*(FortranParserState::getCurrentIntentSpecStack()))
#define astAttributeSpecStack      (*(FortranParserState::getCurrentAttributeSpecStack()))
#define astInitializerStack        (*(FortranParserState::getCurrentInitializerStack()))
#define astTypeKindStack           (*(FortranParserState::getCurrentTypeKindStack()))
#define astTypeParameterStack      (*(FortranParserState::getCurrentTypeParameterStack()))
#define astLabelSymbolStack        (*(FortranParserState::getCurrentLabelSymbolStack()))
#define astIfStatementStack        (*(FortranParserState::getCurrentIfStatementStack()))
#define astActualArgumentNameStack (*(FortranParserState::getCurrentActualArgumentNameStack()))
#define astFunctionAttributeStack  (*(FortranParserState::getCurrentFunctionAttributeStack()))
#define astIncludeStack            (*(FortranParserState::getCurrentIncludeStack()))


using std::string;
using std::map;
using std::stack;
using std::list;
using std::vector;


class FortranParserState
  {

     private:
       static stack<FortranParserState*>  statesStack;

     private:
       list<SgScopeStatement*> currScopeStack;
       list<SgExpression*>     currExpressionStack;
       list<SgNode*>           currNodeStack;
       AstNameListType         currNameStack;
       list<SgType*>           currTypeStack;
       list<SgType*>           currBaseTypeStack;
       list<int>               currIntentSpecStack;
       list<int>               currAttributeSpecStack;
       list<SgExpression*>     currInitializerStack;
       list<SgExpression*>     currTypeKindStack;
       list<SgExpression*>     currTypeParameterStack;
       list<SgLabelSymbol*>    currLabelSymbolStack;
       list<SgIfStmt*>         currIfStatementStack;
       AstNameListType         currActualArgumentNameStack;
       AstNameListType         currFunctionAttributeStack;
       vector<string>          currAstIncludeStack;

       void clearStacks();

     public:

     // DQ (7/30/2010): Added empty function to if there are entries in the stack
        static bool empty()
         { return statesStack.empty(); }

     // DQ (7/30/2010): Added assertions to all the functions below.
       // following functions will called by macro in ofp-rose connection files
       static  list<SgScopeStatement*>  *getCurrentScopeStack()
        {
          ROSE_ASSERT(statesStack.empty() == false);
          return &(statesStack.top()->currScopeStack);
        }

       static  list<SgExpression*>      *getCurrentExpressionStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currExpressionStack);
          }

       static  list<SgNode*>            *getCurrentNodeStack()
          { 
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currNodeStack);
          }

       static  AstNameListType          *getCurrentNameStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currNameStack);
          }

       static  list<SgType*>            *getCurrentTypeStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currTypeStack);
          }

       static  list<SgType*>            *getCurrentBaseTypeStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currBaseTypeStack);
          }

       static  list<int>                *getCurrentIntentSpecStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currIntentSpecStack);
          }

       static  list<int>                *getCurrentAttributeSpecStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currAttributeSpecStack);
          }

       static  list<SgExpression*>      *getCurrentInitializerStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currInitializerStack);
          }

       static  list<SgExpression*>      *getCurrentTypeKindStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currTypeKindStack);
          }

       static  list<SgExpression*>      *getCurrentTypeParameterStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currTypeParameterStack);
          }

       static  list<SgLabelSymbol*>     *getCurrentLabelSymbolStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currLabelSymbolStack);
          }

       static  list<SgIfStmt*>          *getCurrentIfStatementStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currIfStatementStack);
          }

       static  AstNameListType          *getCurrentActualArgumentNameStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currActualArgumentNameStack);
          }

       static  AstNameListType          *getCurrentFunctionAttributeStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currFunctionAttributeStack);
          }

       static  vector<string>          *getCurrentIncludeStack()
          {
            ROSE_ASSERT(statesStack.empty() == false);
            return &(statesStack.top()->currAstIncludeStack);
          }

       //Constructor:
       //   push "this" object of FortranParserState into the "statesStack"
       FortranParserState();

       
       // Destructor: 
       //   Pop out the stack, clean all the member stacks 
       ~FortranParserState();

  };

#endif /*__FORTRANPARSERSTATE_H_*/
