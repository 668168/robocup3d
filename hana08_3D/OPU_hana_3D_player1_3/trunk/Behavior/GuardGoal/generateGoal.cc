#include "guardgoal.ih"

rf<Behavior::Goal> GuardGoal::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  //if (step == 1)
  //{

    WorldModel& wm = WorldModel::getInstance();
    Vector3D goalCenter = (wm.getObjectPosition(Types::GOAL1US).getMu() + wm.getObjectPosition(Types::GOAL2US).getMu()) / 2;

    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

    Vector3D goalLine = wm.getObjectPosition(Types::GOAL1US).getMu() - wm.getObjectPosition(Types::GOAL2US).getMu();

    Vector3D dir = ballPos - goalCenter;
    double alpha = fabs(dir.angle(Math::calcPerpend(goalLine)));
    
    double dist = 3.0 + alpha / (.5 * M_PI) * 2.0;
    
    Vector3D pos = goalCenter + dir.normalize() * dist;
    con->addVar("Pos",pos);

    //if (d_ballEndPos.getY() < d_goalL.getY()) {
      //if (slot == 0) {
        // Move to the left goal post.
        //con->addVar("Pos",Vector3D(0.0,d_goalL.getY()+1,0));
        //      cerr << "Want to move to 1: " << Vector3D(0.0,d_goalL.getY()+1,0) << endl;
      //} else {
      //  angle = -0.5*M_PI + atan(d_goalL.getX()/d_goalL.getY());
      //  con->addVar("Angle",angle,angle);
      //  cerr << "Want to turn " << angle << endl;
      //}
    //} else if (d_ballEndPos.getY() > d_goalR.getY()) {
      //if (slot == 0) {
        // Move to the right goal post.
        //con->addVar("Pos",Vector3D(0.0,d_goalR.getY()-1,0));
        //      cerr << "Want to move to 2: " << Vector3D(0.0,d_goalL.getY()-1,0) << endl;
      //}/* else {
      //  angle = -0.5*M_PI + atan(d_goalR.getX()/d_goalR.getY());
      //  con->addVar("Angle",angle,angle);
      //  cerr << "Want to turn " << angle << endl;
      //}*/
    //} else {
      // Move in that direction.
    //    con->addVar("Pos",d_ballEndPos);
    //}
  /*}
  else
  {
    WorldModel& wm = WorldModel::getInstance();
    
    Vector3D goalLine = wm.getObjectPosition(Types::GOAL1US).getMu() - wm.getObjectPosition(Types::GOAL2US).getMu();
    goalLine.setZ(0);
    Vector3D straight(1, 0, 0);
    Vector3D goalDir;
    goalDir.setX(goalLine.getY());
    goalDir.setY(goalLine.getX());

    double angle = straight.angle(goalDir);
    if (goalDir.getY() < 0)
      angle = -angle;
    if (angle > .5 * M_PI)
      angle = -M_PI + angle;
    if (angle < -.5 * M_PI)
      angle = M_PI + angle;
      

    con->addVar("Angle",angle,angle);
    cerr << "Want to turn " << angle << endl;
  }*/
  return goal;
}
