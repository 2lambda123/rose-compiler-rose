#include <featureTests.h>
#ifdef ROSE_ENABLE_SOURCE_ANALYSIS

#ifndef PARTITIONED_ANALYSIS_H
#define PARTITIONED_ANALYSIS_H

#include <sage3.h>

#include "genericDataflowCommon.h"
#include "variables.h"
#include "cfgUtils.h"
#include "analysisCommon.h"
#include "functionState.h"
#include "latticeFull.h"
#include "analysis.h"
#include "dataflow.h"
#include "VirtualCFGIterator.h"
#include "LogicalCond.h"
#include "printAnalysisStates.h"

#include <list>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class IntraPartitionDataflow;
class IntraPartitionDataflowCheckpoint;

// Set of partition dataflow analyses that were split in a given call to split.
// The original analysis that was split is explicitly identified as the "master" of the split.
class partSplit
{
        public:
        std::set<IntraPartitionDataflow*> splitSet;
        IntraPartitionDataflow* master;
        
        partSplit(IntraPartitionDataflow* master)
        {
                this->master = master;
                splitSet.insert(master);
        }
        
        void addChild(IntraPartitionDataflow* child)
        {
                splitSet.insert(child);
        }
        
        std::string str(std::string indent="")
        {
          std::ostringstream oss;
                
                oss << indent << "[partSplit:\n";
                oss << indent << "    splitSet = <";
                for(std::set<IntraPartitionDataflow*>::iterator it=splitSet.begin(); it!=splitSet.end(); )
                {
                        oss << (*it);
                        it++;
                        if(it!=splitSet.end()) oss << ", ";
                }
                oss << ">\n";
                oss << indent << "    master = "<< master << "]\n";

                return oss.str();
        }
};

class PartitionedAnalysis : virtual public IntraProceduralAnalysis
{
        // the partitions that are currently executing
        std::set<IntraPartitionDataflow*> activeParts;
        // the set of partitions that are currently blocked and need to be explicitly
        // unblocked before they may resume execution
        //std::set<IntraPartitionDataflow*> blockedParts;
        // the set of partitions that have called join and are simply waiting to be joined
        // to the master partitions that they split from
        std::set<IntraPartitionDataflow*> joinParts;
        
        // Maps partitions to their respective splits. A given partition may be split
        // multiple times in a hierarchical fashion (split-join). The first split
        // in the list corresponds to the outer-most split and the last split
        // is the inner-most split. Thus, if a given partition performs a join,
        // the jointed split is the last/inner-most split in parts2splits.
        std::map<IntraPartitionDataflow*, std::list<partSplit*> > parts2splits;
        
        // Maps analysis partitions to their respective current execution states
        // (these are only upto-date for analyses that are currently stopped)
        std::map<IntraPartitionDataflow*, IntraPartitionDataflowCheckpoint*> parts2chkpts;
        
        // Sample interprocedural analysis object that we'll use as a factory to create more such objects
        IntraPartitionDataflow* intraFactory;
        
        public:
        // Creates a PartitionedAnalysis, starting the analysis with the given
        // master analysis partition and creating an initial split that only contains the master.
        PartitionedAnalysis(IntraPartitionDataflow* intraFactory);
        
        // Create the initial partition state for analyzing some function
        void initMaster();
        
        // Returns a reference to the master dataflow analysis. At the end of the partitioned analysis,
        // it is this object that owns all the dataflow state generated by the overall analysis.
        IntraPartitionDataflow* getMasterDFAnalysis();
        
        // Activates the given partition, returning true if it was previously inactive and false otherwise.
        bool activatePart(IntraPartitionDataflow* part);
        
        // Splits the given dataflow analysis partition into several partitions, one for each given checkpoint
        // The partition origA will be assigned the last checkpoint in partitionChkpts.
        // If newSplit==true, this split operation creates a new split within origA's current split and place
        //    the newly-generated partitions into this split. 
        // If newSplit==false, the newly-generated partitions will be added to origA's current split.
        // If newPartActive==true, the newly-generated partitions will be made initially active. If not,
        //    they will start out in joined status.
        // Returns the set of newly-created partitions.
        std::set<IntraPartitionDataflow*> split(IntraPartitionDataflow* origA, std::vector<IntraPartitionDataflowCheckpoint*> partitionChkpts,
                                           const Function& func, NodeState* fState, bool newSplit, bool newPartActive);
        
