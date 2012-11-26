#include "cochlea.ih"

Vector4F Cochlea::parseVect(rf<Predicate> const &pred)
{
  assert(pred);        

  Vector4F res;
  for (unsigned i = 0; i < pred->size(); ++i)
    res.set(i,*rf_cast<Predicate>(pred->getChild(i)));
  return res;
}

