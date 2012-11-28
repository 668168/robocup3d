#include "geometry.h"

//#include "iostream"
//using namespace std;

Vector *Vp;


Geometry::Geometry()
{
}

//*******************Class Angle*********************
Angle::Angle()
{
	dAngle=0.0;
}

Angle::Angle(double dAng)
{
	while(dAng>180.0)
		dAng=dAng-360.0;
	while(dAng<-180.0)	
		dAng=360.0+dAng;
	dAngle=dAng;
}

void Angle::ChangeTheAngleIn180(Angle& obj_Ang)
{
	while(obj_Ang.dAngle>180.0)
		obj_Ang.dAngle=obj_Ang.dAngle-360.0;
	while(obj_Ang.dAngle<-180.0)
		obj_Ang.dAngle=360.0+obj_Ang.dAngle;	
}

Angle Angle::operator+(const Angle obj_Ang)
{
      	Angle result;
	result.dAngle=dAngle+obj_Ang.dAngle;
	ChangeTheAngleIn180(result);
	return result;
}

Angle Angle::operator-(const Angle obj_Ang)
{
	Angle result;
	result.dAngle=dAngle-obj_Ang.dAngle;
	ChangeTheAngleIn180(result);
	return result;
}

Angle Angle::operator*(const double dAng)
{
	Angle result;
	result.dAngle=dAngle*dAng;
	ChangeTheAngleIn180(result);
	return result;
}

Angle Angle::operator/(const double dAng)
{
	Angle result;
	result.dAngle=dAngle/dAng;
	ChangeTheAngleIn180(result);
	return result;
}

void  Angle::operator=(Angle obj_Ang)
{
	dAngle=obj_Ang.dAngle;
}

bool  Angle::operator==(const Angle obj_Ang)
{
	return(dAngle==obj_Ang.dAngle);
}

std::ostream& operator<<(std::ostream& out,Angle angle )
{
	out << angle.dAngle;
	return out;
}
double Angle::GetdAngle()
{
	return dAngle;
}

void   Angle::SetdAngle( double dSetValue )
{
	dAngle = dSetValue;
}


//******************Class Polar*******************
Polar::Polar()
{
	Px=Py=Pz=0;
}

Polar::Polar(double x,double y,double z)
{
	Px=x,Py=y,Pz=z;
}

void Polar::SetZero()
{
	Px=Py=Pz=0;
}

void Polar::operator=(const Polar& p)
{
	Px=p.Px,Py=p.Py,Pz=p.Pz;
}

bool Polar::operator==(const Polar& p)
{
	return (Px==p.Px)&&(Py==p.Py)&&(Pz==p.Pz);
}

Polar  Polar::operator+(const Polar& p)
{
	return Polar(Px+p.Px,Py+p.Py,Pz+p.Pz);
}

Polar  Polar::operator-(const Polar& p)
{
	return Polar(Px-p.Px,Py-p.Py,Pz-p.Pz);
}

std::ostream& operator<<(std::ostream& out,Polar p)
{
	out<<'('<<p.Px<<' '<<p.Py<<' '<<p.Pz<<')';
	return out;
}

double Polar::GetPx()
{
	return Px;
}

double Polar::GetPy()
{
	return Py;
}

double Polar::GetPz()
{
	return Pz;
}

void   Polar::SetPx( double dSetValue)
{
	Px = dSetValue;
}

void   Polar::SetPy( double dSetValue)
{
	Angle aAng;
	aAng.dAngle = dSetValue;
	aAng.ChangeTheAngleIn180( aAng );
	Py = aAng.dAngle;
}

void   Polar::SetPz( double dSetValue)
{
	Angle aAng;
	aAng.dAngle = dSetValue;
	aAng.ChangeTheAngleIn180( aAng );
	Pz = aAng.dAngle;
}
//*****************************************

//****************Class Vector***************
Vector::Vector()
{
	Vx=Vy=Vz=0;
}

