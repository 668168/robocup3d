#include "predicate.ih"

namespace bats {

  /**
   *  This should be moved to AST::Node!
   */
  ostream &operator<<(ostream &os, Predicate const &pred)
  {
    if (pred.isLeaf())
      os << pred.d_value;
    else {
      os << "(" << pred.d_value;

      if (!pred.isList() && !pred.isLeaf())
	os << " ";

      for (AST::Node::NodeVector::const_iterator i = pred.d_nodes.begin();
	   i != pred.d_nodes.end(); ++i)
	os << (i != pred.d_nodes.begin()?" ":"") << *rf_cast<Predicate>(*i);

      os << ")";
    
    }
    return os;
  }

}
