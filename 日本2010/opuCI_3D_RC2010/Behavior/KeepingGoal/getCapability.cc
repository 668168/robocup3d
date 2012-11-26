#include "keepinggoal.ih"

Behavior::ConfidenceInterval KeepingGoal::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

    // blocking!!!
    if(wm.kpBlocking() != WorldModel::NOTBLOCK)
	return ConfidenceInterval(1.0, 0.2);
    /*
    // camera angle
    double neckang, headang;
    Vector3D straight(1,0,0);
    headang = Vector3D(ballPos.getX(), 0, ballPos.getZ()).angle(straight) / M_PI * 180.0 / 3.0; 
    neckang = Vector3D(ballPos.getX(), ballPos.getY(), 0).angle(straight) / M_PI * 180.0;    
    if(ballPos.getY() < 0)
	neckang *= -1;
    if(ballPos.getZ() < 0)
	headang *= -1;
    
    if(!wm.visibleObject(Types::BALL))
    {
	neckang = 0;
	headang = 30;
    }

    std::cout << "KeepingGoal! neck:" << neckang << "  head:" << headang << std::endl;
    wm.setNeckDir(neckang, headang);
    */
    return ConfidenceInterval(0.4, 0.1);
}
