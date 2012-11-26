#include "sine.ih"

Sine::Sine(string const &id, string const &playerClass)
  : Behavior("Sine", id, playerClass),
    d_params(Types::NJOINTS),
    d_startupTime(1.0),
    d_shutdownTime(1.0),
    d_startTime(-1),
    d_factor(0),
    d_gain(0.1)
{
  XMLNodeSet params = Behavior::getParams("/settings");
  istringstream paramReader;
  if(params && !params.empty())
  {
    XMLNode paramNode = params.front();
    paramReader.str(paramNode.getContent());

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
	  cout << "error sine parameters out of bound for joint " << joint << endl;
	  throw runtime_error("sine parameters out of bound");
	}
	*/
        d_params[joint].push_back(parameters);
      }
      
    }
  }
  else
  {
    _debugLevel4("no settings parameters found");
  }

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
