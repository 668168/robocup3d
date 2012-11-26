#include "worldmodel.ih"

WorldModel::WorldModel(SocketComm &comm)
  :
  d_comm(comm),
  d_unum(0),
  d_time(0),
  d_playMode(UNKNOWN),
  d_firstTime(-1),
  d_numMsgReceived(0)
{
  for (unsigned i = 0; i < Types::NOBJECTS; ++i) {
    d_lastVisionUpdate[i] = -1000.0;
    d_objectPositions[i].init(Vector3D(0.0,0.0,0.0), Matrix9D());
  }
}
