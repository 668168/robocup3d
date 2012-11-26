#include "beam.ih"


using namespace bats;

bool Beam::run()
{
//  _debugLevel4("Beam is being run!");
  //  Parser parser;

//  _debugLevel4((rf_cast<StateVarNode>(d_goal->findDeep("X")) ? "got X" : "dont have X"));
//  _debugLevel4((rf_cast<StateVarNode>(d_goal->findDeep("Y")) ? "got Y" : "dont have Y"));
//  _debugLevel4((rf_cast<StateVarNode>(d_goal->findDeep("Z")) ? "got Z" : "dont have Z"));
  
  StateVar x = rf_cast<StateVarNode>(d_goal->findDeep("X"))->getVar();
  Range xrange = x.second;
  StateVar y = rf_cast<StateVarNode>(d_goal->findDeep("Y"))->getVar();
  Range yrange = y.second;
  StateVar z = rf_cast<StateVarNode>(d_goal->findDeep("Z"))->getVar();
  Range zrange = z.second;
  
//  std::cout << "X: (" << xrange.getFirst() << ", " << xrange.getSecond() << ")" << std::endl;
//  std::cout << "Y: (" << yrange.getFirst() << ", " << yrange.getSecond() << ")" << std::endl; 
//  std::cout << "Z: (" << zrange.getFirst() << ", " << zrange.getSecond() << ")" << std::endl;   

  // This is faster than using the parser.
  d_action = new Cerebellum::BeamAction(Vector3D(xrange.mean(), yrange.mean(), zrange.mean()));
//  d_action = new Cerebellum::BeamAction(Vector3D(-9, 0, 0));  
//  std::cout << "Add action: " << d_action->type << std::endl;

  addToActionCommandBehaviors();
  
  return true;
}
