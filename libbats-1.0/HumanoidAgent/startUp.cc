#include "humanoidagent.ih"

void HumanoidAgent::startUp()
{
  // Before messages can be parsed, the parser should be initialized.
  Parser::initialize();

  if (d_confFile != "")
    SConf::getInstance().setFile(d_confFile);
  
  AgentModel& am = SAgentModel::getInstance();
  am.setUnum(d_unum);
  am.initBody();
  
  //  WorldModel& wm = SWorldModel::getInstance();
  SAgentSocketComm::getInstance().connect();

  rf<Predicate> scene = new Predicate("scene");
  scene->pushLeaf("rsg/agent/" + am.getRSG());
    
  _debugLevel4(*scene);
  SAgentSocketComm::getInstance().send(scene);

  // Set blokcing mode.
  //  d_comm.setBlocking(true);
}
