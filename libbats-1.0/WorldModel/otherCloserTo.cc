#include "worldmodel.ih"

unsigned WorldModel::otherCloserTo(Vector3D const& pos, bool standing, bool count)
{
  double dist = pos.length();
  _debugLevel1("Own distance: " << dist);
  unsigned cnt = 0;
  
  for (player_iterator iter = beginPlayers(); iter != endPlayers(); ++iter)
  {
    _debugLevel1(iter->first);
    double otherDist = (iter->second.getPosition() - pos).length();
    _debugLevel1("Other distance: " << iter->second.getPosition() << " " << iter->second.getWorldPosition() << " " << otherDist);
    
    if (otherDist < dist && (!standing || !iter->second.onGround()))
    {
      ++cnt;
      if (!count)
        break;
    }
  }
  return cnt;
}

unsigned WorldModel::otherCloserToBall(bool standing, bool count)
{
  return otherCloserTo(d_objects[Types::BALL].position.getMu(), standing, count);
}