        // Joins all the analysis partitions in a given split into a single partition, unioning
        // their respective dataflow information
        void join(IntraPartitionDataflow* joinA, IntraPartitionDataflowCheckpoint* chkpt,
                  const Function& func, NodeState* fState);
        
        // Called by the base PartitionedAnalysis class when all partitions in a given split have decided 
        //    to join to decide whether they should be joined or all released. It may also do some 
        //    processing of their state prior to the release or join.
        // Returns the set of partitions that will remain in joined status after this join. If all partitions in the split
        //    set are on this list, they are all joined(all but one will be deleted). Any remaining partitions will be released.
        virtual std::set<IntraPartitionDataflow*> preJoin(partSplit* s, const Function& func, NodeState* fState,
                                                     const std::map<IntraPartitionDataflow*, 
                                                     IntraPartitionDataflowCheckpoint*>& parts2chkpts)=0;
        
        // Called by the base PartitionedAnalysis class when all partitions in a given split have 
        //    finished their respective executions.
        virtual void postFinish(partSplit* s, 
                                const std::map<IntraPartitionDataflow*, IntraPartitionDataflowCheckpoint*>& parts2chkpts)=0;
        
        // runs the intra-procedural analysis on the given function, returns true if 
        // the function's NodeState gets modified as a result and false otherwise
        // state - the function's NodeState
        bool runAnalysis(const Function& func, NodeState* state);
};

// Given a source analysis, splits the dataflow states of all the CFG nodes in
// a given function so that the target analysis gets copies of the source analysis'
// state.
class partitionDFAnalysisState: virtual public UnstructuredPassIntraAnalysis
{
        Analysis* srcAnalysis;
        Analysis* tgtAnalysis;
        
        public:
        partitionDFAnalysisState(Analysis* srcAnalysis, Analysis* tgtAnalysis)
        {
                this->srcAnalysis = srcAnalysis;
                this->tgtAnalysis = tgtAnalysis;
        }
        
        void visit(const Function &/*func*/, const DataflowNode &/*n*/, NodeState &state)
        {
                state.cloneAnalysisState(srcAnalysis, tgtAnalysis);
        }
};

// Given a set of analyses, one of which is designated as a master, unions together the 
// dataflow states associated on each CFG node with each of these analyses.
// The results are associated on each CFG node with the master analysis.
class unionDFAnalysisStatePartitions: virtual public UnstructuredPassIntraAnalysis
{
        std::set<Analysis*> unionSet;
        Analysis* master;
        
        public:
        unionDFAnalysisStatePartitions(
                std::set<Analysis*>& unionSet, Analysis* master)
        {
                for(std::set<Analysis*>::iterator it = unionSet.begin(); it!=unionSet.end(); it++)
                { this->unionSet.insert(*it); }
                //this->unionSet = unionSet;
                this->master = master;
        }
        
        void visit(const Function& func, const DataflowNode& n, NodeState& state);
};

// Deletes all the state associated with the given analyses
class deleteDFAnalysisState: virtual public UnstructuredPassIntraAnalysis
{
        std::set<IntraPartitionDataflow*> tgtA;
        
        public:
        deleteDFAnalysisState(std::set<IntraPartitionDataflow*>& tgtA)
        {
                this->tgtA = tgtA;
        }
        
        void visit(const Function &/*func*/, const DataflowNode &/*n*/, NodeState &state)
        {
                for(std::set<IntraPartitionDataflow*>::iterator it = tgtA.begin(); it!=tgtA.end(); it++)
                        state.deleteState((Analysis*)*it);
        }
};


class IntraPartitionDataflow : virtual public IntraProceduralDataflow
{
        protected:
        PartitionedAnalysis* parent;
        
        public:
        // The logic expression that describes the invariant that holds for this partition      
        /*LogicalCond*/printable* partitionCond;
        
        IntraPartitionDataflow(const IntraPartitionDataflow& that)
        {
                parent = that.parent;
                partitionCond = that.partitionCond;
        }
        
        IntraPartitionDataflow(PartitionedAnalysis* parent)
        {
                this->parent = parent;
                partitionCond = NULL;
        }
        
        ~IntraPartitionDataflow()
        {
                delete partitionCond;
        }
        
        PartitionedAnalysis* getParent() const
        {
                return parent;  
        }
        
        // A dummy analysis that is associated with facts connected with the 
        // IntraPartitionDataflow-specific logic rather than the logic of a class that 
        // derives from IntraPartitionDataflow.
        // Analysis* dummy;
        
