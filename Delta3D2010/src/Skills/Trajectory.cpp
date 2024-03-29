/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Trajectory.h"
//#include <zeitgeist/logserver/logserver.h>

#define FLOAT_EPS 1e-05

using namespace std;
using namespace salt;
//using namespace zeitgeist;
//for turn qf and qb =0;
Trajectory::Trajectory()
{
    mModelInit = false;

    mDs3D   = Vector3f(0.0, 0.1, 0.0); /// our walking cycle lenght

    Ds      = Vector2f(mDs3D.x(), mDs3D.y()).Length(); ///a cycle(step) walking(lenght)

    k       =     1;        ///the number of walking cycle

    Tc      =  0.14f;            ///(time of)walking cycle

    Td      =  0.2 * Tc;   ///time of double support phase step

    Tm      =  0.5 * Tc;   ///time of when foot reach the highest point in z axis

   Qgs     =   0.0f;  ///the angle of surface under supported foot(because our ground is surface this attribute is zero

    Qb      =  0.2f;        ///the angle of back foot with ground in t=ts+td(step 2)

    Qf      =  0.2f;        ///the angle of back foot with ground in t=ts+tc(step 4)

    Qge     =  0.0f;   ///the angle of surface under supported foot(because our ground is surface this attribute is zero

    Xed     =  0.5 * Ds ;   ///distance of x axis from hip to ankle for rear foot in ssp

    Xsd     =  0.5 * Ds;   ///distance of x axis from hip to ankle for front foot in dsp

    Lao     =  0.5 * Ds;   ///highest point in x axis

    Hnor    =  0.23f;

    Lan     =  0.035f;        ///the height of foot(from lj5 to lj6)

    Laf     =  0.08f;   ///the lenght between ankle and toe

    Lab     =  0.08f;        ///the lenght between ankle and heel

    Lth     =  0.1201f; ///NAO_A   //0.115f;

    Lsh     =  0.1f;    ///NAO_B

    Hgs     =  0.015f;

    Hge     =  0.015f;

    Hao     =  0.0;//0.10f;  ///foot's highest point in z axis

    Ts      =  1.0f * Tc;  ///time of start phase

    Te      =  1.0f * Tc; ///time of end phase

    mTurnAngle = 0.0f;
    TorsoRot_X = -10.0f;;
    TorsoRelHip_Z = 0.115f;

    FootOffset_X = 0.055f;

    mHoldAnkleMatrix.Identity();
    mMoveAnkleMatrix.Identity();
    mHipMatrix.Identity();
}

Trajectory::~Trajectory()
{
}

Trajectory& Trajectory::instance()
{
    static Trajectory sTrajectory;
    return sTrajectory;
}

void Trajectory::setParams(WalkParams walk)
{
    this->mDs3D[0]  = walk.mDs3D[0];
    this->mDs3D[1]  = walk.mDs3D[1];
    Ds              = Vector2f(mDs3D.x(), mDs3D.y()).Length();
    this->Tc        = walk.Tc;
    this->Td        = walk.Td;
    this->Tm        = walk.Tm;
    this->Xed       = walk.Xed;
    this->Xsd       = walk.Xsd;
    this->Hnor      = walk.Hnor;
    this->Hao       = walk.Hao;
    this->mTurnAngle= walk.TurnAngle;
    Lao             = Ds;
    Ts              = 1.0f * Tc;
    Te              = 1.0f * Tc;
}

void Trajectory::initModelParams(ModelParams model)
{
    this->TorsoRot_X    = model.TorsoRot_X;
    this->TorsoRelHip_Z = model.TorsoRelHip_Z;
    this->FootOffset_X  = model.FootOffset_X;
    if (mModelInit) return ;
    this->Lan       =  model.Lan;
    this->Laf       =  model.Laf;
    this->Lab       =  model.Lab;
    this->Lth       =  model.Lth;
    this->Lsh       =  model.Lsh;
    this->Hgs       =  model.Hgs;
    this->Hge       =  model.Hge;
    mModelInit          = true;
}

