#include "conf.ih"


XMLNode Conf::getSection(std::string const &gamestate, std::string const &name)
{
  XMLNode node(xmlDocGetRootElement(d_doc));

  for (XMLNode i = node.getChildren(); i; i = i.getNext())
    if (i.getName() == "gamestate" &&
	i.getProp("id") == gamestate)
      return i.find(name);

  return 0;
}
