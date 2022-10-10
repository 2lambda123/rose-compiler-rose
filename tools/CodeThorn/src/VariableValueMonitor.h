#ifndef VARIABLE_VALUE_MONITOR
#define VARIABLE_VALUE_MONITOR

#include "VariableIdMapping.h"
#include "AbstractValue.h"
#include "EState.h"

namespace CodeThorn {

  class CTAnalysis;
  class EState;
  class PState;

  class VariableValueMonitor {
  public:
    enum VariableMode { VARMODE_FORCED_TOP, VARMODE_ADAPTIVE_TOP, VARMODE_PRECISE};
    VariableValueMonitor();
    // the init function only uses the variableIds of a given estate (not its values) for initialization
    void init(EStatePtr estate);
    void init(PStatePtr pstate);
    AbstractValueSet getVariables();
    void setVariableMode(VariableMode,CodeThorn::AbstractValue);
    VariableMode getVariableMode(CodeThorn::AbstractValue);
    bool isHotVariable(CTAnalysis* analyzer, CodeThorn::AbstractValue varId);
    std::string toString(CodeThorn::VariableIdMapping* variableIdMapping);
  private:
    std::map<CodeThorn::AbstractValue,std::set<int>* > _variablesMap;
    std::map<CodeThorn::AbstractValue,VariableMode> _variablesModeMap;
};

} // end of namespace CodeThorn

#endif