///in this comments we assume that the right leg is back(swing foot)
bool Trajectory::general()
{
    float t[5]; ///this array saves 4 step in one walking cycle
    float f[5]; ///this array saves 4 parametr for foot angle with ground

///*********walking steps**********************///
    t[0] = k * Tc;
    t[1] = k * Tc + Td;
    t[2] = (k + 1) * Tc;
    t[3] = (k + 1) * Tc + Td;
///*******************************************///

///*********Foot angles with ground***********///	
    f[0] = Qgs;
    f[1] = -Qb;
    f[2] = Qf;
    f[3] = -Qge;
///******************************************///
    foot_theta.SetBreakPoints(t, f, 4);
    if (! foot_theta.general()) return false;

    t[0] = k * Tc;        ///starting walking
    t[1] = k * Tc + Td; ///double support phase
    t[2] = k * Tc + Tm; ///move swing leg to highest point
    t[3] = (k + 1) * Tc; ///single support phase	
    t[4] = (k + 1) * Tc + Td; ///end walking and start next walking cycle
        ///*********************************************************
        ///****************FOOOOOOOOT TRAJECTORT*****************///
        ///********************************************************

        ///defining Xa(t)         
        ///**the x position for ankle in coordinate***///

    f[0] = k * Ds;        ///at t=kTc

    f[1] = k * Ds + Lan * sin(Qb) + Laf * (1.0f - cos(Qb));        ///at t=kTc+Td

    f[2] = k * Ds + Lao;        ///at t=kTc+Tm

    f[3] = (k + 2) * Ds - Lan * sin(Qf) - Lab * (1.0f - cos(Qf)); ///at t=(k+1)Tc

    f[4] = (k + 2) * Ds;        ///at t=(k+1)Tc+Td

    foot_x.SetBreakPoints(t, f, 5);
    if (! foot_x.general()) return false;
    ///defining Za(t)
    ///**the z position for ankle in coordinate***///

    f[0] = Hgs + Lan;        ///at t=kTc

    f[1] = Hgs + Laf * sin(Qb) + Lan * cos(Qb);        ///at t=kTc+Td

    f[2] = Hao;        ///at t=kTc+Tm

    f[3] = Hge + Lab * sin(Qf) + Lan * cos(Qf);        ///at t=(k+1)Tc

    f[4] = Hge + Lan;        ///at t=(k+1)Tc+Td

    foot_z.SetBreakPoints(t, f, 5);
    if (! foot_z.general()) return false;

    t[0] = k * Tc + 0.5 * Td;
    t[1] = k * Tc + 0.5 * (Tc - Td);
    t[2] = (k + 1) * Tc + 0.5 * Td;

    f[0] = Hnor;
    f[1] = Hnor;
    f[2] = Hnor;

    hip_z.SetBreakPoints(t, f, 3);
    if (! hip_z.general()) return false;

    /** *********************** start phase splines ************/
    t[0] = 0.0f;
    t[1] = Ts;

    f[0] = 0.0f;
    f[1] = Qf;

    foot_start_theta.SetBreakPoints(t, f, 2);
    if (! foot_start_theta.general()) return false;

    t[0] = 0.0f;
    t[1] = Ts;

    f[0] = 0.0f;
    f[1] = Ds - Lan * sin(Qf) - Lab * (1.0f - cos(Qf));

    foot_start_x.SetBreakPoints(t, f, 2);
    if (! foot_start_x.general()) return false;

    t[0] = 0.0f;
    t[1] = Td;
    t[2] = Ts;

    f[0] = Hgs + Lan;
    f[1] = Hgs + Laf * sin(Qb) + Lan * cos(Qb);
    f[2] = Hge + Lab * sin(Qf) + Lan * cos(Qf);

    foot_start_z.SetBreakPoints(t, f, 3);
    if (! foot_start_z.general()) return false;

    t[0] = 0.0f;
    t[1] = Ts;

    f[0] = 0.0f;
    f[1] = Xed;

    hip_start_x.SetBreakPoints(t, f, 2);
    if (! hip_start_x.general()) return false;

    t[0] = 0.0f;
    t[1] = 0.5f * Td;
    t[2] = Ts;

    f[0] = Hnor;
    f[1] = Hnor;
    f[2] = Hnor;

    hip_start_z.SetBreakPoints(t, f, 3);
    if (! hip_start_z.general()) return false;

    /** ***************** end phase *************************/
    t[0] = 0.0f;
    t[1] = Te;

    f[0] = Lan * sin(Qb) + Laf * (1.0f - cos(Qb));
    f[1] = Ds;

    foot_end_x.SetBreakPoints(t, f, 2);
    if (! foot_end_x.general()) return false;

    t[0] = 0.0f;
    t[1] = Te;

    f[0] = Hgs + Laf * sin(Qb) + Lan * cos(Qb);
    f[1] = Hge + Lan;

    foot_end_z.SetBreakPoints(t, f, 2);
    if (! foot_end_z.general()) return false;

    t[0] = 0.0f;
    t[1] = Te;

    f[0] = Ds - Xsd;
    f[1] = Ds;

    hip_end_x.SetBreakPoints(t, f, 2);
    if (! hip_end_x.general()) return false;

    t[0] = 0.0f;
    t[1] = 0.5f * Td;
    t[2] = Te;

    f[0] = Hnor;
    f[1] = Hnor;
    f[2] = Hnor;

    hip_end_z.SetBreakPoints(t, f, 3);
    if (! hip_end_z.general()) return false;

    return true;
}

