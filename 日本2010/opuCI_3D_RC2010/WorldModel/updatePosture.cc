#include "worldmodel.ih"

void WorldModel::updatePosture()
{
  Vector4F torsoNeck(0, 0, 0.09, 0);
  Vector4F neckHead(0, 0, 0.06, 0);

  Vector4F torsoToA_ARM_R(0.098, 0, 0.075, 0); // A: shoulder
  Vector4F torsoToA_ARM_L(-0.098, 0, 0.075, 0); 
  Vector4F AtoB_ARM(0, 0.09, 0.01, 0); // B: upper arm
  Vector4F BtoC_ARM(0, 0.105, 0, 0);   // C: lower arm

  Vector4F torsoToA_LEG_R(0.055, -0.01, -0.11, 0);  // A: hip1, hip2
  Vector4F torsoToA_LEG_L(-0.055, -0.01, -0.11, 0); //
  Vector4F AtoB_LEG(0, 0.005, -0.12, 0); // B: shank
  Vector4F BtoC_LEG(0, 0.0, -0.1, 0);    // C: ankle, foot
  Vector4F CtoD_LEG(0, -0.05, -0.035, 0); // D: heel
  Vector4F CtoE_LEG(0, 0.13, -0.035, 0); // E: toe

  Vector3D rotationVec;
  Vector4F tmp;

  // 計算を簡単にするため，まずTORSOを原点として各パーツの接合部の位置を算出する．
  d_bodyConnectionPositions[Types::BC_TORSO] = Vector3D(0, 0, 0);
  // 頭の計算
  rotationVec = Vector3D(0, 0, 0);
  // neck
  d_bodyConnectionPositions[Types::BC_NECK] = Vector3D(torsoNeck.getX(), torsoNeck.getY(), torsoNeck.getZ());

  // head
  rotationVec.setZ( - d_jointAngles[Types::HEAD_1].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * neckHead;
  d_bodyConnectionPositions[Types::BC_HEAD] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_NECK];

  // 右腕の計算
  rotationVec = Vector3D(0, 0, 0);
  // torso->A
  d_bodyConnectionPositions[Types::BC_RSHOULDER] =
    Vector3D(torsoToA_ARM_R.getX(), torsoToA_ARM_R.getY(), torsoToA_ARM_R.getZ());
    
  // A->B
  rotationVec = Vector3D( 0, 0, - d_jointAngles[Types::RARM2].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * AtoB_ARM;
  rotationVec = Vector3D( - d_jointAngles[Types::RARM1].getMu(), 0, 0 );
  tmp = Matrix4D::rotation(rotationVec) * tmp;
  d_bodyConnectionPositions[Types::BC_RELBOW] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_RSHOULDER];
    
  // B->C  
  rotationVec = Vector3D(0, 0, - d_jointAngles[Types::RARM4].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * BtoC_ARM;
  rotationVec = Vector3D(0, - d_jointAngles[Types::RARM3].getMu() , 0);
  tmp = Matrix4D::rotation(rotationVec) * tmp;
  rotationVec = Vector3D( 0, 0, - d_jointAngles[Types::RARM2].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * tmp;
  rotationVec = Vector3D( - d_jointAngles[Types::RARM1].getMu(), 0, 0 );
  tmp = Matrix4D::rotation(rotationVec) * tmp;

  d_bodyConnectionPositions[Types::BC_RHAND] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_RELBOW];


  // 左腕の計算
  rotationVec = Vector3D(0, 0, 0);
  // torso->A
  d_bodyConnectionPositions[Types::BC_LSHOULDER] =
    Vector3D(torsoToA_ARM_L.getX(), torsoToA_ARM_L.getY(), torsoToA_ARM_L.getZ());
    
  // A->B
  rotationVec = Vector3D( 0, 0, - d_jointAngles[Types::LARM2].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * AtoB_ARM;
  rotationVec = Vector3D( - d_jointAngles[Types::LARM1].getMu(), 0, 0 );
  tmp = Matrix4D::rotation(rotationVec) * tmp;
  d_bodyConnectionPositions[Types::BC_LELBOW] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_LSHOULDER];
    
  // B->C  
  rotationVec = Vector3D(0, 0, - d_jointAngles[Types::LARM4].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * BtoC_ARM;
  rotationVec = Vector3D(0, - d_jointAngles[Types::LARM3].getMu(), 0 );
  tmp = Matrix4D::rotation(rotationVec) * tmp;
  rotationVec = Vector3D(0, 0, - d_jointAngles[Types::LARM2].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * tmp;
  rotationVec = Vector3D(- d_jointAngles[Types::LARM1].getMu(), 0, 0 );
  tmp = Matrix4D::rotation(rotationVec) * tmp;

  d_bodyConnectionPositions[Types::BC_LHAND] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_LELBOW];


// 右足の計算
  rotationVec = Vector3D(0, 0, 0);
  // hip1, hip2 (A)
  d_bodyConnectionPositions[Types::BC_RHIP] =
    Vector3D(torsoToA_LEG_R.getX(), torsoToA_LEG_R.getY(), torsoToA_LEG_R.getZ());

  // A->B
  rotationVec.setX(-d_jointAngles[Types::RLEG1].getMu() * (-0.7071) - d_jointAngles[Types::RLEG3].getMu());
  rotationVec.setY(-d_jointAngles[Types::RLEG2].getMu() );
  rotationVec.setZ(-d_jointAngles[Types::RLEG1].getMu() * 0.7071);
  tmp = Matrix4D::rotation(rotationVec) * AtoB_LEG;
  d_bodyConnectionPositions[Types::BC_RKNEE] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_RHIP];
    
  // B->C
  rotationVec.setX(rotationVec.getX() - d_jointAngles[Types::RLEG4].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * BtoC_LEG;
  d_bodyConnectionPositions[Types::BC_RANKLE] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_RKNEE];
    
  // C->D, C->E
  rotationVec.setX(rotationVec.getX() - d_jointAngles[Types::RLEG5].getMu() );
  rotationVec.setY(rotationVec.getY() - d_jointAngles[Types::RLEG6].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * CtoD_LEG;
  d_bodyConnectionPositions[Types::BC_RHEEL] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_RANKLE];

  tmp = Matrix4D::rotation(rotationVec) * CtoE_LEG;
  d_bodyConnectionPositions[Types::BC_RTOE] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_RANKLE];

// 左足の計算
  rotationVec = Vector3D(0, 0, 0);
  // hip1, hip2
  d_bodyConnectionPositions[Types::BC_LHIP] =
    Vector3D(torsoToA_LEG_L.getX(), torsoToA_LEG_L.getY(), torsoToA_LEG_L.getZ());

  // A->B
  rotationVec.setX(-d_jointAngles[Types::LLEG1].getMu() * (-0.7071) - d_jointAngles[Types::LLEG3].getMu());
  rotationVec.setY(-d_jointAngles[Types::LLEG2].getMu() );
  rotationVec.setZ(-d_jointAngles[Types::LLEG1].getMu() * (-0.7071));
  tmp = Matrix4D::rotation(rotationVec) * AtoB_LEG;
  d_bodyConnectionPositions[Types::BC_LKNEE] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_LHIP];
    
  // B->C
  rotationVec.setX(rotationVec.getX() - d_jointAngles[Types::LLEG4].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * BtoC_LEG;
  d_bodyConnectionPositions[Types::BC_LANKLE] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_LKNEE];
    
  // C->D
  rotationVec.setX(rotationVec.getX() - d_jointAngles[Types::LLEG5].getMu() );
  rotationVec.setY(rotationVec.getY() - d_jointAngles[Types::LLEG6].getMu() );
  tmp = Matrix4D::rotation(rotationVec) * CtoD_LEG;
  d_bodyConnectionPositions[Types::BC_LHEEL] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_LANKLE];

  // C->E
  tmp = Matrix4D::rotation(rotationVec) * CtoE_LEG;
  d_bodyConnectionPositions[Types::BC_LTOE] = Vector3D(tmp.getX(), tmp.getY(), tmp.getZ())
    + d_bodyConnectionPositions[Types::BC_LANKLE];

  // HEAD(カメラ)からのベクトルに変換．Nao的にはx,yが逆なのでそれを修正
  Vector3D defaultHead = d_bodyConnectionPositions[Types::BC_HEAD];
  for(int i=Types::BC_NECK; i<Types::BC_NUM;i++){
    Vector3D tmp =
      d_bodyConnectionPositions[(Types::BodyConnection)i] - defaultHead;
    d_bodyConnectionPositions[(Types::BodyConnection)i] =
      Vector3D(tmp.getY(), -tmp.getX(), tmp.getZ());
  }

  // Torso is identity
  d_bodyPartPositions[Types::TORSO] = Vector4F(0, 0, 0, 1);

  // Head is just translated
  d_bodyPartPositions[Types::HEAD] = d_bodyPartPositions[Types::TORSO]
    + Vector4F(0, 0, 0.09 + 0.065, 0);

  // Shoulders too
  d_bodyPartPositions[Types::LSHOULDER] = d_bodyPartPositions[Types::TORSO]
    + Vector4F(-0.098, 0, 0.075, 0);
  d_bodyPartPositions[Types::RSHOULDER] = d_bodyPartPositions[Types::TORSO]
    + Vector4F( 0.098, 0, 0.075, 0);

  // Upper legs too
  d_bodyPartPositions[Types::LUPPERLEG] = d_bodyPartPositions[Types::TORSO]
    + Vector4F(-0.055, -0.01, -0.115, 0);
  d_bodyPartPositions[Types::RUPPERLEG] = d_bodyPartPositions[Types::TORSO]
    + Vector4F( 0.055, -0.01, -0.115, 0);

  // Lower legs
  double lj1 = d_jointAngles[Types::LLEG1].getMu(); // radian
  double lj2 = d_jointAngles[Types::LLEG2].getMu();
  double lj3 = d_jointAngles[Types::LLEG3].getMu();
  double rj1 = d_jointAngles[Types::RLEG1].getMu(); // radian
  double rj2 = d_jointAngles[Types::RLEG2].getMu();
  double rj3 = d_jointAngles[Types::RLEG3].getMu();

  double oldPos_y,lastPos_y,curPos_y;

  oldPos_y = d_lastBodyPartPos[Types::LLOWERLEG].getY();
  d_lastBodyPartPos[Types::LLOWERLEG] = d_bodyPartPositions[Types::LLOWERLEG];
  lastPos_y = d_bodyPartPositions[Types::LLOWERLEG].getY();
  d_bodyPartPositions[Types::LLOWERLEG] = d_bodyPartPositions[Types::LUPPERLEG]
    + Matrix4D::rotation(Vector3D(lj3-0.7071*lj1, lj2, -0.7071*lj1)) * Vector4F(0, 0, -0.14, 0);
  curPos_y = d_bodyPartPositions[Types::LLOWERLEG].getY();
  if(curPos_y < lastPos_y && lastPos_y > oldPos_y)
    updateBodyPartPeakTime(Types::LLOWERLEG);

  oldPos_y = d_lastBodyPartPos[Types::RLOWERLEG].getY();
  d_lastBodyPartPos[Types::RLOWERLEG] = d_bodyPartPositions[Types::RLOWERLEG];
  lastPos_y = d_bodyPartPositions[Types::RLOWERLEG].getY();
  d_bodyPartPositions[Types::RLOWERLEG] = d_bodyPartPositions[Types::RUPPERLEG]
    + Matrix4D::rotation(Vector3D(rj3-0.7071*rj1, rj2, -0.7071*rj1)) * Vector4F(0, 0, -0.14, 0);
  curPos_y = d_bodyPartPositions[Types::RLOWERLEG].getY();
  if(curPos_y < lastPos_y && lastPos_y > oldPos_y)
    updateBodyPartPeakTime(Types::RLOWERLEG);

  double lj4 = d_jointAngles[Types::LLEG4].getMu();
  double rj4 = d_jointAngles[Types::RLEG4].getMu();

  // Foots
  oldPos_y = d_lastBodyPartPos[Types::LFOOT].getY();
  d_lastBodyPartPos[Types::LFOOT] = d_bodyPartPositions[Types::LFOOT];
  lastPos_y = d_bodyPartPositions[Types::LFOOT].getY();
  d_bodyPartPositions[Types::LFOOT] = d_bodyPartPositions[Types::LUPPERLEG]
    + Matrix4D::rotation(Vector3D(lj3-0.7071*lj1, lj2, -0.7071*lj1))
    * Matrix4D::rotation(Vector3D(lj4, 0, 0)) * Vector4F(0, 0, -0.11, 0);
  curPos_y = d_bodyPartPositions[Types::LFOOT].getY();
