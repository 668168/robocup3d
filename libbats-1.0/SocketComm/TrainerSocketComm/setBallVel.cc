#include "trainersocketcomm.ih"

void TrainerSocketComm::setBallVel(Vector3D const& vel)
{
  send(makeSetBallVelMessage(vel));
}

rf<Predicate> TrainerSocketComm::makeSetBallVelMessage(Vector3D const& vel)
{
  rf<Predicate> msg = new Predicate("ball");
  rf<Predicate> velPred = rf_cast<Predicate>(msg->addChild(new Predicate("vel")));
  velPred->pushLeafs(vel);
  return msg;
}

