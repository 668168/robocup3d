#include "beamto.ih"

BeamTo::BeamTo(string const &id, string const &playerClass)
  : Behavior("BeamTo", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
  
  d_x = getParam("/where/@x", 0.0);
  d_y = getParam("/where/@y", 10.0);
  d_z = getParam("/where/@z", 0.0);
  
//  std::cout << "Con: (X, Y, Z) = (" << d_x << ", " << d_y << ", " << d_z << ")" << std::endl;  
}
