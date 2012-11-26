#include "leftstep.ih"

Behavior::ConfidenceInterval LeftStep::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu(); // **
    Vector3D goal1uPos = wm.getObjectPosition(Types::GOAL1US).getMu();
    Vector3D goal2uPos = wm.getObjectPosition(Types::GOAL2US).getMu();
    Vector3D goal1to2 = (goal2uPos - goal1uPos).normalize();
    Vector3D goaluPos = (goal1uPos + goal2uPos) / 2.0;
    Vector3D goal1uOut = goal1uPos - goal1to2 * 0.3; // **
    Vector3D goal2uOut = goal1uPos + goal1to2 * 0.3; // **
    Vector3D straight(1.0, 0.0, 0.0);

    double angtoBall = getAngleWithStraight(ballPos);
    double angtoGoal1o = getAngleWithStraight(goal1uOut);
    double angtoGoal2o = getAngleWithStraight(goal2uOut);
 
    if( !wm.visibleObject(Types::BALL) || ! wm.allObjectPosAvailable() )
    {
      return ConfidenceInterval(0.0, 0.0);
    }

    bool execute = false;
    if( fabs(angtoBall) < 30.0 ) // ball zenpo 
    {
	    if ( goal1uOut.getY() < ballPos.getY() && ballPos.getY() < goal2uOut.getY() ) // goal zenpo, jisatsu!?
	    {
		if( goal1uOut.length() > goal2uOut.length()) // near goal2pos
		    execute = true;
	    }
	}

    if(execute)
	return ConfidenceInterval(0.75, 0.2);

    return ConfidenceInterval(0.0, 0.0);
}

