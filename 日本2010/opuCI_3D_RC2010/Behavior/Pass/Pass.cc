#include "pass.ih"

Pass::Pass(string const &id, string const &playerClass)
  : Behavior("Pass", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
