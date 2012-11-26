#include "simplelocalizer.ih"

SimpleLocalizer::SimpleLocalizer()
{
  for (unsigned i = 0; i < Types::NOBJECTS; ++i)
  {
    d_locationsRaw[i].init(Vector3D(0.0, 0.0, 0.0), Matrix9D());
    d_locationsLocal[i].init(Vector3D(0.0, 0.0, 0.0), Matrix9D());
    d_locationsGlobal[i].init(Vector3D(0.0, 0.0, 0.0), Matrix9D());

    d_velocitiesLocal[i].init(Vector3D(0.0, 0.0, 0.0), Matrix9D());
    d_velocitiesGlobal[i].init(Vector3D(0.0, 0.0, 0.0), Matrix9D());
/*
    d_locationsRaw[i] = new NormalDistribution3D();
    d_locationsLocal[i] = new NormalDistribution3D();
    d_locationsGlobal[i] = new NormalDistribution3D();

    d_velocitiesLocal[i] = new NormalDistribution3D();
    d_velocitiesGlobal[i] = new NormalDistribution3D();
 */  }
}

