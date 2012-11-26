#include "block.ih"

Behavior::ConfidenceInterval Block::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    double ballX = ballPos.getX();
    double ballY = ballPos.getY();
    double neckang, headang;
    Vector3D straight(1,0,0);
    Vector3D goal1tPos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
    Vector3D goal2tPos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
    Vector3D flag1tPos = wm.getObjectPosition(Types::FLAG1THEM).getMu();
    Vector3D flag2tPos = wm.getObjectPosition(Types::FLAG2THEM).getMu();
    Vector3D flag1uPos = wm.getObjectPosition(Types::FLAG1US).getMu();
    Vector3D flag2uPos = wm.getObjectPosition(Types::FLAG2US).getMu();
    headang = Vector3D(ballPos.getX(), 0, ballPos.getZ()).angle(straight) / M_PI * 180.0; 
    neckang = Vector3D(ballPos.getX(), ballPos.getY(), 0).angle(straight) / M_PI * 180.0;    
    if(ballPos.getY() < 0)
	neckang *= -1;
    if(ballPos.getZ() < 0)
	headang *= -1;
    
    if(!wm.visibleObject(Types::BALL))
    {
	neckang = 0;
	headang = 40;
    }
    bool outOfPenaltyArea = 
      ((wm.visibleObject(Types::GOAL1THEM) && goal1tPos.length() < 10.5)
       || (wm.visibleObject(Types::GOAL2THEM) && goal2tPos.length() < 10.5)
       || (wm.visibleObject(Types::FLAG1THEM) && flag1tPos.length() < 10.5)
       || (wm.visibleObject(Types::FLAG2THEM) && flag2tPos.length() < 10.5)
       || (wm.visibleObject(Types::FLAG1US) && flag1uPos.length() < 3.0)
       || (wm.visibleObject(Types::FLAG2US) && flag2uPos.length() < 3.0));
      
    ballPos.setZ(0);
    // blocking!!!
    if(wm.kpBlocking() != WorldModel::NOTBLOCK &&
       wm.kpBlocking() != WorldModel::FINISHED)
    {
	wm.setNeckDir(neckang, headang);
	wm.setNeckDirUpdate(true);
	

	return ConfidenceInterval(1.0, 0.2);
    }

    if(d_ballHoldTime + 1.0 < wm.getTime() &&
       ballPos.length() < 3.0 && ballPos.length() >= 1.5 && !outOfPenaltyArea)
    {
	wm.setNeckDir(neckang, headang);
	wm.setNeckDirUpdate(true);
	
	if(ballX > 0 && wm.kpBlocking() == WorldModel::NOTBLOCK)
	{
	  if(!wm.visibleObject(Types::GOAL1US) &&
	     wm.visibleObject(Types::FLAG1US) && flag1uPos.getY() > 0)
	    {
	      wm.kpBlocking(WorldModel::B_RIGHT);
	    }	 
	  else if(!wm.visibleObject(Types::GOAL2US) &&
		  wm.visibleObject(Types::FLAG2US) && flag2uPos.getY() < 0)
	    {
	      wm.kpBlocking(WorldModel::B_LEFT);
	    }
	  if(fabs(ballY) < 0.3)
	    {
	      wm.kpBlocking(WorldModel::B_FORWARD);
	    }
	  else if(ballY < 0)
	    {
	      wm.kpBlocking(WorldModel::B_RIGHT);
	    }
	  else if(ballY > 0)
	    {
	      wm.kpBlocking(WorldModel::B_LEFT);
	    }
	}
	else
	{
	  //std::cout << "Block::getCapability()  which side to dive?! FORWARD(kari)!!" << std::endl;
	}
	wm.kpStartBlockTimeUpdate();
//	std::cout << "block start! " << wm.kpStartBlockTime() << std::endl;
	return ConfidenceInterval(0.5, 0.2);
    }
    return ConfidenceInterval(0.0, 0.31);
}
