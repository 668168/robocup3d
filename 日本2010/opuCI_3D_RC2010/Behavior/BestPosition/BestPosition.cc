#include "bestposition.ih"

BestPosition::BestPosition(string const &id, string const &playerClass)
    : Behavior("BestPosition", id, playerClass),
      d_positioning(false)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
