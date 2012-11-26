#include "cankickleft.ih"

CanKickLeft::CanKickLeft(string const &id, string const &playerClass)
  : Behavior("CanKickLeft", id, playerClass)
{
  //  XMLNodeSet params = getParams("/settings");



  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(1)->addChild(new AST::Node(orType));
}
