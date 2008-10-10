#include <rose.h>
#include <iostream>
#include <sstream>
#include <string>

#include "abstract_handle.h"
#include "roseAdapter.h"

using namespace std;
using namespace AbstractHandle;
using namespace SageInterface;

// A helper function to convert SageType string to its enumerate type
// TODO move to SageInterface, add error checking using bound check
static VariantT getVariantT(string type_str)
{
  int i=0;
   while (Cxx_GrammarTerminalNames[i].name!=type_str)
     i++;
   return (VariantT)i;  
}

   string roseNode::getConstructTypeName() const
   {
     //ROSE_ASSERT(mNode!=NULL);
      if (mNode==NULL) return "";
      return mNode->sage_class_name();
   }

   //return name for various named constructs
   string roseNode::getName() const
   {
     string result;
     ROSE_ASSERT(mNode!=NULL);
     // only declarations with symbols in ROSE have user-level names
     // need to double check this
     if (isSgFile(mNode)) 
     {
       return isSgFile(mNode)->get_file_info()->get_filenameString ();
     } else  if (isSgProject(mNode))
     { // No name field for rose projects
       return "";
     }

     SgDeclarationStatement* decl = isSgDeclarationStatement(mNode); 
     if (decl)
     {
       switch (decl->variantT())
        { 
          case V_SgVariableDeclaration:
          {
            SgVariableSymbol * symbol=SageInterface::getFirstVarSym(isSgVariableDeclaration(decl));
            result = symbol->get_name();
            break;
          }
          case V_SgClassDeclaration:
          case V_SgTypedefDeclaration:
          case V_SgNamespaceDeclarationStatement:
          case V_SgFunctionDeclaration:
          case V_SgTemplateDeclaration:
          case V_SgMemberFunctionDeclaration:
          {
            result = (decl->search_for_symbol_from_symbol_table()->get_name()).getString();
            ROSE_ASSERT(result.length()!=0);
            break;
          }
          // No explicit name available
          case V_SgCtorInitializerList:
          case V_SgPragmaDeclaration:
          case V_SgFunctionParameterList:
          case V_SgUsingDirectiveStatement:
          {
            break;
          }
         default:
          {
            cerr<<"error, unhandled declaration type in roseNode::getName(): "<<mNode->class_name()<<endl;
            ROSE_ASSERT(false);
            break;
          }
        }// end switch
     }
     return result ;
   }

   bool roseNode::hasSourcePos() const
   {
     source_position pos = getStartPos();
     //0 line number means no source position information for ROSE AST
     if (pos.line==0)
       return false;
     else
       return true;
   }

   bool roseNode::hasName() const
   {
     string name = getName();
     // 0 sized name means no name for ROSE AST
     return (name.size()>0);
   }

   string roseNode::getFileName() const
   {
     string result;
     ROSE_ASSERT(mNode!=NULL);
     // no uniform way to get file name in ROSE
     SgLocatedNode* lnode = isSgLocatedNode(mNode);
     SgSourceFile* sfile = isSgSourceFile(mNode);
     if (lnode)
       result = lnode->getFilenameString();
      else if (sfile)
        result = sfile->getFileName();
      else
        {
          cerr<<"error: unrecognized sage node to get a file name:"
           <<mNode->class_name()<<endl;
          ROSE_ASSERT(false);
        }

     return result;
   }

  abstract_node* roseNode::getParent() const
  {
    ROSE_ASSERT(mNode!=NULL); // NULL roseNode allowed?
    //if (mNode==NULL) return NULL;
    abstract_node* result = NULL;
    if (mNode->get_parent()!=NULL)
      result = new roseNode(mNode->get_parent());
    return result;
  }

