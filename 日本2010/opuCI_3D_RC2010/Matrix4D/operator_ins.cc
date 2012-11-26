#include "matrix4d.hh"

std::ostream& bats::operator<<(std::ostream &out, bats::Matrix4D const& mat)
{
  out << mat.get(0, 0) << "\t" << mat.get(0, 1) << "\t" << mat.get(0, 2) << "\t" << mat.get(0, 3) << std::endl <<
         mat.get(1, 0) << "\t" << mat.get(1, 1) << "\t" << mat.get(1, 2) << "\t" << mat.get(1, 3) << std::endl <<
         mat.get(2, 0) << "\t" << mat.get(2, 1) << "\t" << mat.get(2, 2) << "\t" << mat.get(2, 3) << std::endl <<
         mat.get(3, 0) << "\t" << mat.get(3, 1) << "\t" << mat.get(3, 2) << "\t" << mat.get(3, 3) << std::endl;
                
  return out;
  
}
