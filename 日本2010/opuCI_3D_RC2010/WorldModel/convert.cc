#include "worldmodel.ih"

void WorldModel::convertToWorldCoord()
{
  Vector3D vec(d_fieldNormal.getX(), 0, d_fieldNormal.getZ());
  Vector3D straightZ(0, 0, 1);
  double angleX = straightZ.angle(vec);
  vec = Vector3D(0, d_fieldNormal.getY(), d_fieldNormal.getZ());
  double angleY = straightZ.angle(vec);
  if(d_fieldNormal.getY() < 0)
    angleY *= -1;
  if(d_fieldNormal.getX() < 0)
    angleX *= -1;

  // all object positions convert to world coordinate
  for(int i=0; i<Types::NOBJECTS; i++){
    //  d_objectPositionsW[i].init(d_objectPositions[i].getMu(), Matrix9D());
    if(visibleObject((Types::Object)i))
    {
      Vector4F rt = Matrix4D::rotation( Vector3D(angleX, angleY, 0))
        * Vector4F(d_objectPositions[i].getMu().getX(),
                   d_objectPositions[i].getMu().getY(),
                   d_objectPositions[i].getMu().getZ(),0);


      d_objectPositionsW[i].init(Vector3D(rt.getX(),rt.getY(),rt.getZ()), Matrix9D());
    }
  }

  // all bodypart positions convert to world coordinate
  for(int i=Types::BC_NECK; i<Types::BC_NUM;i++){
    Vector4F rt = Matrix4D::rotation( Vector3D(angleX, angleY, 0))
      * Vector4F(d_bodyConnectionPositions[i].getX(),
                 d_bodyConnectionPositions[i].getY(),
                 d_bodyConnectionPositions[i].getZ(),0);
    d_bodyConnectionPositions[i] = Vector3D(rt.getX(),rt.getY(),rt.getZ()), Matrix9D();
  }
}