///return the X of hip
float Trajectory::getHipX(float t, int der) const
{
    /** this should not happen */
    if (t < k * Tc - FLOAT_EPS || t > (k + 1) * Tc + FLOAT_EPS)
    {
        std::cout << "(Trajectory getHipX error)\n";
        return 0.0f;
    }

    float rec = 0.0f;

    float A = k * Tc - t;
    float B = Tc - Td;
    float C = Ds - Xsd;
    float D = Ds + Xed;
    float E = Ds - Xed - Xsd;

    if (t < k * Tc + Td)
    {
        rec = k * Ds + E / (B * Td * Td) *
            ( (Td + A) * (Td + A) * (Td + A) - (-A) * (-A) * (-A) 
              - Td * Td * (Td + A) + Td * Td * (-A) )
            + Xed / Td * (Td + A)
            + C / Td * (-A);
    }
    else
    {
        rec = k * Ds + E / (B * B * Td) *
            ( (-A - Td) * (-A - Td) * (-A - Td) - (Tc + A) * (Tc + A) * (Tc + A) 
              + B * B * (Tc + A) - B * B * (-A - Td)) 
            + C / B * (Tc + A) 
            + D / B * (-A - Td);
    }

    return rec;
}

///return the Z of hip
float Trajectory::getHipZ(float t, int der) const
{
    /** this should not happen */
    if (t < k * Tc + 0.5f * Td - FLOAT_EPS ||
        t > (k + 1) * Tc + 0.5f * Td + FLOAT_EPS)
    {
        std::cout
            << "(Trajectory getHipZ error)\n";
        return 0.0f;
    }

    float rec = 0.0f;

    rec = hip_z.getYGivenX(t, der);

    return rec;
}

///return theta for hip
float Trajectory::getHipTheta(float t, int der) const
{
    float rec = 0.0f;

    if (der == 0)
    {
        rec = M_PI / 2;
    }
    else if (der >= 1)
    {
        rec = 0.0f;
    }
    else
    {
        std::cout
            << "(Trajectory getHipTheta der error)\n";
    }

    return rec;
}

///return the X coordinate for ankle(foot)
float Trajectory::getFootX(float t, int der) const
{
    /** this should not happen */
    if (t < k * Tc - FLOAT_EPS || t > (k + 2) * Tc + FLOAT_EPS)
    {
        std::cout
            << "(Trajectory) getFootX error\n";
        return 0.0f;
    }

    float rec = 0.0f;

    if (t < (k + 1) * Tc + Td)
    {
        rec = foot_x.getYGivenX(t, der);
    }
    else
    {
        if (der == 0)
        {
            rec = (k + 2) * Ds;
        }
        else if (der >= 1)
        {
            rec = 0.0f;
        }
        else
        {
            std::cout
                << "(Trajectory getFootX der error)\n";
        }
    }

    return rec;
}

///return the Z coordinatte for ankle(foot)
float Trajectory::getFootZ(float t, int der) const
{
    /** this should not happen */
    if (t < k * Tc - FLOAT_EPS || t > (k + 2) * Tc + FLOAT_EPS)
    {
        std::cout
            << "(Trajectory) getFootZ error\n";
        return 0.0f;
    }

    float rec = 0.0f;

    if (t < (k + 1) * Tc + Td)
    {
        rec = foot_z.getYGivenX(t, der);
    }
    else
    {
        if (der == 0)
        {
            rec = Hge + Lan;
        }
        else if (der >= 1)
        {
            rec = 0.0f;
        }
        else
        {
            std::cout
                << "(Trajectory getFootZ der error)\n";
        }
    }

    return rec;
}

