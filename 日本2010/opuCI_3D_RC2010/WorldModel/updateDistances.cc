#include "worldmodel.ih"

void WorldModel::updateDistances()
{
	Vector3D ballPos = d_objectPositionsW[Types::BALL].getMu();
	//std::cout << "I am the player number " << s_playerTypeMap[d_unum] << std::endl;

	
	double angleR = M_PI / 4;
	double angleL = 3 * M_PI / 4;

	closestPlayer[0] = 1;
	closestPlayer[1] = 1;

	closestPlayerDist[0] = 1000;
	closestPlayerDist[1] = 1000;

	for (int i = 0; i < 6; ++i)
	{
		distToBall[i][0] = 1000; //player
		distToBall[i][1] = 1000; //Opponent
		distToGoal[i] = 1000; //goal
		sortDistPlayerBall[i][0] = 1;
		sortDistPlayerBall[i][1] = 1;
		sortDistPlayerGoal[i] = 1;
	}

	for (int i = 0; i < 12; i++)
	{
		sortDistPlayerPlayer[i] = 1;
		distToPlayer[i] = 1000;
	}

	for (int i = Types::PLAYER1; i <= Types::PLAYER6; i++)
	{
		int dep = Types::PLAYER1;

		if (visibleObject((Types::Object) i) || (i - dep + 1) == d_unum)
		{
			//std::cout << "visible object " << i - dep <<std::endl;
			Vector3F agentToBall = ballPos
					- d_objectPositionsW[(Types::Object) i].getMu();
			Vector3F agentToPlayer =
					d_objectPositionsW[(Types::Object) i].getMu();
			Vector3F agentToGoal = (d_objectPositionsW[Types::GOAL1US].getMu()
					+ d_objectPositionsW[Types::GOAL2US].getMu()) * 0.5
					- d_objectPositionsW[(Types::Object) i].getMu();

			agentToBall.setZ(0);
			agentToPlayer.setZ(0);
			agentToGoal.setZ(0);

			distToBall[i - dep][0] = agentToBall.length();
			distToPlayer[i - dep] = agentToPlayer.length();
			distToGoal[i - dep] = agentToGoal.length();
		
		}

		Vector3F agentToPlayer = d_objectPositionsW[(Types::Object)i].getMu();
		double angle = fabs(Vector3D(1,0,0).angle(agentToPlayer));
		
		d_angleToPlayer[i-dep]=angle;

		if (distToBall[i - dep][0] < closestPlayerDist[0])
		{
			closestPlayerDist[0] = distToBall[i - dep][0];
			closestPlayer[0] = i - dep + 1;
		}
	}

	for (int i = Types::OPPONENT1; i <= Types::OPPONENT6; i++)
	{
		int dep = Types::OPPONENT1;
		if (visibleObject((Types::Object) i))
		{
			//std::cout << "visible object " << i - dep <<std::endl;
			Vector3F agentToBall = ballPos
					- d_objectPositionsW[(Types::Object) i].getMu();
			Vector3F agentToPlayer =
					d_objectPositionsW[(Types::Object) i].getMu();

			agentToBall.setZ(0);
			agentToPlayer.setZ(0);

			distToBall[i - dep][1] = agentToBall.length();
			distToPlayer[i - dep + 6] = agentToPlayer.length();
			
		}

			
		Vector3F agentToPlayer = d_objectPositionsW[(Types::Object)i].getMu();
			
		double angle = fabs(Vector3D(1,0,0).angle(agentToPlayer));
		
		d_angleToPlayer[i-dep+6]=angle;
		
		if (distToBall[i - dep][1] < closestPlayerDist[1])
		{
			closestPlayerDist[1] = distToBall[i - dep][1];
			closestPlayer[1] = i - dep + 1;
		}
	}

	for (int t1 = 0; t1 < 5; t1++)
		for (int t2 = t1 + 1; t2 < 6; t2++)
			distToBall[t1][0] >= distToBall[t2][0] ? sortDistPlayerBall[t1][0]++
					: sortDistPlayerBall[t2][0]++;

	for (int t1 = 0; t1 < 5; t1++)
		for (int t2 = t1 + 1; t2 < 6; t2++)
			distToBall[t1][1] >= distToBall[t2][1] ? sortDistPlayerBall[t1][1]++
					: sortDistPlayerBall[t2][1]++;

	for (int t1 = 0; t1 < 5; t1++)
		for (int t2 = t1 + 1; t2 < 6; t2++)
			distToGoal[t1] >= distToGoal[t2] ? sortDistPlayerGoal[t1]++
					: sortDistPlayerGoal[t2]++;

	for (int t1 = 0; t1 < 11; t1++)
		for (int t2 = t1 + 1; t2 < 12; t2++)
			distToPlayer[t1] >= distToPlayer[t2] ? sortDistPlayerPlayer[t1]++
					: sortDistPlayerPlayer[t2]++;

	setPlayersZone();
}
