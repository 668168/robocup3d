#include "challenge1.ih"

Challenge1::Challenge1(string const &id, string const &playerClass)
  : Behavior("Challenge1", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
