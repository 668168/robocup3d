#include "worldmodel.ih"

WorldModel::WorldModel()
  :
  d_time(0),
  d_teamName(""),
  d_gameTime(0),
  d_prevGameTime(0),
  d_timeStep(0.04),
  d_playMode(Types::UNKNOWN),
  d_lastPlayMode(Types::UNKNOWN),
  d_team(Types::LEFT),
  d_scoreUs(0),
  d_scoreThem(0),
  d_firstTime(-1),
  d_numMsgReceived(0),
  d_ballRadius(0.042)
{
  for (unsigned i = 0; i < Types::NOBJECTS; ++i) {
    d_lastVisionUpdate[i] = -1000.0;
    d_objects[i].position.init(Vector3D(0.0,0.0,0.0), Matrix9D());
  }

  d_getUpTheOldFashionedWay = false;

}