Vector::Vector(double x,double y,double z)
{
	Vx=x;
	Vy=y;
	Vz=z;
}

void Vector::operator=(const Vector& v)
{
	Vx=v.Vx;
	Vy=v.Vy;
	Vz=v.Vz;
}

bool Vector::operator==(const Vector& v)
{
	return (Vx==v.Vx)&&(Vy==v.Vy)&&(Vz==v.Vz);
}

Vector  Vector::operator+(const Vector& v)
{
	return Vector(Vx+v.Vx, Vy+v.Vy, Vz+v.Vz);
}

Vector  Vector::operator*(const double f)
{
	return Vector(Vx*f, Vy*f, Vz*f);
}

Vector  Vector::operator/(const double f)
{
	return Vector(Vx/f,Vy/f,Vz/f);
}

Vector  Vector::operator-(const Vector& v)
{
	return Vector(Vx-v.Vx,Vy-v.Vy,Vz-v.Vz);
}

double Vector::DotMultiply(const Vector& vector1,const Vector& vector2)
{
	return (vector1.Vx*vector2.Vx+vector1.Vy*vector2.Vy+vector1.Vz*vector2.Vz);
}

bool Vector::IsVectorParallel(Vector vector)
{
	return(((Vy*vector.Vz-Vz*vector.Vy)==0)&&((Vz*vector.Vx-Vx*vector.Vz)==0)&&((Vx*vector.Vy-Vy*vector.Vx)==0));
}

double Vector::GetMod()
{
	return sqrt(square(Vx)+square(Vy)+square(Vz));
}

bool Vector::IsSourceFrontTarget( Vector vSource, Vector vTarget )
{
	return  vSource.GetVx() > vTarget.GetVx();
}
bool Vector::IsSourceBehindTarget( Vector vSource, Vector vTarget )
{
	return  vSource.GetVx() < vTarget.GetVx();
}
bool Vector::IsSourceLeftTarget( Vector vSource, Vector vTarget )
{
	return  vSource.GetVy() > vTarget.GetVy();
}
bool Vector::IsSourceRightTarget( Vector vSource, Vector vTarget )
{
	return vSource.GetVy() < vTarget.GetVy();
}
bool Vector::IsSourceOverTarget( Vector vSource, Vector vTarget )
{
	return vSource.GetVz() > vTarget.GetVz() ;
}
bool Vector::IsSourceBelowTarget( Vector vSource, Vector vTarget )
{
	return vSource.GetVz() < vTarget.GetVz();
}
bool Vector::IsPointBetweenSourceAndTarget( Vector vSource, Vector vTarget, Vector vPoint )//这里只考虑水平面上的点，即Vz=0,对Vz不考虑;
{
	return ((IsSourceFrontTarget( vSource, vPoint ) && IsSourceFrontTarget(vPoint, vTarget ) ) || (IsSourceBehindTarget( vSource, vPoint ) && IsSourceBehindTarget(vPoint, vTarget ) ) ) && ( ( IsSourceLeftTarget( vSource, vPoint ) && IsSourceLeftTarget(vPoint, vTarget ) ) || (IsSourceRightTarget( vSource, vPoint ) && IsSourceRightTarget(vPoint, vTarget ) ) );
}
Vector Vector::GetVerticalVector()
{
	Vector  VerticalVector(0,0,0);
	if(GetMod()==0)return VerticalVector;
	Angle  angle90(90.0);
	Angle  myAngle(GetXYAngle());
	Angle  verticalAngle=angle90+myAngle;
	VerticalVector=Vector(cos(verticalAngle.dAngle*PAI/180.0),sin(verticalAngle.dAngle*PAI/180.0),0.0);
	return  VerticalVector;
}
double Vector::GetXYAngle()
{
//	double test;
 	if(Vx==0.0)
 	{
		if(Vy==0.0)
 			return 0.0;
 		else if(Vy<0.0) return -90.0;
 		else	return 90.0;
 	}
	else if(Vx>0.0)return (atan(Vy/Vx))*180.0/PAI;
 	else
 	{
		if(Vy>0.0)
			return (180.0+(atan(Vy/Vx))*180.0/PAI);
		else if(Vy<0.0)
			return (-180.0+(atan(Vy/Vx))*180.0/PAI);
		else return -180.0;
 	}
}

