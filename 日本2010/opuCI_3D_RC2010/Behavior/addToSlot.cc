#include "behavior.ih"

void Behavior::addToSlot(rf<Behavior> behavior, unsigned step, unsigned slot)
{
  rf<BehaviorNode> behaviorNode = new BehaviorNode(behavior);
  
//  std::cout << ident() << ": " << step << " >= " << d_tree->size() << std::endl; 
  if (step >= d_tree->size())
    throw runtime_error(ident() + ":" + behavior->ident() + ": not enough steps");

  if (slot >= d_tree->getChild(step)->size())
    throw runtime_error(ident() + ":" + behavior->ident() + ": not enough slots");

  d_tree->getChild(step)->getChild(slot)->addChild(rf_cast<AST::Node>(behaviorNode));
}