        // Creates a new instance of the derived object that is a copy of the original instance.
        // This instance will be used to instantiate a new partition of the analysis.
        virtual IntraPartitionDataflow* copy()=0;
        
        using IntraProceduralDataflow::runAnalysis;
        virtual bool runAnalysis(const Function& func, NodeState* fState, bool& splitPart, 
                                      bool &joinPart, IntraPartitionDataflowCheckpoint*& outChkpt) = 0;
        
        // Resumes the execution of runAnalysis from the given checkpoint
        // splitPart - set by the call to indicate that it exited because it was split
        // joinPart - set by the call to indicate that it exited because it wishes to join the partitions that it split from
        // outChkpt - set by the call to be the checkpoint that representing the state of this analysis at the time of the exit
        //            set to NULL in the case of a normal exit or a split exit
        virtual bool runAnalysisResume(const Function& func, NodeState* fState, 
                               IntraPartitionDataflowCheckpoint* chkpt, bool& splitPart, 
                               bool &joinPart, IntraPartitionDataflowCheckpoint*& outChkpt)=0;
        
        // Called when a partition is created to allow a specific analysis to initialize
        // its dataflow information from the partition condition
        virtual void initDFfromPartCond(const Function &, const DataflowNode &, NodeState &,
                                        const std::vector<Lattice*> &, const std::vector<NodeFact*> &,
                                        /*LogicalCond*/printable*) {
        }
};

class IntraPartitionDataflowCheckpoint
{
        public: 
        // A checkpoint of the dataflow state associated with the given state of the dataflow analysis
        dataflow::checkpoint dfChkpt;
        // Set of nodes that this analysis has blocked progress on until the next join point
        std::set<DataflowNode>    joinNodes;
        // The DataflowNode that that analysis was processing when the checkpoint was taken
        DataflowNode*        curNode;
        // The logical condition that is an invariant of all the states of the dataflow analysis
        /*LogicalCond*/printable*         partitionCond;
        // Given that the current node in the dataflow analysis has one or more successors, the index of 
        // the given node's successor
        int                  partitionIndex;
        
        // the arguments to runAnalysis() used as part of the dataflow pass
        const Function& func;
        NodeState* fState;
        
        IntraPartitionDataflowCheckpoint(IntraPartitionDataflowCheckpoint &that): 
                dfChkpt(that.dfChkpt), func(that.func)
        {
                this->joinNodes      = that.joinNodes;
                if(that.curNode)
                        this->curNode     = new DataflowNode(*(that.curNode));
                else
                        this->curNode     = NULL;
                
                this->partitionCond  = that.partitionCond;
                this->partitionIndex = that.partitionIndex;
                this->fState         = that.fState;
        }
        
        IntraPartitionDataflowCheckpoint(dataflow::checkpoint& dfChkpt, const std::set<DataflowNode>& joinNodes, 
                                         const DataflowNode* curNode,
                                         /*LogicalCond*/printable* partitionCond, int partitionIndex, 
                                         const Function& func, NodeState* fState) : 
                dfChkpt(dfChkpt), func(func)
        {
                this->joinNodes      = joinNodes;
                if(curNode)
                        this->curNode     = new DataflowNode(*curNode);
                else
                        this->curNode     = NULL;
                
                this->partitionCond  = partitionCond;
                this->partitionIndex = partitionIndex;
                this->fState         = fState;
        }
        
        ~IntraPartitionDataflowCheckpoint()
        {
                //delete partitionCond;
                if(curNode)
                        delete curNode;
        }
        
        std::string str(std::string indent="")
        {
          std::ostringstream outs;
                outs << indent << "[IntraPartitionDataflowCheckpoint : \n"; //fflush(stdout);
                outs << indent << "    dfChkpt = \n"<<dfChkpt.str(indent+"    ")<<"\n";
                if(curNode)
                        outs << indent << "    curNode = <"<<curNode->getNode()->class_name()<<" | "<<curNode->getNode()->unparseToString()<<" | "<< curNode->getIndex() << ">\n";
                else
                        outs << indent << "    curNode = NULL\n";
                
                if(joinNodes.size()==0)
        outs << indent << "    joinNodes = None\n";
      else
      {
        outs << indent << "    joinNodes = \n";
                        for(std::set<DataflowNode>::iterator it=joinNodes.begin(); it!=joinNodes.end(); it++)
                        { outs << indent << "        <"<<(*it).getNode()->class_name()<<" | "<<(*it).getNode()->unparseToString()<<">\n"; }
                }
                if(partitionCond)
                        outs << indent << "    partitionCond = \n"<<partitionCond->str(indent+"        ")<<"\n";

                if(partitionIndex>=0)
                        outs << indent << "    partitionIndex = descendant "<<partitionIndex<<"]";
                else
                        outs << indent << "    partitionIndex = all descendants ("<<partitionIndex<<")]";
                return outs.str();
        }
};

