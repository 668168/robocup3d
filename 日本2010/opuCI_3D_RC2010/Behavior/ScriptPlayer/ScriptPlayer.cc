#include "scriptplayer.ih"

ScriptPlayer::ScriptPlayer(string const &id, string const &playerClass)
  : Behavior("ScriptPlayer", id, playerClass),
    d_waitUntil(-1),
    d_lastStepTime(0),
    d_curLine(0),
    d_lastChecked(0),
    d_maxSpeed(100.0),
    d_gain(0.1)
{
  d_committed = true;

  XMLNodeSet params = getParams("/script");
  istringstream scriptReader;
  if(params && !params.empty())
  {
    XMLNode scriptNode = params.front();
    scriptReader.str(scriptNode.getContent());

    //unsigned nLines;
    //scriptReader >> nLines;
    vector<pair<double, pair<double, double> > >
      scriptLine(Types::NJOINTS + 1,
                 pair<double, pair<double, double> >(
                   0,
                   pair<double, double>(d_maxSpeed / 180.0 * M_PI, d_gain)) );

    while (!scriptReader.eof())
    {
      _debugLevel4("Reading new line");

      int joint = -1;
      char eq = '=';
      double value = 0;
      char punc = 0;

      bool newline = false;

      while (eq == '=' && punc != ';')
      {
        // Set wait to 0
        scriptLine[Types::NJOINTS] = pair<double, pair<double, double> >(0, pair<double, double>(0, 0));

        scriptReader >> joint >> eq >> value >> punc;
// std::cout << "ScriptPlayer::scriptReader >> (joint)" << joint << "| (eq)" << eq
//    << "| (value)" << value << "| (punc)" << punc << std::endl; 
        double maxSpeed = d_maxSpeed;
 double gain = d_gain;
        if (punc == ':')
 {
          scriptReader >> maxSpeed >> punc;
//   std::cout << "(maxSpeed)" << maxSpeed << std::endl;
   if (punc == ':'){
     scriptReader >> gain >> punc;
//     std::cout << "gain = " << gain << std::endl;
   }
 }
        if (joint < 0 || joint > Types::NJOINTS)
          break;

        newline = true;

        _debugLevel4("eq: " << eq << ", angle: " << value << ", punc: " << punc);

        if (joint < Types::NJOINTS){
          scriptLine[joint] =
            pair<double, pair<double, double> >((value / 180.0) * M_PI, 
                                                pair<double, double>((maxSpeed / 180.0) * M_PI,
                                                                     gain));
        }
        else // Wait instruction
          scriptLine[Types::NJOINTS] = pair<double, pair<double, double> >(value, pair<double, double>(0,0));

      }

      if (newline)
        d_script.push_back(scriptLine);
      else
        break;

      //for (unsigned j = 0; j <= Types::NJOINTS; ++j)
      // cerr << scriptLine[j] << " ";
      //cerr << endl;
    }
  }

  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  for (unsigned i = 0; i < Types::NJOINTS; ++i)
    d_tree->getChild(0)->addChild(new AST::Node(orType));
}
