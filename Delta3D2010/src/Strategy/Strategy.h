//
// C++ Interface: Strategy
//
// Description: 
//
//
// Author: delta3d team 2009 <deltateams2009@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STRATEGY_H
#define STRATEGY_H

#include "../Formation/Formation.h"
#include "../Formation/TeamPlayer.h"
#include "../WorldModel/WorldModel.h"
#include "../Agent_Roles/SoccerRole.h"
#include "../Agent_Roles/RoleLeftForward.h"
#include "../Utility/Types.h"
class Strategy
{

private:
  Vector3f m_homePosTeloranse;
  Vector2f m_rangeTeloranse;
  
public:

    Strategy();
    
    static Strategy& instance ();

   //static  boost::shared_ptr <SoccerRole>  role;
    
    void createRole();
    void executeRole(); 
    PlayerType getPlayerType( ) const;
    PlayerType getPlayerType( const int number         ) const;

    bool gotoStrategyPos();
    
    bool gotoHomePos();
    
    bool isInRange();
    
    bool isInHomePos();
    
    bool isInOppPenaltyArea(const Vector3f & pos)const;
    
    void analyzeOpponentFormation(  );

    void analyzeOpponentStrategy(  );

protected:





};
#endif