#include "worldmodel.ih"


void WorldModel::updateVision()
{
  _debugLevel4("Ball: " << d_info[iVisionBall]);

  // Degrees to radians
  for (unsigned i = iVisionFlag1L; i <= iVisionBall; ++i)
  {
    d_info[i].setY(d_info[i].getY() * M_PI / 180.0);
    d_info[i].setZ(d_info[i].getZ() * M_PI / 180.0);
  }
  
  // Polar to Cartesian
  _debugLevel4("Flag angles: " << d_info[iVisionFlag1L] << " " << d_info[iVisionFlag1R] << " " << d_info[iVisionFlag2L] << " " << d_info[iVisionFlag2R]);

  Vector3D flag1LPos = Math::polarToCartesian(d_info[iVisionFlag1L]);
  Vector3D flag1RPos = Math::polarToCartesian(d_info[iVisionFlag1R]);
  Vector3D flag2LPos = Math::polarToCartesian(d_info[iVisionFlag2L]);
  Vector3D flag2RPos = Math::polarToCartesian(d_info[iVisionFlag2R]);

// ---------------------- mucha hajime   --------------------
/*
  if(flag1LPos.getX() == 0 && flag1RPos.getX() != 0)
  {
      flag1LPos.setX(12-flag1RPos.getX());
      flag1LPos.setY(8-flag1RPos.getY());
      flag1LPos.setZ(flag1RPos.getZ());
  }

// ---------------------- mucha kokomade --------------------
  std::cout << "flagPos... [1L:" << flag1LPos << ", 1R:" << flag1RPos 
	    << ", 2L:" << flag2LPos << ", 2R:" << flag2RPos << "]" << std::endl;
  std::cout << "*d_info[iVisionFrag]* " << d_info[iVisionFlag1L] 
	    <<  d_info[iVisionFlag1R] <<  d_info[iVisionFlag2L] 
	    <<  d_info[iVisionFlag2R] <<  std::endl;
*/
  Vector3D goal1LPos = Math::polarToCartesian(d_info[iVisionGoal1L]);
  Vector3D goal1RPos = Math::polarToCartesian(d_info[iVisionGoal1R]);
  Vector3D goal2LPos = Math::polarToCartesian(d_info[iVisionGoal2L]);
  Vector3D goal2RPos = Math::polarToCartesian(d_info[iVisionGoal2R]);
//  std::cout << "goalPos... [" << goal1LPos << ", " << goal1RPos << ", " 
//	    << goal2LPos << ", " << goal2RPos << "]" << std::endl;

  // Determine field normal
  Vector3D a = flag2LPos - flag1LPos;
  Vector3D b = flag1RPos - flag1LPos;
  d_fieldNormal = a.crossProduct(b).normalize();
//  std::cout << "Normal: " << d_fieldNormal << std::endl;
  
  double d = -(d_fieldNormal * flag1LPos);
  d_distToField = -d;

  for (unsigned i = 0; i < 5; ++i) {
    Vector3D playerPos = Math::toFieldCoords(Math::polarToCartesian(d_info[iVisionPlayer1 + i]), d_fieldNormal);
    Vector3D oldPlayerPos = d_objectPositions[Types::PLAYER1 + i].getMu();
    Vector3D deltaPlayerPos = playerPos - oldPlayerPos;
    d_objectPositions[Types::PLAYER1 + i].init(playerPos, Matrix9D());
    d_objectSpeeds[Types::PLAYER1 + i].init(deltaPlayerPos/d_timeStep, Matrix9D());
  }

  for (unsigned i = 0; i < 5; ++i) {
    Vector3D opponentPos = Math::toFieldCoords(Math::polarToCartesian(d_info[iVisionOpponent1 + i]), d_fieldNormal);
    Vector3D oldOpponentPos = d_objectPositions[Types::OPPONENT1 + i].getMu();
    Vector3D deltaOpponentPos = opponentPos - oldOpponentPos;
    _debugLevel4("Opponent position: " << opponentPos << "(" << (iVisionOpponent1 + i) << ")");
    d_objectPositions[Types::OPPONENT1 + i].init(opponentPos, Matrix9D());
    d_objectSpeeds[Types::OPPONENT1 + i].init(deltaOpponentPos/d_timeStep, Matrix9D());
  }

  // Ball position
  _debugLevel1("Ball!");
  Vector3D ballPos = Math::toFieldCoords(Math::polarToCartesian(d_info[iVisionBall]), d_fieldNormal);
/*
  if(d_info[iVisionBall].getX() != 0)
  {
      std::cout << "d_info[iVisionBall] = " << d_info[iVisionBall] << ", d_fieldNormal = " << d_fieldNormal << std::endl;
  }
*/
//  std::cout << "Dist:  " << d_info[iVisionBall].getX() << "  Angle: " << d_info[iVisionBall].getY() << std::endl;
//  std::cout << "(" << ballPos.getX() << ", " << ballPos.getY() << ")" << std::endl << std::endl;

  
  Vector3D oldBallPos = d_objectPositions[Types::BALL].getMu();
  Vector3D deltaBallPos = ballPos - oldBallPos;

  flag1LPos = Math::toFieldCoords(flag1LPos, d_fieldNormal);
  flag1RPos = Math::toFieldCoords(flag1RPos, d_fieldNormal);
  flag2LPos = Math::toFieldCoords(flag2LPos, d_fieldNormal);
  flag2RPos = Math::toFieldCoords(flag2RPos, d_fieldNormal);

  goal1LPos = Math::toFieldCoords(goal1LPos, d_fieldNormal);
  goal1RPos = Math::toFieldCoords(goal1RPos, d_fieldNormal);
  goal2LPos = Math::toFieldCoords(goal2LPos, d_fieldNormal);
  goal2RPos = Math::toFieldCoords(goal2RPos, d_fieldNormal);

  /*
  _debugLevel4("goal1l: " << goal1LPos);
  _debugLevel4("goal1r: " << goal1RPos);
  _debugLevel4("goal2l: " << goal2LPos);
  _debugLevel4("goal2r: " << goal2RPos);
  */

  d_objectPositions[Types::BALL].init(ballPos, Matrix9D());
  _debugLevel4("deltaBallPos = " << deltaBallPos << ", timeStep = " << d_timeStep);
//  std::cout << "ballPos = " << ballPos << ", deltaBallPos = " << deltaBallPos << ", timeStep = " << d_timeStep << std::endl;
  d_objectSpeeds[Types::BALL].init(deltaBallPos/d_timeStep, Matrix9D());
  d_lastVisionUpdate[Types::BALL] = d_gameTime;
  
  d_objectPositions[Types::GOAL1L].init(goal1LPos, Matrix9D());
  d_objectPositions[d_team == LEFT ? Types::GOAL1US : Types::GOAL2THEM].init(goal1LPos, Matrix9D());
  
  d_objectPositions[Types::GOAL2L].init(goal2LPos, Matrix9D());
  d_objectPositions[d_team == LEFT ? Types::GOAL2US : Types::GOAL1THEM].init(goal2LPos, Matrix9D());
   
  d_objectPositions[Types::GOAL1R].init(goal1RPos, Matrix9D());
  d_objectPositions[d_team == RIGHT ? Types::GOAL1US : Types::GOAL2THEM].init(goal1RPos, Matrix9D());
   
  d_objectPositions[Types::GOAL2R].init(goal2RPos, Matrix9D());
  d_objectPositions[d_team == RIGHT ? Types::GOAL2US : Types::GOAL1THEM].init(goal2RPos, Matrix9D());

  /*
  _debugLevel4("Goal1US: " << d_objectPositions[Types::GOAL1US].getMu());
  _debugLevel4("Goal2US: " << d_objectPositions[Types::GOAL2US].getMu());
  _debugLevel4("Goal1THEM: " << d_objectPositions[Types::GOAL1THEM].getMu());
  _debugLevel4("Goal2THEM: " << d_objectPositions[Types::GOAL2THEM].getMu());
  */

  d_objectPositions[Types::FLAG1L].init(flag1LPos, Matrix9D());
  d_objectPositions[d_team == LEFT ? Types::FLAG1US : Types::FLAG2THEM].init(flag1LPos, Matrix9D());
  
  d_objectPositions[Types::FLAG2L].init(flag2LPos, Matrix9D());
  d_objectPositions[d_team == LEFT ? Types::FLAG2US : Types::FLAG1THEM].init(flag2LPos, Matrix9D());
   
  d_objectPositions[Types::FLAG1R].init(flag1RPos, Matrix9D());
  d_objectPositions[d_team == RIGHT ? Types::FLAG1US : Types::FLAG2THEM].init(flag1RPos, Matrix9D());
   
  d_objectPositions[Types::FLAG2R].init(flag2RPos, Matrix9D());
  d_objectPositions[d_team == RIGHT ? Types::FLAG2US : Types::FLAG1THEM].init(flag2RPos, Matrix9D());


  

  _debugLevel4("Flags: " << flag1LPos << " " << flag1RPos << " " << flag2LPos << " " << flag2RPos);
  _debugLevel4("Goals: " << goal1LPos << " " << goal1RPos << " " << goal2LPos << " " << goal2RPos);
  _debugLevel4("Ball: " << d_info[iVisionBall] << " " << ballPos);
  _debugLevel4("Field normal: " << d_fieldNormal);
  _debugLevel4("d: " << d);
  
  //cout << /*"Dist to ball: " <<*/ d_info[iVisionBall][0] << endl;
  
}

// 5.65696 -177.269 -89.7783