void WorldModel::estimateInvisibleObject()
{
  bool canCalcX = false, canCalcY = false;
  // search for side line vector
  if(visibleObject(Types::FLAG2L) && visibleObject(Types::FLAG2R)){
    d_worldUnitX = d_objectPositionsW[Types::FLAG2R].getMu() - d_objectPositionsW[Types::FLAG2L].getMu();
    canCalcX=true;
  }
  else if(visibleObject(Types::FLAG1L)&&visibleObject(Types::FLAG1R)){
    d_worldUnitX = d_objectPositionsW[Types::FLAG1R].getMu() - d_objectPositionsW[Types::FLAG1L].getMu();
    canCalcX=true;
  }
  else if(visibleObject(Types::GOAL2L)&&visibleObject(Types::GOAL2R)){
    d_worldUnitX = d_objectPositionsW[Types::GOAL2R].getMu() - d_objectPositionsW[Types::GOAL2L].getMu();
    canCalcX=true;
  }
  else if(visibleObject(Types::GOAL1L)&&visibleObject(Types::GOAL1R)){
    d_worldUnitX = d_objectPositionsW[Types::GOAL1R].getMu() - d_objectPositionsW[Types::GOAL1L].getMu();
    canCalcX=true;
  }
  if(canCalcX){
    d_worldUnitX.setZ(0);
    d_worldUnitX = d_worldUnitX.normalize();
  }

  // search for goal line vector
  if(visibleObject(Types::FLAG1L)){
    if(visibleObject(Types::FLAG2L)){
      d_worldUnitY = d_objectPositionsW[Types::FLAG2L].getMu() - d_objectPositionsW[Types::FLAG1L].getMu();
      canCalcY=true;
    }
    else if(visibleObject(Types::GOAL2L)){
      d_worldUnitY = d_objectPositionsW[Types::GOAL2L].getMu() - d_objectPositionsW[Types::FLAG1L].getMu();
      canCalcY=true;
    }
    else if(visibleObject(Types::GOAL1L)){
      d_worldUnitY = d_objectPositionsW[Types::GOAL1L].getMu() - d_objectPositionsW[Types::FLAG1L].getMu();
      canCalcY=true;
    }
  }
  else if(visibleObject(Types::FLAG2L)){
    if(visibleObject(Types::GOAL1L)){
      d_worldUnitY = d_objectPositionsW[Types::FLAG2L].getMu() - d_objectPositionsW[Types::GOAL1L].getMu();
      canCalcY=true;
    }
    else if(visibleObject(Types::GOAL2L)){
      d_worldUnitY = d_objectPositionsW[Types::FLAG2L].getMu() - d_objectPositionsW[Types::GOAL2L].getMu();
      canCalcY=true;
    }
  }
  else if((visibleObject(Types::GOAL1L))&&(visibleObject(Types::GOAL2L))){
    d_worldUnitY = d_objectPositionsW[Types::GOAL2L].getMu() - d_objectPositionsW[Types::GOAL1L].getMu();
    canCalcY=true;
  }
  else if(visibleObject(Types::FLAG1R)){
    if(visibleObject(Types::FLAG2R)){
      d_worldUnitY = d_objectPositionsW[Types::FLAG2R].getMu() - d_objectPositionsW[Types::FLAG1R].getMu();
      canCalcY=true;
    }
    else if(visibleObject(Types::GOAL2R)){
      d_worldUnitY = d_objectPositionsW[Types::GOAL2R].getMu() - d_objectPositionsW[Types::FLAG1R].getMu();
      canCalcY=true;
    }
    else if(visibleObject(Types::GOAL1R)){
      d_worldUnitY = d_objectPositionsW[Types::GOAL1R].getMu() - d_objectPositionsW[Types::FLAG1R].getMu();
      canCalcY=true;
    }
  }
  else if(visibleObject(Types::FLAG2R)){
    if(visibleObject(Types::GOAL1R)){
      d_worldUnitY = d_objectPositionsW[Types::FLAG2R].getMu() - d_objectPositionsW[Types::GOAL1R].getMu();
      canCalcY=true;
    }
    else if(visibleObject(Types::GOAL2R)){
      d_worldUnitY = d_objectPositionsW[Types::FLAG2R].getMu() - d_objectPositionsW[Types::GOAL2R].getMu();
      canCalcY=true;
    }
  }
  else if((visibleObject(Types::GOAL1R))&&(visibleObject(Types::GOAL2R))) {
    d_worldUnitY = d_objectPositionsW[Types::GOAL2R].getMu() - d_objectPositionsW[Types::GOAL1R].getMu();
    canCalcY=true;
  }
  if(canCalcY){
    d_worldUnitY.setZ(0);
    d_worldUnitY = d_worldUnitY.normalize();
  }

  if(!canCalcX && !canCalcY){
    d_allObjectPosAvailable = false;
    return;
  }
  else if(canCalcX && !canCalcY){
    d_worldUnitY.setX( d_worldUnitX.getY());
    d_worldUnitY.setY( -d_worldUnitX.getX());
    d_worldUnitY = d_worldUnitY.normalize();
  }
  else if(!canCalcX && canCalcY){
    d_worldUnitX.setX( -d_worldUnitY.getY());
    d_worldUnitX.setY( d_worldUnitY.getX());
    d_worldUnitX = d_worldUnitX.normalize();
  }

//  if( visibleLandmarkNum() == 0 ){
  if( visibleLandmarkNum() <= 1 ){
    d_allObjectPosAvailable = false;
    return;
  }


  Vector3D calculatedPos[Types::NOBJECTS];
  for(int i=0;i<Types::NOBJECTS;i++){
    calculatedPos[i] = Vector3D(0, 0, 0);
  }
  int calcCount = 0;
  // 見えているオブジェクトから他のオブジェクト位置を推測
  if(visibleObject(Types::FLAG1L)){
    calculatedPos[Types::FLAG2L] +=
      d_objectPositionsW[Types::FLAG1L].getMu()
      + (d_worldUnitY * s_fieldWidth);
    calculatedPos[Types::FLAG1R] +=
      d_objectPositionsW[Types::FLAG1L].getMu()
      + (d_worldUnitX * s_fieldLength);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::FLAG1L].getMu() +
      (d_worldUnitY * s_fieldWidth) +
      (d_worldUnitX * s_fieldLength);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::FLAG1L].getMu() +
      (d_worldUnitY * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::FLAG1L].getMu() +
      (d_worldUnitY * (s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::FLAG1L].getMu() +
      (d_worldUnitX * s_fieldLength) +
      (d_worldUnitY * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::FLAG1L].getMu() +
      (d_worldUnitY * (s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitX * s_fieldLength);
    calcCount++;
  }
  if(visibleObject(Types::FLAG2L)){
    
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitY * -s_fieldWidth);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitX * s_fieldLength);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitY * -s_fieldWidth) +
      (d_worldUnitX * s_fieldLength);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitY * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitY * -(s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitX * s_fieldLength) +
      (d_worldUnitY * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitY * -(s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitX * s_fieldLength);
    calcCount++;
  }
  if(visibleObject(Types::GOAL1L)){
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitY * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitY * (s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitX * s_fieldLength) +
      (d_worldUnitY * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitY * (s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitX * s_fieldLength);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitY * s_goalWidth);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitX * s_fieldLength);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitY * s_goalWidth) +
      (d_worldUnitX * s_fieldLength);
    calcCount++;
  }
  if(visibleObject(Types::GOAL2L)){
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitY * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitY * -(s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitX * s_fieldLength) +
      (d_worldUnitY * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitY * -(s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitX * s_fieldLength);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitY * -s_goalWidth);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitX * s_fieldLength);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitY * -s_goalWidth) +
      (d_worldUnitX * s_fieldLength);
    calcCount++;
  }
  if(visibleObject(Types::FLAG1R)){
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitY * s_fieldWidth) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitY * s_fieldWidth);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitY * (s_fieldWidth-s_goalWidth)/2) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitY * (s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitY * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitY * (s_fieldWidth+s_goalWidth)/2);
    calcCount++;
  }
  if(visibleObject(Types::FLAG2R)){
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitY * -s_fieldWidth) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitY * -s_fieldWidth);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitY * -(s_fieldWidth-s_goalWidth)/2) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitY * -(s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitY * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitY * -(s_fieldWidth+s_goalWidth)/2);
    calcCount++;
  }
  if(visibleObject(Types::GOAL1R)){
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitY * -(s_fieldWidth-s_goalWidth)/2) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitY * (s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitY * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitY * (s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitY * s_goalWidth) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitY * s_goalWidth);
    calcCount++;
  }
  if(visibleObject(Types::GOAL2R)){
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitY * (s_fieldWidth-s_goalWidth)/2) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitY * -(s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitY * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitY * -(s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitY * -s_goalWidth) +
      (d_worldUnitX * -s_fieldLength);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitY * -s_goalWidth);
    calcCount++;
  }

  calculatedPos[d_team == RIGHT ? Types::FLAG2US : Types::FLAG2THEM] = calculatedPos[Types::FLAG1R];
  calculatedPos[d_team == RIGHT ? Types::FLAG1US : Types::FLAG1THEM] = calculatedPos[Types::FLAG2R];
  calculatedPos[d_team == RIGHT ? Types::FLAG1THEM : Types::FLAG1US] = calculatedPos[Types::FLAG1L];
  calculatedPos[d_team == RIGHT ? Types::FLAG2THEM : Types::FLAG2US] = calculatedPos[Types::FLAG2L];
  calculatedPos[d_team == RIGHT ? Types::GOAL2US : Types::GOAL2THEM] = calculatedPos[Types::GOAL1R];
  calculatedPos[d_team == RIGHT ? Types::GOAL1US : Types::GOAL1THEM] = calculatedPos[Types::GOAL2R];
  calculatedPos[d_team == RIGHT ? Types::GOAL1THEM : Types::GOAL1US] = calculatedPos[Types::GOAL1L];
  calculatedPos[d_team == RIGHT ? Types::GOAL2THEM : Types::GOAL2US] = calculatedPos[Types::GOAL2L];
    
  // 予測した値を代入
  //std::cout << "time: " << d_gameTime << std::endl;
  for(int i=Types::FLAG1L; i<=Types::GOAL2THEM; i++){
    if(!visibleObject((Types::Object)i)){
      d_objectPositionsW[i].init(calculatedPos[i] / calcCount, Matrix9D());
    }
    // std::cout << "object"<<i<<" position world : " << d_objectPositionsW[i].getMu() << std::endl;
  }
  d_allObjectPosAvailable = true;

}

