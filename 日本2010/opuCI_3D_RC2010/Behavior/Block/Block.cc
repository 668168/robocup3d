#include "block.ih"

Block::Block(string const &id, string const &playerClass)
    : Behavior("Block", id, playerClass),
      d_ballHoldTime(0)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
