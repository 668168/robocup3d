#include "sine2.ih"

void Sine2::update()
{
//  std::cout << " -> Sine2::update()" << std::endl;
  Behavior::update();

  d_committed = d_committed || d_factor < 1.0;

}

