#include "worldmodel.ih"

WorldModel::WorldModel(SocketComm &comm) :
	d_comm(comm),
	d_unum(0),
	d_time(0),
	d_playMode(UNKNOWN),
	d_firstTime(-1),
	d_numMsgReceived(0),
	d_freeze(false),
	d_onFeetCount(0),
	d_onRightLeg(0),
	d_onLeftLeg(0),
	d_KP_blocking(NOTBLOCK),
	d_KP_positioning(true),
	d_KP_startBlockTime(-100),
	d_ballOnOurSide(false),
	d_lastCoordUpdate(0),
	d_velocity(Vector3D(0, 0, 0)),
	isCheck(false),
	d_first(false),
        d_ballZone(NOZONE)

{
	for (unsigned i = 0; i < Types::NOBJECTS; ++i) {
		d_lastVisionUpdate[i] = 0.0;
		d_objectPositions[i].init(Vector3D(0.0, 0.0, 0.0), Matrix9D());
	}

}
