#ifndef MSPACEGEOMETRY_H
#define MSPACEGEOMETRY_H
#include <iostream>
#include <cmath>
#define PAI 3.1415926

/**
this class is used for geometry computation.
*/

class Angle
{
public:
   	Angle();
   	Angle(double dAng);
   	void ChangeTheAngleIn180(Angle& obj_Ang);
   	Angle operator+(const Angle obj_Ang);
   	Angle operator-(const Angle obj_Ang);
   	Angle operator*(const double dAng);
   	Angle operator/(const double dAng);
   	void  operator=(Angle obj_Ang);
   	bool  operator==(const Angle obj_Ang);
	friend  std::ostream& operator<<(std::ostream& out,Angle angle );
 	double GetdAngle();
	void   SetdAngle( double dSetValue );
	double dAngle;
};

class  Polar
{
public:
	Polar();
	Polar(double x,double y,double z);
	void operator=(const Polar& p);
	bool operator==(const Polar& p);
	Polar  operator+(const Polar& p);
	Polar  operator-(const Polar& p);
	friend  std::ostream& operator<<(std::ostream& out,Polar p);
	double GetPx();
	double GetPy();
	double GetPz();
	void   SetPx( double dSetValue);
	void   SetPy( double dSetValue);
	void   SetPz( double dSetValue);
	void SetZero();
	
     double Px;
     double Py;
     double Pz;
     //~Polar();
};

class  Vector
{
public:
     	Vector();
     	Vector(double x,double y,double z);
     	void operator=(const Vector& v);
     	bool operator==(const Vector& v);
     	Vector  operator+(const Vector& v);
	Vector  operator*(const double f);
	Vector  operator/(const double f);
     	Vector  operator-(const Vector& v);
	double DotMultiply(const Vector& vector1,const Vector& vector2);
	bool IsVectorParallel(Vector vector);
	double GetMod();
	Vector GetVerticalVector();
	double GetXYAngle();
	double GetZAngle();
	bool IsSourceFrontTarget( Vector vSource, Vector vTarget );
	bool IsSourceBehindTarget( Vector vSource, Vector vTarget );
	bool IsSourceLeftTarget( Vector vSource, Vector vTarget );
	bool IsSourceRightTarget( Vector vSource, Vector vTarget );
	bool IsSourceOverTarget( Vector vSource, Vector vTarget );
	bool IsSourceBelowTarget( Vector vSource, Vector vTarget );
	bool IsPointBetweenSourceAndTarget( Vector vSource, Vector vTarget, Vector vPoint );
	void  SetMod(double mod);
	Vector TwoPointMakeVector(const Vector sourcePos,const Vector targetPos);
	Vector DistAndDirectionMakeVector(double dDist,double dXYAngle,double dZAngle);
     	friend  std::ostream& operator<<(std::ostream& out,Vector &v);

	double GetVx();
	double GetVy();
	double GetVz();
	void   SetVx( double dSetValue);
	void   SetVy( double dSetValue);
	void   SetVz( double dSetValue);

     	double Vx;
     	double Vy;
     	double Vz;
private:
	double square(double x){return x*x;}
};



class Line
{
public:
  	Line();
  	Line(Vector V1,Vector V2);
	Line operator=(Line line);
	bool operator==(Line line);
	bool IsLineParallel(Line line);
	friend  std::ostream& operator<<(std::ostream& out,Line &line);
	Vector GetvVector();
	Vector GetvPoint();
	void   SetvVector( Vector vValue );
	void   SetvPoint( Vector vValue );
	
	Vector vVector;
	Vector vPoint;
};

class Circle
{
public:
	Circle();
	Circle( Vector vCenterValue, double dRadiusValue );
	bool operator=( Circle cTarget );
	bool operator==( Circle cTarget );
	friend  std::ostream& operator<<(std::ostream& out,Circle &circle);
	bool   IsPointInCircle( Vector vPoint, Circle circle );
	bool   IsPointOnCircle( Vector vPoint, Circle circle );
	bool   IsPointOutOfCircle( Vector vPoint, Circle circle );
	int GetIntersection(Circle circle, Vector &vPoint1, Vector &vPoint2);
	Vector GetvCenter();
	double GetdRadius();
	void   SetvCenter( Vector vSetValue );
	void   SetdRadius( double dSetValue );

private:
	Vector vCenter;
	double dRadius;
	double square(double x){return x*x;}
};
class Geometry{
public:
    Geometry();
    Vector ChangePolarToVector(const Polar p);
    Polar  ChangeVectorToPolar(const Vector v);
   

    double GetDistToPointA(double dDistA, double dDistB, double dDistC, double &dHeight);


    double GetDistance(const Vector sourcePos, const Vector vTargetPos);
    Line  MakeLineWithTwoVec(const Vector sourcePos,const Vector vTargetPos);
    Vector   GetIntersectionPoint(const Line line1,const Line line2);
    Vector  GetFootPointToLine(const Vector v,const Line line);
    bool  GetIntersectionLineToCircle( Line line, Circle circle, Vector & vFirstIntersection, Vector & vSecondIntersection );
    bool GetTangentToCircle( Vector vMarkPoint, Circle circle, Line & lFirstTangentLine, Line & lSecondTangentLine );
    double GetProjectionDistance( Vector vPoint1, Vector vPoint2, Vector vPoint3 );
    Polar ChangeCalPolarGivePos(Polar pCalPol,Vector vRelPos ,Vector vPosGiven) ;
    Vector MakeVectorFromVectorAndAngle( Vector vMarkVector, double dMarkAngle );
    Line MakeLineFromLineAndAngle( Line lMarkLine, double dMarkAngle );
    ~Geometry();



private:
	double square(double x){return x*x;}

};



#endif
