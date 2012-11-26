#include "worldmodel.ih"

void WorldModel::updatePosture()
{
  // Torso is identity
  d_bodyPartPositions[Types::TORSO] = Matrix4D();
  
  // Head is just translated
  d_bodyPartPositions[Types::HEAD] = d_bodyPartPositions[Types::TORSO] * Matrix4D::translation(Vector3D(0, 0, 0.295 + 1.410 / 2));

  // Shoulders too
  d_bodyPartPositions[Types::LSHOULDER] = d_bodyPartPositions[Types::TORSO] *
                                          Matrix4D::translation(Vector3D(0, 1.370 / 2 + 0.15 + 445.0 / 2, 1.410 / 2 - 0.536 / 2));
  d_bodyPartPositions[Types::RSHOULDER] = d_bodyPartPositions[Types::TORSO] *
                                          Matrix4D::translation(Vector3D(0, -(1.370 / 2 + 0.15 + 445.0 / 2), 1.410 / 2 - 0.536 / 2));
                                          
  
  
  d_footForceContacts[0] = d_info[iFootLeft];
  d_footForces[0] = d_info[iFootLeft2];
  //_debugLevel4("Force left: " << d_footForceContacts[0] << " " << d_footForces[0]);
  
  d_footForceContacts[1] = d_info[iFootRight];
  d_footForces[1] = d_info[iFootRight2];
  //_debugLevel4("Force right: " << d_footForceContacts[1] << " " << d_footForces[1]);

  _debugLevel4(d_footForces[0].length() << "\t" << d_footForces[1].length() << "\t" << fabs(d_footForces[0].length() - d_footForces[1].length()));
  d_gyro = d_info[iTorsoGyro];
  //_debugLevel4("Gyro: " << d_gyro);
  
  //_debugLevel4("Field normal: " << d_fieldNormal);
}
