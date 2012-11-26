#include "scriptplayer.ih"

void ScriptPlayer::reset()
{
  Behavior::reset();
  d_curLine = 0;
  d_waitUntil = -1;
  d_lastChecked = 0;
  d_lastStepTime = 0;
}

