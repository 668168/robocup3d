#include "worldmodel.ih"


void WorldModel::updateVision()
{
  _debugLevel4("Ball: " << d_info[iVisionBall]);
  double neckangle = d_jointAngles[Types::NECK].getMu();
  double headangle = d_jointAngles[Types::HEAD].getMu();
  //  std::cout << "neckangle(now) = " << neckangle / M_PI * 180.0
  // << ", headangle(now) = " << headangle / M_PI * 180.0 << std::endl;

  Matrix4D rotateByNeck = Matrix4D::rotation(Vector3D(0, headangle, -neckangle));

  // Degrees to radians
  for (unsigned i = iVisionFlag1L; i <= iVisionBall; ++i)
  {
    d_info[i].setY(d_info[i].getY() * M_PI / 180.0);
    d_info[i].setZ(d_info[i].getZ() * M_PI / 180.0);
  }
  
  // Polar to Cartesian
  _debugLevel4("Flag angles: " << d_info[iVisionFlag1L] << " " << d_info[iVisionFlag1R] 
               << " " << d_info[iVisionFlag2L] << " " << d_info[iVisionFlag2R]);

  Vector3D flag1LPos = Math::polarToCartesian(d_info[iVisionFlag1L]);
  flag1LPos = rotateByNeck * flag1LPos;
  Vector3D flag1RPos = Math::polarToCartesian(d_info[iVisionFlag1R]);
  flag1RPos = rotateByNeck * flag1RPos;
  Vector3D flag2LPos = Math::polarToCartesian(d_info[iVisionFlag2L]);
  flag2LPos = rotateByNeck * flag2LPos;
  Vector3D flag2RPos = Math::polarToCartesian(d_info[iVisionFlag2R]);
  flag2RPos = rotateByNeck * flag2RPos;

  Vector3D goal1LPos = Math::polarToCartesian(d_info[iVisionGoal1L]);
  goal1LPos = rotateByNeck * goal1LPos;
  Vector3D goal1RPos = Math::polarToCartesian(d_info[iVisionGoal1R]);
  goal1RPos = rotateByNeck * goal1RPos;
  Vector3D goal2LPos = Math::polarToCartesian(d_info[iVisionGoal2L]);
  goal2LPos = rotateByNeck * goal2LPos;
  Vector3D goal2RPos = Math::polarToCartesian(d_info[iVisionGoal2R]);
  goal2RPos = rotateByNeck * goal2RPos;


  // current version
  double delta_t = d_timeStep;
  if(delta_t == 0){
    delta_t = 0.02; // the length of one step
  }

  if((d_deadTime == 0 || d_deadTime > 9000) && // 自殺モードでない場合
    (d_playMode == BEFORE_KICKOFF || d_playMode == GOAL_THEM
     || d_playMode == GOAL_US     || d_playMode == GOAL_RIGHT
     || d_playMode == GOAL_LEFT || d_fieldNormal.length() == 0))
  {
    d_fieldNormal = Vector3D(0, 0, 1);

    if( getSide() == RIGHT )
    {
      d_worldUnitXtest = Vector3D(-1, 0, 0);
      d_worldUnitYtest = Vector3D(0, 1, 0);
    }
    else
    {
      d_worldUnitXtest = Vector3D(1, 0, 0);
      d_worldUnitYtest = Vector3D(0,-1, 0);
    }

  }
  else{
    // rotate FieldNormal by gyro
    Vector4F fn = Matrix4D::rotation(Vector3D(d_gyro.getX() * delta_t * M_PI/180.0,
                                              d_gyro.getY() * delta_t * M_PI/180.0,
                                              d_gyro.getZ() * delta_t * M_PI/180.0))
      * Vector4F(d_fieldNormal.getX(), d_fieldNormal.getY(), d_fieldNormal.getZ(), 0);

    d_fieldNormal = Vector3D(fn.getX(), fn.getY(), fn.getZ());

    // rotate Unit X by gyro
    Vector4F ux = Matrix4D::rotation(Vector3D(d_gyro.getX() * delta_t * M_PI/180.0,
                                              d_gyro.getY() * delta_t * M_PI/180.0,
                                              d_gyro.getZ() * delta_t * M_PI/180.0))
      * Vector4F(d_worldUnitXtest.getX(), d_worldUnitXtest.getY(), d_worldUnitXtest.getZ(), 0);

    d_worldUnitXtest = Vector3D(ux.getX(), ux.getY(), ux.getZ());

    // rotate Unit Y by gyro
    Vector4F uy = Matrix4D::rotation(Vector3D(d_gyro.getX() * delta_t * M_PI/180.0,
                                              d_gyro.getY() * delta_t * M_PI/180.0,
                                              d_gyro.getZ() * delta_t * M_PI/180.0))
      * Vector4F(d_worldUnitYtest.getX(), d_worldUnitYtest.getY(), d_worldUnitYtest.getZ(), 0);

    d_worldUnitYtest = Vector3D(uy.getX(), uy.getY(), uy.getZ());

  }
/*
  setDebugLine(Vector3D(0, 0, 0), d_worldUnitXtest);
  setDebugPointWithLabel(d_worldUnitXtest, "UnitX");
  setDebugLine(Vector3D(0, 0, 0), d_worldUnitYtest);
  setDebugPointWithLabel(d_worldUnitYtest, "UnitY");
*/
  for (unsigned i = 0; i < 11; ++i) {
    Vector3D playerPos = Math::polarToCartesian(d_info[iVisionPlayer1 + i]);
    playerPos = rotateByNeck * playerPos;
    Vector3D oldPlayerPos = d_objectPositions[Types::PLAYER1 + i].getMu();
    Vector3D deltaPlayerPos = playerPos - oldPlayerPos;
    if(playerPos.length() != 0)
    {
      d_objectPositions[Types::PLAYER1 + i].init(playerPos, Matrix9D());
      d_objectSpeeds[Types::PLAYER1 + i].init(deltaPlayerPos/d_timeStep, Matrix9D());
    }
  }

  for (unsigned i = 0; i < 11; ++i) {
    Vector3D opponentPos = Math::polarToCartesian(d_info[iVisionOpponent1 + i]);
    opponentPos = rotateByNeck * opponentPos;
    // opponentPos = Math::toFieldCoords(opponentPos, d_fieldNormal);
    Vector3D oldOpponentPos = d_objectPositions[Types::OPPONENT1 + i].getMu();
    Vector3D deltaOpponentPos = opponentPos - oldOpponentPos;
    if(opponentPos.length() != 0)
    {
      d_objectPositions[Types::OPPONENT1 + i].init(opponentPos, Matrix9D());
      d_objectSpeeds[Types::OPPONENT1 + i].init(deltaOpponentPos/d_timeStep, Matrix9D());
    }
  }

  // Ball position
  _debugLevel1("Ball!");
  Vector3D ballPos = Math::polarToCartesian(d_info[iVisionBall]);
  ballPos = rotateByNeck * ballPos;
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
  d_oldBallPos = oldBallPos;


  if(ballPos.length() != 0)
  {
    d_objectPositions[Types::BALL].init(ballPos, Matrix9D());
    d_objectSpeeds[Types::BALL].init(deltaBallPos/d_timeStep, Matrix9D());
    d_lastVisionUpdate[Types::BALL] = d_time;
  }

  if(goal1LPos.length() != 0)
  {
    d_objectPositions[Types::GOAL1L].init(goal1LPos, Matrix9D());
    d_lastVisionUpdate[Types::GOAL1L] = d_time;
    d_objectPositions[d_team == LEFT ? Types::GOAL1US : Types::GOAL1THEM].init(goal1LPos, Matrix9D());
    d_lastVisionUpdate[d_team == LEFT ? Types::GOAL1US : Types::GOAL1THEM] = d_time;
  }
  
  if(goal2LPos.length() != 0)
  {
    d_objectPositions[Types::GOAL2L].init(goal2LPos, Matrix9D());
    d_objectPositions[d_team == LEFT ? Types::GOAL2US : Types::GOAL2THEM].init(goal2LPos, Matrix9D());
    d_lastVisionUpdate[Types::GOAL2L] = d_time;
    d_lastVisionUpdate[d_team == LEFT ? Types::GOAL2US : Types::GOAL2THEM] = d_time;
  }
  
  if(goal1RPos.length() != 0)
  {
    d_objectPositions[Types::GOAL1R].init(goal1RPos, Matrix9D());
    d_objectPositions[d_team == RIGHT ? Types::GOAL2US : Types::GOAL2THEM].init(goal1RPos, Matrix9D());
    d_lastVisionUpdate[Types::GOAL1R] = d_time;
    d_lastVisionUpdate[d_team == RIGHT ? Types::GOAL2US : Types::GOAL2THEM] = d_time;
  }

  if(goal2RPos.length() != 0)
  {
    d_objectPositions[Types::GOAL2R].init(goal2RPos, Matrix9D());
    d_objectPositions[d_team == RIGHT ? Types::GOAL1US : Types::GOAL1THEM].init(goal2RPos, Matrix9D());
    d_lastVisionUpdate[Types::GOAL2R] = d_time;
    d_lastVisionUpdate[d_team == RIGHT ? Types::GOAL1US : Types::GOAL1THEM] = d_time;
  }

  if(flag1LPos.length() != 0)
  {
    d_objectPositions[Types::FLAG1L].init(flag1LPos, Matrix9D());
    d_objectPositions[d_team == LEFT ? Types::FLAG1US : Types::FLAG1THEM].init(flag1LPos, Matrix9D());
    d_lastVisionUpdate[Types::FLAG1L] = d_time;
    d_lastVisionUpdate[d_team == LEFT ? Types::FLAG1US : Types::FLAG1THEM] = d_time;
  }

  if(flag2LPos.length() != 0)
  {
    d_objectPositions[Types::FLAG2L].init(flag2LPos, Matrix9D());
    d_objectPositions[d_team == LEFT ? Types::FLAG2US : Types::FLAG2THEM].init(flag2LPos, Matrix9D());
    d_lastVisionUpdate[Types::FLAG2L] = d_time;
    d_lastVisionUpdate[d_team == LEFT ? Types::FLAG2US : Types::FLAG2THEM] = d_time;
  }

  if(flag1RPos.length() != 0)
  {
    d_objectPositions[Types::FLAG1R].init(flag1RPos, Matrix9D());
    d_objectPositions[d_team == RIGHT ? Types::FLAG2US : Types::FLAG2THEM].init(flag1RPos, Matrix9D());
    d_lastVisionUpdate[Types::FLAG1R] = d_time;
    d_lastVisionUpdate[d_team == RIGHT ? Types::FLAG2US : Types::FLAG2THEM] = d_time;
  }

  if(flag2RPos.length() != 0)
  {
    d_objectPositions[Types::FLAG2R].init(flag2RPos, Matrix9D());
    d_objectPositions[d_team == RIGHT ? Types::FLAG1US : Types::FLAG1THEM].init(flag2RPos, Matrix9D());
    d_lastVisionUpdate[Types::FLAG2R] = d_time;
    d_lastVisionUpdate[d_team == RIGHT ? Types::FLAG1US : Types::FLAG1THEM] = d_time;
  }

  _debugLevel4("Flags: " << flag1LPos << " " << flag1RPos << " " << flag2LPos << " " << flag2RPos);
  _debugLevel4("Goals: " << goal1LPos << " " << goal1RPos << " " << goal2LPos << " " << goal2RPos);
  _debugLevel4("Ball: " << d_info[iVisionBall] << " " << ballPos);
  _debugLevel4("Field normal: " << d_fieldNormal);
  _debugLevel4("d: " << d);

  if(d_info[iMyPos].length() != 0)
    d_myPos = d_info[iMyPos];

}

double WorldModel::getLastVisionUpdateTime()
{

  double updateTime = 0;
  for(int i=0;i<Types::NOBJECTS;i++)
  {
    if(updateTime < d_lastVisionUpdate[i])
    {
      updateTime = d_lastVisionUpdate[i];
    }
  }
  return updateTime;

}

// 5.65696 -177.269 -89.7783
