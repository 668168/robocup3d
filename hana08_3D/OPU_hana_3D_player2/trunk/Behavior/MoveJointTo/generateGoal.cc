#include "movejointto.ih"

rf<Behavior::Goal> MoveJointTo::generateGoal(unsigned step, unsigned slot)
{
	WorldModel& wm = WorldModel::getInstance();
	
  // Get our own goal.
  rf<StateVarNode> angleNode = rf_cast<StateVarNode>(d_goal->findDeep("Angle"));
  if (!angleNode)
  {
    throw runtime_error("MoveJointTo behavior did not recieve 'Angle' goal");
  }
  Range angleRange = angleNode->getVar().second;
  double goalAngle = angleRange.mean();

  rf<StateVarNode> maxSpeedNode = rf_cast<StateVarNode>(d_goal->findDeep("MaxSpeed"));
  double maxSpeed = 0;
  if (maxSpeedNode)
  {
    Range maxSpeedRange = maxSpeedNode->getVar().second;
    maxSpeed = maxSpeedRange.mean();
  }

  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

	
	NormalDistribution1D angle = wm.getJointAngle(d_joint);
	//double da = Math::normalizeRad(goalAngle - angle.getMu());
	double da = goalAngle - angle.getMu();
	
#ifdef EXPSPEED	
	double speed = (exp(da) - 1) * d_gain;
#else
	double speed = d_gain * da;
#endif

	speed = d_gain * da;
	//double minspeed = 0.005;
	//if(speed < minspeed && speed > -minspeed)
	//	speed = 0.0;
	//cout << speed << "\n";

	
	if (maxSpeed > 0)
	{
    if (speed > maxSpeed)
      speed = maxSpeed;
    if (speed < -maxSpeed)
      speed = -maxSpeed;
  }
  else if (maxSpeed < 0)
    speed *= 2;
	  
	  
	_debugLevel4(ident() << ": " << goalAngle << " " << angle.getMu() << " " << da << " " << speed << " " << maxSpeed);
	
	con->addVar("Speed", speed, speed);
	con->addVar("Joint", d_joint, d_joint);
	
	return goal;
}
