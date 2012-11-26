#include "types.ih"
Types::Object Types::objectEnumFor(std::string const &a, Types::Object def)
{
      for(size_t i = 0; i < Types::NOBJECTS; ++i)
    {
      Types::Object o = static_cast<Types::Object>(i);
      if(a == nameOf(o))
      {
        def = o;
        break;
      }
    }
  return def;
}
