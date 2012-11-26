#include "predicate.ih"

void Predicate::copy(Predicate const &other)
{
  //  AST::Node::copy(other);
  d_value = other.d_value;
}
