// Original Author (AstProcessing classes): Markus Schordan
// Rewritten by: Gergo Barany
// $Id: AstProcessing.h,v 1.6 2008/01/08 02:56:38 dquinlan Exp $

#ifndef ASTPROCESSING_H
#define ASTPROCESSING_H
#define INHERITED 0
#define SYNTHESIZED 1
#define BOTH 2



#include "staticCFG.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

//using namespace boost;


//using namespace std;

// tps (01/08/2010) Added sage3basic since this doesnt compile under gcc4.1.2
//#include "sage3basic.h"
//#include "sage3.h"
// Non-templated helper function in AstProcessing.C

// 07/12/10
/*These sets are for keeping track of the traversed nodes so as to
avoid getting stuck in a loop. DO NOT REMOVE or the code will break 
NOTE: All of the traverse functions (besides traverseWithinFile and traverseInputFiles)
are overloaded to allow for graph node inputs */

// 07/16/10
/* traverseWithinFile and traverseInputFiles now contain an option input string so
one can choose to use StaticCFG or Interprocedural (not sure that interprocedural is worth doing)
by using "StaticCFG" or "Interprocedural" as inputs */

static std::set<SgGraphNode*> traversed;
static std::set<SgGraphNode*> traversed2;


bool 
SgTreeTraversal_inFileToTraverse(SgNode* node, bool traversalConstraint, SgFile* fileToVisit);

/*
   GB (06/01/2007):
   Changes to the original code were roughly:
   - removed unneeded includes and other code
   - removed everything related to visit flags
   - changed support for SynthesizedAttributesList; synthesized attributes are
     now handled in a smarter way, by keeping them on a stack and (in
     principle) only passing iterators instead of copying a container;
     traverse() is now only a thin wrapper around performTraversal() that
     takes care of visiting nodes and pushing/popping synthesized attributes
   - rewrote inFileToTraverse() to use new AST features instead of lots of
     string comparisons; it is now explicitly stated (at least in this
     comment) that we *do* visit subtrees from other files unless their root
     is in global or namespace scope, which is how we hope to avoid headers
     but still handle all included "code"
   - renamed class _DummyAttribute because that identifier is reserved for the
     implementation
   - everything that was not changed in some other way was totally
     reformatted, so diffing the old and new files won't do anything
     meaningful
   - appended "" suffix to pretty much any global identifier that would
     clash with the existing ones; if this code is ever moved into ROSE to
     replace the old version, it should not be exceedingly hard to remove the
     suffix everywhere
   - added some new virtual functions the user may choose to implement:
        atTraversalStart(), atTraversalEnd(), destroyInheritedValue()
   - other stuff I have probably forgotten
   GB (7/6/2007):
   - added new class AstPrePostProcessing and changed the traverseOrder
     flag so that it can now be pre and post order at the same time
 */





#include "AstSuccessorsSelectors.h"
#include "StackFrameVector.h"

// This type is used as a dummy template parameter for those traversals
// that do not use inherited or synthesized attributes.
typedef void *DummyAttribute;
// We initialize DummyAttributes to this value to avoid "may not be
// initialized" warnings. If you change the typedef, adjust the constant...
static const DummyAttribute defaultDummyAttribute = NULL;
// The attribute _DummyAttribute is reserved for the implementation, so we
// should deprecate it, but there is code using it explicitly. Which it
// shouldn't.
typedef DummyAttribute _DummyAttribute;

template <class InheritedAttributeType, class SynthesizedAttributeType>
class SgCombinedTreeTraversal;

struct compareSgGraphNode {
    bool operator()(const SgGraphNode* a, const SgGraphNode* b) const
    {
        return a==b;
    }
};



// Base class for all traversals.
template <class InheritedAttributeType, class SynthesizedAttributeType>
class SgTreeTraversal
{
public:  
    typedef StackFrameVector<SynthesizedAttributeType> SynthesizedAttributesList;

    SynthesizedAttributeType traverse(SgNode* basenode,
            InheritedAttributeType inheritedValue,
            t_traverseOrder travOrder = preandpostorder);

    SynthesizedAttributeType traverseWithinFile(SgNode* basenode,
            InheritedAttributeType inheritedValue,
            t_traverseOrder travOrder = preandpostorder);

    void traverseInputFiles(SgProject* projectNode,
            InheritedAttributeType inheritedValue,
            t_traverseOrder travOrder = preandpostorder);

    // Default destructor/constructor
    virtual ~SgTreeTraversal();
    SgTreeTraversal();

    // Copy operations
    SgTreeTraversal(const SgTreeTraversal &);
    const SgTreeTraversal &operator=(const SgTreeTraversal &);

    friend class SgCombinedTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>;
   

#include "Cxx_GrammarTreeTraversalAccessEnums.h"

protected:
    virtual InheritedAttributeType evaluateInheritedAttribute(SgNode* astNode,
            InheritedAttributeType inheritedValue) = 0;

    
    virtual SynthesizedAttributeType evaluateSynthesizedAttribute(SgNode* n,
            InheritedAttributeType in,
            SynthesizedAttributesList l) = 0;

    
    typedef typename AstSuccessorsSelectors::SuccessorsContainer SuccessorsContainer;
    typedef SuccessorsContainer& SuccessorsContainerRef;

    // GB (09/25/2007): Feel free to override this to implement custom traversals, but see the
    // comment for set_useDefaultIndexBasedTraversal() below!
    virtual void setNodeSuccessors(SgNode* node, SuccessorsContainer& succContainer);

    virtual SynthesizedAttributeType defaultSynthesizedAttribute(InheritedAttributeType inh);

    // GB (06/04/2007): A new virtual function called at the start of the
    // traversal, before any node is actually visited; can be used to
    // compute attributes that may have changed since the constructor was
    // executed, but are constant during the traversal itself. A no-op by
    // default. If you don't know what you would use this for, ignore it.
    virtual void atTraversalStart();
    // GB (06/13/2007): Added this just for symmetry, not sure if it is
    // useful, but it won't hurt to have it.
    virtual void atTraversalEnd();

    // GB (09/25/2007): This flag determines whether the new index-based traversal mechanism or the more general
    // mechanism based on successor containers is to be used. Indexing should be faster, but it would be quite hard to
    // adapt it to the reverse traversal and other specialized traversals. Thus: This is true by default, and anybody
    // who overrides setNodeSuccessors() *must* change this to false to force the traversal to use their custom
    // successor container.
    void set_useDefaultIndexBasedTraversal(bool);
private:
    void performTraversal(SgNode *basenode,
            InheritedAttributeType inheritedValue,
            t_traverseOrder travOrder);
    SynthesizedAttributeType traversalResult();

