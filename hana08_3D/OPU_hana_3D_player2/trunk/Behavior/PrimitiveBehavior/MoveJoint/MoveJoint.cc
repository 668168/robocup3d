#include "movejoint.hh"

using namespace bats;

MoveJoint::MoveJoint(std::string const &id, std::string const &playerClass)
  : PrimitiveBehavior("MoveJoint", id, playerClass)
{

  XMLNodeSet params = getParams("/joint");
  //_debugLevel4("Params: " << (params.empty() ? "yes" : "no"));
  
  if(!params || params.empty())
    throw new BatsException("MoveJoint behavior requires a joint parameter");
  else
  {
    XMLNode jointNode = params.front();
    d_joint = (Types::Joint)atoi(jointNode.getContent().c_str());

    if (jointNode.hasProp("min"))
      d_min = atoi(jointNode.getProp("min").c_str()) * M_PI / 180.0;
    else
      d_min = -M_PI;

    if (jointNode.hasProp("max"))
      d_max = atoi(jointNode.getProp("max").c_str()) * M_PI / 180.0;
    else
      d_max = M_PI;

  }
}