class IntraPartitionFWDataflow  : public virtual IntraPartitionDataflow
{
        public:
        IntraPartitionFWDataflow(PartitionedAnalysis* parent): IntraPartitionDataflow(parent)
        { }
        
        IntraPartitionFWDataflow(const IntraPartitionFWDataflow& that): 
                        IntraPartitionDataflow((const IntraPartitionDataflow&)that)
        {
        }
        
        /*IntraPartitionFWDataflow(): IntraPartitionDataflow()
        { }*/
        
        // the transfer function that is applied to every node
        // n - the dataflow node that is being processed
        // state - the NodeState object that describes the state of the node, as established by earlier 
        //         analysis passes
        // dfInfo - the Lattices that this transfer function operates on. The function takes these lattices
        //          as input and overwrites them with the result of the transfer.
        // splitAnalysis - set by callee to 
        //    - noSplit if the analysis does not want a split
        //    - splitNew if the analysis wants to perform a split and place the newly-generated partitions into
        //      a fresh split set that is nested inside this partition's current split
        //    - splitParent if the analysis wants to perform a split and place the newly-generated partitions 
        //      into this partition's current split (i.e. on the same split level as the current partition)
        typedef enum {noSplit, splitNew, splitParent} splitType;
        // splitConditions - if splitAnalysis==splitNew or ==splitParent, the analysis sets this vector to the conditions for all the 
        //                   descendant CFG nodes in the split
        /* // joinAnalysis - set to true if the analysis wants to perform a join */
        // joinNode - set to true if progress along the given dataflow node needs to be blocked until the next join point.
        //            If all paths of dataflow progress are blocked in this analysis, this is the same as the analysis 
        //            requesting to be joined.
        // Returns true if any of the input lattices changed as a result of the transfer function and
        //    false otherwise.
        virtual bool transfer(const Function& func, const DataflowNode& n, NodeState& state, const std::vector<Lattice*>& dfInfo, 
                              splitType& splitAnalysis, std::vector</*LogicalCond*/printable*>& splitConditions, /*bool& joinAnalysis, */bool& joinNode)=0;
        
        // Runs the intra-procedural analysis on the given function. Returns true if 
        // the function's NodeState gets modified as a result and false otherwise.
        // state - the function's NodeState
        bool runAnalysis(const Function& func, NodeState* fState, bool analyzeDueToCallers, std::set<Function> calleesUpdated);
        
        // Runs the intra-procedural analysis on the given function. 
        // Returns true if the function's NodeState gets modified as a result and false otherwise.
        // state - the function's NodeState
        bool runAnalysis(const Function& func, NodeState* fState,
                         bool& splitPart, bool &joinPart, IntraPartitionDataflowCheckpoint*& outChkpt);
        
        // Resumes the execution of runAnalysis from the given checkpoint
        bool runAnalysisResume(const Function& func, NodeState* fState, 
                               IntraPartitionDataflowCheckpoint* chkpt, bool& splitPart,
                               bool &joinPart, IntraPartitionDataflowCheckpoint*& outChkpt);
        
        typedef enum {retFalse, cont, normal} partitionTranferRet;

        partitionTranferRet partitionTranfer(
                                   const Function& func, NodeState* fState, const DataflowNode& n, NodeState* state, VirtualCFG::dataflow& dfIt,
                                   const std::vector<Lattice*>& dfInfoBelow, bool& splitPart, std::set<DataflowNode>& joinNodes, 
                                   IntraPartitionDataflowCheckpoint*& outChkpt);
        
        // propagates the forward dataflow info from the current node's NodeState (curNodeState) to the next node's 
        // NodeState (nextNodeState)
        bool propagateFWStateToNextNode(
             const std::vector<Lattice*>& curNodeState, DataflowNode curDFNode, int nodeIndex,
             const std::vector<Lattice*>& nextNodeState, DataflowNode nextDFNode);
};

#endif
#endif