    bool useDefaultIndexBasedTraversal;
    bool traversalConstraint;
    SgFile *fileToVisit;

    // stack of synthesized attributes; evaluateSynthesizedAttribute() is
    // automagically called with the appropriate stack frame, which
    // behaves like a non-resizable std::vector
    SynthesizedAttributesList *synthesizedAttributes;
};


template <class InheritedAttributeType, class SynthesizedAttributeType>
class SgGraphTraversal
{
   public:

    virtual ~SgGraphTraversal();
    SgGraphTraversal();

    // Copy operations
    SgGraphTraversal(const SgGraphTraversal &);
    const SgGraphTraversal &operator=(const SgGraphTraversal &);

    typedef StackFrameVector<SynthesizedAttributeType> SynthesizedAttributesList;
    //void buildGraph(SgNode*);
    static boost::unordered_map<SgGraphNode*, InheritedAttributeType, boost::hash<SgGraphNode*>, compareSgGraphNode> graphnodeinheritedmap; 
    static boost::unordered_map<SgGraphNode*, InheritedAttributeType, boost::hash<SgGraphNode*>, compareSgGraphNode> graphnodeinheritedmaploop;
    SgIncidenceDirectedGraph* getGraph();
    SgGraphNode* getStartNode();
    //void setStartNode(SgGraphNode* n);
    //void setGraph(SgIncidenceDirectedGraph* gr);
    //void setCFG(StaticCFG::CFG cfgh);
    SynthesizedAttributeType traverse(SgGraphNode* basenode, SgIncidenceDirectedGraph* g,
            InheritedAttributeType inheritedValue, InheritedAttributeType nullInherit,
            int graphTraversal, bool loop);
   protected:
    
    InheritedAttributeType solveInheritedAttribute(SgGraphNode* child, std::set<SgGraphNode*> parentset);
    virtual InheritedAttributeType evaluateInheritedAttribute(SgGraphNode* n,
            std::vector<InheritedAttributeType> inheritedValues, bool loop) = 0;
    virtual SynthesizedAttributeType evaluateSynthesizedAttribute(SgGraphNode* n,
            InheritedAttributeType in,
            SynthesizedAttributesList l) = 0;
    
    static SgIncidenceDirectedGraph* graph;
    static SgGraphNode* startNode;
    static StaticCFG::CFG cfghold;
    SynthesizedAttributeType defaultSynthesizedAttribute(InheritedAttributeType);
   private:
    
    InheritedAttributeType solveInheritedAttribute(SgGraphNode* node, std::set<SgGraphNode*> nodeset, SgIncidenceDirectedGraph* g,
        InheritedAttributeType inheritedValue, InheritedAttributeType nullInherit, int graphTraversal, std::set<SgGraphNode*> traversedlocal, std::set<SgGraphNode*> traversedreverse, bool loop = false, bool inloop = false, SgGraphNode* endnode = NULL);
    void
    performTraversal(SgGraphNode*, SgIncidenceDirectedGraph*,
        InheritedAttributeType, InheritedAttributeType, int graphTraversal, std::set<SgGraphNode*> traversedlocal, std::set<SgGraphNode*> traversedreverse, bool loop);
    SynthesizedAttributesList *synthesizedAttributes;
    SynthesizedAttributeType traversalResult();
};

template <class InheritedAttributeType, class SynthesizedAttributeType> boost::unordered_map<SgGraphNode*, InheritedAttributeType, boost::hash<SgGraphNode*>, compareSgGraphNode> SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::graphnodeinheritedmap;
template <class InheritedAttributeType, class SynthesizedAttributeType> boost::unordered_map<SgGraphNode*, InheritedAttributeType, boost::hash<SgGraphNode*>, compareSgGraphNode> SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::graphnodeinheritedmaploop;
template <class InheritedAttributeType, class SynthesizedAttributeType> SgIncidenceDirectedGraph* SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::graph;
template <class InheritedAttributeType, class SynthesizedAttributeType> SgGraphNode* SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::startNode;
template <class InheritedAttributeType, class SynthesizedAttributeType> StaticCFG::CFG SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::cfghold;

template <class InheritedAttributeType, class SynthesizedAttributeType>
class AstCombinedTopDownBottomUpProcessing;

template <class InheritedAttributeType, class SynthesizedAttributeType>
class AstTopDownBottomUpProcessing
    : public SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>
{
public:
    typedef typename SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>
        ::SynthesizedAttributesList SynthesizedAttributesList;

    // deprecated
    typedef SynthesizedAttributesList SubTreeSynthesizedAttributes;

    //! evaluates attributes on the entire AST
    SynthesizedAttributeType traverse(SgNode* node, InheritedAttributeType inheritedValue);
    
    
    

    

    //! evaluates attributes only at nodes which represent the same file as where the evaluation was started
    SynthesizedAttributeType traverseWithinFile(SgNode* node, InheritedAttributeType inheritedValue);
    

    friend class AstCombinedTopDownBottomUpProcessing<InheritedAttributeType, SynthesizedAttributeType>;

protected:
    //! pure virtual function which must be implemented to compute the inherited attribute at a node
    virtual InheritedAttributeType evaluateInheritedAttribute(SgNode* astNode,
            InheritedAttributeType inheritedValue) = 0;
    
    //! pure virtual function which must be implemented to compute the synthesized attribute at a node. The list of
    //! synthesized attributes consists of the synthesized attributes computed at the children node of the current node.
    //! The inherited attribute value is computed by evaluateInheritedAttribute at the same node and simply passed to this function.
    //! Use the typedef SynthesizedAttributeList as type for the synthesized attributes list.
    virtual SynthesizedAttributeType evaluateSynthesizedAttribute(SgNode*,
            InheritedAttributeType,
            SynthesizedAttributesList) = 0;


    
    //! Function called at the start of the traversal, before any node is
    //! visited; override if necessary, the default implementation is a
    //! no-op.
    virtual void atTraversalStart();
    virtual void atTraversalEnd();
};

template <class InheritedAttributeType>
class AstCombinedTopDownProcessing;

template <class InheritedAttributeType>
class DistributedMemoryAnalysisPreTraversal;