double Vector::GetZAngle()
{
	double dModule;
	dModule=GetMod();
	if(dModule==0)return 0;
	return (asin(Vz/dModule))*180.0/PAI;
}

void  Vector::SetMod(double mod)
{
	double dModule = GetMod();
	if(mod==0)
	{
		Vx=0;
		Vy=0;
		Vz=0;
	}
       else
	{
		Vx=Vx/dModule*mod;
		Vy=Vy/dModule*mod;
		Vz=Vz/dModule*mod;
	}
}

std::ostream& operator<<(std::ostream& out,Vector &v)
{
         out<<'('<<v.Vx<<' '<<v.Vy<<' '<<v.Vz<<')';
         return out;
}

double Vector::GetVx()
{
	return Vx;
}

double Vector::GetVy()
{
	return Vy;
}

double Vector::GetVz()
{
	return Vz;
}

void   Vector::SetVx( double dSetValue)
{
	Vx = dSetValue;
}

void   Vector::SetVy( double dSetValue)
{
	Vy = dSetValue;
}

void   Vector::SetVz( double dSetValue)
{
	Vz = dSetValue;
}

Vector Vector::TwoPointMakeVector(const Vector sourcePos,const Vector targetPos)
{
        Vector objVector,tmpPoint;
	tmpPoint=targetPos;
	objVector=tmpPoint-sourcePos;
	return objVector;
}

Vector Vector::DistAndDirectionMakeVector(double dDist,double dXYAngle,double dZAngle)
{
	Vector obj_TempVector;
	double dTemp;
	dTemp=dDist*cos(dZAngle*PAI/180.0);
	obj_TempVector.Vx=dTemp*cos(dXYAngle*PAI/180.0);
	obj_TempVector.Vy=dTemp*sin(dXYAngle*PAI/180.0);
	obj_TempVector.Vz=dDist*sin(dZAngle*PAI/180.0);
	return obj_TempVector;	
}



//*******************************************

//******************Class Line*****************
Line::Line()
{
	vPoint=Vector();
	vVector=Vector();
}

Line::Line(Vector V1,Vector V2)
{
	vPoint=V1;
	vVector=V2;
}

Line Line::operator=(Line line)
{
	vPoint=line.vPoint;
	vVector=line.vVector;
}

bool Line::operator==(Line line)
{
	return(vPoint==line.vPoint)&&(vVector==line.vVector);
}

bool Line::IsLineParallel(Line line)
{
	return vVector.IsVectorParallel(line.vVector);
}

std::ostream& operator<<(std::ostream& out,Line &line)
{
         out<<'('<<line.vPoint.Vx<<' '<<line.vPoint.Vy<<' '<<line.vPoint.Vz<<')'<<','<<'('<<line.vVector.Vx<<' '<<line.vVector.Vy<<' '<<line.vVector.Vz<<')';
         return out;
}

Vector Line::GetvVector()
{
	return vVector;
}

Vector Line::GetvPoint()
{
	return vPoint;
}

void   Line::SetvVector( Vector vValue )
{
	vVector = vValue;
}

void   Line::SetvPoint( Vector vValue )
{
	vPoint = vValue;
}
//***********************************************

//*********************Class Circle***************
Circle::Circle()
{
	vCenter = Vector(0, 0, 0);
	dRadius = 0.0;
}

Circle::Circle( Vector vCenterValue, double dRadiusValue )
{
	vCenter = vCenterValue;
	dRadius = dRadiusValue;
}

bool Circle::operator=( Circle cTarget )
{
	vCenter = cTarget.vCenter;
	dRadius = cTarget.dRadius;
}

