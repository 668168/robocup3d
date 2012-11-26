#include "humanoidagent.ih"

void HumanoidAgent::startUp()
{
  // Before messages can be parsed, the parser should be initialized.
  Parser::initialize();

  WorldModel::initialize(d_comm/*, d_teamName*/);
  
  WorldModel::getInstance().setUnum(d_unum);


  //  WorldModel& wm = WorldModel::getInstance();
  d_comm.connect();

  rf<Predicate> scene = new Predicate("scene");
//  scene->pushLeaf("rsg/agent/soccerbot056.rsg");
//  scene->pushLeaf("rsg/agent/soccerbot058/soccerbot.rsg");
  scene->pushLeaf("rsg/agent/nao/nao.rsg");
//  scene->pushLeaf("rsg/agent/soccerbot_x7.rsg");
//  scene->pushLeaf("rsg/agent/soccerbotcomp.rsg");
  _debugLevel4(*scene);
  d_comm.send(scene);

  // Set blokcing mode.
  //  d_comm.setBlocking(true);
}
