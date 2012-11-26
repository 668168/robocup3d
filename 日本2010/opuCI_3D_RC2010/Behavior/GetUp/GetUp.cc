#include "getup.ih"

GetUp::GetUp(string const &id, string const &playerClass)
    : Behavior("GetUp", id, playerClass),
      d_nearBallTime(0), d_startTime(0), d_startTimeUpdated(false)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(1)->addChild(new AST::Node(orType));
}
