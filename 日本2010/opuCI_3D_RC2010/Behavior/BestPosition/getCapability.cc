#include "bestposition.ih"

Behavior::ConfidenceInterval BestPosition::getCapability(rf<State> s, rf<Goal> g)
{
  Vector3D pos = g->getVector("Pos");
  pos.setZ(0);
  WorldModel& wm = WorldModel::getInstance();

  if(pos.length() < 0.1)
  {
    if(wm.getPlayerType(wm.getUnum()) == Types::KEEPER && d_positioning) // keeper
    {
      wm.kpGoodPosition(true);
      d_positioning = false;
    }
    return ConfidenceInterval(0.2, 0.0);
  }
  else
  {
    d_positioning = true;
    return ConfidenceInterval(0.75, 0.0);
  }
}