template <class InheritedAttributeType>
class AstTopDownProcessing
    : public SgTreeTraversal<InheritedAttributeType, DummyAttribute>
{
public:
    typedef typename SgTreeTraversal<InheritedAttributeType, DummyAttribute>
        ::SynthesizedAttributesList SynthesizedAttributesList;

    //! evaluates attributes on the entire AST
    void traverse(SgNode* node, InheritedAttributeType inheritedValue);
    
 
    //! evaluates attributes only at nodes which represent the same file as where the evaluation was started
    void traverseWithinFile(SgNode* node, InheritedAttributeType inheritedValue);
    

    friend class AstCombinedTopDownProcessing<InheritedAttributeType>;
    friend class DistributedMemoryAnalysisPreTraversal<InheritedAttributeType>;

protected:
    //! pure virtual function which must be implemented to compute the inherited attribute at a node
    virtual InheritedAttributeType evaluateInheritedAttribute(SgNode* astNode,
            InheritedAttributeType inheritedValue) = 0;


    //! Function called at the start of the traversal, before any node is
    //! visited; override if necessary, the default implementation is a
    //! no-op.
    virtual void atTraversalStart();
    virtual void atTraversalEnd();
    // GB (06/04/2007): This is a new virtual function, a no-op by
    // default. It is called for every node, after its successors have
    // been visited, with the inherited attribute computed at this node.
    // The intention is to be able to free any memory (or other resources)
    // allocated by evaluateInheritedAttribute().
    virtual void destroyInheritedValue(SgNode*, InheritedAttributeType);

private:
    DummyAttribute evaluateSynthesizedAttribute(SgNode* astNode,
            InheritedAttributeType inheritedValue,
            SynthesizedAttributesList l);

   
    DummyAttribute defaultSynthesizedAttribute(InheritedAttributeType inh);
};

template <class SynthesizedAttributeType>
class AstCombinedBottomUpProcessing;

template <class InheritedAttributeType>
class DistributedMemoryAnalysisPostTraversal;

template <class SynthesizedAttributeType>
class AstBottomUpProcessing
    : public SgTreeTraversal<DummyAttribute,SynthesizedAttributeType>
{
public:
    typedef typename SgTreeTraversal<DummyAttribute, SynthesizedAttributeType>
        ::SynthesizedAttributesList SynthesizedAttributesList;
 
    // deprecated
    typedef SynthesizedAttributesList SubTreeSynthesizedAttributes; 

    

    //! evaluates attributes on the entire AST
    SynthesizedAttributeType traverse(SgNode* node);
    

    //! evaluates attributes only at nodes which represent the same file as where the evaluation was started
    SynthesizedAttributeType traverseWithinFile(SgNode* node);
    

    //! evaluates attributes only at nodes which represent files which were specified on the command line (=input files).
    void traverseInputFiles(SgProject* projectNode);

    friend class AstCombinedBottomUpProcessing<SynthesizedAttributeType>;
    friend class DistributedMemoryAnalysisPostTraversal<SynthesizedAttributeType>;

protected:
    //! pure virtual function which must be implemented to compute the synthesized attribute at a node. The list of
    //! synthesized attributes consists of the synthesized attributes computed at the children node of the current node.
    //! The inherited attribute value is computed by the function evaluateInheritedAttribute at the same node and simply passed to this function.
    //! Use the typedef SynthesizedAttributeList as type for the synthesized attributes list. 
    virtual SynthesizedAttributeType evaluateSynthesizedAttribute(SgNode*, SynthesizedAttributesList) = 0;
    

    //! Allows to provide a default value for a synthesized attribute of primitive type (e.g. int, bool, etc.).
    //! If a class is used as type for a synthesized attribute the default constructor of this class is sufficient and this function does not have be
    //! implemented.
    virtual SynthesizedAttributeType defaultSynthesizedAttribute();
    //! Function called at the start of the traversal, before any node is
    //! visited; override if necessary, the default implementation is a
    //! no-op.
    virtual void atTraversalStart();
    virtual void atTraversalEnd();

private:
    virtual DummyAttribute evaluateInheritedAttribute(SgNode* astNode, DummyAttribute inheritedValue);
    

    virtual SynthesizedAttributeType evaluateSynthesizedAttribute(SgNode* astNode, DummyAttribute inheritedValue, SynthesizedAttributesList l);
       

     
    virtual SynthesizedAttributeType defaultSynthesizedAttribute(DummyAttribute inheritedValue);
};

// deprecated classes (provided for compatibility with existing user code - will be removed at some point in future)
class AstSynthesizedAttribute {};
class AstInheritedAttribute {};
class SgSynthesizedAttribute : public AstSynthesizedAttribute {};
class SgInheritedAttribute : public AstInheritedAttribute {};

template <class InheritedAttributeType, class SynthesizedAttributeType>
class SgTopDownBottomUpProcessing : public AstTopDownBottomUpProcessing <InheritedAttributeType, SynthesizedAttributeType> {};
template <class InheritedAttributeType>
class SgTopDownProcessing : public AstTopDownProcessing <InheritedAttributeType> {};
template <class SynthesizedAttributeType>
class SgBottomUpProcessing : public AstBottomUpProcessing <SynthesizedAttributeType> {};

// Original Author (AstProcessing classes): Markus Schordan
// Rewritten by: Gergo Barany
// $Id: AstProcessing.C,v 1.10 2008/01/25 02:25:48 dquinlan Exp $

// For information about the changes introduced during the rewrite, see
// the comment in AstProcessing.h

template<class InheritedAttributeType, class SynthesizedAttributeType>
void
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
setNodeSuccessors(SgNode* node, SuccessorsContainer& succContainer)
{
    AstSuccessorsSelectors::selectDefaultSuccessors(node, succContainer);
}




// The default constructor of the internal tree traversal class
template<class InheritedAttributeType, class SynthesizedAttributeType>
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
SgTreeTraversal() 
  : useDefaultIndexBasedTraversal(true),
    traversalConstraint(false),
    fileToVisit(NULL),
    synthesizedAttributes(new SynthesizedAttributesList())
{
}

#ifndef SWIG
// The destructor of the internal tree traversal class
template<class InheritedAttributeType, class SynthesizedAttributeType>
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
~SgTreeTraversal()
{
    ROSE_ASSERT(synthesizedAttributes != NULL);
    delete synthesizedAttributes;
    synthesizedAttributes = NULL;
}
#endif

template<class InheritedAttributeType, class SynthesizedAttributeType>
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
SgTreeTraversal(const SgTreeTraversal &other)
  : useDefaultIndexBasedTraversal(other.useDefaultIndexBasedTraversal),
    traversalConstraint(other.traversalConstraint),
    fileToVisit(other.fileToVisit),
    synthesizedAttributes(other.synthesizedAttributes->deepCopy())
{
}

template<class InheritedAttributeType, class SynthesizedAttributeType>
const SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType> &
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
operator=(const SgTreeTraversal &other)
{
    useDefaultIndexBasedTraversal = other.useDefaultIndexBasedTraversal;
    traversalConstraint = other.traversalConstraint;
    fileToVisit = other.fileToVisit;

    ROSE_ASSERT(synthesizedAttributes != NULL);
    delete synthesizedAttributes;
    synthesizedAttributes = other.synthesizedAttributes->deepCopy();

    return *this;
}

