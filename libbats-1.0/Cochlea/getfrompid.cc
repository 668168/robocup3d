#include "cochlea.ih"

PlayerInfo &Cochlea::getPlayerFromPid(unsigned pid)
{
  map<unsigned,PlayerInfo>::iterator i = d_players.find(pid);

  if (i == d_players.end())
	d_players[pid].setID(d_players.size());

  return d_players[pid];

  // Warning: the returned reference is invalidated when a new player is added.
}

PlayerInfo &Cochlea::getOpponentFromPid(unsigned pid)
{
  map<unsigned,PlayerInfo>::iterator i = d_opponents.find(pid);

  if (i == d_opponents.end())
	d_opponents[pid].setID(d_opponents.size());

  return d_opponents[pid];

  // Warning: the returned reference is invalidated when a new player is added.

}
