#include "conf.ih"
#include <stdexcept>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xinclude.h>

void Conf::parseConf(std::string const &confFile)
{
  d_doc = xmlReadFile(confFile.c_str(), 0, XML_PARSE_NOENT);

  if (!d_doc)
    throw runtime_error("error reading config file!");

  int subs = xmlXIncludeProcessFlags(d_doc, XML_PARSE_NOENT);
  if ( subs < 0)
    throw runtime_error("error processing XInclude on config file!");
  else
    _debugLevel4("number of XInclude substitutions: " << subs);
  //XMLNode root = xmlDocGetRootElement(d_doc);
  
}