/* we need a file handle, not just the file name string
 * so a node for file is needed to generate the file handle legally.
*/
   abstract_node* roseNode::getFileNode() const
   {
     ROSE_ASSERT(mNode!=NULL);
     if (isSgProject(mNode)) // project node has no single file associated. 
       return NULL;
     SgFile* filenode = getEnclosingFileNode(mNode);

     abstract_node* result = new roseNode(filenode);
     return result;
   }
   source_position roseNode::getStartPos() const
   {
     source_position pos; 
     ROSE_ASSERT(mNode!=NULL);
     SgLocatedNode* lnode = isSgLocatedNode(mNode);
     if (lnode != NULL)
     {
       pos.line = lnode->get_file_info()->get_line();
       pos.column= lnode->get_file_info()->get_col();
     }
     else
     {
       pos.line=0;
       pos.column=0;
     }
     return pos;
   }

   source_position roseNode::getEndPos() const
   {
     source_position pos; 
     ROSE_ASSERT(mNode!=NULL);
     SgLocatedNode* lnode = isSgLocatedNode(mNode);
     if (lnode != NULL)
     {  
       pos.line = lnode->get_endOfConstruct()->get_line();
       pos.column= lnode->get_endOfConstruct()->get_col(); 
     }else
     {
       pos.line=0;
       pos.column=0;
     }
     return pos;
   }

   source_position_pair roseNode::getSourcePos() const
   {
     source_position_pair result;
     result.first = getStartPos();
     result.second= getEndPos();
     return result;
   }

  // return the numbering within a scope 
  size_t roseNode::getNumbering(const abstract_node * another_node) const
  {
    size_t number = 1;
    // self is counted as number 1 if no parent node exists
    if (another_node==NULL)
      return 1;
    SgNode* root = (dynamic_cast<const roseNode*> (another_node))->getNode();
    ROSE_ASSERT(root !=NULL);
    Rose_STL_Container <SgNode*> nodeArray = NodeQuery::querySubTree(root,mNode->variantT());
    for (Rose_STL_Container<SgNode *>::iterator i=nodeArray.begin();
        i!=nodeArray.end(); i++)
    {
      if (*i == mNode) 
        break;
      else 
      // should consider the node within the same file only!!
        if ((*i)->get_file_info()->get_filenameString() == 
             mNode->get_file_info()->get_filenameString())
          number++;
    }  
    return number;
  }
  // A simplest implementation here, for now
   bool roseNode::operator==(const abstract_node & x) const
   {
     SgNode* other_node =  (dynamic_cast<const roseNode&> (x)).getNode();

     return (mNode ==other_node);
   }

  //TODO  
  size_t roseNode::getIntLabel() const
  {
    return 0;
  }
  //TODO  
  std::string roseNode::getStringLabel() const
  {
    string result;
    return result;
  }
std::string roseNode::toString() const
{
  std::string result;
  result= mNode->unparseToString();
  return result;
}

 //Find a node from a string for a abstract handle
// eg. find a file node from a string like SgSourceFile<name,/home/liao6/names.cpp>
abstract_node* roseNode::findNode(std::string input) const
{
   ROSE_ASSERT(input.size()>0);
   istringstream buffer(input);
   char type_str[256], specifier_str[PATH_MAX+512];
   AbstractHandle::specifier mspecifier;

   buffer.getline(type_str,256,'<');

   buffer.unget(); // put back '<'
   buffer.getline(specifier_str,PATH_MAX+512,'>');

  fromString(mspecifier,specifier_str);

  return findNode(type_str,mspecifier);
}

abstract_node* roseNode::findNode(std::string construct_type_str, specifier mspecifier) const  
{
  abstract_node* result=NULL;
  VariantT vt = getVariantT(construct_type_str); 

  //Get all matched nodes according to node type
  Rose_STL_Container<SgNode*> nodelist =  NodeQuery::querySubTree(getNode(),vt);

  for (Rose_STL_Container<SgNode *>::iterator i=nodelist.begin();i!=nodelist.end();i++)
  {
    abstract_node* cnode = new roseNode(*i);
    if (mspecifier.get_type()==e_position)
    {
      if (isEqual(mspecifier.get_value().positions, cnode->getSourcePos()))
      {
        result = cnode;
        break;
      }
    }
    else if (mspecifier.get_type()==e_name)
    {
      if (mspecifier.get_value().str_v == cnode->getName())
      {
        result = cnode;
        break;
      }
    } else if (mspecifier.get_type()==e_numbering)
    {
      if (mspecifier.get_value().int_v == cnode->getNumbering(this))
      {
        result = cnode;
        break;
      }
    } else
    {
      cerr<<"error: unhandled specifier type in roseNode::findNode()"<<endl;
      ROSE_ASSERT(false);
    }
  }//end for

   return result;
}









