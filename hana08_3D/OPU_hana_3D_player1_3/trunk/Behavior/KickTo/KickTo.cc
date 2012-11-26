#include "kickto.ih"

KickTo::KickTo(string const &id, string const &playerClass)
  : Behavior("KickTo", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(1)->addChild(new AST::Node(orType));
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(2)->addChild(new AST::Node(orType));
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(3)->addChild(new AST::Node(orType));
//  d_tree->addChild(new AST::Node(andType));
//  d_tree->getChild(4)->addChild(new AST::Node(orType));
  
}