bool Circle::operator==( Circle cTarget )
{
	return (vCenter == cTarget.vCenter && dRadius == cTarget.dRadius);
}

std::ostream& operator<<(std::ostream& out, Circle &circle)
{
	out << '(' << circle.GetvCenter().GetVx() << ',' << circle.GetvCenter().GetVy() << ',' << circle.GetvCenter().GetVz() << ')' << "  " << circle.GetdRadius();
         return out;
}

//      圆的方程：   (x-k)2 + (y-h)2 = r2, z=0;       a2为a的平方; 
bool   Circle::IsPointInCircle( Vector vPoint, Circle circle )
{
	double k, h, r;
	k = circle.GetvCenter().GetVx();
	h = circle.GetvCenter().GetVy();
	r = circle.GetdRadius();
	if( square(vPoint.GetVx() - k) + square(vPoint.GetVy() - h) < square(r) )
		return true;
	return false;
}
bool   Circle::IsPointOnCircle( Vector vPoint, Circle circle )
{
	double k, h, r;
	k = circle.GetvCenter().GetVx();
	h = circle.GetvCenter().GetVy();
	r = circle.GetdRadius();
	if( square(vPoint.GetVx() - k) + square(vPoint.GetVy() - h) == square(r) )
		return true;
	return false;
}
bool   Circle::IsPointOutOfCircle( Vector vPoint, Circle circle )
{
	return !(IsPointInCircle( vPoint, circle ) && IsPointOnCircle( vPoint, circle ) );
}

int Circle::GetIntersection(Circle circle, Vector &vPoint1, Vector &vPoint2)
{
	double x0, y0, r0, x1, y1, r1;
	x0 = vCenter.Vx;
	y0 = vCenter.Vy;
	r0 = dRadius;
	x1 = circle.vCenter.Vx;
	y1 = circle.vCenter.Vy;
	r1 = circle.dRadius;

	double d, dx, dy, h, a, x, y, p2_x, p2_y;
	dx = x1 - x0;
	dy = y1 - y0;
	d = sqrt(dx*dx + dy*dy);
	dx /= d; dy /= d;

	a = (r0*r0 + d*d - r1*r1) / (2.0 * d);

	double arg = r0*r0 - a*a;
	h = (arg > 0.0) ? sqrt(arg) : 0.0;

	p2_x = x0 + a * dx;
	p2_y = y0 + a * dy;

	x =  p2_x - h * dy;
	y =  p2_y + h * dx;
	vPoint1 = Vector( x, y, 0);
	x =  p2_x + h * dy;
	y =  p2_y - h * dx;
	vPoint2 = Vector( x, y, 0);

	return (arg < 0.0) ? 0 : ((arg == 0.0 ) ? 1 :  2);
}

Vector Circle::GetvCenter()
{
	return vCenter;
}

double Circle::GetdRadius()
{
	return dRadius;
}

void   Circle::SetvCenter( Vector vSetValue )
{
	vCenter = vSetValue;
}

void   Circle::SetdRadius( double dSetValue )
{
	dRadius = dSetValue;
}
//******************************************

//*****************Class Geometry*****************
Vector Geometry::ChangePolarToVector(const Polar obj_Pol)
{
	Vector obj_TempVec;
	double dTemp;
	dTemp=obj_Pol.Px*cos(obj_Pol.Pz*PAI/180.0);
	obj_TempVec.Vx=dTemp*cos(obj_Pol.Py*PAI/180.0);
	obj_TempVec.Vy=dTemp*sin(obj_Pol.Py*PAI/180.0);
	obj_TempVec.Vz=obj_Pol.Px*sin(obj_Pol.Pz*PAI/180.0);
	return obj_TempVec;
}

