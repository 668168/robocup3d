#include "block.ih"

rf<Behavior::Goal> Block::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D goal1tPos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D goal2tPos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  Vector3D flag1tPos = wm.getObjectPosition(Types::FLAG1THEM).getMu();
  Vector3D flag2tPos = wm.getObjectPosition(Types::FLAG2THEM).getMu();
  Vector3D flag1uPos = wm.getObjectPosition(Types::FLAG1US).getMu();
  Vector3D flag2uPos = wm.getObjectPosition(Types::FLAG2US).getMu();
  double ballX = ballPos.getX();
  double ballY = ballPos.getY();
  bool outOfPenaltyArea =
    ((wm.visibleObject(Types::GOAL1THEM) && goal1tPos.length() < 10.5)
     || (wm.visibleObject(Types::GOAL2THEM) && goal2tPos.length() < 10.5)
     || (wm.visibleObject(Types::FLAG1THEM) && flag1tPos.length() < 10.5)
     || (wm.visibleObject(Types::FLAG2THEM) && flag2tPos.length() < 10.5)
     || (wm.visibleObject(Types::FLAG1US) && flag1uPos.length() < 3.0)
     || (wm.visibleObject(Types::FLAG2US) && flag2uPos.length() < 3.0));

    
  if(wm.kpBlocking() == WorldModel::B_FORWARD)
  {
      con->addVar("FallF", 0, 0);
  }
  else if(wm.kpBlocking() == WorldModel::B_LEFT)
  {
      con->addVar("FallL", 0, 0);
  }
  else if(wm.kpBlocking() == WorldModel::B_RIGHT)
  {
      con->addVar("FallR", 0, 0);
  }
  else if(ballX > 0 && !outOfPenaltyArea && // ball is forward & kp in penalty area
	  wm.kpBlocking() == WorldModel::NOTBLOCK) // block chance
    {
      if(!wm.visibleObject(Types::GOAL1US) &&
	 wm.visibleObject(Types::FLAG1US) && flag1uPos.getY() > 0)
	{
	  wm.kpBlocking(WorldModel::B_RIGHT);
	  con->addVar("FallR", 0, 0);
	}	 
      else if(!wm.visibleObject(Types::GOAL2US) &&
	 wm.visibleObject(Types::FLAG2US) && flag2uPos.getY() < 0)
	{
	  wm.kpBlocking(WorldModel::B_LEFT);
	  con->addVar("FallL", 0, 0);
	}
      else if(fabs(ballY) < 0.3)
      {
	  wm.kpBlocking(WorldModel::B_FORWARD);
	  con->addVar("FallF", 0, 0);
      }
      else if(ballY < 0)
      {
	  wm.kpBlocking(WorldModel::B_RIGHT);
	  con->addVar("FallR", 0, 0);
      }
      else if(ballY > 0)
      {
	  wm.kpBlocking(WorldModel::B_LEFT);
	  con->addVar("FallL", 0, 0);
      }
  }
  else
  {
    //std::cout << "Block::generateGoal()  cant generate goal of block!" << std::endl;
  }

  return goal;
}
