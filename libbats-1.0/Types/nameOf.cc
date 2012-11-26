#include "types.ih"

#define _case(name) case name: return #name

std::string Types::nameOf(Types::Object const object)
{
 switch(object) {
	_case(SELF);
	_case(BALL);
	_case(PLAYER1);
	_case(PLAYER2);
	_case(PLAYER3);
	_case(PLAYER4);
	_case(PLAYER5);
	_case(OPPONENT1);
	_case(OPPONENT2);
	_case(OPPONENT3);
	_case(OPPONENT4);
	_case(OPPONENT5);
	_case(FLAG1L);
	_case(FLAG1R);
	_case(FLAG2L);
	_case(FLAG2R);
	_case(FLAG1US);
	_case(FLAG2US);
	_case(FLAG1THEM);
	_case(FLAG2THEM);
	_case(GOAL1L);
	_case(GOAL1R);
	_case(GOAL2L);
	_case(GOAL2R);
	_case(GOAL1US);
	_case(GOAL2US);
	_case(GOAL1THEM);
	_case(GOAL2THEM);
	_case(NOBJECTS);
}
 
  return "???";
}
