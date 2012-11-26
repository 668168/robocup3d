#include "trainersocketcomm.ih"

void TrainerSocketComm::setPlayMode(Types::PlayMode mode)
{
  send(makeSetPlayModeMessage(mode));
}

rf<Predicate> TrainerSocketComm::makeSetPlayModeMessage(Types::PlayMode mode)
{
  WorldModel& wm = SWorldModel::getInstance();
  
  rf<Predicate> msg = new Predicate("playMode");
  string modeStr;
  switch (mode)
  {
    case Types::BEFORE_KICKOFF:
      modeStr = "BeforeKickOff";
      break;
          
    case Types::KICKOFF_LEFT:
      modeStr = "KickOff_Left";
      break;
    
    case Types::KICKOFF_RIGHT:
      modeStr = "KickOff_Right";
      break;

    case Types::KICKOFF_US:
      modeStr = wm.getSide() == Types::LEFT ? "KickOff_Left" : "KickOff_Right";
      break;

    case Types::KICKOFF_THEM:
      modeStr = wm.getSide() == Types::LEFT ? "KickOff_Right" : "KickOff_Left";
      break;
        
    case Types::PLAY_ON:
      modeStr = "PlayOn";
      break;
        
    case Types::FREEKICK_LEFT:
      modeStr = "free_kick_left";
      break;

    case Types::FREEKICK_RIGHT:
      modeStr = "free_kick_right";
      break;

    case Types::FREEKICK_US:
      modeStr = wm.getSide() == Types::LEFT ? "free_kick_left" : "free_kick_right";
      break;

    case Types::FREEKICK_THEM:
      modeStr = wm.getSide() == Types::LEFT ? "free_kick_right" : "free_kick_left";
      break;
        
    case Types::GOAL_LEFT:
      modeStr = "Goal_Left";
      break;

    case Types::GOAL_RIGHT:
      modeStr = "Goal_Right";
      break;

    case Types::GOAL_US:
      modeStr = wm.getSide() == Types::LEFT ? "Goal_Left" : "Goal_Right";
      break;

    case Types::GOAL_THEM:
      modeStr = wm.getSide() == Types::LEFT ? "Goal_Right" : "Goal_Left";
      break;
        
    case Types::GOAL_KICK_LEFT:
      modeStr = "goal_kick_left";
      break;

    case Types::GOAL_KICK_RIGHT:
      modeStr = "goal_kick_right";
      break;

    case Types::GOAL_KICK_US:
      modeStr = wm.getSide() == Types::LEFT ? "goal_kick_left" : "goal_kick_right";
      break;

    case Types::GOAL_KICK_THEM:
      modeStr = wm.getSide() == Types::LEFT ? "goal_kick_right" : "goal_kick_left";
      break;

    case Types::CORNER_KICK_LEFT:
      modeStr = "corner_kick_left";
      break;

    case Types::CORNER_KICK_RIGHT:
      modeStr = "corner_kick_right";
      break;

    case Types::CORNER_KICK_US:
      modeStr = wm.getSide() == Types::LEFT ? "corner_kick_left" : "corner_kick_right";
      break;

    case Types::CORNER_KICK_THEM:
      modeStr = wm.getSide() == Types::LEFT ? "corner_kick_right" : "corner_kick_left";
      break;

    case Types::KICKIN_LEFT:
      modeStr = "KickIn_Left";
      break;

    case Types::KICKIN_RIGHT:
      modeStr = "KickIn_Right";
      break;

    case Types::KICKIN_US:
      modeStr = wm.getSide() == Types::LEFT ? "KickIn_Left" : "KickIn_Right";
      break;

    case Types::KICKIN_THEM:
      modeStr = wm.getSide() == Types::LEFT ? "KickIn_Right" : "KickIn_Left";
      break;
    
    case Types::UNKNOWN:
      break;
  }
  
  msg->pushLeaf(modeStr);
  return msg;
}

