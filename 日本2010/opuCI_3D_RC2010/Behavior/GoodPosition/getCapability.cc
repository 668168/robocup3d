#include "goodposition.ih"

Behavior::ConfidenceInterval GoodPosition::getCapability(rf<State> s, rf<Goal> g)
{

  Vector3D pos = g->getVector("Pos");
  if( pos.length() < 1.5 )
  {
    return ConfidenceInterval(0.72, 0);
  }

  //  pos.setZ(0);
  //  _debugLevel4(ident() << ": " << pos << " " << pos.length());
  
  // if (pos.length() < 0.5)
  // return ConfidenceInterval(0.0, 0.0);
  
  // WorldModel& wm = WorldModel::getInstance();
  // Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  
  // if(ballPos.length() <= 1.0 && wm.visibleObject(Types::BALL))
//  if(pos.length() > 0.5)
  return ConfidenceInterval(0.68, 0.0);

}
