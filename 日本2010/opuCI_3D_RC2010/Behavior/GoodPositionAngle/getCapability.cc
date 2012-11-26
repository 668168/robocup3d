#include "goodpositionangle.ih"

Behavior::ConfidenceInterval GoodPositionAngle::getCapability(rf<State> s, rf<Goal> g)
{   
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  if( wm.getPlayerType(wm.getUnum()) == Types::KEEPER )
    return ConfidenceInterval(0.4, 0.0);

  if (ballPos.length() <= 1.0 )
    return ConfidenceInterval(0.6, 0.0);
 
  return ConfidenceInterval(0.2, 0.0);
}
