#include "agentmodel.ih"

std::string AgentModel::getJointName(Types::Joint id) const
{
  _foreach(a, d_jointNameMap)
    if(a->second == id)
      return a->first;
  return "";
}
