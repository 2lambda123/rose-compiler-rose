#ifndef STATIC_CFG_H 
#define STATIC_CFG_H 

#if 0
#include <AstInterface.h>
#include <GraphDotOutput.h>
#include <VirtualGraphCreate.h>
#endif
//#include <sage3basic.h>
//#include <rose.h>
#include "virtualCFG.h"
#include <map>
#include <set>
#include <string>


class SgIncidenceDirectedGraph;
class SgGraphNode;
class SgDirectedGraphEdge;


namespace StaticCFG 
{

using VirtualCFG::CFGNode;
using VirtualCFG::CFGEdge;


class CFG
{
    SgIncidenceDirectedGraph* graph_;
    std::map<CFGNode, SgGraphNode*> all_nodes_;
    std::set<CFGNode> explored_;
    SgNode* start_;

public:
    CFG() : graph_(NULL), start_(NULL) {}

    // The valid nodes are SgProject, SgStatement, SgExpression and SgInitializedName
    CFG(SgNode* node)
        : graph_(NULL), start_(node)
    {
        //buildCFG();
    }

    ~CFG() 
    { clearNodesAndEdges(); }

    // Set the start node for graph building. 
    // The valid nodes are SgProject, SgStatement, SgExpression and SgInitializedName
    void setStart(SgNode* node)
    { start_ = node; }

    // Build CFG for debugging.
    void buildCFG();
    // Build filtered CFG which only contains interesting nodes.
    void buildFilteredCFG();
    

    // The following four functions are for getting in/out edges of a given node.
    std::vector<SgDirectedGraphEdge*> getOutEdges(SgNode* node, int index);
    std::vector<SgDirectedGraphEdge*> getInEdges(SgNode* node, int index);

    std::vector<SgDirectedGraphEdge*> getOutEdges(SgGraphNode* node);
    std::vector<SgDirectedGraphEdge*> getInEdges(SgGraphNode* node);

    // Provide the same interface to get the beginning/end graph node for a SgNode
    SgGraphNode* cfgForBeginning(SgNode* node);
    SgGraphNode* cfgForEnd(SgNode* node);

    // Get the index of a CFG node.
    int getIndex(SgGraphNode* node);

    // Turn a graph node into a CFGNode which is defined in VirtualCFG namespace.
    CFGNode toCFGNode(SgGraphNode* node);

    // Output the graph to a DOT file.
    void cfgToDot(SgNode* node, const std::string& file_name)
    {
        std::ofstream ofile(file_name.c_str(), std::ios::out);
        ofile << "digraph defaultName {\n";
        std::set<SgGraphNode*> explored;
        processNodes(ofile, cfgForBeginning(node), explored);
        ofile << "}\n";
    }

private:
    void buildCFG(CFGNode n);
    template <class NodeT, class EdgeT>
    void buildCFG(NodeT n, std::map<NodeT, SgGraphNode*>& all_nodes, std::set<NodeT>& explored);
    void clearNodesAndEdges();

    void processNodes(std::ostream & o, SgGraphNode* n, std::set<SgGraphNode*>& explored);
    void printNodePlusEdges(std::ostream & o, SgGraphNode* node);
    void printNode(std::ostream & o, SgGraphNode* node);
    void printEdge(std::ostream & o, SgDirectedGraphEdge* edge, bool isInEdge);
};


// The following are some auxiliary functions, since SgGraphNode cannot provide them.

std::vector<SgDirectedGraphEdge*> outEdges(SgGraphNode* node);
std::vector<SgDirectedGraphEdge*> inEdges(SgGraphNode* node);

} // end of namespace StaticCFG

#endif
