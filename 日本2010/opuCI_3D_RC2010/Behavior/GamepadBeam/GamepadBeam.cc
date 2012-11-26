#include "gamepadbeam.ih"

GamepadBeam::GamepadBeam(string const &id, string const &playerClass)
  : Behavior("GamepadBeam", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));

//  d_x = getParam("/where/@x", 0.0);
//  d_y = getParam("/where/@y", 10.0);
//  d_z = getParam("/where/@z", 0.0);
  WorldModel& wm = WorldModel::getInstance();
  d_x = -1.0 * static_cast<int>((wm.getUnum()+4) / 5);
  d_y = wm.fieldWidth() * ( 0.4 - 0.2 * ((wm.getUnum() -1) % 5));
  d_z = 0;

}
