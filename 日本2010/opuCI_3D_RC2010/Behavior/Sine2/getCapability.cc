#include "sine2.ih"

Behavior::ConfidenceInterval Sine2::getCapability(rf<State> s, rf<Goal> g)
{
  stringstream ss;
  int i=0;
  ss << "Weight" << (i+1);

  // Weight1, Weight2, ...
  rf<StateVarNode> node = rf_cast<StateVarNode>(g->findDeep(ss.str()));

  // Get weights from goal
  double dTime = 0.07, threshould = 0.3; // dTime * threshould ~= 0.02

  while( node )
  {
    double newWeight = node->getVar().second.mean();

    if( d_factor == 1 && d_weights.at(i) - newWeight > threshould )
    {
      d_weights.at(i) += (newWeight - d_weights.at(i)) * dTime / d_startupTime;
    }
    else
      d_weights.at(i) = newWeight;

    ss.str(""); i++;
    ss << "Weight" << (i+1);
    node = rf_cast<StateVarNode>(g->findDeep(ss.str()));
  }

  return ConfidenceInterval(0.3, 0.1);
}
