#include "worldmodel.ih"

bool WorldModel::onMySide()
{
  return (d_fieldNormal.getY() > 0.95 || d_fieldNormal.getY() < -0.95) && d_gyro.length() < 1.0;
}

