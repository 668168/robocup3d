#include "path.ih"

Path::Path(char const* _path)
{
  init(_path);
}

Path::Path(string const &_path)
{
  init(_path);
}
