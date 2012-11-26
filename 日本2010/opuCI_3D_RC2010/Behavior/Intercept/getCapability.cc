#include "intercept.ih"

Behavior::ConfidenceInterval Intercept::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    WorldModel::PlayMode pm = wm.getPlayMode();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D goalPos1 = wm.getObjectPosition(Types::GOAL1US).getMu();
    Vector3D goalPos2 = wm.getObjectPosition(Types::GOAL2US).getMu();
    bool     canseeGPos1 = wm.visibleObject(Types::GOAL1US);
    bool     canseeGPos2 = wm.visibleObject(Types::GOAL2US);
    Vector3D straight(1,0,0);
    ballPos.setZ(0);
    goalPos1.setZ(0);
    goalPos2.setZ(0);
    Vector3D goalPos = (goalPos1 + goalPos2) / 2.0;
    double distToBall = ballPos.length();

    // camera setting
    ballPos = wm.getObjectPosition(Types::BALL).getMu();
    double neckang, headang;
    headang = Vector3D(ballPos.getX(), 0, ballPos.getZ()).angle(straight) / M_PI * 180.0; 
    neckang = Vector3D(ballPos.getX(), ballPos.getY(), 0).angle(straight) / M_PI * 180.0;    
    if(ballPos.getY() < 0)
	neckang *= -1;
    if(ballPos.getZ() < 0)
	headang *= -1;

    if(!wm.visibleObject(Types::BALL))
    {
//	std::cout << "block: set neck=0, head=-40" << std::endl;
	neckang = 0;
	headang = -40;
    }

    if(wm.visibleObject(Types::BALL))
    {
	if((distToBall < 1.5 
	    || ( canseeGPos1 && (goalPos1 - ballPos).length() < 0.7)
	    || ( canseeGPos2 && (goalPos2 - ballPos).length() < 0.7)
	    || ( canseeGPos1 && canseeGPos2 && (goalPos - ballPos).length() < 1.0))
	   && wm.kpBlocking() == WorldModel::NOTBLOCK )
	{
	    wm.setNeckDir(neckang, headang);
	    wm.setNeckDirUpdate(true);
	    return ConfidenceInterval(0.55, 0.2);
	}
    }
    return ConfidenceInterval(0.0, 0.2);
}