template<class InheritedAttributeType, class SynthesizedAttributeType>
void
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
set_useDefaultIndexBasedTraversal(bool val)
{
    useDefaultIndexBasedTraversal = val;
}

// MS: 03/22/02
// function to traverse all ASTs representing inputfiles (excluding include files), 
template<class InheritedAttributeType, class SynthesizedAttributeType>
void
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
traverseInputFiles(SgProject* projectNode,
        InheritedAttributeType inheritedValue,
        t_traverseOrder travOrder)
   {
     const SgFilePtrList& fList = projectNode->get_fileList();

  // DQ (9/1/2008): It is observed that this prevents a SgProject from being built on the generated DOT file!
  // We might want a better design to be used here or call the evaluation directly to force the handling of 
  // inherited and synthesized attributes on the SgProject.  This detail effect the handling of multiple
  // files on the command line (something we want to get a global perspective on if possible).
     if ( SgProject::get_verbose() > 0 )
          printf ("Warning: The traverseInputFiles() iteration over the file list prevents the evaluation of inherited and synthesized attributes on the SgProject IR node! \n");

     for (SgFilePtrList::const_iterator fl_iter = fList.begin(); fl_iter != fList.end(); fl_iter++)
        {
          ROSE_ASSERT(*fl_iter != NULL);
          traverseWithinFile((*fl_iter), inheritedValue, travOrder);
        }
   }

template<class InheritedAttributeType, class SynthesizedAttributeType>
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
SgGraphTraversal() 
  : //useDefaultIndexBasedTraversal(true),
    //traversalConstraint(false),
    //fileToVisit(NULL),
    synthesizedAttributes(new SynthesizedAttributesList())
{
}

template<class InheritedAttributeType, class SynthesizedAttributeType>
const SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType> &
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
operator=(const SgGraphTraversal &other)
{
    //useDefaultIndexBasedTraversal = other.useDefaultIndexBasedTraversal;
    //traversalConstraint = other.traversalConstraint;
    //fileToVisit = other.fileToVisit;

    ROSE_ASSERT(synthesizedAttributes != NULL);
    delete synthesizedAttributes;
    synthesizedAttributes = other.synthesizedAttributes->deepCopy();

    return *this;
}


#ifndef SWIG
// The destructor of the internal tree traversal class
template<class InheritedAttributeType, class SynthesizedAttributeType>
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
~SgGraphTraversal()
{
    ROSE_ASSERT(synthesizedAttributes != NULL);
    delete synthesizedAttributes;
    synthesizedAttributes = NULL;
}
#endif

/*
template<class InheritedAttributeType, class SynthesizedAttributeType>
SgIncidenceDirectedGraph*
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
getGraph()
{
	return SgGraphTraversal::graph;
}

template<class InheritedAttributeType, class SynthesizedAttributeType>
SgGraphNode*
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
getStartNode()
{
	return SgGraphTraversal::startNode;
}

template<class InheritedAttributeType, class SynthesizedAttributeType>
void
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
setCFG(StaticCFG::CFG cfgh)
{
	SgGraphTraversal::cfghold = cfgh;
}
*/

/*
template<class InheritedAttributeType, class SynthesizedAttributeType>
void
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
buildGraph(SgNode* n)
{
    cout << "I have a: " << n->sage_class_name() << endl;
    StaticCFG::CFG cfg(n);
    cout << "before build\n";
    cfg.buildFullCFG();
    cout << "after build\n";
    SgGraphNode* sn = cfg.cfgForBeginning(n);
    ROSE_ASSERT(isSgGraphNode(sn));
    SgIncidenceDirectedGraph* gr = cfg.getGraph();
    ROSE_ASSERT(isSgIncidenceDirectedGraph(gr));
    setStartNode(sn);
    setGraph(gr);
    setCFG(cfg);
}
*//*
template<class InheritedAttributeType, class SynthesizedAttributeType>
void
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
setGraph(SgIncidenceDirectedGraph* n)
{
    SgGraphTraversal::graph = n;
}

template<class InheritedAttributeType, class SynthesizedAttributeType>
void
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
setStartNode(SgGraphNode* n)
{
    SgGraphTraversal::startNode = n;
}
*/
template<class InheritedAttributeType, class SynthesizedAttributeType>
SynthesizedAttributeType
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
traverse(SgGraphNode* n, SgIncidenceDirectedGraph* g, InheritedAttributeType inheritedValue, InheritedAttributeType nullInherit, int graphTraversal, bool loop) {
   traversed.clear();
   traversed2.clear();
   synthesizedAttributes->resetStack();
   ROSE_ASSERT(synthesizedAttributes->debugSize() == 0);
   std::set<SgGraphNode*> traversedlocal;
   std::set<SgGraphNode*> traversedreverse;
   graphnodeinheritedmap[n] = inheritedValue;
   performTraversal(n, g, inheritedValue, nullInherit, graphTraversal, traversedlocal, traversedreverse, false);
   return traversalResult();
}

template <class InheritedAttributeType, class SynthesizedAttributeType>
SynthesizedAttributeType
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
defaultSynthesizedAttribute(InheritedAttributeType inh)
{
    SynthesizedAttributeType s = SynthesizedAttributeType();
    return s;
}

                
//////////////////////////////////////////////////////
//// TOP DOWN BOTTOM UP PROCESSING IMPLEMENTATION ////
//////////////////////////////////////////////////////


// MS: 04/25/02
template <class InheritedAttributeType, class SynthesizedAttributeType>
SynthesizedAttributeType 
AstTopDownBottomUpProcessing<InheritedAttributeType, SynthesizedAttributeType>::
traverse(SgNode* node, InheritedAttributeType inheritedValue)
{
    // this is now explicitly marked as a pre *and* post order traversal
    return SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>
        ::traverse(node, inheritedValue, preandpostorder);
}


// MS: 04/25/02
template <class InheritedAttributeType, class SynthesizedAttributeType>
SynthesizedAttributeType 
AstTopDownBottomUpProcessing<InheritedAttributeType, SynthesizedAttributeType>::
traverseWithinFile(SgNode* node, InheritedAttributeType inheritedValue)
{
    // this is now explicitly marked as a pre *and* post order traversal
    return SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::traverseWithinFile(node, inheritedValue, preandpostorder);
}

////////////////////////////////////////////
//// TOP DOWN PROCESSING IMPLEMENTATION ////
////////////////////////////////////////////

// MS: 04/25/02
template <class InheritedAttributeType>
DummyAttribute
AstTopDownProcessing<InheritedAttributeType>::
evaluateSynthesizedAttribute(SgNode* astNode,
        InheritedAttributeType inheritedValue,
        typename AstTopDownProcessing<InheritedAttributeType>::SynthesizedAttributesList l)
{
    // call the cleanup function
    destroyInheritedValue(astNode, inheritedValue);
    // return value is not used
    DummyAttribute a = defaultDummyAttribute;
    return a;
}


