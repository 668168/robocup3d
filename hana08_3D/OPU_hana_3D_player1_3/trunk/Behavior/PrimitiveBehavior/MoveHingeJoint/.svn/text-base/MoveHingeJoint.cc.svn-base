#include "movehingejoint.hh"

using namespace bats;

MoveHingeJoint::MoveHingeJoint(std::string const &id, std::string const &playerClass)
  : PrimitiveBehavior("MoveHingeJoint", id, playerClass)
{

  XMLNodeSet params = getParams("/joint");
  //_debugLevel4("Params: " << (params.empty() ? "yes" : "no"));
  
  if(!params || params.empty())
    throw new BatsException("MoveHingeJoint behavior requires a joint parameter");
  else
  {
    XMLNode jointNode = params.front();
    d_joint = (Types::Joint)atoi(jointNode.getContent().c_str());
  }
}
