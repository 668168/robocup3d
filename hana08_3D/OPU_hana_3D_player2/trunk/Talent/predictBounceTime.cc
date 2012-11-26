#include "talent.ih"

double Talent::predictBounceTime(Vector3D startPos, Vector3D startSpeed, double dragFactor, double m)
{
  double z = startPos[2];
  double v = startSpeed[2];
  
  double t = 0;
  
  while (z > 0.15)
  {
    t += 0.01;
    double Fd = v * -dragFactor;
    double Fz = -9.81 * m;
    double a = (Fd + Fz) / m;
    v += a * 0.01;
    z += v * 0.01;
    
  }
  
  return t;
}

Vector3D Talent::predictBouncePos(Vector3D startPos, Vector3D startSpeed, double dragFactor, double m)
{
  double t = predictBounceTime(startPos, startSpeed, dragFactor, m);
  pair<Vector3D, Vector3D> xv = predictPos(startPos, startSpeed, t, Vector3D(), dragFactor, m);
  return xv.first;
}
