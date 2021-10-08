#ifndef ESTATE_H
#define ESTATE_H

#define NO_ESTATE -4

#include <string>
#include <set>
#include <map>
#include <utility>
#include "Labeler.h"
#include "CFAnalysis.h"
#include "AbstractValue.h"
#include "VariableIdMapping.h"

#include "PState.h"
#include "InputOutput.h"
#include "CallString.h"

using namespace CodeThorn;

typedef int EStateId;

#include "HashFun.h"
#include "HSetMaintainer.h"
#include "PropertyState.h"

namespace CodeThorn {

  class VariableValueMonitor;
  class CTAnalysis;

/*! 
  * \author Markus Schordan
  * \date 2012.
 */

  typedef const CodeThorn::PState* PStatePtr;

  //#define NO_ESTATE_PSTATE_MEM_COPY
  
  class EState : public Lattice {
  public:
    EState();
    EState(Label label, PStatePtr pstate):_label(label),_pstate(pstate) {}
    EState(Label label, PStatePtr pstate, CodeThorn::InputOutput io):_label(label),_pstate(pstate),io(io){}
    EState(Label label, CallString cs, PStatePtr pstate, CodeThorn::InputOutput io):_label(label),_pstate(pstate),io(io),callString(cs) {}
    ~EState();
    #ifndef NO_ESTATE_PSTATE_MEM_COPY
    EState(const EState &other); // copy constructor
    EState& operator=(const EState &other); // assignment operator
    #endif
    
    std::string toString() const;
    std::string toString(CodeThorn::VariableIdMapping* variableIdMapping) const;
    std::string toHTML() const; /// multi-line version for dot output
    std::string labelString() const;
    long memorySize() const;
    
    void setLabel(Label lab) { _label=lab; }
    Label label() const { return _label; }
    void setPState(PStatePtr pstate) { _pstate=pstate; }
    //void setIO(CodeThorn::InputOutput io) { io=io;} TODO: investigate
    PStatePtr pstate() const { return _pstate; }
    CodeThorn::InputOutput::OpType ioOp() const;
    // isBot():no value, isTop(): any value (not unique), isConstInt():one concrete integer (int getIntValue())
    AbstractValue determineUniqueIOValue() const;
    /* Predicate that determines whether all variables can be determined to be bound to a constant value.
       This function uses the entire PState to determine constness.
    */
    bool isConst(CodeThorn::VariableIdMapping* vid) const;
    bool isRersTopified(CodeThorn::VariableIdMapping* vid) const;
    std::string predicateToString(CodeThorn::VariableIdMapping* vid) const;
    std::string programPosToString(Labeler* labeler) const;

    // uses isApproximatedBy of PState
    bool isApproximatedBy(const CodeThorn::EState* other) const;

    // required for PropertyState class
    bool isBot() const; 
    bool approximatedBy(PropertyState& other) const;
    void combine(PropertyState& other);
    
  private:
    Label _label;
    PStatePtr _pstate;
  public:
    static bool sharedPStates;
    CodeThorn::InputOutput io;
    void setCallString(CallString cs);
    CallString getCallString() const;
    size_t getCallStringLength() const;
    CallString callString;
    
  };

  // define order for EState elements (necessary for EStateSet)
  bool operator==(const EState& c1, const EState& c2);
  bool operator!=(const EState& c1, const EState& c2);

#if 1
  bool operator<(const EState& c1, const EState& c2);
  struct EStateLessComp {
    bool operator()(const EState& c1, const EState& c2) {
      return c1<c2;
    }
  };
#endif
  
  /*! 
   * \author Markus Schordan
   * \date 2012.
   */
class EStateHashFun {
 public:
  EStateHashFun() {}
  long operator()(EState* s) const {
    unsigned int hash=1;
    if(EState::sharedPStates) {
      hash=(long)s->label().getId()*(((long)s->pstate())+1);
    } else {
      long pstateHash=1;
      PStatePtr pstateptr=s->pstate(); // const
      if(pstateptr!=nullptr) {
	PState* pstate=const_cast<PState*>(pstateptr); // non-const
	PStateHashFun pstateHashFun;
	pstateHash=pstateHashFun(pstate);
      }
      hash=(long)s->label().getId()*(pstateHash+1);
    }
    return long(hash);
  }
 private:
};
 class EStateEqualToPred {
 public:
   EStateEqualToPred() {}
   long operator()(EState* s1, EState* s2) const {
     return *s1==*s2;
   }
 private:
 };
 /*! 
  * \author Markus Schordan
  * \date 2012.
  */
 class EStateSet : public HSetMaintainer<EState,EStateHashFun,EStateEqualToPred> {
 public:
 EStateSet():HSetMaintainer<EState,EStateHashFun,EStateEqualToPred>(){}
 public:
   typedef HSetMaintainer<EState,EStateHashFun,EStateEqualToPred>::ProcessingResult ProcessingResult;
   std::string toString(CodeThorn::VariableIdMapping* variableIdMapping=0) const;
   EStateId estateId(const EState* estate) const;
   EStateId estateId(const EState estate) const;
   std::string estateIdString(const EState* estate) const;
   int numberOfIoTypeEStates(CodeThorn::InputOutput::OpType) const;
   int numberOfConstEStates(CodeThorn::VariableIdMapping* vid) const;
 private:
 };
 
 class EStateList : public std::list<EState> {
 public:
   std::string toString();
 };
 
} // namespace CodeThorn

#endif
