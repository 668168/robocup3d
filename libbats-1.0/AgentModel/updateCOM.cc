#include "agentmodel.ih"

void AgentModel::updateCOM()
{
  list<rf<BodyPart> > partQueue;
  partQueue.push_back(d_torso);
  Vector3D com(0, 0, 0);
  
  while (!partQueue.empty())
  {
    rf<BodyPart> part = partQueue.front();
    partQueue.pop_front();
    while (rf<Joint> joint = rf_dynamic_cast<Joint>(part))
      part = joint->bodyPart;
    
    rf<Limb> limb = rf_dynamic_cast<Limb>(part);
    
    com += limb->transform.trans() * limb->relativeWeight;
    for (vector<rf<Joint> >::iterator iter = limb->joints.begin(); iter != limb->joints.end(); ++iter)
    {
      rf<Joint> joint = *iter;
      partQueue.push_back(joint->bodyPart);
    }
  }
  _debugLevel4(com);
  d_COM = com;
}