// MS: 07/30/04
template <class InheritedAttributeType>
DummyAttribute
AstTopDownProcessing<InheritedAttributeType>::
defaultSynthesizedAttribute(InheritedAttributeType inh)
{
    // called but not used
    DummyAttribute a = defaultDummyAttribute;
    return a;
}

// MS: 04/25/02
template <class InheritedAttributeType>
void
AstTopDownProcessing<InheritedAttributeType>::
traverse(SgNode* node, InheritedAttributeType inheritedValue)
{
    // "top down" is now marked as a pre *and* post order traversal because
    // there is a post order component (the call to destroyInheritedAttribute)
    SgTreeTraversal<InheritedAttributeType, DummyAttribute>
        ::traverse(node, inheritedValue, preandpostorder);
}


// MS: 09/30/02
template <class InheritedAttributeType>
void
AstTopDownProcessing<InheritedAttributeType>::
traverseWithinFile(SgNode* node, InheritedAttributeType inheritedValue)
{
    // "top down" is now marked as a pre *and* post order traversal because
    // there is a post order component (the call to destroyInheritedAttribute)
    SgTreeTraversal<InheritedAttributeType, DummyAttribute>::traverseWithinFile(node, inheritedValue, preandpostorder);
}


/////////////////////////////////////////////
//// BOTTOM UP PROCESSING IMPLEMENTATION ////
/////////////////////////////////////////////

// MS: 04/25/02
template <class SynthesizedAttributeType>
DummyAttribute
AstBottomUpProcessing<SynthesizedAttributeType>::
evaluateInheritedAttribute(SgNode* astNode, DummyAttribute inheritedValue)
{
    /* called but not used */
    DummyAttribute a = defaultDummyAttribute;
    return a;
}




// MS: 30/07/04
template <class SynthesizedAttributeType>
SynthesizedAttributeType AstBottomUpProcessing<SynthesizedAttributeType>::
defaultSynthesizedAttribute()
{
    // GB (8/6/2007): This can give "may not be initialized" warnings when
    // compiling with optimization (because -O flags cause gcc to perform
    // data-flow analysis). I wonder how this might be fixed.
    SynthesizedAttributeType s = SynthesizedAttributeType();
    return s;
}

// MS: 30/07/04
template <class SynthesizedAttributeType>
SynthesizedAttributeType AstBottomUpProcessing<SynthesizedAttributeType>::
defaultSynthesizedAttribute(DummyAttribute inheritedValue)
{
    return defaultSynthesizedAttribute();
}

// MS: 04/25/02//ENDEDIT
template <class SynthesizedAttributeType>
SynthesizedAttributeType AstBottomUpProcessing<SynthesizedAttributeType>::
evaluateSynthesizedAttribute(SgNode* astNode,
        DummyAttribute inheritedValue,
        SynthesizedAttributesList l)
{
    return evaluateSynthesizedAttribute(astNode, l);
}





// MS: 04/25/02
template <class SynthesizedAttributeType>
SynthesizedAttributeType AstBottomUpProcessing<SynthesizedAttributeType>::
traverse(SgNode* node)
{

    static DummyAttribute da;
    return SgTreeTraversal<DummyAttribute, SynthesizedAttributeType>
        ::traverse(node, da, postorder);

}

// MS: 04/25/02
template <class SynthesizedAttributeType>
SynthesizedAttributeType AstBottomUpProcessing<SynthesizedAttributeType>::
traverseWithinFile(SgNode* node)
{
    static DummyAttribute da;
    return SgTreeTraversal<DummyAttribute, SynthesizedAttributeType>::traverseWithinFile(node, da, postorder);
}



// MS: 04/25/02
template <class SynthesizedAttributeType>
void AstBottomUpProcessing<SynthesizedAttributeType>::
traverseInputFiles(SgProject* projectNode)
{
    static DummyAttribute da;
    // GB (8/6/2007): This is now a postorder traversal; this did not really
    // matter until now, but now evaluateSynthesizedAttribute is only called
    // for traversals that have the postorder bit set.
    SgTreeTraversal<DummyAttribute, SynthesizedAttributeType>
        ::traverseInputFiles(projectNode, da, postorder);
}
#ifdef _MSC_VER
//class BooleanQueryInheritedAttributeType;
#include "../astQuery/booleanQuery.h"
#include "../astQuery/booleanQueryInheritedAttribute.h"
#endif
// MS: 07/29/04
template <class InheritedAttributeType, class SynthesizedAttributeType>
SynthesizedAttributeType SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
defaultSynthesizedAttribute(InheritedAttributeType inh)
{
    // we provide 'inh' but do not use it in the constructor of 's' to allow primitive types
    SynthesizedAttributeType s = SynthesizedAttributeType(); 
    return s;
}

// MS: 09/30/02
template <class InheritedAttributeType, class SynthesizedAttributeType>
SynthesizedAttributeType
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
traverseWithinFile(SgNode* node,
        InheritedAttributeType inheritedValue,
        t_traverseOrder treeTraversalOrder)
{
  // DQ (1/18/2006): debugging
     ROSE_ASSERT(this != NULL);
     traversalConstraint = true;

     SgFile* filenode = isSgFile(node);
     ROSE_ASSERT(filenode != NULL); // this function will be extended to work with all nodes soon

     // GB (05/30/2007): changed to a SgFile* instead of a file name,
     // comparisons are much cheaper this way
     fileToVisit = filenode;

     ROSE_ASSERT(SgTreeTraversal_inFileToTraverse(node, traversalConstraint, fileToVisit) == true);
     
     SynthesizedAttributeType synth = traverse(node, inheritedValue, treeTraversalOrder);
     traversalConstraint = false;
     return synth;
}




// GB (06/31/2007): Wrapper function around the performT
//raversal()
// function that does the real work; when that function is done, we call
// traversalResult() to get the final result off the stack of synthesized
// attributes.
/*
template <class InheritedAttributeType>
DummyAttribute
AstTopDownProcessing<InheritedAttributeType>::
defaultSynthesizedAttribute(InheritedAttributeType inh)
{arentset.begin(); i != parentset.end(); i++) {
     map<SgGraphNode*, InheritedAttribute
    // called but not used
    DummyAttribute a = defaultDummyAttribute;
    return a;
}
*/
template <class InheritedAttributeType, class SynthesizedAttributeType>
SynthesizedAttributeType SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
traverse(SgNode *node, InheritedAttributeType inheritedValue,
        t_traverseOrder treeTraversalOrder)
{
    // make sure the stack is empty
    synthesizedAttributes->resetStack();
    ROSE_ASSERT(synthesizedAttributes->debugSize() == 0);

    // notify the concrete traversal class that a traversal is starting
    atTraversalStart();

    // perform the actual traversal
    performTraversal(node, inheritedValue, treeTraversalOrder);

    // notify the traversal that we are done
    atTraversalEnd();

    // get the result off the stack
    return traversalResult();
}

