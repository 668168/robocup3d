#include "conf.ih"

XMLNodeSet Conf::getParams(std::string const &playerclass, std::string const &behaviorid, std::string const &path)
{
	//_debugLevel1(name);
	std::ostringstream xpath("");
	xpath << "/conf/player-class[@id='" << playerclass << "']/behaviors/behavior[@id='" << behaviorid << "']/param" << path;
	_debugLevel1(xpath.str());
//	std::cout << "Conf::getParams xpath.str=" << xpath.str() << std::endl;
  return selectXPath(xpath.str());
}
