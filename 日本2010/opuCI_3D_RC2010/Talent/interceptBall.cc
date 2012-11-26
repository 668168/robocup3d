#include "talent.ih"

Vector3D Talent::interceptBall(Vector3D targetPos, Vector3D targetSpeed, Vector3D ownPos, Vector3D ownSpeed)
{
  /*if (!(targetSpeed.length() < 20 && ownSpeed.length() < 20)
    return Vector3D();*/
  
  _debugLevel3("Intercept all: " << WorldModel::getInstance().getTime() << std::endl <<
               " " << targetPos << std::endl <<
               " " << targetSpeed);
  Vector3D ta(0, 0, 0);
  double oa = 0;
  Vector3D tv = targetSpeed;
  double ov = 0;
  Vector3D tx = targetPos;
  double ox = 0;
  Vector3D ownAccel(0, 0, 0);
  
  double driveForce = 100 * POWERFACTOR;
  double ownDragFactor = 12;
  double targetDragFactor = 0.3;
  double ownMass = WorldModel::getInstance().getAgentProperty("mass");
  double targetMass = WorldModel::getInstance().getBallProperty("mass");
  
  double t = 0;
  while (t < 5)
  {
    t += 0.01;
    
    // Calculate position from old speed
    Vector3D Fdo = ownSpeed * -ownDragFactor;
    ownAccel = Fdo / ownMass;
    ownSpeed += ownAccel;
    if (ownSpeed.length() > 10.0)
      ownSpeed = ownSpeed / ownSpeed.length() * 10.0;
    ownPos += ownSpeed * 0.01;
    
    // Calculate radius of obtainable locations
    double oF = driveForce + ov * -ownDragFactor;
    oa = oF / ownMass;
    ov += oa * 0.01;
    ox += ov * 0.01;
    
    // Calculate ball position
    Vector3D tF = tv * targetDragFactor;
    ta = tF / targetMass;
    tv += ta * 0.01;
    tx += tv * 0.01;
    
    // Break if ball is within that radius
    double dist = (tx - ownPos).length();
    if (dist < ox)
      break;
    
  }

  return tx;
}
