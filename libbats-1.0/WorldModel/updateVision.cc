#include "worldmodel.ih"


void WorldModel::updateVision()
{
  Cochlea& cochlea = SCochlea::getInstance();
  _debugLevel4("Ball: " << cochlea.getInfo(Cochlea::iVisionBall));

  for(size_t i = 0; i < Types::NOBJECTS; ++i)
  {
    d_prevObjects[i] = d_objects[i];
    d_prevVisionUpdate[i] = d_lastVisionUpdate[i];
  }
  
  // Polar to Cartesian
  Vector3D ballPos = Math::polarToCartesian(cochlea.getInfo(Cochlea::iVisionBall));

  Vector3D flag1LPos = Math::polarToCartesian(cochlea.getInfo(Cochlea::iVisionFlag1L));
  Vector3D flag1RPos = Math::polarToCartesian(cochlea.getInfo(Cochlea::iVisionFlag1R));
  Vector3D flag2LPos = Math::polarToCartesian(cochlea.getInfo(Cochlea::iVisionFlag2L));
  Vector3D flag2RPos = Math::polarToCartesian(cochlea.getInfo(Cochlea::iVisionFlag2R));

  Vector3D goal1LPos = Math::polarToCartesian(cochlea.getInfo(Cochlea::iVisionGoal1L));
  Vector3D goal1RPos = Math::polarToCartesian(cochlea.getInfo(Cochlea::iVisionGoal1R));
  Vector3D goal2LPos = Math::polarToCartesian(cochlea.getInfo(Cochlea::iVisionGoal2L));
  Vector3D goal2RPos = Math::polarToCartesian(cochlea.getInfo(Cochlea::iVisionGoal2R));

  //  _debugLevel4("UHBGJHBDF: " << cochlea.getInfo(Cochlea::iVisionBall) << " " << ballPos);
  // Store positions in local coordinates
  d_objects[Types::BALL].position.init(ballPos, Matrix9D());
  d_lastVisionUpdate[Types::BALL] = getTime();
  

  d_objects[Types::GOAL1L].position.init(goal1LPos, Matrix9D());
  d_objects[d_team ==Types::LEFT ? Types::GOAL1US : Types::GOAL2THEM].position.init(goal1LPos, Matrix9D());
  
  d_objects[Types::GOAL2L].position.init(goal2LPos, Matrix9D());
  d_objects[d_team ==Types::LEFT ? Types::GOAL2US : Types::GOAL1THEM].position.init(goal2LPos, Matrix9D());
   
  d_objects[Types::GOAL1R].position.init(goal1RPos, Matrix9D());
  d_objects[d_team ==Types::LEFT ? Types::GOAL1THEM : Types::GOAL2US].position.init(goal1RPos, Matrix9D());
   
  d_objects[Types::GOAL2R].position.init(goal2RPos, Matrix9D());
  d_objects[d_team ==Types::LEFT ? Types::GOAL2THEM : Types::GOAL1US].position.init(goal2RPos, Matrix9D());

  d_objects[Types::FLAG1L].position.init(flag1LPos, Matrix9D());
  d_objects[d_team == Types::LEFT ? Types::FLAG1US : Types::FLAG2THEM].position.init(flag1LPos, Matrix9D());
  
  d_objects[Types::FLAG2L].position.init(flag2LPos, Matrix9D());
  d_objects[d_team ==Types::LEFT ? Types::FLAG2US : Types::FLAG1THEM].position.init(flag2LPos, Matrix9D());
   
  d_objects[Types::FLAG1R].position.init(flag1RPos, Matrix9D());
  d_objects[d_team ==Types::LEFT ? Types::FLAG1THEM : Types::FLAG2US].position.init(flag1RPos, Matrix9D());
   
  d_objects[Types::FLAG2R].position.init(flag2RPos, Matrix9D());
  d_objects[d_team ==Types::LEFT ? Types::FLAG2THEM : Types::FLAG1US].position.init(flag2RPos, Matrix9D());

  Vector3D worldRight = (d_objects[Types::FLAG1THEM].position.getMu() - d_objects[Types::FLAG1US].position.getMu()).normalize();
  Vector3D worldForward = (d_objects[Types::FLAG1US].position.getMu() - d_objects[Types::FLAG2US].position.getMu()).normalize();
  // Determine field orientation
  Vector3D up = worldRight.crossProduct(worldForward).normalize();
  
  // Project local right and forward onto field plane:
  // P = F + N * ((F * N) / (N * N))
  // N is normalized so: N * N = 1
  // Vector3D right =  Vector3D(1, 0, 0) + up * up[0]
  // Vector3D forward = Vector3D(0, 1, 0) + up * up[1];
  Vector3D right = up.crossProduct(Vector3D(1, 0, 0).crossProduct(up));
  Vector3D forward = up.crossProduct(Vector3D(0, 1, 0).crossProduct(up));
  
  d_fieldTransform = Matrix4D(right.normalize(), forward.normalize(), up.normalize());
  _debugLevel4("field trans: " << endl << d_fieldTransform);
  
  double d = -(up * d_objects[Types::FLAG1THEM].position.getMu());
  d_distToField = -d;

  // Transform all positions into world coordinates
  Matrix4D invFieldTransform = d_fieldTransform.inverse();
  

  _debugLevel4("Ball position: " << d_objects[Types::BALL].position.getMu());

  Vector3F flag1t = getObjectPositionLocal(Types::FLAG1THEM).getMu();
  Vector3F flag1u = getObjectPositionLocal(Types::FLAG1US).getMu();
  Vector3F flag2u = getObjectPositionLocal(Types::FLAG2US).getMu();

  //  Vector3F v0 = (flag1RPos-flag1LPos).normalize(); // right
  //  Vector3F v1 = (flag1LPos-flag2LPos).normalize(); // forward
  //  Vector3F v2 = v0.crossProduct(v1).normalize();   // up

  Vector3F v0 = (flag1t-flag1u).normalize(); // right
  Vector3F v1 = (flag1u-flag2u).normalize(); // forward
  Vector3F v2 = v0.crossProduct(v1).normalize();   // up

  //  cerr << "Forward: " << v0 << endl;
  //  cerr << "Right: " << v1 << endl;
  //  cerr << "Up: " << v2 << endl;

  // Calculate the world transform and its inverse.
  d_invWorldTransform = Matrix4D(v0,v1,v2);//,-flag1u);
  d_worldTransform    = d_invWorldTransform.inverse();
  
  //5 players
  for (unsigned i = 0; i < 5; ++i) {
    Vector3D playerPosPolar = cochlea.getInfo((Cochlea::InfoID)(Cochlea::iVisionPlayer1 + i));
    if (playerPosPolar[0] != 0)
    {
	  //	  _debugLevel4("Player pos pola: " << playerPosPolar);
      Vector3D playerPosCart = Math::polarToCartesian(playerPosPolar);
	  //	  _debugLevel4("Player pos cart: " << playerPosCart);
      d_objects[Types::PLAYER1 + i].position.init(playerPosCart, Matrix9D());
      d_lastVisionUpdate[Types::PLAYER1 + i] = d_time;

	  PlayerInfo &pinfo = getPlayerFromPid(i);
	  pinfo.updatePosition(playerPosCart,d_time);
    }
    else
      d_objects[Types::PLAYER1 + i].position.init(Vector3D(0,0,0), Matrix9D());
  }
  //5 players
  for (unsigned i = 0; i < 5; ++i) {
    Vector3D opponentPosPolar = cochlea.getInfo((Cochlea::InfoID)(Cochlea::iVisionOpponent1 + i));
    if (opponentPosPolar[0] != 0)
    {
      Vector3D opponentPosCart = Math::polarToCartesian(opponentPosPolar);
      d_objects[Types::OPPONENT1 + i].position.init(opponentPosCart, Matrix9D());
      d_lastVisionUpdate[Types::OPPONENT1 + i] = d_time;

	  PlayerInfo &pinfo = getOpponentFromPid(i);
	  pinfo.updatePosition(opponentPosCart,d_time);
    }
    else
      d_objects[Types::OPPONENT1 + i].position.init(Vector3D(0,0,0), Matrix9D());
  }

  for (unsigned i = 0; i < Types::NOBJECTS; ++i)
    d_objects[i].position.init(invFieldTransform * d_objects[i].position.getMu(), Matrix9D());


}

// 5.65696 -177.269 -89.7783
