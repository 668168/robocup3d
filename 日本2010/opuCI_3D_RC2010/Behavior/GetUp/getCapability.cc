#include "getup.ih"

Behavior::ConfidenceInterval GetUp::getCapability(rf<State> s, rf<Goal> g)
{
	WorldModel& wm = WorldModel::getInstance();

	/*if(wm.getUnum() == 1 && wm.kpBlocking() != WorldModel::NOTBLOCK && wm.kpBlocking()!= WorldModel::FINISHED)
	{
		//the keeper is up
		wm.setNeckDirUpdate(true);
		return ConfidenceInterval(-1.0, 0.0);
	}*/

	//if the game state is before the game start or that one goal was
	//scored then there is no chance the keeper to be down
	if(wm.getPlayMode() == WorldModel::BEFORE_KICKOFF ||
			wm.getPlayMode() == WorldModel::GOAL_THEM ||
			wm.getPlayMode() == WorldModel::GOAL_US ||
			wm.getPlayMode() == WorldModel::GOAL_RIGHT ||
			wm.getPlayMode() == WorldModel::GOAL_LEFT )
	return ConfidenceInterval(-1.0, 0.0);

	//get the vector of the ball position over the player
	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	//
	ballPos.setZ(ballPos.getZ() + 0.5);

	if (wm.getUnum() == 1 && (wm.kpStartBlockTime() + 15 > wm.getTime()) && (wm.onMyBelly() || wm.onMyBack()))
	{
		wm.setNeckDirUpdate(false);
		wm.kpGoodPosition(false);
		wm.kpBlocking(WorldModel::NOTBLOCK);

		return ConfidenceInterval(1.0,1.0);
	}

	//if the keeper state is set to finnished (ie it's been less than 20s
	//that the keeper is down)
	if (wm.getUnum() == 1 && wm.kpBlocking() == WorldModel::FINISHED )
	{
		//the keeper is down
		wm.setNeckDirUpdate(false);
		//the keeper is not in good position
		wm.kpGoodPosition(false);
		//deblock the keeper
		wm.kpBlocking(WorldModel::NOTBLOCK);

		return ConfidenceInterval(1.3, 0.2);
	}

	// if((!wm.onMyFeet() && wm.getGameTime() > 0.2 ) || wm.onMyBelly() || wm.onMyBack()
	// || wm.getLastVisionUpdateTime() + 5.0 < wm.getTime() )
	if( wm.onMyBelly() || wm.onMyBack() )
	{
		wm.setNeckDirUpdate(false);
		wm.kpGoodPosition(false);
		wm.kpBlocking(WorldModel::NOTBLOCK);
		return ConfidenceInterval(1.0, 0.2);
	}
	return ConfidenceInterval(-1.0, 0.0);
}