///return the theta of ankle(foot)
float Trajectory::getFootTheta(float t, int der) const
{
    /** this should not happen */
    if (t < k * Tc - FLOAT_EPS || t > (k + 2) * Tc + FLOAT_EPS) return 0.0f;

    float rec = 0.0f;

    if (t < (k + 1) * Tc + Td)
    {
        rec = foot_theta.getYGivenX(t, der);
    }
    else
    {
        if (der == 0)
        {
            rec = -Qge;
        }
        else if (der >= 1)
        {
            rec = 0.0f;
        }
        else
        {
            std::cout
                << "(Trajectory getFootTheta der error)\n";
        }
    }

    return rec;
}


void Trajectory::calTrajectoryMatrix(float t)
{
    if (t < k * Tc - FLOAT_EPS || t > (k + 2) * Tc + FLOAT_EPS)
    {
        std::cout
            << "Trajectory calTrajectoryMatrix error\n";
    }

    Vector3f hip_pos, holdankle_pos, moveankle_pos;
    float hx, hz, fx1, fz1, fx2, fz2, ft1, ft2;

    if (t < (k + 1) * Tc)
    {
        hx = getHipX(t);
    }
    else
    {
        hx = getHipX(t - Tc) + Ds;
    }

    if (t < k * Tc + 0.5 * Td)
    {
        hz = getHipZ(t + Tc);
    }
    else if ( t < (k + 1) * Tc + 0.5 * Td)
    {
        hz = getHipZ(t);
    }
    else
    {
        hz = getHipZ(t - Tc);
    }

    if (t < (k + 1) * Tc + Td)
    {
        fx1 = getFootX(t);
        ft1 = getFootTheta(t);
        fz1 = getFootZ(t);
    }
    else
    {
        fx1 = (k + 2) * Ds;
        ft1 = -Qge;
        fz1 = Hge + Lan;
    }

    if (t < k * Tc + Td)
    {
        fx2 = getFootX(t + Tc) - Ds;
        ft2 = getFootTheta(t + Tc);
        fz2 = getFootZ(t + Tc);
    }
    else if (t < (k + 1) * Tc )
    {
        fx2 = getFootX(t + Tc) - Ds;
        ft2 = getFootTheta(t + Tc);
        fz2 = getFootZ(t + Tc);
    }
    else
    {
        fx2 = getFootX(t - Tc) + Ds;
        ft2 = getFootTheta(t - Tc);
        fz2 = getFootZ(t - Tc);
    }

    hip_pos = hx / Ds * mDs3D;
    hip_pos[2] = hz;
    mHipMatrix.Pos() = hip_pos;

    holdankle_pos = fx2 / Ds * mDs3D;
    holdankle_pos[2] = fz2;
    mHoldAnkleMatrix.Pos() = holdankle_pos;

    moveankle_pos = fx1 / Ds * mDs3D;
    moveankle_pos[2] = fz1;
    mMoveAnkleMatrix.Pos() = moveankle_pos;
}

bool Trajectory::getTrajectoryMatrix(float t,
                                     salt::Matrix& torso,
                                     salt::Matrix& holdfoot,
                                     salt::Matrix& movefoot,
                                     bool lefthold
                                    )
{
    if (t < k * Tc - FLOAT_EPS || t > (k + 2) * Tc + FLOAT_EPS)
    {
        std::cout
            << "Trajectory getTrajectoryMatrix error\n";
        return false;
    }

    calTrajectoryMatrix(t);
    calWalkTrajectoryMatrix(lefthold);
    torso = mTorsoMatrix;
    movefoot = mMoveFootMatrix;
    holdfoot = mHoldFootMatrix;

    /** turn in normal step (not used in start or end phase)
     *  hold foot matrix should not be rotated.
     */
    //torso.RotateZ(gDegToRad(mTurnAngle));
    //movefoot.RotateZ(gDegToRad(mTurnAngle));
    holdfoot.RotateZ(gDegToRad(mTurnAngle));
    return true;
}