Polar Geometry::ChangeVectorToPolar(const Vector objVec)
{
	Polar objTempPol;
	Vector Zero;
	objTempPol.Px=GetDistance(objVec, Zero);
	if(objVec.Vx==0.0)
	{
		if(objVec.Vy==0.0)
			objTempPol.Py=0.0;
		else if(objVec.Vy<0.0)
			objTempPol.Py=-90.0;
		else	objTempPol.Py=90.0;
	}
	else if(objVec.Vx>0.0)
		objTempPol.Py=(atan(objVec.Vy/objVec.Vx))*180.0/PAI;
	else
	{
		if(objVec.Vy>0.0)
			objTempPol.Py=180.0+(atan(objVec.Vy/objVec.Vx))*180.0/PAI;
		else	objTempPol.Py=-180.0+(atan(objVec.Vy/objVec.Vx))*180.0/PAI;
	}
	if(objTempPol.Px==0.0)
		objTempPol.Pz=0.0;
	else	objTempPol.Pz=asin(objVec.Vz/objTempPol.Px)*180.0/PAI;
	return objTempPol;	
}


double Geometry::GetDistToPointA(double dDistA, double dDistB, double dDistC, double &dHeight)
{
	double dCosB = (dDistA*dDistA + dDistC*dDistC - dDistB*dDistB)/(2.0*dDistA*dDistC);
	double dAngB = acos(dCosB)*180.0/PAI;
	dHeight = dDistA*sin(dAngB*PAI/180.0);
	return dDistA*dCosB;
}


double Geometry::GetDistance(const Vector sourcePos,const Vector targetPos)
{
	return(sqrt(square(sourcePos.Vx-targetPos.Vx)+square(sourcePos.Vy-targetPos.Vy)+square(sourcePos.Vz-targetPos.Vz)));
}

Line Geometry::MakeLineWithTwoVec(const Vector sourcePos,const Vector targetPos)
{
	Line tempLine;
	Vector objTempVec=targetPos;
	tempLine.vPoint=sourcePos;
	tempLine.vVector=objTempVec-sourcePos;
	return tempLine;
}

Vector Geometry::GetIntersectionPoint(const Line objLine1,const Line objLine2)
{
	Vector objTempPoint;//Vector fits to both point and.vVector
	double x1, y1, z1, m1, n1, p1;
	double x2, y2, z2, m2, n2, p2;
	x1 = objLine1.vPoint.Vx;
	y1 = objLine1.vPoint.Vy;
	z1 = objLine1.vPoint.Vz;
	m1 = objLine1.vVector.Vx;
	n1 = objLine1.vVector.Vy;
	p1 = objLine1.vVector.Vz;
	
	x2 = objLine2.vPoint.Vx;
	y2 = objLine2.vPoint.Vy;
	z2 = objLine2.vPoint.Vz;
	m2 = objLine2.vVector.Vx;
	n2 = objLine2.vVector.Vy;
	p2 = objLine2.vVector.Vz;
	if( ( m2 * n1 - n2 * m1 ) != 0 )
	{
		objTempPoint.Vx = ( m2 * n1 * x1 - n2 * m1 * x2 - m2 * m1 * ( y1 - y2 ) ) / ( m2 * n1 - n2 * m1 );
		objTempPoint.Vy = ( n2 * n1 * ( x1 - x2 ) + m2 * n1 * y2 - n2 * m1 * y1 ) / ( m2 * n1 - n2 * m1 );
		objTempPoint.Vz = 0.0;	//只求水平面上的交点，如果水平面上没有交点，
					//上面的点就是直线在水平面上的投影的交点,故Vz=0; 
	}
	else
	{
		objTempPoint.Vx = 0.0;
		objTempPoint.Vy = 0.0;
		objTempPoint.Vz = 1.0;//Vz==0表示两直线没有交点，就是异面且水平上的投影平行。
		
	}
	return objTempPoint;
}

