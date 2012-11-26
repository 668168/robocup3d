#include "search.ih"

// set camera angle
void Search::update()
{
  Behavior::update();

  WorldModel& wm = WorldModel::getInstance();

  // the cycle of camera swinging.
  double T = 3.5; // sec.

  if( d_timeout )
    wm.searching(false);

  // beam ==> reset camera
  WorldModel::PlayMode pm = wm.getPlayMode();
  if( pm == WorldModel::BEFORE_KICKOFF
      || pm == WorldModel::GOAL_THEM
      || pm == WorldModel::GOAL_US
      || pm == WorldModel::GOAL_RIGHT
      || pm == WorldModel::GOAL_LEFT )
  {
    std::vector<Types::Object> target;
    target.push_back(Types::BALL);
    moveCameraToBall(target);
    return;
  }

  double timeoutTime = 5.0;
  // Search実行中かつ実行開始からtimeoutTime秒経ってない
  if(wm.nowSearching() && !d_timeout){

    // Search開始から2周期分経てばタイムアウト
    if( d_searchStartTime + 2*T < wm.getGameTime()){
      d_timeout = true;
      d_timeoutStart = wm.getGameTime();
    }
    else // 2周期分は首振り
    {
      //ss << "N:" << wm.getJointAngle(Types::HEAD_1).getMu()*180.0/M_PI
      //<< ", H:" << wm.getJointAngle(Types::HEAD_2).getMu()*180.0/M_PI;
      wm.addDebugMessage(WorldModel::COMMENT, "Now Searching...");
      wm.setNeckDirUpdate(true);
      wm.setNeckDir(120.0*sin(wm.getTime()*2*M_PI/T), -30);
    }
  }
  else // Search実行中でないorタイムアウトした場合
  {

    d_searchStartTime = wm.getGameTime();

    // timeoutTimeだけ経つまではタイムアウト(Searchしない)
    if(d_timeoutStart + timeoutTime < wm.getGameTime())
      d_timeout = false;

    // ボールが見えないときは先ずボール探し
    if(!wm.visibleObject(Types::BALL)){
      d_searchStartTime = wm.getGameTime();
      wm.addDebugMessage(WorldModel::COMMENT, "Now Searching for BALL");
      wm.setNeckDirUpdate(true);
      if( wm.getObjectPosition(Types::BALL).getMu().getY() > 0 )
        wm.setNeckDir(-120.0*sin(wm.getTime()*2*M_PI/T), -30);
      else
        wm.setNeckDir(120.0*sin(wm.getTime()*2*M_PI/T), -30);
    }
    // 見えてるランドマークはなるべく逃さないように視点移動
    else{
      std::vector<Types::Object> target;
      target.push_back(Types::BALL);
      target.push_back(Types::GOAL1THEM);
      target.push_back(Types::GOAL2THEM);
      target.push_back(Types::FLAG1THEM);
      target.push_back(Types::FLAG2THEM);
      target.push_back(Types::GOAL1US);
      target.push_back(Types::GOAL2US);
      target.push_back(Types::FLAG1US);
      target.push_back(Types::FLAG2US);
      moveCameraToBall(target);
    }
  }
//  wm.addDebugMessage(WorldModel::COMMENT, ss.str());
}
