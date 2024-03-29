#include "dive.ih"

rf<Behavior::Goal> Dive::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  WorldModel& wm = WorldModel::getInstance();

  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D goalPos1 = wm.getObjectPosition(Types::GOAL1US).getMu();
  Vector3D goalPos2 = wm.getObjectPosition(Types::GOAL2US).getMu();
  Vector3D ballSpeed = wm.getObjectVector(Types::BALL).getMu();
  Vector3D ballToAgent = -ballPos;
  Vector3D goalPos = ( goalPos1 + goalPos2 ) / 2;
  Vector3D straightX(1.0, 0.0, 0.0);
  Vector3D straightY(0.0, 1.0, 0.0);

  ballSpeed.setZ(0);
  ballToAgent.setZ(0);
  
  double absBallX = fabs(ballPos.getX());
  double absBallY = fabs(ballPos.getY());
  
  double goalX = goalPos.getX();
  double goalY = goalPos.getY();
  
  double ballSpeedAnglex = straightX.angle(ballSpeed) * M_PI / 180.0;
  double ballPosAnglex = straightX.angle(ballToAgent) * M_PI / 180.0;
  double ballSpeedAngley = straightY.angle(ballSpeed) * M_PI / 180.0;
  double ballPosAngley = straightY.angle(ballToAgent) * M_PI / 180.0;

  con->addVar("PAngleX", ballPosAnglex, ballPosAnglex);
  con->addVar("SAngleX", ballSpeedAnglex, ballSpeedAnglex);

  con->addVar("PAngleY", ballPosAngley, ballPosAngley);
  con->addVar("SAngleY", ballSpeedAngley, ballSpeedAngley);



  return goal;
}