//      圆的方程：   (x-k)2 + (y-h)2 = r2, z=0;       a2为a的平方; 
//     直线的对称方程：    (x-X)/m = (y-Y)/n, z=0;
//     直线的参数方程：   x=m*t+X; y=n*t+Y; z=0;
// 求交点的方程：(m2+n2)*t2 + 2*[m*(X-k)+n*(Y-h)]*t+(X-k)2 +(Y-h)2 -r2 = 0;
bool  Geometry::GetIntersectionLineToCircle( Line line, Circle circle, Vector & vFirstIntersection, Vector & vSecondIntersection )
{
	double m, n, k, h, X, Y, r, t;
	X = line.GetvPoint().GetVx();
	Y = line.GetvPoint().GetVy();
	m = line.GetvVector().GetVx();
	n = line.GetvVector().GetVy();
	k = circle.GetvCenter().GetVx();
	h = circle.GetvCenter().GetVy();
	r = circle.GetdRadius();

	double dJudge = square( 2*( m * ( X - k ) + n * ( Y - h ) ) ) - 4 * ( square(m) + square(n) ) * ( square( X - k ) + square( Y - h ) - square(r) );
	std::cout << "the dJudge is:   " << dJudge << std::endl;
	if( dJudge < 0 )
		return false;
	else
	{
		t = ( -1.0*2*( m * ( X - k ) + n * ( Y - h ) ) - sqrt( dJudge ) ) / ( 2 * ( square( m ) + square( n ) ) );
		X = m*t + X;
		Y = n*t + Y;
		vFirstIntersection.SetVx( X );
		vFirstIntersection.SetVy( Y );
		vFirstIntersection.SetVz( 0 );

		t = ( -1.0*2*( m * ( X - k ) + n * ( Y - h ) )  + sqrt( dJudge ) ) / ( 2 * ( square( m ) + square( n ) ) );
		X = m*t + X;
		Y = n*t + Y;
		vSecondIntersection.SetVx( X );
		vSecondIntersection.SetVy( Y );
		vSecondIntersection.SetVz( 0 );	
	}
	return true;
}

//      圆的方程：   (x-k)2 + (y-h)2 = r2, z=0;       a2为a的平方;
bool Geometry::GetTangentToCircle( Vector vMarkPoint, Circle circle, Line & lFirstTangentLine, Line & lSecondTangentLine )
{
	//double k, h, r;
	double r;
	Vector vCenter = circle.GetvCenter();
	Vector vVector;
	Line lMarkCenter = MakeLineWithTwoVec( vMarkPoint, vCenter );
	vVector = lMarkCenter.GetvVector();
	std::cout << "the line's vVector is: " << vVector << std::endl;
	Angle aDirectAngle = vVector.GetXYAngle();
	std::cout << "the aDirectAngle is: " << aDirectAngle << std::endl;
	Angle aTangentAngle, aRelativeAngle;
	r = circle.GetdRadius();
	if( circle.IsPointInCircle( vMarkPoint, circle ) )
		return false;
	else if ( circle.IsPointOnCircle( vMarkPoint, circle ) )
	{
		double dMarkCenter = GetDistance( vMarkPoint, vCenter );
		aRelativeAngle.dAngle = asin( r / dMarkCenter ) * 180.0 / PAI;
		vVector = MakeVectorFromVectorAndAngle( vMarkPoint, aRelativeAngle.dAngle );
		lFirstTangentLine.SetvPoint( vMarkPoint );
		lFirstTangentLine.SetvVector( vVector );
		lSecondTangentLine = lFirstTangentLine;
	}
	else
	{
		double dMarkCenter = GetDistance( vMarkPoint, vCenter );
		aRelativeAngle.dAngle = asin( r / dMarkCenter ) * 180.0 / PAI;
		std::cout << "the aRelativeAngle is: " << aRelativeAngle << std::endl;
		lFirstTangentLine = MakeLineFromLineAndAngle( lMarkCenter, aRelativeAngle.dAngle );
		//aTangentAngle = aDirectAngle + aRelativeAngle;
		//std::cout << "the aTangentAngle is: " << aTangentAngle << std::endl;
		//vVector = vMarkPoint.DistAndDirectionMakeVector( 4.0, aTangentAngle.dAngle, 0.0 );
		//vVector = vMarkPoint + vVector;
		//lFirstTangentLine = MakeLineWithTwoVec( vMarkPoint, vVector );
		//vVector = MakeVectorFromVectorAndAngle( vMarkPoint, aRelativeAngle.dAngle );
		//lFirstTangentLine.SetvPoint( vMarkPoint );
		//lFirstTangentLine.SetvVector( vVector );
		
		lSecondTangentLine = MakeLineFromLineAndAngle( lMarkCenter, -1*aRelativeAngle.dAngle );
		//aTangentAngle = aDirectAngle - aRelativeAngle;
		//vVector = vMarkPoint.DistAndDirectionMakeVector( 4.0, aTangentAngle.dAngle, 0.0 );
		//vVector = vMarkPoint + vVector;
		//lSecondTangentLine = MakeLineWithTwoVec( vMarkPoint, vVector );
		//vVector = MakeVectorFromVectorAndAngle( vMarkPoint, -1*aRelativeAngle.dAngle );
		//lSecondTangentLine.SetvPoint( vMarkPoint );
		//lSecondTangentLine.SetvVector( vVector );
	}
	return true;
}

