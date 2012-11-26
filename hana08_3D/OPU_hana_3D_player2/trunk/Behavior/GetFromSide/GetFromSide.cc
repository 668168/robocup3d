#include "getfromside.ih"

GetFromSide::GetFromSide(string const &id, string const &playerClass)
  : Behavior("GetFromSide", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