//  std::cout << oldPos_y << " " << lastPos_y << " " << curPos_y << std::endl;
  if(curPos_y < lastPos_y && lastPos_y > oldPos_y)
    updateBodyPartPeakTime(Types::LFOOT);

  oldPos_y = d_lastBodyPartPos[Types::RFOOT].getY();
  d_lastBodyPartPos[Types::RFOOT] = d_bodyPartPositions[Types::RFOOT];
  lastPos_y = d_bodyPartPositions[Types::RFOOT].getY();
  d_bodyPartPositions[Types::RFOOT] = d_bodyPartPositions[Types::RUPPERLEG]
    + Matrix4D::rotation(Vector3D(rj3-0.7071*rj1, rj2, -0.7071*rj1)) * 
    Matrix4D::rotation(Vector3D(rj4, 0, 0)) * Vector4F(0, 0, -0.11, 0);
  curPos_y = d_bodyPartPositions[Types::RFOOT].getY();
  if(curPos_y < lastPos_y && lastPos_y > oldPos_y)
    updateBodyPartPeakTime(Types::RFOOT);
  
  d_footForceContacts[0] = d_info[iFootLeft];
  d_footForces[0] = d_info[iFootLeft2];
  //_debugLevel4("Force left: " << d_footForceContacts[0] << " " << d_footForces[0]);
  
  d_footForceContacts[1] = d_info[iFootRight];
  d_footForces[1] = d_info[iFootRight2];
  //_debugLevel4("Force right: " << d_footForceContacts[1] << " " << d_footForces[1]);

  _debugLevel4(d_footForces[0].length() << "\t" << d_footForces[1].length() << "\t" << fabs(d_footForces[0].length() - d_footForces[1].length()));
  d_gyro = d_info[iTorsoGyro];

  d_acceleration = d_info[iAcceleration];

}

void WorldModel::updateBodyPartPeakTime(Types::BodyPart bp)
{
  checkStability(bp);

  d_bodyPartPeakTime4[bp] = d_bodyPartPeakTime3[bp];
  d_bodyPartPeakTime3[bp] = d_bodyPartPeakTime2[bp];
  d_bodyPartPeakTime2[bp] = d_bodyPartPeakTime1[bp];
  d_bodyPartPeakTime1[bp] = d_time;
    
}


void WorldModel::checkStability(Types::BodyPart bp) 
{
  double averageOfF = ( d_bodyPartPeakTime1[bp] - d_bodyPartPeakTime4[bp] ) / 3.0;
  
  if( fabs(averageOfF - (d_time - d_bodyPartPeakTime1[bp])) > 0.05 )
    d_isUnstable[bp] = true;
  else
    d_isUnstable[bp] = false;
  
}

