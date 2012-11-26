#include "search.ih"

Search::Search(string const &id, string const &playerClass)
  : Behavior("Search", id, playerClass),
    d_searchStartTime(0),
    d_timeoutStart(0),
    d_timeout(false)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
