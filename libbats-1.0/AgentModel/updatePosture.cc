#include "agentmodel.ih"

void AgentModel::updatePosture()
{
  assert(d_torso);
  
  Cochlea& cochlea = SCochlea::getInstance();
  WorldModel& wm = SWorldModel::getInstance();
  
  list<rf<BodyPart> > partQueue;

  d_torso->transform = wm.getFieldTransform().inverse();

  partQueue.push_back(d_torso);
  
  while (!partQueue.empty())
  {
    rf<BodyPart> part = partQueue.front();
    partQueue.pop_front();
    
    if (rf<Limb> limb = rf_dynamic_cast<Limb>(part))
    {
      _debugLevel4(limb->name << " " << limb->transform.trans() << " " << limb->relativeWeight);
      for (vector<rf<Joint> >::iterator iter = limb->joints.begin(); iter != limb->joints.end(); ++iter)
      {
        rf<Joint> joint = *iter;
        _debugLevel4(joint->name << " " << joint->anchors.first);
        joint->transform = limb->transform *
                           Matrix4D::translation(joint->anchors.first);
                           
        partQueue.push_back(joint);
      }
    }
    else
    {
      rf<Joint> joint = rf_dynamic_cast<Joint>(part);
      _debugLevel4(joint->name << " " << joint->transform.trans() << " " << cochlea.getInfo(cochlea.translateInfo(joint->name))[0]);
      joint->angle.init(Math::degToRad(cochlea.getInfo(cochlea.translateInfo(joint->name))[0]), 1.0);
      _debugLevel4(joint->name << " " << -joint->anchors.second);
      
      rf<BodyPart> part2 = joint->bodyPart;
      part2->transform = joint->transform *
                          Matrix4D::rotation(joint->axis, joint->angle.getMu()) *
                          Matrix4D::translation(-joint->anchors.second);
                          
      partQueue.push_back(part2);
    }
  }
  
}