Vector Geometry::GetFootPointToLine(const Vector objVec,const Line objLine)
{
	double dTemp, dRelativeMod, dModule;
	Vector objTempPoint, objTempVector1, objTempVector2;
	objTempVector1 = Vp->TwoPointMakeVector(objLine.vPoint, objVec);
	objTempVector2 = objLine.vVector;
	dTemp = Vp->DotMultiply(objTempVector1, objTempVector2);
	dModule = objTempVector2.GetMod();
	dRelativeMod = dTemp/dModule;
	objTempPoint.Vx = objLine.vPoint.Vx+dRelativeMod*objLine.vVector.Vx/dModule;
	objTempPoint.Vy = objLine.vPoint.Vy+dRelativeMod*objLine.vVector.Vy/dModule;
	objTempPoint.Vz = objLine.vPoint.Vz+dRelativeMod*objLine.vVector.Vz/dModule;
	return objTempPoint;
}

double Geometry::GetProjectionDistance( Vector vPoint1, Vector vPoint2, Vector vPoint3 )
{
	Vector vVector1, vVector2;
	vVector1 = vPoint2 - vPoint1;
	vVector2 = vPoint3 - vPoint1;
	return vPoint1.DotMultiply( vVector1, vVector2 ) / GetDistance( vPoint1, vPoint2 );
}

Vector Geometry::MakeVectorFromVectorAndAngle( Vector vMarkVector, double dMarkAngle )
{
	Vector vNewVector;
	double dDirectAngle = vMarkVector.GetXYAngle() + dMarkAngle;
	double dModule = vMarkVector.GetMod();
	vNewVector = vMarkVector.DistAndDirectionMakeVector( dModule, dDirectAngle, vMarkVector.GetZAngle() );
	//vNewVector = vNewVector + vMarkVector;
	return vNewVector;
}

Line Geometry::MakeLineFromLineAndAngle( Line lMarkLine, double dMarkAngle )
{
	Line lNewLine;
	Vector vNewVector = MakeVectorFromVectorAndAngle( lMarkLine.GetvVector(), dMarkAngle );
	//vNewVector = vNewVector + lMarkLine.GetvPoint();
	//lNewLine = MakeLineWithTwoVec( lMarkLine.GetvPoint(), vNewVector );
	lNewLine.SetvPoint( lMarkLine.GetvPoint() );
	lNewLine.SetvVector( vNewVector );//vNewVector只是方向而已
	return lNewLine;
}

// default oPoint must be FLAG_1l

