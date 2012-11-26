#include "console.ih"

Console::Console(string const &id, string const &playerClass)
  :
  Behavior("Console", id, playerClass),
  d_pos(Types::NJOINTS + 1, 0.0),
  d_cap(0.5),
  d_changed(Types::NJOINTS + 1, false),
  d_joints(Types::NJOINTS + 1, ""),
  d_save(true)
{

  d_joints[0] = "head_1";
  d_joints[1] = "lleg1";
  d_joints[2] = "lleg2";
  d_joints[3] = "lleg3";
  d_joints[4] = "lleg4";
  d_joints[5] = "lleg5";
  d_joints[6] = "lleg6";
  d_joints[7] = "rleg1";
  d_joints[8] = "rleg2";
  d_joints[9] = "rleg3";
  d_joints[10] = "rleg4";
  d_joints[11] = "rleg5";
  d_joints[12] = "rleg6";
  d_joints[13] = "larm1";
  d_joints[14] = "larm2";
  d_joints[15] = "larm3";
  d_joints[16] = "larm4";
  d_joints[17] = "rarm1";
  d_joints[18] = "rarm2";
  d_joints[19] = "rarm3";
  d_joints[20] = "rarm4";

  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  for (unsigned i = 0; i < Types::NJOINTS; ++i)
    d_tree->getChild(0)->addChild(new AST::Node(orType));
  
}
