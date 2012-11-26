#include "behavior.ih"

#define _elseif(X) else if (b.getProp("type") == #X)	\
    behavior = new X(b.getProp("id"), playerClass)

#define _elseif1(X) else if (b.getProp("type") == #X)	\
    behavior = new X(b.getProp("id"))


rf<Behavior> Behavior::buildTree(XMLNode& b, string playerClass)
{
  Conf& conf = Conf::getInstance();

  // Make behavior of this node's type
  rf<Behavior> behavior;
  
  // --------------------------- Add new behavior types here -----------------------
  if (b.getProp("type") == "MoveHingeJoint")
    behavior = new MoveHingeJoint(b.getProp("id"), playerClass);

  _elseif(MoveUniversalJoint);
  _elseif(MoveJoint);
  _elseif(MoveJointTo);
  _elseif(Wait);
  _elseif1(Beam);
  _elseif(ScriptPlayer);
  _elseif(Sine);
  _elseif(Sine2);
  _elseif(Empty);
  _elseif(WalkTo);
  _elseif(CanKickLeft);
  _elseif(CanKickRight);
//  _elseif(CanTurnLeft);
//  _elseif(CanTurnRight);
//  _elseif(MiniWalkForward);
//  _elseif(MiniWalkBackward);
  _elseif(GoodPositionAngle);
  _elseif(GoodPosition);
  _elseif(GetUpFromBelly);
  _elseif(GetUpFromBack);
  _elseif(BeamTo);
  _elseif(GetFromSide);
  _elseif(WalkStraightTo);
  _elseif(TurnAndWait);
  _elseif(TurnTo);
  _elseif(KickTo);
  _elseif(Score);
//  _elseif(StrafeLeft);
//  _elseif(StrafeRight);
//  _elseif(StrafeToBall);
  _elseif(FallForward);
  _elseif(FallBackward);
  _elseif(FallRightSide);
  _elseif(FallLeftSide);
  _elseif(Dribble);
  _elseif(Freeze);
  _elseif(GetUp);
  _elseif(StandBy);
//  _elseif(ClearBall);
  _elseif(Guard);
  _elseif(GuardGoal);
  _elseif(Intercept);
  _elseif(KeepingGoal);
  _elseif(DribbleForward);
  _elseif(DribbleSide);
//  _elseif(DribbleRight);
//  _elseif(DribbleLeft);
  _elseif(TurnForDribble);
  _elseif(KickPosition);
  _elseif(BestPosition);
  _elseif(BestAngle);
//  _elseif(TurnRightStrict);
//  _elseif(TurnLeftStrict);
  _elseif(Search);
  _elseif(GoalKick);
  _elseif(Block);
  _elseif(AvoidOthers);
  _elseif(ReadyToGuard);
  _elseif(RightStep);
  _elseif(LeftStep);
  _elseif(KeeperWalk);
  _elseif(KeeperGoodPosition);
  _elseif(KeeperKickPosition);
  _elseif(WaitAndSee);
  _elseif(Stop);
  _elseif(KickLeftL);
  _elseif(KickRightR);
  _elseif(Defense);
  _elseif(DirectDefense);
  _elseif(SupportDefense);
  _elseif(Position);
  _elseif(ReturnToPosition);
  _elseif(KickStraight);
  _elseif(Stay);
  _elseif(AssaultGoal);
  _elseif(KickToEnnemy);
  _elseif(KickPositionDefender);
  _elseif(Pass);
  _elseif(SidePass);
  _elseif(DiagPass);
  _elseif(FacePass);
  _elseif(SideKickRight);
  _elseif(SideKickLeft);
  _elseif(DiagKickRight);
  _elseif(DiagKickLeft);
  _elseif(FaceKickRight);
  _elseif(FaceKickLeft);
  _elseif(GoToBall);
  _elseif(WalkAndTurn);
  _elseif(CornerKick);
  _elseif(CornerKickPosition);
  _elseif(CornerKickRight);
  _elseif(CornerKickLeft);
  _elseif(GamepadPlay);
  _elseif(GamepadWalk);
  _elseif(GamepadStepping);
  _elseif(GamepadOmnidirectionalWalk);
  _elseif(GamepadWalkBackward);
  _elseif(GamepadMiniWalkForward);
  _elseif(GamepadMiniWalkBackward);
  _elseif(GamepadStrafeRight);
  _elseif(GamepadStrafeLeft);
  _elseif(GamepadKickRight);
  _elseif(GamepadKickLeft);
  _elseif(GamepadTurnRight);
  _elseif(GamepadTurnLeft);
  _elseif(GamepadFallForward);
  _elseif(GamepadFallBackward);
  _elseif(GamepadFallRightside);
  _elseif(GamepadFallLeftside);
  _elseif(GamepadBeam);
  _elseif(GamepadJoy);
  _elseif(GamepadGetUp);

// else if (b.getProp("type") == "SmoothStop")
//  behavior = new SmoothStop(b.getProp("id"), playerClass);

  // --------------------------- End add new behavior types ------------------------

  if (!behavior)
    throw runtime_error(b.getProp("type") + ": unknown behavior type");
  
  behavior->setPlayerClass(playerClass);
  
  // Go through the slots
  for(XMLNode s = b.getChildren(); s; s = s.getNext())
  {
    if (s.getName() != "slot")
      continue;

    string index = s.getProp("index");
    unsigned step = atoi(index.substr(0, index.find("-")).c_str());
    unsigned slot = atoi(index.substr(index.find("-") + 1).c_str());

    _debugLevel2("Adding to slot " << step << "-" << slot << ":");
    for (XMLNode sb = s.getChildren(); sb; sb = sb.getNext())
      if (sb.getName() == "behavior")
      {
        _debugLevel2("\t" << sb.getProp("refid"));
        try{
          string path = "/conf/player-class[@id='" + playerClass + "']/behaviors/behavior[@id='" + sb.getProp("refid") + "']";
          string commit = sb.getProp("commit");
          string scicc = sb.getProp("scicc");
          XMLNodeSet set = conf.selectXPath(path);

          if (set.empty())
            throw runtime_error(string() + "buildTree: '" + path + "' not found...");

          XMLNode sb = set.front();
          rf<Behavior> subBehavior = buildTree(sb, playerClass);
          subBehavior->shouldCommit(commit == "1");
          subBehavior->shouldCommitIfChildrenCommitted(scicc == "1");
          behavior->addToSlot(subBehavior, step, slot);
        }
        catch(BatsException *e)
        {
          cerr << "Could not find refid: " << sb.getProp("refid") << endl;
          _debugLevel1("Could not find refid: " << sb.getProp("refid"));
          _log("Could not find refid, see errpr logs");
        }

      }
  }

  return behavior;
}

