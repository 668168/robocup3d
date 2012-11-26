#include "vector4.hh"

namespace bats {

  std::ostream &operator<<(std::ostream &_os, Vector4F const &_vect)
  {
    return _os << "(" << _vect.d_values[0] << "," << _vect.d_values[1] << "," << _vect.d_values[2] << "," << _vect.d_values[3] << ")";
  }

}
