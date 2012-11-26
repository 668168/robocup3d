#include "supportdefense.ih"

rf<Behavior::Goal> SupportDefense::generateGoal(unsigned step, unsigned slot)
{
	rf<Goal> goal = new Goal();
	rf<OrNode> dis = goal->addDisjunct();
	rf<AndNode> con = dis->addConjunct();

	WorldModel& wm = WorldModel::getInstance();

	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	ballPos.setZ(0.0);

	Vector3D target = ballPos;

	Vector3D goalDirUS = (wm.getObjectPosition(Types::GOAL1US).getMu()
			+ wm.getObjectPosition(Types::GOAL2US).getMu()) * 0.5;
	goalDirUS.setZ(0);

	Vector3D goalDirTHEM = (wm.getObjectPosition(Types::GOAL1THEM).getMu()
			+ wm.getObjectPosition(Types::GOAL2THEM).getMu()) * 0.5;
	goalDirTHEM.setZ(0);
	
	Vector3D fieldSide = wm.getObjectPosition(Types::GOAL1US).getMu()
				- wm.getObjectPosition(Types::GOAL2US).getMu();
		Vector3D fieldSidePerp = -Math::calcPerpend(fieldSide);

	//calculation of the direction goalTHEM/ball
	Vector3D dirGoalBallTHEM = (ballPos - goalDirTHEM).normalize();
	Vector3D perpTHEM = Math::calcPerpend(dirGoalBallTHEM);
	//calculation of the direction goalUS/ball
	Vector3D dirGoalBallUS = (ballPos - goalDirUS).normalize();
	Vector3D perpUS = Math::calcPerpend(dirGoalBallUS);
	
	target =  -perpUS * Math::distanceLinePoint(goalDirUS, dirGoalBallUS,
			Vector3D(0, 0, 0))*1.5 -fieldSidePerp;

	//if we are far from the ball
	//TODO determine if the ball is going in the left or the right area to determine which defenser will act.
	//TODO if the area is between the two defenser then player the closest to the prediction ballPos will act
	//Prediction of the direction of the ball
	//if the ball is going to an empty zone go in the direction of the predicted goalPos
	//if the ball is going to a crowded zone replace yourself between the goal and the predicted goalpos
	/*if (ballPos.length() > 1.01)
	{
		int opUnum = wm.getClosestOpponentUnum();

		Vector3D closestPlayer = wm.getPlayerByUnum(1, opUnum);
		Vector3D distBallOpponent = ballPos - closestPlayer;

		if (distBallOpponent.length() < 0.8)
		{

			Vector3D prediction = distBallOpponent
					+ wm.getOpponentVectorByUnum((unsigned) opUnum).getMu();

			//maybe replace this one by no one in a semi sphere of radius r
			Types::Object obj = getObjectBetweenPos(prediction, 2
					* prediction.length() * tan(60 * M_PI / 180));

			if (obj != Types::NOBJECTS)
			{
				//if object same side of the goal from me go a little to the prediction dir and object not keeper
				if (Math::atSameSideOf(prediction,
						wm.getObjectPosition(obj).getMu(), goalDirUS))
					target = prediction.normalize();

			} else
				target = prediction;
		} else
			//then go to the perpendicular point of the segment ball/goal
			target = -perpUS * Math::distanceLinePoint(ballPos, perpUS,
					Vector3D(0, 0, 0));
	}

	//if we are close to the ball
	if (ballPos.length() < 0.2)
	{
		if (ballPos.length() >= 0.1)
			target = -perpTHEM * Math::distanceLinePoint(ballPos, perpTHEM,
					Vector3D(0, 0, 0));
		else
			target = goalDirTHEM.normalize();
	}*/

	con->addVar("Pos", target);
	wm.setDebugPointWithLabel(target,"SupportDefense_TGT");

	return goal;
}
