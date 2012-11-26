#include "cornerkick.ih"

void CornerKick::update()
{
  Behavior::update();

  WorldModel& wm = WorldModel::getInstance();

  WorldModel::PlayMode pm = wm.getPlayMode();

  // playmode is not CornerKick, reset s_kickPos
  if( pm != WorldModel::CORNER_KICK_US &&
      pm != WorldModel::CORNER_KICK_RIGHT &&
      pm != WorldModel::CORNER_KICK_LEFT )
  {
    s_kickPos = NONE;
  }
  else if( wm.allObjectPosAvailable() && wm.visibleObject(Types::BALL))
  {
    // set s_kickPos when all objects (including ball) are in the sight
    Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D flag1 = wm.getObjectPosition(Types::FLAG1THEM).getMu();
    Vector3D flag2 = wm.getObjectPosition(Types::FLAG2THEM).getMu();

    if( (ball - flag1).length() < (ball - flag2).length() )
      s_kickPos = FLAG1;
    else
      s_kickPos = FLAG2;
  }
}
