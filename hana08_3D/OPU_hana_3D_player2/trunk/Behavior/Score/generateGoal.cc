#include "score.ih"

rf<Behavior::Goal> Score::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  static int count = 0;

  WorldModel& wm = WorldModel::getInstance();

  Vector3D oppGoalCenter = (wm.getObjectPosition(Types::GOAL1THEM).getMu() + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2.0;
  oppGoalCenter.setZ(0.0);
  Vector3D oppPos[2];
  // if OPPONENT# does not exist -> (0, 0, 0)
  oppPos[0] = wm.getObjectPosition(Types::OPPONENT1).getMu();
  oppPos[0].setZ(0.0);
  oppPos[1] = wm.getObjectPosition(Types::OPPONENT2).getMu();
  oppPos[1].setZ(0.0);
  oppPos[2] = wm.getObjectPosition(Types::OPPONENT3).getMu();
  oppPos[2].setZ(0.0);
/*
  for(int i=0; i<3; i++){
	std::cout << "opp" << i + 1 << "Pos = (" << oppPos[i].getX() << ", " << oppPos[i].getY() << ", " << oppPos[i].getZ() << ")" << std::endl;
  }std::cout << std::endl;
*/
  double oppDist[] = {(oppPos[0] - oppGoalCenter).length(),
				(oppPos[1] - oppGoalCenter).length(),
				(oppPos[2] - oppGoalCenter).length()};
  int unum[] = {1, 2, 3};
  if(count == 0){
	for(int i=1; i<3; i++){
	  if(oppDist[0] > oppDist[i]){
		double tmp_d = oppDist[0];
		oppDist[0] = oppDist[i];
		oppDist[i] = tmp_d;
		int tmp_i = unum[0];
		unum[0] = unum[i];
		unum[i] = tmp_i;
	  }
	}
	count++;
  }
/*
  for(int i=0; i<3; i++){
	std::cout << "opp" << i + 1 << "Pos = (" << oppPos[i].getX() << ", " << oppPos[i].getY() << ", " << oppPos[i].getZ() << ")" << std::endl;
  }std::cout << "unum = {" << unum[0] << ", " << unum[1] << ", " << unum[2] << "}" << std::endl;
  std::cout << "oppDist = {" << oppDist[0] << ", " << oppDist[1] << ", " << oppDist[2] << "}" << std::endl;
*/
  Vector3D targetPos = (wm.getObjectPosition(Types::BALL).getMu() * 2.0 + oppPos[unum[1] - 1] * 1.0) / 3.0;
//  Vector3D targetPos = oppPos[unum[0] - 1];
  targetPos.setZ(0.0);

/*
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  ballPos.setZ(0.0);
//  Vector3D goalPos = (wm.getObjectPosition(Types::GOAL1THEM).getMu() + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2.0;

  Vector3D goal1Pos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  goal1Pos.setZ(0.0);
  Vector3D goal2Pos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  goal2Pos.setZ(0.0);

  Vector3D g1ToBall = ballPos - goal1Pos;
  Vector3D g1ToG2 = goal2Pos - goal1Pos;
	
  double k = g1ToBall.dotProduct(g1ToG2) / (g1ToG2.length() * g1ToG2.length());

  if(k < 0 || k > 1)
	k = 0.5;
	
  Vector3D dest = goal2Pos * k + goal1Pos * (1 - k);
  Vector3D targetPos = ballPos - (dest - ballPos).normalize() * 0.3;
*/
//  std::cout << "ballPos.length() = " << ballPos.length() << ": (" << ballPos.getX() << ", " << ballPos.getY() << ")" << std::endl;
  
  con->addVar("Pos", targetPos);
  con->addVar("OppPos", oppPos[unum[1] - 1]);
/*
  switch (step)
  {
    case 0:
      con->addVar("Pos", balPos);
      break;
      
    case 1:
      break;
  }
*/
/*
  switch (step)
  {
	case 0:
		destination = wm.getObjectPosition(Types::SELF).getMu();
//		std::cout << destination.getX() << ", " << destination.getY() << ", " << destination.getZ() << std::endl;
//		destination.setX((wm.getObjectPosition(Types::FLAG1L).getMu().getX() + wm.getObjectPosition(Types::FLAG2L).getMu().getX()) / 2.0);
		destination.setX( wm.getObjectPosition(Types::FLAG1THEM).getMu().getX() );	
		con->addVar("Pos", destination);
		break;
		
	case 1:
		break;
  }
*/	  
  // con->addVar("Var", 0, 1);
  
  return goal;
}
