#include "walkstraightto.ih"

void WalkStraightTo::update()
{
  Behavior::update();
  
  if (d_committed)
    return;

  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.get(WorldModel::iVisionBall);
  double angleToBall = ballPos.getY() / M_PI * 180;
  //double minAngle = 10.0;
  //double maxAngle = 20.0;
  //double angle = minAngle;
  
//  NormalDistribution3D BallInfo = wm.getObjectPosition(Types::BALL);
//  Vector3D ballPosCar = BallInfo.getMu();
//  double ballX = ballPosCar.getX();
//  double ballY = ballPosCar.getY();
  //bool leftTouch = wm.getLeftTouch();
  //bool rightTouch = wm.getRightTouch();
  // Distance from foot to ball (not from camera)
//  double distToBall = sqrt(ballX * ballX + ballY * ballY);


  Vector3D oppGoalCenter = (wm.getObjectPosition(Types::GOAL1THEM).getMu() + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2.0;
  oppGoalCenter.setZ(0.0);
  Vector3D oppPos[2];
  oppPos[0] = wm.getObjectPosition(Types::BALL).getMu();
  oppPos[0].setZ(0.0);
  oppPos[1] = wm.getObjectPosition(Types::BALL).getMu();
  oppPos[1].setZ(0.0);
  oppPos[2] = wm.getObjectPosition(Types::OPPONENT3).getMu();
  oppPos[2].setZ(0.0);

  double oppDist[] = {(oppPos[0] - oppGoalCenter).length(),
					(oppPos[1] - oppGoalCenter).length(),
					(oppPos[2] - oppGoalCenter).length()};
  int unum[] = {1, 2, 3};
  for(int i=1; i<3; i++){
	if(oppDist[0] < oppDist[i]){
	  double tmp_d = oppDist[0];
	  oppDist[0] = oppDist[i];
	  oppDist[i] = tmp_d;
	  int tmp_i = unum[0];
	  unum[0] = unum[i];
	  unum[i] = tmp_i;
	}
  }

  Vector3D targetPos = (wm.getObjectPosition(Types::BALL).getMu() * 2.0 + oppPos[unum[0] - 1] * 1.0) / 3.0;
  targetPos.setZ(0.0);

//  Vector3D pos = d_goal->getVector("Pos");
//  pos.setZ(0);
  Vector3D straight(1, 0, 0);
  double angleToPos = straight.angle(targetPos) / M_PI * 180;

//  if (distToBall < 7.5)
//  if (distToBall < 1.875)
//    d_committed = false;
  if (fabs(angleToPos) < 20.0)
    d_committed = true;
//  else if (!wm.onMyFeet())
//    d_committed = true;
  else
    d_committed = false;
    
//  std::cout << "In WalkStraightto::update()" << std::endl;
//  std::cout << "  d_committed = " << d_committed << std::endl;
  
  //d_committed = !wm.onMyFeet();
}

