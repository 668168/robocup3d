#include "canturnleft.ih"

CanTurnLeft::CanTurnLeft(string const &id, string const &playerClass)
  : Behavior("CanTurnLeft", id, playerClass)
{
  d_committed = true;
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
