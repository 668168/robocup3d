#include "getupfrombelly.ih"

GetUpFromBelly::GetUpFromBelly(string const &id, string const &playerClass)
  : Behavior("GetUpFromBelly", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
