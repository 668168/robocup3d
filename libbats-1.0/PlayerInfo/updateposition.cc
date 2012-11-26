#include "playerinfo.ih"

void PlayerInfo::updatePosition(Vector3F const &pos, float time)
{
  // Round the robin?
  if (++d_histPos > c_histLength)
    d_histPos = 0;

  // Calculate time difference.
  float d_lastStep = time-d_lastSeen;

  if (d_lastStep <= 0.0) {
    //    _flog("WARNING: ZERO TIME STEP IN PLAYERINFO UPDATE!");
    return;
  }


  /* WRONG: I FORGOT TO TRANSLATE TO WORLD COORDINATES! */

  Vector3F MP = SWorldModel::getInstance().getWorldTransform() * pos;
  Vector3F F  = SWorldModel::getInstance().getObjectPositionLocal(Types::FLAG1US).getMu();
  Vector3F MF = SWorldModel::getInstance().getWorldTransform() * F;
  Vector3F L  = Vector3F(-6,4,0);

  Vector3F A  = MP - MF + L;

  //  cout << "Pos: " <<  MP << " " << MF << " " << A << endl;

  Vector3F worldPos = A;

  // Calculate the velocity over the last step in world coordinates.
  Vector3F vel = (worldPos - d_lastPosition) / d_lastStep;

  d_lastPosition = worldPos;

  // Adding the current position and velocity to the history.
  //  d_positionHist[d_histPos] = pos;
  d_velocityHist[d_histPos] = vel;

  // Resetting the position and velocity.
  //  d_estPosition = Vector3F(0.0,0.0,0.0);
  d_estWorldVelocity = Vector3F(0.0,0.0,0.0);

  // Calculate the sum position and velocity over the history.
  for (unsigned i = 0; i < c_histLength; ++i) {
    //    d_estPosition += d_positionHist[i];
    d_estWorldVelocity += d_velocityHist[i];
  }

  // Calculate the mean position and velocity over the history.
  //  d_estPosition /= c_histLength;
  d_estWorldVelocity /= c_histLength;

  //  cerr << "Estimated velocity: " << d_estWorldVelocity << endl;

  // Transform velocity back into world velocity.
  d_estVelocity = SWorldModel::getInstance().getWorldTransform() * d_estWorldVelocity;

  // Transform the world position back to agent coordinates.
  d_worldPosition = d_lastPosition;
  d_position      = SWorldModel::getInstance().getFieldTransform().inverse() * pos; //SWorldModel::getInstance().getInvWorldTransform()*d_worldPosition;

  // Remmember global position over a long time.
  d_longPosIntergrate = d_longPosIntergrate*0.40 + d_worldPosition*0.60;

  /*
  // Calculate the goal center.
  Vector3F flag1t = WorldModel::instance().getObjectPositionLocal(Types::FLAG1THEM);
  Vector3F flag2t = WorldModel::instance().getObjectPositionLocal(Types::FLAG2THEM);
  Vector3F centerGoal = 0.5*(flag1t+flag2t);

  // See if it might be a goally.
  if ((d_longPosIntergrate - centerGoal).length() < 2)
    d_thinkGoally = true;

  Vector3F balpos = WorldModel::instance().getObjectPositionLocal(
  */
}
