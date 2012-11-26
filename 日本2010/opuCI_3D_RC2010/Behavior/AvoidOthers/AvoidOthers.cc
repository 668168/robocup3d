#include "avoidothers.ih"

AvoidOthers::AvoidOthers(string const &id, string const &playerClass)
  : Behavior("AvoidOthers", id, playerClass),d_zoneToGo(nozone),d_ballZone(nozone)
{
	d_tree = new AST::Node(sequenceType);
	d_tree->addChild(new AST::Node(andType));
	d_tree->getChild(0)->addChild(new AST::Node(orType));
}
