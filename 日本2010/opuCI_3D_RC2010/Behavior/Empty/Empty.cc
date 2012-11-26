#include "empty.ih"

      Empty::Empty(std::string const &id, std::string const &playerClass)
        : Behavior("Empty", id)
      {
        // Single slot
        d_tree = new AST::Node(sequenceType);
        for(unsigned i = 0; i < 4; ++i)
        {
	        d_tree->addChild(new AST::Node(andType));
	        d_tree->getChild(i)->addChild(new AST::Node(orType));
	        d_tree->getChild(i)->addChild(new AST::Node(orType));
	        d_tree->getChild(i)->addChild(new AST::Node(orType));
	        d_tree->getChild(i)->addChild(new AST::Node(orType));
	        d_tree->getChild(i)->addChild(new AST::Node(orType));
	        d_tree->getChild(i)->addChild(new AST::Node(orType));
	        d_tree->getChild(i)->addChild(new AST::Node(orType));
        }
      }
