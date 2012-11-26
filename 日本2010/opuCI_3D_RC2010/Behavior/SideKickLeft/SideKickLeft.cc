#include "sidekickleft.ih"

SideKickLeft::SideKickLeft(string const &id, string const &playerClass)
  : Behavior("SideKickLeft", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(1)->addChild(new AST::Node(orType));
}
