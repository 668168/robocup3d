#include "path.ih"

Path::Path(string const &_path)
{
  string elem;

  for (string::const_iterator i = _path.begin();
       i != _path.end(); ++i) {
    if ((*i) == '/') {
      if (!elem.empty()) {
        if (elem == "#")
          path.push_back("");
        else
          path.push_back(elem);
        elem.clear();
      }
      path.push_back("/");
    } else
      elem += *i;
  }

  if (!elem.empty()) {
    if (elem == "#")
      path.push_back("");
    else
      path.push_back(elem);
  }
}