template<class InheritedAttributeType, class SynthesizedAttributeType>
InheritedAttributeType
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
solveInheritedAttribute(SgGraphNode* child, std::set<SgGraphNode*> parentset, SgIncidenceDirectedGraph* g,
        InheritedAttributeType inheritedValue, InheritedAttributeType nullInherit, int graphTraversal, std::set<SgGraphNode*> traversedlocal, std::set<SgGraphNode*> traversedreverse, bool loop, bool inloop, SgGraphNode* endnode)
{

/* testing whether or not we have traversed the node before while trying to calculate it's value. 
If it has been traversed then we are in a loop, and need to set the loop boolean to true */
  if (traversedreverse.find(child) != traversedreverse.end()) {
      //cout << "in loop" << endl;
      loop = true;
  }
/* otherwise we need to insert the child node into traversedreverse so that it can be used to
detect if we run into a loop later */
  else {
      traversedreverse.insert(child);
      loop = false;
  }
/* This test checks to make sure we need to traverse the parents at all. It may be that the node has
already been calculated, in which case we don't need to visit the node */
  if (graphnodeinheritedmap.find(child) != graphnodeinheritedmap.end()) {
      //cout << "child already explored" << endl;
      return graphnodeinheritedmap[child];
  }

      
       
  /* These variables are to setup two sets. One for those nodes that are in a loop, and one for those which are
not. */
  std::set<SgGraphNode*> noloopnodes;
  std::set<SgGraphNode*> loopnodes;
  std::vector<InheritedAttributeType> inheritedAttributeSet;
  std::vector<InheritedAttributeType> loopInheritedAttributeSet;
  //bool end = false;
/* proxyloopnode is used to create a node whose parents are the nodes that were classified as loopnodes */
   SgGraphNode* proxyloopnode = new SgGraphNode;
/* Here we iterate through the parent set, checking if loop is true and if the node is inside traversedreverse. If both are true we
attach this node to the set of loop nodes*/
   for (std::set<SgGraphNode*>::iterator i = parentset.begin(); i != parentset.end(); i++) {
     if (loop == true) {
     if (traversedreverse.find(*i) != traversedreverse.end()) {
         loopnodes.insert(*i);
     }
     else {
          noloopnodes.insert(*i);
     }
     }

         
         
     SgGraphNode* tofind = *i;
     ROSE_ASSERT(*i != NULL);
     //noloopnodes.insert(tofind);
     ROSE_ASSERT(isSgGraphNode(tofind));
/* The reason for using the unordered_map is that if the map is ordered we have to define a preorder on InheritedAttributeType. This
is not easily generically done, so unordered_map is used to avoid this problem and still get the answer we need */
     typename boost::unordered_map<SgGraphNode*, InheritedAttributeType, boost::hash<SgGraphNode*>, compareSgGraphNode>::const_iterator it;
     typename boost::unordered_map<SgGraphNode*, InheritedAttributeType, boost::hash<SgGraphNode*>, compareSgGraphNode>::const_iterator it2; 
     //it = graphnodeinheritedmap.find(tofind);
     //it2 = graphnodeinheritedmaploop.find(tofind);
     
/* This section is used to compute the node inheritedAttribute values for the parents of the node we want to solve. Once we have collected
these we can collect the parent values into a vector of inheritedAttributes (we use a vector for the same reason we use an unordered_map,
otherwise a preorder must be defined and, as stated earlier, this is not an easy problem to solve, nor is it helpful */
     std::set<SgGraphNode*> parentsetnew;
     if (graphnodeinheritedmap.find(*i) != graphnodeinheritedmap.end()) {
         /* Checking to see if the parent has already been traversed and thus is already calculated. */
         //cout << "parent has already been traversed!" << endl;
         inheritedAttributeSet.push_back(graphnodeinheritedmap[*i]);
     }
     else {
     std::set<SgDirectedGraphEdge*> edgeset2 = g->computeEdgeSetIn(tofind);
     /* Calculating the in edges for our parent to compute it from the values of its parents */
     for (std::set<SgDirectedGraphEdge*>::iterator r = edgeset2.begin(); r != edgeset2.end(); r++) {
           SgGraphNode* gn = (*r)->get_from();
           if (loop == false || (loop == true && loopnodes.find(tofind) == loopnodes.end())) {
           //if (child != gn) {
           //cout << "inserting grandparent" << endl;
           parentsetnew.insert(gn);
      //     }
           }
      if (parentsetnew.size() != 0) {
      //Checking to see if the parent is already computed...
      if (graphnodeinheritedmap.find(tofind) == graphnodeinheritedmap.end()) {
      /* Solving the inherited Attribute */
      InheritedAttributeType inh = solveInheritedAttribute(tofind, parentsetnew, g, inheritedValue, nullInherit, graphTraversal, traversedlocal, traversedreverse, false, inloop, endnode);
      graphnodeinheritedmap[tofind] = inh;
      //graphnodeinheritedmaploop[tofind] = inh;
      inheritedAttributeSet.push_back(inh);
     }
     }
     }
     }
     }
     //ROSE_ASSERT(inheritedAttributeSet.size() != 0);
     /* Solving the inheritedAttribute with the user defined function */
     InheritedAttributeType noLoopAtt = evaluateInheritedAttribute(child, inheritedAttributeSet, false);
     graphnodeinheritedmap[child] = noLoopAtt; //Attaching the attribute to the node via our map
     // Checking if we're in a loop.
     if (loop == true) {
     //cout << "In a loop" << endl;
     std::set<SgGraphNode*> loopparentset;
     //Creating a proxy node that has all the loop nodes coming into child, but none of it's children so as to avoid a loop.
     for (std::set<SgGraphNode*>::iterator it = loopnodes.begin(); it != loopnodes.end(); it++) {
           g->addDirectedEdge(*it, proxyloopnode);
     }
     //traversedreverse.clear();
     //Solving the value at the loop, storing in a separate map.
     InheritedAttributeType inhe = solveInheritedAttribute(proxyloopnode, loopnodes, g, inheritedValue, nullInherit, graphTraversal, traversedlocal, traversedreverse, false, true, child);
     graphnodeinheritedmaploop[child] = inhe;
     }
}
 
 

