#include "strafetoball.ih"

rf<Behavior::Goal> StrafeToBall::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  if (step == 1) {

    WorldModel& wm = WorldModel::getInstance();

    // The ball position.
    Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();
    
    //cerr << "I'M STRAFING!!" << endl;

    con->addVar("PosX", 1.0, 1.0);
    con->addVar("PosY", ball.getY(), ball.getY());
    con->addVar("PosZ", 0.0, 0.0);
  
  }

  return goal;
}
