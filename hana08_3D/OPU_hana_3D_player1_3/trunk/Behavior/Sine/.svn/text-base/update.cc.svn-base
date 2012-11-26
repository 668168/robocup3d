#include "sine.ih"

void Sine::update()
{
//  std::cout << " -> Sine::update()" << std::endl;
  Behavior::update();
  

  d_committed = d_committed || d_factor < 1.0;
      
  _debugLevel4(ident() << " committed: " << (d_committed ? "yes" : "no"));
}

