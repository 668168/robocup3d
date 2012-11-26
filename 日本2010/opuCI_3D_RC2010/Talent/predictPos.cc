#include "talent.ih"

std::pair<Vector3D, Vector3D> Talent::predictPos(Vector3D startPos, Vector3D startSpeed, double dt, Vector3D driveForce, double dragFactor, double m)
{
  //  double t = 0;
  Vector3D a;
  Vector3D v;
  Vector3D x;

  double c1 = -dragFactor / m;
  Vector3D c2 = driveForce / -dragFactor;
  
//  v = (v0 + c2) * e ** (c1 * t) - c2;
//  x = 1 / c1 * (v0 + c2) * e ** (c1 * t) - c2 * t + x0 - 1 / c1 * (v0 + c2);
  v = (startSpeed + c2) * exp(c1 * dt) - c2;
  x = (startSpeed + c2) / c1 * exp(c1 * dt) - c2 * dt + startPos - (startSpeed + c2) / c1;
  /*while (t < dt)
  {
    t += 0.01;
    Vector3D Fd = v * -dragFactor;
    a = (Fd + driveForce) / m;
    v += a * 0.01;
    x += v * 0.01;
    
    if (v.length() < 0.001)
      break;
  }*/
  
  return std::pair<Vector3D, Vector3D>(x, v);
}




//Versimpelde delegatie methode, met object id uit worldmodel
std::pair<Vector3D, Vector3D> Talent::predictPos(unsigned objid, double dt, Vector3D driveForce, double dragFactor, double m)
{

  WorldModel &wm = WorldModel::getInstance();
  rf<IDistribution> pos = wm.getPosition(objid);
  rf<IDistribution> speed = wm.getSpeed(objid);
  Vector3D v;
  speed->getMu(v);
  Vector3D x;
  pos->getMu(x);
        

  return predictPos(x, v, dt, driveForce, dragFactor, m);
}