// calculate invisible object position from worldUnitXtest and worldUnitYtest
void WorldModel::estimateInvisibleObjectFromUnit()
{
  if( visibleLandmarkNum() == 0 ){
    d_allObjectPosAvailable = false;
    return;
  }

  Vector3D calculatedPos[Types::NOBJECTS];
  for(int i=0;i<Types::NOBJECTS;i++){
    calculatedPos[i] = Vector3D(0, 0, 0);
  }
  int calcCount = 0;
  // 見えているオブジェクトから他のオブジェクト位置を推測
  if(visibleObject(Types::FLAG1L)){
    calculatedPos[Types::FLAG2L] +=
      d_objectPositionsW[Types::FLAG1L].getMu()
      + (d_worldUnitYtest * s_fieldWidth);
    calculatedPos[Types::FLAG1R] +=
      d_objectPositionsW[Types::FLAG1L].getMu()
      + (d_worldUnitXtest * s_fieldLength);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::FLAG1L].getMu() +
      (d_worldUnitYtest * s_fieldWidth) +
      (d_worldUnitXtest * s_fieldLength);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::FLAG1L].getMu() +
      (d_worldUnitYtest * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::FLAG1L].getMu() +
      (d_worldUnitYtest * (s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::FLAG1L].getMu() +
      (d_worldUnitXtest * s_fieldLength) +
      (d_worldUnitYtest * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::FLAG1L].getMu() +
      (d_worldUnitYtest * (s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitXtest * s_fieldLength);
    calcCount++;
  }
  if(visibleObject(Types::FLAG2L)){
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitYtest * -s_fieldWidth);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitXtest * s_fieldLength);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitYtest * -s_fieldWidth) +
      (d_worldUnitXtest * s_fieldLength);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitXtest * s_fieldLength) +
      (d_worldUnitYtest * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::FLAG2L].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitXtest * s_fieldLength);
    calcCount++;
  }
  if(visibleObject(Types::GOAL1L)){
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitYtest * (s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitXtest * s_fieldLength) +
      (d_worldUnitYtest * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitYtest * (s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitXtest * s_fieldLength);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitYtest * s_goalWidth);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitXtest * s_fieldLength);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::GOAL1L].getMu() +
      (d_worldUnitYtest * s_goalWidth) +
      (d_worldUnitXtest * s_fieldLength);
    calcCount++;
  }
  if(visibleObject(Types::GOAL2L)){
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitYtest * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitXtest * s_fieldLength) +
      (d_worldUnitYtest * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitXtest * s_fieldLength);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitYtest * -s_goalWidth);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitXtest * s_fieldLength);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::GOAL2L].getMu() +
      (d_worldUnitYtest * -s_goalWidth) +
      (d_worldUnitXtest * s_fieldLength);
    calcCount++;
  }
  if(visibleObject(Types::FLAG1R)){
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitYtest * s_fieldWidth) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitYtest * s_fieldWidth);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitYtest * (s_fieldWidth-s_goalWidth)/2) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitYtest * (s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitYtest * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::FLAG1R].getMu() +
      (d_worldUnitYtest * (s_fieldWidth+s_goalWidth)/2);
    calcCount++;
  }
  if(visibleObject(Types::FLAG2R)){
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitYtest * -s_fieldWidth) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitYtest * -s_fieldWidth);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth-s_goalWidth)/2) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::FLAG2R].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth+s_goalWidth)/2);
    calcCount++;
  }
  if(visibleObject(Types::GOAL1R)){
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth-s_goalWidth)/2) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitYtest * (s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitYtest * (s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitYtest * s_goalWidth) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::GOAL2R]+=
      d_objectPositionsW[Types::GOAL1R].getMu() +
      (d_worldUnitYtest * s_goalWidth);
    calcCount++;
  }
  if(visibleObject(Types::GOAL2R)){
    calculatedPos[Types::FLAG2L]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitYtest * (s_fieldWidth-s_goalWidth)/2) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::FLAG1L]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth+s_goalWidth)/2) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::FLAG2R]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitYtest * (s_fieldWidth-s_goalWidth)/2);
    calculatedPos[Types::FLAG1R]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitYtest * -(s_fieldWidth+s_goalWidth)/2);
    calculatedPos[Types::GOAL2L]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::GOAL1L]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitYtest * -s_goalWidth) +
      (d_worldUnitXtest * -s_fieldLength);
    calculatedPos[Types::GOAL1R]+=
      d_objectPositionsW[Types::GOAL2R].getMu() +
      (d_worldUnitYtest * -s_goalWidth);
    calcCount++;
  }

  calculatedPos[d_team == RIGHT ? Types::FLAG2US : Types::FLAG2THEM] = calculatedPos[Types::FLAG1R];
  calculatedPos[d_team == RIGHT ? Types::FLAG1US : Types::FLAG1THEM] = calculatedPos[Types::FLAG2R];
  calculatedPos[d_team == RIGHT ? Types::FLAG1THEM : Types::FLAG1US] = calculatedPos[Types::FLAG1L];
  calculatedPos[d_team == RIGHT ? Types::FLAG2THEM : Types::FLAG2US] = calculatedPos[Types::FLAG2L];
  calculatedPos[d_team == RIGHT ? Types::GOAL2US : Types::GOAL2THEM] = calculatedPos[Types::GOAL1R];
  calculatedPos[d_team == RIGHT ? Types::GOAL1US : Types::GOAL1THEM] = calculatedPos[Types::GOAL2R];
  calculatedPos[d_team == RIGHT ? Types::GOAL1THEM : Types::GOAL1US] = calculatedPos[Types::GOAL1L];
  calculatedPos[d_team == RIGHT ? Types::GOAL2THEM : Types::GOAL2US] = calculatedPos[Types::GOAL2L];
    
  // 予測した値を代入
  //std::cout << "time: " << d_gameTime << std::endl;
  for(int i=Types::FLAG1L; i<=Types::GOAL2THEM; i++){
    if(!visibleObject((Types::Object)i)){
      d_objectPositionsW[i].init(calculatedPos[i] / calcCount, Matrix9D());
    }
    // std::cout << "object"<<i<<" position world : " << d_objectPositionsW[i].getMu() << std::endl;
  }
  d_allObjectPosAvailable = true;

}