/*
Polar Geometry::ChangeCalPolar(int iIndex ,Polar p,Vector v)
{double dTemp=p.GetPx()*cos(p.Pz*PAI/180.0);
 double dPointX=0.0;
 double dPointY=0.0;
 Polar pGoal(0,0,0);
 
 switch (iIndex)
    {
       case 1:
                                   dPointX=dTemp*cos((180.0-p.GetPy())*PAI/180.0);
                                   dPointY=senseHandle.FieldWidth-dTemp*sin((180.0-p.GetPy())*PAI/180.0);
                                   break;
       case 2:
                                   dPointX=senseHandle.FieldLength-dTemp*cos(p.GetPy()*PAI/180.0);
                                   dPointY=dTemp*sin(p.GetPy()*PAI/180.0);
                                   break;
       case 3:
                                   dPointX=senseHandle.FieldLength-dTemp*cos(p.GetPy()*PAI/180.0);
                                   dPointY=senseHandle.FieldWidth-dTemp*sin(p.GetPy()*PAI/180.0);
                                   break;
       case 4:
                                   
                                   dPointX=dTemp*cos((p.GetPy()-180.0)*PAI/180.0);
                                   dPointY=senseHandle.FieldWidth/2.0-0.5*senseHandle.GoalWidth+dTemp*sin((p.GetPy()-180.0)*PAI/180.0);
                                   break;
       case 5:
                                   dPointX=dTemp*cos((p.GetPy()-180.0)*PAI/180.0);
                                   dPointY=senseHandle.FieldWidth/2.0+0.5*senseHandle.GoalWidth+dTemp*sin((p.GetPy()-180.0)*PAI/180.0);
                                   break; 
       case 6:
                                   
                                   dPointX=senseHandle.FieldLength-dTemp*cos(p.GetPy()*PAI/180.0);
                                   dPointY=senseHandle.FieldWidth/2.0-0.5*senseHandle.GoalWidth-dTemp*sin(p.GetPy()*PAI/180.0);
                                   break;
       case 7:
                                   
                                   dPointX=senseHandle.FieldLength-dTemp*cos(p.GetPy()*PAI/180.0);
                                   dPointY=senseHandle.FieldWidth/2.0+0.5*senseHandle.GoalWidth-dTemp*sin(p.GetPy()*PAI/180.0);
                                   break;

                                   
    }
    double dPointZ=p.GetPx()*sin(p.GetPz()*PAI/180.0);
    double dPolarX=sqrt(dPointX*dPointX+dPointY*dPointY+dPointZ*dPointZ);
    double dPolarY=2.0*180.0-0.5*180.0-atan(sqrt(dPointX*dPointX)/sqrt(dPointY*dPointY))*180.0/PAI;
    double dPolarZ=atan(dPointZ/sqrt(dPointX*dPointX+dPointY*dPointY))*180.0/PAI;
    Polar pResult(dPolarX,dPolarY,dPolarZ);
    return pResult;
 
}
*/

Polar Geometry::ChangeCalPolarGivePos(Polar pCalPol, Vector vRelPos,Vector vPosGiven)
{
 Vector vCalPos=vRelPos-ChangePolarToVector(pCalPol);
 /*double dDistance=GetDistance (vPosGiven,vCalPos);
 Angle dPolY=0.0;
 if (vPosGiven.GetVx()-vCalPos.GetVx()!=0.0 ) dPolY=Angle(atan((vPosGiven.GetVy()-vCalPos.GetVy())/(vPosGiven.GetVx()-vCalPos.GetVx()))*180.0/PAI);
 else dPolY=vPosGiven.GetVy()>vCalPos.GetVy()? 90.0:270.0;
 Angle dPolZ=Angle(atan(senseHandle.AgentRadius/dDistance)*180.0/PAI);
 double dPolX=sqrt(dDistance*dDistance+senseHandle.AgentRadius*senseHandle.AgentRadius);
 Polar pPol(dPolX,dPolY.GetdAngle(),dPolZ.GetdAngle());
*/
 Vector vTempPos=vPosGiven-vCalPos;
 return ChangeVectorToPolar(vTempPos); 
}



Geometry::~Geometry()
{
}



