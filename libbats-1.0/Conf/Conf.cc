#include "conf.ih"

#define QUOTE_IMPL(mp_token) #mp_token
#define QUOTE(mp_token) QUOTE_IMPL(mp_token) 


Conf::Conf()
  : d_doc(0)
{
  LIBXML_TEST_VERSION;
  parseConf(QUOTE(DATADIR) "/conf.xml");
  xpathCtx = xmlXPathNewContext(d_doc);
}

/**
  *  @param confFile specifies the path to the xml configuration file.
  */
Conf::Conf(std::string const &confFile)
  : d_doc(0)
{
  LIBXML_TEST_VERSION;
  parseConf(confFile);
  xpathCtx = xmlXPathNewContext(d_doc);
}

