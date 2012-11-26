#include "agentmodel.ih"

double AgentModel::initBody(XMLNode& part1Node, string playerClass, rf<Joint> joint)
{
  Conf& conf = SConf::getInstance();
  Cochlea& cochlea = SCochlea::getInstance();
  
  _debugLevel4("Attaching " << part1Node.getProp("name") << " to " << (joint ? joint->name : "nothing"));
  double weight = 0;
  
  // Create current part. Check whether it is a body part or a joint (happens when joints are attached to joints, ie universal joints)
  if (part1Node.getName() == "bodypart")
  {
    _debugLevel4("Got a body part");
    
    rf<Limb> p = new Limb();
    p->name = part1Node.getProp("name");
    d_limbs[d_limbNameMap[p->name]] = p;
    
    weight = p->weight = atof(part1Node.getProp("weight").c_str());
    p->relativeWeight = 0;
    if (part1Node.hasProp("sizex"))
    {
      p->size[0] = atof(part1Node.getProp("sizex").c_str());
      p->size[1] = atof(part1Node.getProp("sizey").c_str());
      p->size[2] = atof(part1Node.getProp("sizez").c_str());
    }
    
    if (joint)
      joint->bodyPart = p;
    else
      d_torso = p;

    // Find joints or parts attached to this part
    string path = "/conf/player-class[@id='" + playerClass + "']/agentmodel/joint[@part1='" + part1Node.getProp("name") + "']";
    XMLNodeSet set = conf.selectXPath(path);

    _debugLevel4(path);
    _debugLevel4("Joints connected to part: " << set.size());
    
    for (XMLNodeSet::iterator iter = set.begin(); iter != set.end(); ++iter)
    {
      XMLNode jointNode = *iter;
      _debugLevel4("Attaching " << jointNode.getProp("name") << " to " << part1Node.getProp("name"));
      
      rf<Joint> j = new Joint();
      j->name = jointNode.getProp("name");
      j->perceptor = jointNode.getProp("perceptor");
      j->effector = jointNode.getProp("effector");
      
      if (jointNode.hasProp("ujindex"))
      {
        j->universal = true;
        j->ujindex = atoi(jointNode.getProp("ujindex").c_str());
        if (j->ujindex == 0)
          cochlea.setTranslation(j->perceptor, j->name);
      }
      else
      {
        j->universal = false;
        j->ujindex = 0;
        cochlea.setTranslation(j->perceptor, j->name);
      }
      d_joints[d_jointNameMap[j->name]] = j;

      j->axis[0] = atof(jointNode.getProp("axisx").c_str());
      j->axis[1] = atof(jointNode.getProp("axisy").c_str());
      j->axis[2] = atof(jointNode.getProp("axisz").c_str());
      
      vector<XMLNode> anchors;
      jointNode.findAll(anchors, "anchor");
      _debugLevel4(anchors.size());
      
      if (anchors[0].getProp("index") != "0")
        reverse(anchors.begin(), anchors.end());
        
      j->anchors.first[0] = atof(anchors[0].getProp("x").c_str());
      j->anchors.first[1] = atof(anchors[0].getProp("y").c_str());
      j->anchors.first[2] = atof(anchors[0].getProp("z").c_str());
      
      j->anchors.second[0] = atof(anchors[1].getProp("x").c_str());
      j->anchors.second[1] = atof(anchors[1].getProp("y").c_str());
      j->anchors.second[2] = atof(anchors[1].getProp("z").c_str());
      
      p->joints.push_back(j);
    
      path = "/conf/player-class[@id='" + playerClass + "']/agentmodel/*[@name='" + jointNode.getProp("part2") + "']";
      _debugLevel4(path);
      XMLNodeSet set2 = conf.selectXPath(path);
      XMLNode part2Node = set2.front();
      weight += initBody(part2Node, playerClass, j);
    }
  }
  else
  {
    _debugLevel4("Got a joint part");

    rf<Joint> j = new Joint();
    j->name = part1Node.getProp("name");
    j->perceptor = part1Node.getProp("perceptor");
    j->effector = part1Node.getProp("effector");
    
    if (part1Node.hasProp("ujindex"))
    {
      j->universal = true;
      j->ujindex = atoi(part1Node.getProp("ujindex").c_str());
      if (j->ujindex == 0)
        cochlea.setTranslation(j->perceptor, j->name);
    }
    else
    {
      j->universal = false;
      j->ujindex = 0;
      cochlea.setTranslation(j->perceptor, j->name);
    }
    
    d_joints[d_jointNameMap[j->name]] = j;

    j->axis[0] = atof(part1Node.getProp("axisx").c_str());
    j->axis[1] = atof(part1Node.getProp("axisy").c_str());
    j->axis[2] = atof(part1Node.getProp("axisz").c_str());

    vector<XMLNode> anchors;
    part1Node.findAll(anchors, "anchor");
      _debugLevel4(anchors.size());
    if (anchors[0].getProp("index") != "0")
      reverse(anchors.begin(), anchors.end());
      
    j->anchors.first[0] = atof(anchors[0].getProp("x").c_str());
    j->anchors.first[1] = atof(anchors[0].getProp("y").c_str());
    j->anchors.first[2] = atof(anchors[0].getProp("z").c_str());
    
    j->anchors.second[0] = atof(anchors[1].getProp("x").c_str());
    j->anchors.second[1] = atof(anchors[1].getProp("y").c_str());
    j->anchors.second[2] = atof(anchors[1].getProp("z").c_str());

    joint->bodyPart = j;
    
    // Find part attached to joint
    string path = "/conf/player-class[@id='" + playerClass + "']/agentmodel/*[@name='" + part1Node.getProp("part2") + "']";
    _debugLevel4(path);
    XMLNodeSet set = conf.selectXPath(path);
    XMLNode part2Node = set.front();
    weight += initBody(part2Node, playerClass, j);
  }
  
  return weight;
  _debugLevel4("Done attaching!");
}