template<class InheritedAttributeType, class SynthesizedAttributeType>
void
SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
performTraversal(SgGraphNode* node, SgIncidenceDirectedGraph* g, InheritedAttributeType inheritedValue, InheritedAttributeType nullInherit, int graphTraversal, std::set<SgGraphNode*> traversedlocal, std::set<SgGraphNode*> traversedreverse, bool loop)
   {
    /* The graph traversal mechanism utilizes this function with helper function solveInheritedAttribute. This mechanism goes depth first through a graph, sends the node to the helper function to solve the
    inheritedAttribute, then solves the synthesized attribute itself. the graphTraversal integer specifies what should be calculated.

   0 -> InheritedAttribute Only (corresponds to INHERITED)
   1 -> SynthesizedAttribute Only (corresponds to SYNTHESIZED)
   2 -> Both (corresponds to BOTH)
   */
    //cout << "performing traversal" << endl;
    ROSE_ASSERT(g != NULL);
    ROSE_ASSERT(node != NULL);
    ROSE_ASSERT(isSgNode(node));
    //cout << "I am a: " << node->class_name() << endl;
    ROSE_ASSERT(isSgGraphNode(node));
/* Incidence Directed Graph traversal utilizes get_target() to traverse the graph. We hold the
visited nodes in traversed. In a std set you can check membership by using find and then if 
this returns the traversed.end() we know that the node is not a member of the set. Otherwise
it will return a pointer to the lnode in which case we can not traverse farther down that path */
     if (traversed.find(node) == traversed.end()) {
         
     traversed.insert(node);
     //cout << "passed the if" << endl;
     std::set<SgDirectedGraphEdge*> edgeset2 = g->computeEdgeSetIn(node);
     if (edgeset2.size() == 0) {
         graphnodeinheritedmap[node] = inheritedValue;
     }
     std::set<SgGraphNode*> parentset;
     for (std::set<SgDirectedGraphEdge*>::iterator r = edgeset2.begin(); r != edgeset2.end(); r++) {
        SgGraphNode* gn = (*r)->get_from();
        parentset.insert(gn);
     }
     //cout << "size of parentset:" << parentset.size() << endl;
     if (graphTraversal == INHERITED || graphTraversal == BOTH) {
        if (graphnodeinheritedmap.find(node) == graphnodeinheritedmap.end()) {
            if (node != NULL) {
            //traversedreverse.clear();
            InheritedAttributeType inheritedValue2;
            inheritedValue2 = solveInheritedAttribute(node, parentset, g, inheritedValue, nullInherit, graphTraversal, traversedlocal, traversedreverse, false);
            
            graphnodeinheritedmap[node] = inheritedValue2;
            }
       // cout << "set inherited value: " << endl;
        }
     }

     /*
     for (set<SgGraphNode*>::iterator k = parentset.begin(); k != parentset.end(); k++) {
        
        graphnodeinheritedmap[*k] = inheritedValue;
     }
     */
     ROSE_ASSERT(g != NULL);
     ROSE_ASSERT(isSgIncidenceDirectedGraph(g));
     ROSE_ASSERT(isSgGraphNode(node));
     if (node != NULL) {
     //cout << "node is a: " << node->class_name() << endl;
     std::set<SgDirectedGraphEdge*> edgeset = g->computeEdgeSetOut(node);
     std::set<SgGraphNode*> successorset;
     std::set<SgGraphNode*> successorset2;
     std::set<SgDirectedGraphEdge*>::iterator i;
     std::set<SgDirectedGraphEdge*>::iterator j;
     	
     for (i = edgeset.begin(); i != edgeset.end(); i++) {
        if (traversed.find((*i)->get_to()) == traversed.end()) {				
        successorset.insert((*i)->get_to());
        }
        else {
        //cout << "node already traversed" << endl;
        }
     }
     
        
     //cout << "successors:" << successorset.size() << endl;
     std::set<SgGraphNode*> trueSuccessors;
     //cout << "starting tree descension" << endl;          
     for (std::set<SgGraphNode*>::iterator it = successorset.begin(); it != successorset.end(); it++) {
        SgGraphNode *child = NULL;
        child = (*it);
        if (child != NULL) {
        //      cout << "Child is not null" << endl;
         
	      if (traversed.find(child) == traversed.end() /*& traversed2.find(child) == traversed2.end()*/ ) {
          //        cout << "performing traversal" << endl;
		  performTraversal(child, g, inheritedValue, nullInherit, graphTraversal, traversedlocal, traversedreverse, false);
		  
//                   if (traversedlocal.find(node) == traversedlocal.end()) {
//                      trav
              }
//                   }
         }
//	      else {
 //               traversedlocal.insert(child);
//	      }
              
         else {
	   
           if (graphTraversal == BOTH || graphTraversal == SYNTHESIZED) {
                synthesizedAttributes->push(defaultSynthesizedAttribute(inheritedValue));
           }
         }
         }
     //cout << "completed descension" << endl;
     //cout << "completed descension" << endl;
     size_t numberOfSuccessors = successorset.size();
     //cout << "numberOfSuccessors:" << numberOfSuccessors << endl;
     if (graphTraversal == SYNTHESIZED || graphTraversal == BOTH) {
       //cout << "in postorder if" << endl;
       // Now that every child's synthesized attributes are on the stack:
       // Tell the stack how big the stack frame containing those
       // attributes is to be, and pass that frame to
       // evaluateSynthesizedAttribute(); then replace those results by
       // pushing the computed value onto the stack (which pops off the
       // previous stack frame).
       synthesizedAttributes->setFrameSize(numberOfSuccessors);
       ROSE_ASSERT(synthesizedAttributes->size() == numberOfSuccessors);
       //cout << "right before synth" << endl;
       synthesizedAttributes->push(evaluateSynthesizedAttribute(node, inheritedValue, *synthesizedAttributes));
       }
     }
     else {
          return;
     }
     }
     else {
          return;
     }
}


