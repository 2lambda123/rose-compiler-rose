#ifndef SOLVER17_H
#define SOLVER17_H


// CodeThorn includes
#include "Solver.h"
#include "EState.h"

namespace CodeThorn {

  class EState;
  
  class Solver17 : public Solver {
  public:
    Solver17();
    void run();
    int getId();

    static void initDiagnostics();
  private:
    void initializeSummaryStatesFromWorkList();
    // add Edge {(currentEStatePtr,e,NewEStatePtr)} to STS
    // if currentEStatePtr!=currentEStatePtr) then also add 
    //     (currentEStatePtr,e,NewEStatePtr)} where e'=(currentEStatePtr0,annot(e),NewStatePtr);
    // this represents the effect of merging states also in the STS (without introducing new merge states)
    void recordTransition(EStatePtr currentEStatePtr0,EStatePtr currentEStatePtr,Edge e, EStatePtr newEStatePtr);
    static Sawyer::Message::Facility logger;
    static bool _diagnosticsInitialized;
  };

} // end of namespace CodeThorn

#endif
