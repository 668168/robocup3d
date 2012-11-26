#include "defense.ih"

Defense::Defense(string const &id, string const &playerClass)
  : Behavior("Defense", id, playerClass),d_minTime(0),d_minTimeUpdate(false)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
