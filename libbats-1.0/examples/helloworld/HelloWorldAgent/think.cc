#include "helloworldagent.ih"

void HelloWorldAgent::think()
{
  // The WorldModel keeps track of the state of the world, e.g. play mode, time,
  // players/opponents/ball positions, et cetera
  WorldModel& wm = SWorldModel::getInstance();
  
  // The AgentModel keeps track of the state of the robot, e.g. joint angles,
  // location of COM, et cetera
  AgentModel& am = SAgentModel::getInstance();
  
  // The Cerebellum collects actions to perform, integrating them where necesary
  Cerebellum& cer = SCerebellum::getInstance();
  
  // Get the current time
  double t = wm.getTime();
  
  // Get the current angles of some shoulder joints
  double angles[4];
  angles[0] = am.getJoint(Types::LARM1)->angle.getMu();
  angles[1] = am.getJoint(Types::LARM2)->angle.getMu();
  angles[2] = am.getJoint(Types::RARM1)->angle.getMu();
  angles[3] = am.getJoint(Types::RARM2)->angle.getMu();
  
  // Determine target angles for joints
  double targets[4];
  targets[0] = 0.5 * M_PI;
  targets[1] = 0.25 * M_PI * sin(t / 2.0 * 2 * M_PI) + 0.25 * M_PI;
  targets[2] = 0.5 * M_PI;
  targets[3] = -0.25 * M_PI * sin(t / 2.0 * 2 * M_PI) - 0.25 * M_PI;
  
  // Determine angular velocities needed to achieve these goal angles;
  double velocities[4];
  for (unsigned i = 0; i < 4; ++i)
    velocities[i] = 0.1 * (targets[i] - angles[i]);
  
  // Add actions to the Cerebellum
  cer.addAction(new Cerebellum::MoveJointAction(Types::LARM1, velocities[0]));
  cer.addAction(new Cerebellum::MoveJointAction(Types::LARM2, velocities[1]));
  cer.addAction(new Cerebellum::MoveJointAction(Types::RARM1, velocities[2]));
  cer.addAction(new Cerebellum::MoveJointAction(Types::RARM2, velocities[3]));
  
  // Tell Cerebellum to send the actions to the server
  cer.outputCommands(SAgentSocketComm::getInstance());
}

