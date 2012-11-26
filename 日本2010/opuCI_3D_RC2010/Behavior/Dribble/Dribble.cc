#include "dribble.ih"

Dribble::Dribble(string const &id, string const &playerClass)
    : Behavior("Dribble", id, playerClass),
      d_doStabilityCheck(false),
      d_startTimeUpdated(false)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(1)->addChild(new AST::Node(orType));
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(2)->addChild(new AST::Node(orType));

//  d_doStabilityCheck = false;
//  d_startTimeUpdated = false;
}
