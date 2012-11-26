#include "freeze.ih"

Freeze::Freeze(string const &id, string const &playerClass)
    : Behavior("Freeze", id, playerClass),
      d_startCounting(false)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));

}
