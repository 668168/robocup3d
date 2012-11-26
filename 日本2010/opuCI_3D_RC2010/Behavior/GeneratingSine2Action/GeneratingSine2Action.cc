#include "generatingsine2action.ih"

GeneratingSine2Action::GeneratingSine2Action(string const &id, string const &playerClass)
  : Behavior("GeneratingSine2Action", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
