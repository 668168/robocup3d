#include "canturnright.ih"

CanTurnRight::CanTurnRight(string const &id, string const &playerClass)
  : Behavior("WalkTo", id, playerClass)
{
  //  XMLNodeSet params = getParams("/settings");


  d_committed = true;
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
