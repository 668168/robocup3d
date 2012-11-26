#include "behavior.ih"

void Behavior::reset()
{
  d_reset = true;
  d_committed = false;
	_debugLevel4("Resetting " << ident());
//	std::cout << "Resetting " << ident() << std::endl;

  d_lastChosen.clear();
try
{
  d_curStep = -1;
  if (!d_tree)
    return;
    
  for (AST::Node::iterator seqIter = d_tree->begin(); seqIter != d_tree->end(); ++seqIter)
  {
    rf<AST::Node> stepNode = *seqIter;
    for (AST::Node::iterator slotIter = stepNode->begin(); slotIter != stepNode->end(); ++slotIter)
    {
      rf<AST::Node> slotNode = *slotIter;
      for (AST::Node::iterator behIter = slotNode->begin(); behIter != slotNode->end(); ++behIter)
      {
        rf<BehaviorNode> bNode = rf_cast<BehaviorNode>(*behIter);
        bNode->getBehavior()->reset();
      }
    }
  }
}
catch (BatsException *e)
{
  BATS_CATCH_FRAME(e);
}
}