void Trajectory::calStartTrajectoryMatrix(float t)
{
    if (t < 0.0f - FLOAT_EPS || t > Ts + FLOAT_EPS)
    {
        std::cout
            << "Trajectory calStartTrajectoryMatrix error\n";
        return ;
    }

    Vector3f hip_pos, holdankle_pos, moveankle_pos;
    float hx, hz, fx1, fz1, fx2, fz2;

    hx = hip_start_x.getYGivenX(t);
    hz = hip_start_z.getYGivenX(t);
    fx1 = 0.0f;
    fz1 = Hge + Lan;
    fx2 = foot_start_x.getYGivenX(t);
    fz2 = foot_start_z.getYGivenX(t);

    hip_pos = hx / Ds * mDs3D;
    hip_pos[2] = hz;
    mHipMatrix.Pos() = hip_pos;

    holdankle_pos = fx1 / Ds * mDs3D;
    holdankle_pos[2] = fz1;
    mHoldAnkleMatrix.Pos() = holdankle_pos;

    moveankle_pos = fx2 / Ds * mDs3D;
    moveankle_pos[2] = fz2;
    mMoveAnkleMatrix.Pos() = moveankle_pos;
}

bool Trajectory::getStartTrajectoryMatrix(float t,
                                          salt::Matrix& torso,
                                          salt::Matrix& holdfoot,
                                          salt::Matrix& movefoot,
                                          bool lefthold
                                         )
{
    if (t < 0.0f - FLOAT_EPS || t > Ts + FLOAT_EPS)
    {
        std::cout
            << "Trajectory getStartTrajectoryMatrix error\n";
        return false;
    }

    calStartTrajectoryMatrix(t);
    calWalkTrajectoryMatrix(lefthold);
    torso = mTorsoMatrix;
    movefoot = mMoveFootMatrix;
    holdfoot = mHoldFootMatrix;

    return true;
}

void Trajectory::calEndTrajectoryMatrix(float t)
{
    if (t < 0.0f - FLOAT_EPS || t > Te + FLOAT_EPS)
    {
        std::cout
            << "Trajectory calEndTrajectoryMatrix error\n";
        return ;
    }

    Vector3f hip_pos, holdankle_pos, moveankle_pos;
    float hx, hz, fx1, fz1, fx2, fz2;

    hx = hip_end_x.getYGivenX(t);
    hz = hip_end_z.getYGivenX(t);
    fx1 = Ds;
    fz1 = Hge + Lan;
    fx2 = foot_end_x.getYGivenX(t);
    fz2 = foot_end_z.getYGivenX(t);

    hip_pos = hx / Ds * mDs3D;
    hip_pos[2] = hz;
    mHipMatrix.Pos() = hip_pos;

    holdankle_pos = fx1 / Ds * mDs3D;
    holdankle_pos[2] = fz1;
    mHoldAnkleMatrix.Pos() = holdankle_pos;

    moveankle_pos = fx2 / Ds * mDs3D;
    moveankle_pos[2] = fz2;
    mMoveAnkleMatrix.Pos() = moveankle_pos;
}

bool Trajectory::getEndTrajectoryMatrix(float t,
                                        salt::Matrix& torso,
                                        salt::Matrix& holdfoot,
                                        salt::Matrix& movefoot,
                                        bool lefthold
                                       )
{
    if (t < 0.0f - FLOAT_EPS || t > Te + FLOAT_EPS)
    {
        std::cout
            << "Trajectory getEndTrajectoryMatrix error\n";
        return false;
    }

    calEndTrajectoryMatrix(t);
    calWalkTrajectoryMatrix(lefthold);
    torso = mTorsoMatrix;
    movefoot = mMoveFootMatrix;
    holdfoot = mHoldFootMatrix;

    return true;
}

/** the comment code: should the offset both
 * in axis 'x' and 'y' be considered ?
 */
void Trajectory::calWalkTrajectoryMatrix(bool lefthold)
{
    mTorsoMatrix                = mHipMatrix;
    // mTorsoMatrix.Pos()[1]      += 0.01f;
    mTorsoMatrix.Pos()[2]      += TorsoRelHip_Z;
    mTorsoMatrix.RotateX(gDegToRad(TorsoRot_X));

    mHoldFootMatrix             = mHoldAnkleMatrix;
    float offset = lefthold ? FootOffset_X : -FootOffset_X;
    mHoldFootMatrix.Pos()[0]   -= offset;
    //mHoldFootMatrix.Pos()[1]   += 0.005f;// - 0.03f;
    mHoldFootMatrix.Pos()[2]   -= Lan;

    mMoveFootMatrix             = mMoveAnkleMatrix;
    mMoveFootMatrix.Pos()[0]   += offset;
    //mMoveFootMatrix.Pos()[1]   += 0.005f;// - 0.03f;
    mMoveFootMatrix.Pos()[2]   -= Lan;
}