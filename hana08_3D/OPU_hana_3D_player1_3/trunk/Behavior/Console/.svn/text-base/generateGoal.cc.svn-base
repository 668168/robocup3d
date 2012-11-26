#include "console.ih"

#include "worldmodel.hh"

rf<Behavior::Goal> Console::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  Input &i = Input::getInstance();
  i.collect();
  if(i.lineReady())
    {
      std::string line(i.line());
      istringstream scriptReader(line);
      unsigned joint(0);
      double pos(0);
      //Try number pos
      scriptReader >> joint >> pos;
      if(scriptReader.eof())
	{
	  d_pos[joint] = pos;
	  d_changed[joint] = true;
	}
      else
	{
	  //Try name pos
	  std::string j;
	  joint = 0;
	  pos = 0;
	  istringstream s(line);
	  s >> j >> pos;
	  bool foundJoint(false);
	  if(j.length())
	    {
	      for(unsigned int i =0; i < d_joints.size(); ++i)
		if(d_joints[i] == j)
		  {
		    cout << "Set " << j << "(" << i << ") " << pos << endl;
		    if (d_save &&
			(pos > WorldModel::getInstance().getJointMax(static_cast<Types::Joint>(i)) ||
			 pos < WorldModel::getInstance().getJointMin(static_cast<Types::Joint>(i)))) {
		      cout << "Out of bound (joint constraints: ["
			   << WorldModel::getInstance().getJointMax(static_cast<Types::Joint>(i))
			   << "," << WorldModel::getInstance().getJointMin(static_cast<Types::Joint>(i))
			   << "])." << endl;
		    } else {
		      d_pos[i] = pos;
		      d_changed[i] = true;
		    }
		    foundJoint = true;
		  }
	    }
	  if(!foundJoint)
	    {
	      //Not a joint, value pair -> command??
	      if(line == "p")
		{
		  joint = 0;
					
		  _foreach(i, d_pos)
		    {
		      cout << joint++ << " = " << *i << ", ";
		    }
		  cout << endl;
		}
	      if(line == "s")
		{
		  for(unsigned i = 0; i < d_joints.size(); ++i)
		    {
		      if(d_changed[i])
			cout << "&" << d_joints[i] << ";=" << d_pos[i] << ", ";
		      d_changed[i] = false;
		    }
		  cout << endl;
		}
	      else if (line == "reset")
		{
		  _foreach(i, d_pos)
		    *i = 0;
		}
	      else if(line == "low")
		{
		  //Set capability low
		  d_cap = 0.0;
		}
	      else if (line == "unsave")
		{
		  d_save = false;
		}
	      else if (line == "save")
		{
		  d_save = true;
		}
	      else if (line == "help")
		{
		  cout << "Lines are: <<join> <number> | <command>>\n"
		       << "Commands include: \n"
		       << "p\tprint raw joint info\nreset\treset to zero\n"
		       << "s\tprint script line and start new scriptline\n"
		       << "low\tSet capability to 0 until reset\n"
		       << "save\tSet save mode on,joint bounds will be checked (default)\n"
		       << "unsave\tTurn off save mode\n"
		       << "Joints are: ";
		  _foreach(i, d_joints)
		    cout << *i << " ";
		  cout << "\n";
		}
	      else
		{
		  cout << "Unknown command: \"" << line << "\"" << endl;
		}
	    }
	}
		
    }

  // con->addVar("Var", 0, 1);
  con->addVar("Angle", d_pos[slot]* M_PI/180.0, d_pos[slot]* M_PI/180.0);
  
  return goal;
}
