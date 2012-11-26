#include "cornerkickright.ih"

CornerKickRight::CornerKickRight(string const &id, string const &playerClass)
  : Behavior("CornerKickRight", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
