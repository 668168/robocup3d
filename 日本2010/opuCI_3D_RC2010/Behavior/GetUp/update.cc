#include "getup.ih"

void GetUp::update() {
	Behavior::update();
	WorldModel& wm = WorldModel::getInstance();

	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  WorldModel::PlayMode pm = wm.getPlayMode();

	if (ballPos.length() > 0.7)
		d_nearBallTime = wm.getTime();

	if (wm.getPlayerType(wm.getUnum()) == Types::KEEPER) {
		if (wm.kpStartBlockTime() + 15 < wm.getTime() && wm.kpBlocking()
				!= WorldModel::NOTBLOCK)
			wm.kpBlocking(WorldModel::FINISHED);
		else if (wm.kpBlocking() != WorldModel::NOTBLOCK && wm.visibleObject(
				Types::BALL) && d_nearBallTime + 0.5 < wm.getTime())
			wm.kpBlocking(WorldModel::FINISHED);

		if (pm == WorldModel::GOAL_KICK_US)
			wm.kpBlocking(WorldModel::NOTBLOCK);
	}

	if (pm == WorldModel::BEFORE_KICKOFF
      || pm == WorldModel::GOAL_THEM
      || pm == WorldModel::GOAL_US
      || pm == WorldModel::GOAL_RIGHT
      || pm == WorldModel::GOAL_LEFT) {
		d_committed = false;
		wm.kpBlocking(WorldModel::NOTBLOCK);
	}

}
