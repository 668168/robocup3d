#include "agentmodel.ih"

AgentModel::AgentModel()
: 
  d_unum(0),
  d_torso(0),
  d_kickMaxDistance(100.0,20.0), // Should still be modelled!
  d_kickMaxSpeed(100.0,20.0) // Should still be modelled!
{
  d_jointNameMap["head1"] = Types::HEAD1;
  d_jointNameMap["head2"] = Types::HEAD2;
  
  d_jointNameMap["larm1"] = Types::LARM1;
  d_jointNameMap["larm2"] = Types::LARM2;
  d_jointNameMap["larm3"] = Types::LARM3;
  d_jointNameMap["larm4"] = Types::LARM4;

  d_jointNameMap["rarm1"] = Types::RARM1;
  d_jointNameMap["rarm2"] = Types::RARM2;
  d_jointNameMap["rarm3"] = Types::RARM3;
  d_jointNameMap["rarm4"] = Types::RARM4;

  d_jointNameMap["lleg1"] = Types::LLEG1;
  d_jointNameMap["lleg2"] = Types::LLEG2;
  d_jointNameMap["lleg3"] = Types::LLEG3;
  d_jointNameMap["lleg4"] = Types::LLEG4;
  d_jointNameMap["lleg5"] = Types::LLEG5;
  d_jointNameMap["lleg6"] = Types::LLEG6;

  d_jointNameMap["rleg1"] = Types::RLEG1;
  d_jointNameMap["rleg2"] = Types::RLEG2;
  d_jointNameMap["rleg3"] = Types::RLEG3;
  d_jointNameMap["rleg4"] = Types::RLEG4;
  d_jointNameMap["rleg5"] = Types::RLEG5;
  d_jointNameMap["rleg6"] = Types::RLEG6;

  
  d_limbNameMap["head"] = Types::HEAD;
  d_limbNameMap["neck"] = Types::NECK;
  d_limbNameMap["torso"] = Types::TORSO;
  d_limbNameMap["lowertorso"] = Types::LOWERTORSO;
  
  d_limbNameMap["lshoulder"] = Types::LSHOULDER;
  d_limbNameMap["lupperarm"] = Types::LUPPERARM;
  d_limbNameMap["lelbow"] = Types::LELBOW;
  d_limbNameMap["llowerarm"] = Types::LLOWERARM;
  
  d_limbNameMap["rshoulder"] = Types::RSHOULDER;
  d_limbNameMap["rupperarm"] = Types::RUPPERARM;
  d_limbNameMap["relbow"] = Types::RELBOW;
  d_limbNameMap["rlowerarm"] = Types::RLOWERARM;
  
  d_limbNameMap["lhip1"] = Types::LHIP1;
  d_limbNameMap["lhip2"] = Types::LHIP2;
  d_limbNameMap["lupperleg"] = Types::LUPPERLEG;
  d_limbNameMap["llowerleg"] = Types::LLOWERLEG;
  d_limbNameMap["lankle"] = Types::LANKLE;
  d_limbNameMap["lfoot"] = Types::LFOOT;

  d_limbNameMap["rhip1"] = Types::RHIP1;
  d_limbNameMap["rhip2"] = Types::RHIP2;
  d_limbNameMap["rupperleg"] = Types::RUPPERLEG;
  d_limbNameMap["rlowerleg"] = Types::RLOWERLEG;
  d_limbNameMap["rankle"] = Types::RANKLE;
  d_limbNameMap["rfoot"] = Types::RFOOT;

  //initBody();
  

}
