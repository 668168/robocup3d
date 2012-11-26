#include "predicate.ih"

namespace bats {

  ostream &Predicate::generate(ostream &os) const
  {
    if (isLeaf())
      os << d_value;
    else {
      if (!isList())
	os << "(" << d_value;

      for (AST::Node::NodeVector::const_iterator i = d_nodes.begin();
	   i != d_nodes.end(); ++i) {
	os << " ";
	rf_cast<Predicate>(*i)->generate(os);
      }

      if (!isList())
	os << ")";
    
    }

    return os;
  }

}
