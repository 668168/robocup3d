#include "simplelocalizer.ih"
#include <iostream>

void SimpleLocalizer::update()
{
	WorldModel& wm = WorldModel::getInstance();
  for (unsigned i = 0; i < Types::NOBJECTS; ++i)
    {
  d_locationsRaw[(Types::Object) i] .init(wm.getObjectPosition((Types::Object) i).getMu(), Matrix9D());
    }

  // Determine field orientation
  Vector3D worldRight = (d_locationsRaw[Types::FLAG1THEM].getMu() - d_locationsRaw[Types::FLAG1US].getMu());
  Vector3D worldForward = (d_locationsRaw[Types::FLAG1US].getMu() - d_locationsRaw[Types::FLAG2US].getMu());
  Vector3D up = worldRight.crossProduct(worldForward);
  
  Vector3D wrNorm = worldRight.normalize();// * wrlInv;
  Vector3D wfNorm = worldForward.normalize();// * wflInv;
  Vector3D uNorm = up.normalize();

  Matrix9D invGlobalTransform = Math::makeTransform(wrNorm, wfNorm, uNorm);
  d_globalTransform = invGlobalTransform.inverse();
  
  Vector3D right = up.crossProduct(Vector3D(1, 0, 0).crossProduct(up)).normalize();
  Vector3D forward = up.crossProduct(Vector3D(0, 1, 0).crossProduct(up)).normalize();
  
  Matrix9D invLocalTransform = Math::makeTransform(right, forward, uNorm);
  d_localTransform = invLocalTransform.inverse();
  
  // Transform all positions into local and global coordinates
  for (unsigned i = 0; i < Types::NOBJECTS; ++i)
  {
    Vector3D local = d_localTransform * (Vector3D)d_locationsRaw[i].getMu();
    d_velocitiesLocal[i].init((local - d_locationsLocal[i].getMu()) / 0.02, Matrix9D());
    d_locationsLocal[i].init(local, Matrix9D());
    
    Vector3D global = d_globalTransform * (Vector3D)d_locationsRaw[i].getMu();
    d_locationsGlobal[i].init(global, Matrix9D());
  }

  Vector3D flag1UsRef(-6.0, 4.0, 0);
  Vector3D flag1UsDif = flag1UsRef - d_locationsGlobal[Types::FLAG1US].getMu();
  
  for (unsigned i = 0; i < Types::NOBJECTS; ++i)
  {
    Vector3D global = d_locationsGlobal[i].getMu() + flag1UsDif;
    d_velocitiesGlobal[i].init((global - d_locationsGlobal[i].getMu()) / 0.02, Matrix9D());
    d_locationsGlobal[i].init(global, Matrix9D());
  }
}

