#include "dive.ih"

Dive::Dive(string const &id, string const &playerClass)
  : Behavior("Dive", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
