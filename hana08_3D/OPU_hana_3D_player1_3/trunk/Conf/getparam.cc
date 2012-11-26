#include "conf.ih"

XMLNode Conf::getParam(std::string const &name)
{
    // !!!!! not used !!!!!
	_debugLevel1(name);
  XMLNodeSet nodes = selectXPath(std::string("/conf/parameters/") + name);
//  std::cout << "Conf::getParam(1) nodes =" << "/conf/parameters/" << name << std::endl;
//  int num;
//  std::cin >> num;
//  std::cout << num << std::endl;

  return (nodes.empty() ? XMLNode(0) : nodes.front());
}
XMLNode Conf::getParam(std::string const &playerclass, std::string const &behaviorid)
{
    // !!!!! not used !!!!!
	//_debugLevel1(name);
	std::ostringstream xpath("");
	xpath << "/conf/player-class[@id=" << playerclass << "]/behavior[@id=" << behaviorid << "]/param";
//	std::cout << "Conf::getParam(2) xpath =" << xpath.str() << std::endl;
  XMLNodeSet nodes = selectXPath(xpath.str());
//  int num;
//  std::cin >> num;
//  std::cout << num << std::endl;

  return (nodes.empty() ? XMLNode(0) : nodes.front());
}
