#include "kickpositiondefender.ih"

Behavior::ConfidenceInterval KickPositionDefender::getCapability(rf<State> s, rf<Goal> g)
{
	WorldModel& wm = WorldModel::getInstance();
	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	
    if(!wm.visibleObject(Types::BALL))
      return ConfidenceInterval(0.15, 0.0);
    
    double toeX =
          min(wm.getBodyConnectionPosition(Types::BC_RTOE).getX(), wm.getBodyConnectionPosition(Types::BC_LTOE).getX());
    
    if( toeX < ballPos.getX())
    {
      return ConfidenceInterval(0.7, 0);
    }
    
  return ConfidenceInterval(0.2, 0.0);
}
