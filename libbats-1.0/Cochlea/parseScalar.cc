#include "cochlea.ih"

Vector4F Cochlea::parseScalar(rf<Predicate> const &pred)
{
  Vector4F res;
  res.setX(*rf_cast<Predicate>(pred->getChild(0)));
  return res;
}

