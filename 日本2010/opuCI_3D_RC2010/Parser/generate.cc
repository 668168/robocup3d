#include "parser.ih"

string Parser::generate(rf<Predicate> const &pred)
{
  stringstream sstrm;
  
  pred->generate(sstrm);

  return sstrm.str();
}
