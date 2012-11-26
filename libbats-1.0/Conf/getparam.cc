#include "conf.ih"

XMLNode Conf::getParam(std::string const &name)
{
	_debugLevel1(name);
  XMLNodeSet nodes = selectXPath(std::string("/conf/parameters/") + name);

  return (nodes.empty() ? XMLNode(0) : nodes.front());
}
XMLNode Conf::getParam(std::string const &playerclass, std::string const &behaviorid)
{
	//_debugLevel1(name);
	std::ostringstream xpath("");
	xpath << "/conf/player-class[@id=" << playerclass << "]/behavior[@id=" << behaviorid << "]/param";
  XMLNodeSet nodes = selectXPath(xpath.str());

  return (nodes.empty() ? XMLNode(0) : nodes.front());
}
