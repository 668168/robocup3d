#include "conf.ih"
#include <stdexcept>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xinclude.h>
#include <sys/stat.h>
#include <sys/types.h>
void Conf::parseConf(std::string const &confFile)
{
  struct stat fileInfo;
  int s = stat(confFile.c_str(),&fileInfo);
  if(s != 0)
    throw runtime_error("error opening config file: " + confFile + " not found");

  d_doc = xmlReadFile(confFile.c_str(), 0, XML_PARSE_NOENT);

  if (!d_doc)
    throw runtime_error("error reading config file: "+confFile);

  int subs = xmlXIncludeProcessFlags(d_doc, XML_PARSE_NOENT);
  if ( subs < 0)
    throw runtime_error("error processing XInclude on config file: "+confFile);
  else
    _debugLevel4("number of XInclude substitutions: " << subs);
  //XMLNode root = xmlDocGetRootElement(d_doc);
  
}
