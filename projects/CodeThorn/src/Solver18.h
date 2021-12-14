#ifndef SOLVER18_H
#define SOLVER18_H


// CodeThorn includes
#include "Solver.h"
#include "EState.h"

namespace CodeThorn {

  class EState;
  
  class Solver18 : public Solver {
  public:
    Solver18();
    void run();
    int getId();

    static void initDiagnostics();
  private:
    void initializeSummaryStatesFromWorkList();
    // add Edge {(currentEStatePtr,e,NewEStatePtr)} to STS
    // if currentEStatePtr!=currentEStatePtr) then also add 
    //     (currentEStatePtr,e,NewEStatePtr)} where e'=(currentEStatePtr0,annot(e),NewStatePtr);
    // this represents the effect of merging states also in the STS (without introducing new merge states)
    static Sawyer::Message::Facility logger;
    static bool _diagnosticsInitialized;
  };

} // end of namespace CodeThorn

#endif