template<class InheritedAttributeType, class SynthesizedAttributeType>
void
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
performTraversal(SgNode* node,
        InheritedAttributeType inheritedValue,
        t_traverseOrder treeTraversalOrder)
   {
    //cout << "In SgNode version" << endl;
  // 1. node can be a null pointer, only traverse it if !

  //    (since the SuccessorContainer is order preserving we require 0 values as well!)
  // 2. inFileToTraverse is false if we are trying to go to a different file (than the input file)
  //    and only if traverseInputFiles was invoked, otherwise it's always true

     if (node && SgTreeTraversal_inFileToTraverse(node, traversalConstraint, fileToVisit))
        {
       // In case of a preorder traversal call the function to be applied to each node of the AST
       // GB (7/6/2007): Because AstPrePostProcessing was introduced, a
       // treeTraversalOrder can now be pre *and* post at the same time! The
       // == comparison was therefore replaced by a bit mask check.
          if (treeTraversalOrder & preorder)
               inheritedValue = evaluateInheritedAttribute(node, inheritedValue);
  
       // Visit the traversable data members of this AST node.
       // GB (09/25/2007): Added support for index-based traversals. The useDefaultIndexBasedTraversal flag tells us
       // whether to use successor containers or direct index-based access to the node's successors.
          AstSuccessorsSelectors::SuccessorsContainer succContainer;
          size_t numberOfSuccessors;
          if (!useDefaultIndexBasedTraversal)
             {
               setNodeSuccessors(node, succContainer);
               numberOfSuccessors = succContainer.size();
             }
            else
             {
               numberOfSuccessors = node->get_numberOfTraversalSuccessors();
             }

          for (size_t idx = 0; idx < numberOfSuccessors; idx++)
             {
               SgNode *child = NULL;

               if (useDefaultIndexBasedTraversal)
                  {
                 // ROSE_ASSERT(node->get_traversalSuccessorByIndex(idx) != NULL || node->get_traversalSuccessorByIndex(idx) == NULL);
                    child = node->get_traversalSuccessorByIndex(idx);
                  }
                 else
                  {
                 // ROSE_ASSERT(succContainer[idx] != NULL || succContainer[idx] == NULL);
                    child = succContainer[idx];
                  }

               if (child != NULL)
                  {
		
	   	    
		   
                    	performTraversal(child, inheritedValue, treeTraversalOrder);
		    	
		
	           
		//ENDEDIT
                   }
                 else
                  {
                 // null pointer (not traversed): we put the default value(s) of SynthesizedAttribute onto the stack
                    if (treeTraversalOrder & postorder)
                         synthesizedAttributes->push(defaultSynthesizedAttribute(inheritedValue));
                  }
             }
 
       // In case of a postorder traversal call the function to be applied to each node of the AST
       // GB (7/6/2007): Because AstPrePostProcessing was introduced, a
       // treeTraversalOrder can now be pre *and* post at the same time! The
       // == comparison was therefore replaced by a bit mask check.
       // The call to evaluateInheritedAttribute at this point also had to be
       // changed; it was never elegant anyway as we were not really
       // evaluating attributes here.
          if (treeTraversalOrder & postorder)
             {
            // Now that every child's synthesized attributes are on the stack:
            // Tell the stack how big the stack frame containing those
            // attributes is to be, and pass that frame to
            // evaluateSynthesizedAttribute(); then replace those results by
            // pushing the computed value onto the stack (which pops off the
            // previous stack frame).
               synthesizedAttributes->setFrameSize(numberOfSuccessors);
               ROSE_ASSERT(synthesizedAttributes->size() == numberOfSuccessors);
               synthesizedAttributes->push(evaluateSynthesizedAttribute(node, inheritedValue, *synthesizedAttributes));
             }
        }
       else // if (node && inFileToTraverse(node))
        {
          if (treeTraversalOrder & postorder)
               synthesizedAttributes->push(defaultSynthesizedAttribute(inheritedValue));
        }
       } // function body

// GB (05/30/2007)
template <class InheritedAttributeType, class SynthesizedAttributeType>
SynthesizedAttributeType SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
traversalResult()
{
    // If the stack of synthesizedAttributes contains exactly one object, then
    // that one is the valid final result of the computation, so we should
    // return it. Otherwise, either there are no objects on the stack (because
    // the traversal didn't use any attributes), or there are more than one
    // (usually because the traversal exited prematurely by throwing an
    // exception); in this case, just return a default attribute.
    if (synthesizedAttributes->debugSize() == 1)
    {
        return synthesizedAttributes->pop();
    }
    else
    {
        static SynthesizedAttributeType sa;
        return sa;
    }
}

template <class InheritedAttributeType, class SynthesizedAttributeType>
SynthesizedAttributeType SgGraphTraversal<InheritedAttributeType, SynthesizedAttributeType>::
traversalResult()
{
    // If the stack of synthesizedAttributes contains exactly one object, then
    // that one is the valid final result of the computation, so we should
    // return it. Otherwise, either there are no objects on the stack (because
    // the traversal didn't use any attributes), or there are more than one
    // (usually because the traversal exited prematurely by throwing an
    // exception); in this case, just return a default attribute.
    if (synthesizedAttributes->debugSize() == 1)
    {
        return synthesizedAttributes->pop();
    }
    else
    {
        static SynthesizedAttributeType sa;
        return sa;
    }
}

// GB (05/30/2007)
template <class InheritedAttributeType, class SynthesizedAttributeType>
void
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
atTraversalStart()
{
}

template <class InheritedAttributeType, class SynthesizedAttributeType>
void
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
atTraversalEnd()
{
}
/*
template <class InheritedAttributeType, class SynthesizedAttributeType>
void
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::
afterSingleTraversal()
{
}

template <class InheritedAttributeType, class SynthesizedAttributeType>
void
SgTreeTraversal<InheritedAttributeType, SynthesizedAttributeType>::

beforeSingleTraversal()
{
}
*/

template <class InheritedAttributeType, class SynthesizedAttributeType>
void
AstTopDownBottomUpProcessing<InheritedAttributeType, SynthesizedAttributeType>::
atTraversalStart()
{
}

template <class InheritedAttributeType, class SynthesizedAttributeType>
void
AstTopDownBottomUpProcessing<InheritedAttributeType, SynthesizedAttributeType>::
atTraversalEnd()
{
}

template <class InheritedAttributeType>
void
AstTopDownProcessing<InheritedAttributeType>::
destroyInheritedValue(SgNode*, InheritedAttributeType)
{
}

template <class InheritedAttributeType>
void
AstTopDownProcessing<InheritedAttributeType>::
atTraversalStart()
{
}

template <class InheritedAttributeType>
void
AstTopDownProcessing<InheritedAttributeType>::
atTraversalEnd()
{
}

template <class SynthesizedAttributeType>
void
AstBottomUpProcessing<SynthesizedAttributeType>::
atTraversalStart()
{
}

template <class SynthesizedAttributeType>
void
AstBottomUpProcessing<SynthesizedAttributeType>::
atTraversalEnd()
{
}
// #endif 

#include "AstSimpleProcessing.h" // that's a non-templated class which is put in a different file (for gcc to compile&link properly)

#include "AstCombinedProcessing.h"

// DQ (3/20/2009): Wrap this in a test to make sure that Cygwin is not being used.
// This causes a problem:
//      error: there are no arguments to �cvLoadImage� that depend on a template parameter, so a declaration of <function name> must be available
// which requires:
//      -fpermissive to compile without error (and then it generates a lot of warnings).
#if !_MSC_VER
  #include "AstSharedMemoryParallelProcessing.h"
#endif

#endif
