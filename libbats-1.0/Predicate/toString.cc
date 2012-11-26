#include "predicate.hh"

using namespace bats;
using namespace std;

string Predicate::toString()
{
  std::ostringstream o;
  o.precision(5); //Make sure we don't place to many decimals on the output.
  generate(o);
  return o.str();
}
