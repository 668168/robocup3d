#ifndef __INC_BATS_CONF_HH_
#define __INC_BATS_CONF_HH_

#include "xmlnode.hh"
#include "xmlnodeset.hh"

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include <stdexcept>
#include <cstdlib>

namespace bats {

  /** Conf class
   *
   *  \todo Issues:
   *  - Second if statement in keeper section of conf file makes agents crash.
   *
   *  In this class the XML configuration file is parsed. It also provides
   *  some functionality for retrieving parts of the config tree. It's up
   *  to the using classes to retrieve the relevant parts for that class.
   *
   *  This is a Singleton, use initialize() before using.
   */
  class Conf {
    xmlDocPtr d_doc;
    xmlXPathContextPtr xpathCtx;

    void parseConf(std::string const &confFile);

    void destroy()
    {
      if (xpathCtx)
        xmlXPathFreeContext(xpathCtx); 

      if (d_doc)
        xmlFreeDoc(d_doc);

      xmlCleanupParser();
    }

    XMLNode getParam(std::string const &name);
    
    /**
     *  @param confFile specifies the path to the xml configuration file.
     */
    Conf(std::string const &confFile)
      : d_doc(0)
    {
      LIBXML_TEST_VERSION;

      parseConf(confFile);

      xpathCtx = xmlXPathNewContext(d_doc);
    }

    static Conf* s_conf;
    
  public:

    ~Conf() { destroy(); }

    //Get the params node for the behavior of classType and behaviorId
    XMLNode getParam(std::string const &classType, std::string const &behaviorId);
    XMLNodeSet getParams(std::string const &classType, std::string const &behaviorId, std::string const &subpath = "");
    
    /**
     *  @returns the absolute root node of the config tree.
     */
    XMLNode getRoot() { return xmlDocGetRootElement(d_doc); }

    /**
     *  @returns the node with name inside the gamestate node with id gamestate.
     */
    XMLNode getSection(std::string const &gamestate,
                       std::string const &name);

    /**
     *  @returns a set of nodes which match the XPATH expression expr.
     *  @see http://www.w3schools.com/xpath/
     */
    XMLNodeSet selectXPath(std::string const &expr);

    /**
     *  @returns the to a double converted value of the parameter.
     *  @see getParamStr
     */
    double getParamDbl(std::string const &name, double def = 0.0)
    {
      XMLNode p = getParam(name);
      return (p ? std::atof(p.getProp("value").c_str()) : def);
    }

    /**
     *  @returns the to an unsigned converted value of the parameter.
     *  @see getParamStr
     */
    unsigned getParamUInt(std::string const &name, unsigned def = 0)
    {
      XMLNode p = getParam(name);
      return (p?std::atoi(p.getProp("value").c_str()):def);
    }

    /**
     *  @returns the value of the value attribute of the node specified with
     *           the xpath of /conf/parameters/ + name. If the parameter does not
     *           exist the value def is returned.
     */
    std::string getParamStr(std::string const &name, std::string const &def = "")
    {
      XMLNode p = getParam(name);
      return (p?p.getProp("value"):def);
    }

    static void initialize(std::string const& confFile) { s_conf = new Conf(confFile); }
    
    static Conf& getInstance()
    {
      if (!s_conf)
        throw std::runtime_error("Conf not yet initialized");

      return *s_conf;
    }
  };

};

#endif // __INC_BATS_CONF_HH_
