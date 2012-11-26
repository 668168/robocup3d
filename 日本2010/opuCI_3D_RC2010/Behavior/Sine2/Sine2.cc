#include "sine2.ih"

Sine2::Sine2(string const &id, string const &playerClass)
  : Behavior("Sine2", id, playerClass),
    d_fixedParams(Types::NJOINTS),
    d_startupTime(1.0),
    d_shutdownTime(1.0),
    d_startTime(-1),
    d_factor(0),
    d_gain(0.1)
{

  // fixed settings
  XMLNodeSet params = Behavior::getParams("/fixedSettings");
  if(params && !params.empty())
  {
    istringstream paramReader;
    XMLNode paramNode = params.front();
    paramReader.str(paramNode.getContent());
//    std::cout << "fset " << paramReader.str() << std::endl;

    while (!paramReader.eof())
    {
      _debugLevel4("Reading new line..");
      unsigned joint;
      char punc;

      paramReader >> joint >> punc;
      if (punc != ':')
      {
        _debugLevel4("Wrong format: '" << punc << "', expected ':'");
        _debugLevel4(paramNode.getContent());
        break;
      }
      
      _debugLevel4("For joint " << joint);

      while (punc != ';')
      {
        Params parameters;
        paramReader >> parameters.amplitude >> parameters.period >> parameters.phase >> parameters.offset >> punc;

 /*
 // Check parameters
 double jmin = parameters.offset - parameters.amplitude;
 double jmax = parameters.offset + parameters.amplitude;
 
 if (jmax > WorldModel::getInstance().getJointMax(static_cast<Types::Joint>(joint)) ||
        jmin < WorldModel::getInstance().getJointMin(static_cast<Types::Joint>(joint))) {
        cout << "error sine2 parameters out of bound for joint " << joint << endl;
        throw runtime_error("sine2 parameters out of bound");
 }
 */
//        printParams(parameters);
        d_fixedParams[joint].push_back(parameters);
      }
      
    }
  }
  else
  {
    _debugLevel4("no settings fixed parameters found");
  }


  // variable settings
  stringstream ss;
  unsigned vnum=0;
  ss << "/variableSettings" << (vnum+1);
  params = Behavior::getParams(ss.str());

  while(params && !params.empty())
  {
    istringstream paramReader;
    XMLNode paramNode = params.front();
    paramReader.str(paramNode.getContent());
//    std::cout << "vset" << vnum+1 << " " << paramReader.str() << std::endl;
    std::vector< std::vector<Params> > variableParams(Types::NJOINTS);

    while (!paramReader.eof())
    {
//      std::cout << " found! " << vnum+1 << std::endl;
      _debugLevel4("Reading new line..");
      unsigned joint;
      char punc;

      paramReader >> joint >> punc;
      if (punc != ':')
      {
        _debugLevel4("Wrong format: '" << punc << "', expected ':'");
        _debugLevel4(paramNode.getContent());
        break;
      }
      
      _debugLevel4("For joint " << joint);

      while (punc != ';')
      {
        Params parameters;
        paramReader >> parameters.amplitude >> parameters.period >> parameters.phase >> parameters.offset >> punc;

 /*
 // Check parameters
 double jmin = parameters.offset - parameters.amplitude;
 double jmax = parameters.offset + parameters.amplitude;
 
 if (jmax > WorldModel::getInstance().getJointMax(static_cast<Types::Joint>(joint)) ||
        jmin < WorldModel::getInstance().getJointMin(static_cast<Types::Joint>(joint))) {
        cout << "error sine2 parameters out of bound for joint " << joint << endl;
        throw runtime_error("sine2 parameters out of bound");
 }
 */
//        printParams(parameters);
        variableParams[joint].push_back(parameters);
      }
      
    }
    ss.str(""); vnum++;
    ss << "/variableSettings" << (vnum + 1);
    params = Behavior::getParams(ss.str());
    d_variableParams.push_back(variableParams);
    d_weights.push_back(0); // for initialize
  }
//  else
//  {
//    _debugLevel4("no settings variable parameters found");
//  }

  params = Behavior::getParams("/startupTime");
  if(params && !params.empty())
  {
    XMLNode paramNode = params.front();
    d_startupTime = s_transitionTime = atof(paramNode.getContent().c_str());
  }

  params = Behavior::getParams("/shutdownTime");
  if(params && !params.empty())
  {
    XMLNode paramNode = params.front();
    d_shutdownTime = atof(paramNode.getContent().c_str());
  }

  params = Behavior::getParams("/gain");
  if(params && !params.empty()){
    XMLNode paramNode = params.front();
    d_gain = atof(paramNode.getContent().c_str());
  }


  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  for (unsigned i = 0; i < Types::NJOINTS; ++i)
    d_tree->getChild(0)->addChild(new AST::Node(orType));
  
  s_sines.push_back(this);
}
