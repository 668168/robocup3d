#include "guardgoal.ih"

GuardGoal::GuardGoal(string const &id, string const &playerClass)
  : Behavior("GuardGoal", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
//  d_tree->addChild(new AST::Node(andType));
//  d_tree->getChild(1)->addChild(new AST::Node(orType));
}
