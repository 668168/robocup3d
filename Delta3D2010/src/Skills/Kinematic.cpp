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


#include "Kinematic.h"

#include "../Math/Geometry.h"
#include <cstdio>


using namespace salt;
using namespace boost;

Kinematic::Kinematic()
{
///me
    uLINK.reset(new Link[JID_MAX + 1]);
    mRobotPartInfo.reset(new RobotPartInfo[PART_MAX + 1]);
    mIKJointAngle.reset(new float[JID_MAX + 1]);
    mIKJointVel.reset(new float[JID_MAX + 1]);
///me
///nao
/** these two values must be in constructor */
    JID_MIN             = JID_ROOT;
    JID_MAX             = JID_RLEG_6;
    PART_MIN            = JID_ROOT;
    PART_MAX            = JID_RLEG_6;

    FootLength          = 0.08;
    FootWidth           = 0.16;
    FootHeight          = 0.03;
    FootMass            = 0.2;

    ShankLength         = 0.08;
    ShankWidth          = 0.07;
    ShankHeight         = 0.11;
    ShankMass           = 0.225;

    ThighLength         = 0.07;
    ThighWidth          = 0.07;
    ThighHeight         = 0.14;
    ThighMass           = 0.275;

    TorsoLength         = 0.1;
    TorsoWidth          = 0.1;
    TorsoHeight         = 0.18;
    TorsoMass           = 1.2171;

///************************************TRANSLATION****************************************///


	///first initialize torso
    TorsoInitX          = 0.0f;
    TorsoInitY          = 0.0f;
    TorsoInitZ          = 0.385;
	
    
    /// the relative offset of hip1 to his parent(torso)
    Hip1RelTorso_X      = 0.055; 
    Hip1RelTorso_Y      = -0.01;
    Hip1RelTorso_Z      = -0.115;

    /// the relative offset of hip2 to his parent(hip1)
    Hip2RelHip1_X       = 0;
    Hip2RelHip1_Y       = 0;
    Hip2RelHip1_Z       = 0;

    /// the relative offset of thigh to his parent(hip2)
    ThighRelHip2_X      = 0;
    ThighRelHip2_Y      = 0.01;  //set 0.005 to check the tri-angle algorithm
    ThighRelHip2_Z      = -0.04;

    /// the relative offset of shank to his parent(thigh)
    ShankRelThigh_X     = 0;
    ShankRelThigh_Y     = 0.005;
    ShankRelThigh_Z     = -0.125;

    /// the relative offset of ankle to his parent(shank)
    AnkleRelShank_X     = 0;
    AnkleRelShank_Y     = -0.01;
    AnkleRelShank_Z     = -0.055;

    /// the relative offset of foot to his parent(ankle)
    FootRelAnkle_X      = 0;
    FootRelAnkle_Y      = 0.03;
    FootRelAnkle_Z      = -0.035;
    
    ///the axis of hip1 relative on his body that installed on	
    Hip1Axis_X          = -0.7071;
    Hip1Axis_Y          = 0;
    Hip1Axis_Z          = 0.7071;
///nao

}

Kinematic::~Kinematic()
{
}


Kinematic& Kinematic::instance()
{
   static Kinematic sKinematic;
   return sKinematic;
}



bool Kinematic::init()
{
    uLINK.reset(new Link[JID_MAX + 1]);
    mRobotPartInfo.reset(new RobotPartInfo[PART_MAX + 1]);
    mIKJointAngle.reset(new float[JID_MAX + 1]);
    mIKJointVel.reset(new float[JID_MAX + 1]);

    setupLinks(); // must before 'setupJointIDMap'
    setupRobotPartInfo();
    setupJointIDMap();
    std::cout <<"kinematic init ok"<<std::endl;
    return true;
}

void Kinematic::setupJointIDMap()
{
    mJointIDMap.clear();
    for (int i = JID_MIN; i <= JID_MAX; ++i)
        mJointIDMap[uLINK[i].name] = i;
}

void Kinematic::updateLink(const salt::Matrix& mat)
{
    /** update root */
    uLINK[JID_ROOT].R = mat;
    uLINK[JID_ROOT].p = mat.Pos();

    /** update joint angles */
    for (int i = getJointMin(); i <= getJointMax(); ++i)
    {
        if (i == JID_ROOT) continue;
        /** NOTE if the link is the top one or not been
         * set up correctly, it will not be updated */
        // if (uLINK[i].mother == 0) continue;
            uLINK[i].q = gDegToRad(mHingeJointSenseMap[i].angle);
    }

    /** update links */
    forwardKinematics(JID_ROOT);

    /** update robot part information */
    for (RobotPart part = getRobotPartMin();
         part <= getRobotPartMax();
         ++part)
    {
        mRobotPartInfo[part].p = uLINK[part].p +
                                 uLINK[part].R.Rotate(uLINK[part].c);
        mRobotPartInfo[part].R = uLINK[part].R;

        // NOTE (for old code)
        mRobotPartInfo[part].R.Pos() = mRobotPartInfo[part].p;
    }
//     for (int i = getJointMin(); i <= getJointMax(); ++i)
//     {
//            std::cout<< "link"<<i<<": "<<uLINK[i].q <<",";
//     }
//     std::cout<<std::endl;
}

shared_array<Kinematic::Link> Kinematic::getLink() const
{
    return uLINK;
}

shared_array<Kinematic::RobotPartInfo> Kinematic::getRobotPartInfo() const
{
    return mRobotPartInfo;
}

boost::shared_array<float> Kinematic::getIKJointAngle() const
{
    return mIKJointAngle;
}

boost::shared_array<float> Kinematic::getIKJointVel() const
{
    return mIKJointVel;
}

Matrix Kinematic::getRobotPartMatrix(RobotPart part) const
{
    if (part < PART_MIN || part > PART_MAX)
    {
        std::cout
            << "(Kinematic) ERROR: (getRobotPartMatrix) part unknown\n";
        return Matrix();
    }

    return mRobotPartInfo[part].R;
}

Vector3f Kinematic::getRobotPartPos(RobotPart part) const
{
    if (part < PART_MIN || part > PART_MAX)
    {
        std::cout
            << "(Kinematic) ERROR: (getRobotPartPos) part unknown\n";
        return Vector3f();
    }

    return mRobotPartInfo[part].p;
}

void Kinematic::printLink(int j)
{
    if (j != 0)
    {
        printf("j = %d : %s, %.3f\n", j, uLINK[j].name.c_str(), gRadToDeg(uLINK[j].q));
        // std::cout << "j = " << j << " : " << uLINK[j].name << ", "
        //      << gRadToDeg(uLINK[j].q) << std::endl;
        printLink(uLINK[j].child);
        printLink(uLINK[j].sister);
    }
}

Kinematic::TIndex Kinematic::findRoute(int to)
{
    Kinematic::TIndex idx;
    int i = uLINK[to].mother;

    if (i == 0)
    {
        // this should not happen
        assert(false);
    }
    else if (i == 1)
    {
        idx.push_back(to);
    }
    else
    {
        idx = findRoute(i);
        idx.push_back(to);
    }

    return idx;
}

void Kinematic::forwardKinematics(int j)
{
    if (j == 0) return ;
    if (j != 1)
    {
        int i = uLINK[j].mother;
        uLINK[j].p = uLINK[i].R.Rotate(uLINK[j].b) + uLINK[i].p;
        uLINK[j].R = uLINK[i].R * Rodrigues(uLINK[j].a, uLINK[j].q);
    }
    forwardKinematics(uLINK[j].child);
    forwardKinematics(uLINK[j].sister);
}

void Kinematic::forwardVelocity(int j)
{
    if (j == 0) return ;
    if (j != 1)
    {
        int i = uLINK[j].mother;
        uLINK[j].v = uLINK[i].v + uLINK[i].w.Cross(uLINK[i].R.Rotate(uLINK[j].b));
        uLINK[j].w = uLINK[i].w + uLINK[i].R.Rotate(uLINK[j].a * uLINK[j].dq);
    }
    forwardVelocity(uLINK[j].child);
    forwardVelocity(uLINK[j].sister);
}

bool Kinematic::inverseKinematics(int to, const salt::Matrix& target)
{
    bool rec = true;
    const float lambda = 0.5f;
    TIndex idx = findRoute(to);
    int jsize = idx.size();

    float err[6];
    float* dq = new float[jsize];

    // allot memory for Jacobian matrix
    float** J = new float*[6];
    for (int i = 0; i < 6; ++i)
    {
        J[i] = new float[jsize];
    }

    int n;
    for (n = 1; n <= 30; ++n)
    {
        calcJacobian(J, idx);
        Matrix m = uLINK[to].R;
        m.Pos() = uLINK[to].p;
        calcVWerr(err, target, m);

        float l = 0.0f;
        for (int i = 0; i < 6; ++i)
        {
            l += err[i] * err[i];
        }
        if (gSqrt(l) < 1e-3)
            break ;

        // solve J * dq = err
        // solve(dq, J, err, 6, jsize);
        if (! solve(dq, (const float **)J, (const float *)err, 6, jsize))
        {
            rec = false;
            goto over;
        }

#ifdef DEBUG
        printf("n = %d\n", n);
        printf("err: ");
        for (int i = 0; i < 6; ++i)
            printf("%.3f ", gRadToDeg(err[i]));
        printf("\n");
        printf("dq: ");
#endif
        for (int i = 0; i < jsize; ++i)
        {
            dq[i] *= lambda;
#ifdef DEBUG
            printf("%.3f ", gRadToDeg(dq[i]));
#endif
        }
#ifdef DEBUG
        printf("\n");
        printf("q: ");
#endif
        for (int nn = 0; nn < jsize; ++nn)
        {
            int j = idx.at(nn);
            uLINK[j].q += dq[nn];
            uLINK[j].q = gNormalizeRad(uLINK[j].q);
#ifdef DEBUG
            printf("%.3f ", gRadToDeg(uLINK[j].q));
#endif
        }
#ifdef DEBUG
        printf("\n");
        printf("J:\n");
        for (int i = 0; i < 6; ++i)
        {
            for (int j = 0; j < jsize; ++j)
                printf("%.3f ", J[i][j]);
            printf("\n");
        }
        printf("\n");
#endif
        forwardKinematics(1);
    }
#ifdef DEBUG
    printf("n = %d\n", n);
#endif

over:
    for (int i = 0; i < 6; ++i)
    {
        delete [] J[i];
        J[i] = NULL;
    }
    delete [] J;
    delete [] dq;
    J = NULL;
    dq = NULL;

    return rec;
}

void Kinematic::calcJacobian(float** J, const TIndex& idx)
{
    int jsize = idx.size();
    Vector3f target = uLINK[idx.at(jsize - 1)].p;

    for (int n = 0; n < jsize; ++n)
    {
        int j = idx.at(n);
        Vector3f a = uLINK[j].R * uLINK[j].a;
        Vector3f c = a.Cross(target - uLINK[j].p);
        J[0][n] = c.x();
        J[1][n] = c.y();
        J[2][n] = c.z();
        J[3][n] = a.x();
        J[4][n] = a.y();
        J[5][n] = a.z();
    }
}

void Kinematic::calcVWerr(float err[6], const salt::Matrix& ref, const salt::Matrix& now)
{
    Vector3f perr = ref.Pos() - now.Pos();
    Matrix invNow = now;
    invNow.InvertRotationMatrix();
    // if (! InverseMatrix(invNow)) std::cout << "inverse matrix failed!" << std::endl;
    Matrix Rerr = invNow * ref;
    Vector3f werr = now.Rotate(RotToOmega(Rerr));
    err[0] = perr[0];
    err[1] = perr[1];
    err[2] = perr[2];
    err[3] = werr[0];
    err[4] = werr[1];
    err[5] = werr[2];
}

bool Kinematic::solve(float* X, const float** A, const float* B, int row, int column)
{
    return svd(X, A, B, row, column);
}


void Kinematic::setupLinks()
{
	///initialing root node
    uLINK[JID_ROOT].name         = "j0";
    uLINK[JID_ROOT].eff_name     = "e0";
    uLINK[JID_ROOT].sister       = 0;
    uLINK[JID_ROOT].child        = JID_LLEG_1;
    uLINK[JID_ROOT].mother       = 0;
    uLINK[JID_ROOT].a            = Vector3f(0, 0, 0);
    uLINK[JID_ROOT].c            = Vector3f(0, 0, 0);
    uLINK[JID_ROOT].b            = Vector3f(0, 0, 0);
    uLINK[JID_ROOT].q            = 0;
    uLINK[JID_ROOT].p            = Vector3f(TorsoInitX, TorsoInitY, TorsoInitZ);
    uLINK[JID_ROOT].R.Identity();

    /** ----------------------------- legs begin ---------------------- */

 	///important!! in the link structure a is axis(the joint axis relative to the body that installed on)     and     b is translation(the offset relative to its parent)      and    c is anchor(geometry center in local coordinate system) or (the offset of the joint anchor relative to the body that installed on).
   

			///leg1 --hip1(turn body into outside)

    uLINK[JID_LLEG_1].name       = "llj1";
    uLINK[JID_LLEG_1].eff_name   = "lle1";
    uLINK[JID_LLEG_1].sister     = JID_RLEG_1;
    uLINK[JID_LLEG_1].child      = JID_LLEG_2;
    uLINK[JID_LLEG_1].mother     = JID_ROOT;
    uLINK[JID_LLEG_1].a          = Vector3f(Hip1Axis_X, Hip1Axis_Y, -Hip1Axis_Z);
    uLINK[JID_LLEG_1].c          = Vector3f(0, 0, 0);
    uLINK[JID_LLEG_1].b          = Vector3f(-Hip1RelTorso_X, Hip1RelTorso_Y, Hip1RelTorso_Z)
                                   - uLINK[JID_LLEG_1].c + uLINK[JID_ROOT].c;
    uLINK[JID_LLEG_1].q          = 0;
			
			///leg2  --hip2(open the foot)		
	
    uLINK[JID_LLEG_2].name       = "llj2";
    uLINK[JID_LLEG_2].eff_name   = "lle2";
    uLINK[JID_LLEG_2].sister     = 0;
    uLINK[JID_LLEG_2].child      = JID_LLEG_3;
    uLINK[JID_LLEG_2].mother     = JID_LLEG_1;
    uLINK[JID_LLEG_2].a          = Vector3f(0, 1, 0); // Vector3f(1, 0, 0)
    uLINK[JID_LLEG_2].c          = Vector3f(0, 0, 0);
    uLINK[JID_LLEG_2].b          = Vector3f(Hip2RelHip1_X, Hip2RelHip1_Y, Hip2RelHip1_Z)
                                   - uLINK[JID_LLEG_2].c + uLINK[JID_LLEG_1].c;
    uLINK[JID_LLEG_2].q          = 0;

			///leg3  --thigh(kamar)

    uLINK[JID_LLEG_3].name       = "llj3";
    uLINK[JID_LLEG_3].eff_name   = "lle3";
    uLINK[JID_LLEG_3].sister     = 0;
    uLINK[JID_LLEG_3].child      = JID_LLEG_4;
    uLINK[JID_LLEG_3].mother     = JID_LLEG_2;
    uLINK[JID_LLEG_3].a          = Vector3f(1, 0, 0); // Vector3f(0, 1, 0)
    uLINK[JID_LLEG_3].c          = Vector3f(ThighRelHip2_X, ThighRelHip2_Y, ThighRelHip2_Z);
    uLINK[JID_LLEG_3].b          = Vector3f(ThighRelHip2_X, ThighRelHip2_Y, ThighRelHip2_Z)
                                   - uLINK[JID_LLEG_3].c + uLINK[JID_LLEG_2].c;
    uLINK[JID_LLEG_3].q          = 0;
			
			///leg4 --shank(zanoo)
    uLINK[JID_LLEG_4].name       = "llj4";
    uLINK[JID_LLEG_4].eff_name   = "lle4";
    uLINK[JID_LLEG_4].sister     = 0;
    uLINK[JID_LLEG_4].child      = JID_LLEG_5;
    uLINK[JID_LLEG_4].mother     = JID_LLEG_3;
    uLINK[JID_LLEG_4].a          = Vector3f(1, 0, 0);
    uLINK[JID_LLEG_4].c          = Vector3f(0, 0.01, -0.045);
    uLINK[JID_LLEG_4].b          = Vector3f(ShankRelThigh_X, ShankRelThigh_Y, ShankRelThigh_Z)
                                   - uLINK[JID_LLEG_4].c + uLINK[JID_LLEG_3].c;
    uLINK[JID_LLEG_4].q          = 0;

			///leg5 --ankle(up and down moch)
    uLINK[JID_LLEG_5].name       = "llj5";
    uLINK[JID_LLEG_5].eff_name   = "lle5";
    uLINK[JID_LLEG_5].sister     = 0;
    uLINK[JID_LLEG_5].child      = JID_LLEG_6;
    uLINK[JID_LLEG_5].mother     = JID_LLEG_4;
    uLINK[JID_LLEG_5].a          = Vector3f(1, 0, 0);
    uLINK[JID_LLEG_5].c          = Vector3f(0, 0, 0);
    uLINK[JID_LLEG_5].b          = Vector3f(AnkleRelShank_X, AnkleRelShank_Y, AnkleRelShank_Z)
                                   - uLINK[JID_LLEG_5].c + uLINK[JID_LLEG_4].c;
    uLINK[JID_LLEG_5].q          = 0;

			///leg6 --foot(out and in moch)
    uLINK[JID_LLEG_6].name       = "llj6";
    uLINK[JID_LLEG_6].eff_name   = "lle6";
    uLINK[JID_LLEG_6].sister     = 0;
    uLINK[JID_LLEG_6].child      = 0;
    uLINK[JID_LLEG_6].mother     = JID_LLEG_5;
    uLINK[JID_LLEG_6].a          = Vector3f(0, 1, 0);
    uLINK[JID_LLEG_6].c          = Vector3f(FootRelAnkle_X, FootRelAnkle_Y, FootRelAnkle_Z);
    uLINK[JID_LLEG_6].b          = Vector3f(FootRelAnkle_X, FootRelAnkle_Y, FootRelAnkle_Z)
                                   - uLINK[JID_LLEG_6].c + uLINK[JID_LLEG_5].c;
    uLINK[JID_LLEG_6].q          = 0;

    uLINK[JID_RLEG_1].name       = "rlj1";
    uLINK[JID_RLEG_1].eff_name   = "rle1";
    uLINK[JID_RLEG_1].sister     = 0;
    uLINK[JID_RLEG_1].child      = JID_RLEG_2;
    uLINK[JID_RLEG_1].mother     = JID_ROOT;
    uLINK[JID_RLEG_1].a          = Vector3f(Hip1Axis_X, Hip1Axis_Y, Hip1Axis_Z);
    uLINK[JID_RLEG_1].c          = Vector3f(0, 0, 0);
    uLINK[JID_RLEG_1].b          = Vector3f(Hip1RelTorso_X, Hip1RelTorso_Y, Hip1RelTorso_Z)
                                   - uLINK[JID_RLEG_1].c + uLINK[JID_ROOT].c;
    uLINK[JID_RLEG_1].q          = 0;

    uLINK[JID_RLEG_2].name       = "rlj2";
    uLINK[JID_RLEG_2].eff_name   = "rle2";
    uLINK[JID_RLEG_2].sister     = 0;
    uLINK[JID_RLEG_2].child      = JID_RLEG_3;
    uLINK[JID_RLEG_2].mother     = JID_RLEG_1;
    uLINK[JID_RLEG_2].a          = Vector3f(0, 1, 0); // Vector3f(1, 0, 0)
    uLINK[JID_RLEG_2].c          = Vector3f(0, 0, 0);
    uLINK[JID_RLEG_2].b          = Vector3f(Hip2RelHip1_X, Hip2RelHip1_Y, Hip2RelHip1_Z)
                                   - uLINK[JID_RLEG_2].c + uLINK[JID_RLEG_1].c;
    uLINK[JID_RLEG_2].q          = 0;

    uLINK[JID_RLEG_3].name      = "rlj3";
    uLINK[JID_RLEG_3].eff_name  = "rle3";
    uLINK[JID_RLEG_3].sister    = 0;
    uLINK[JID_RLEG_3].child     = JID_RLEG_4;
    uLINK[JID_RLEG_3].mother    = JID_RLEG_2;
    uLINK[JID_RLEG_3].a         = Vector3f(1, 0, 0); // Vector3f(0, 1, 0)
    uLINK[JID_RLEG_3].c         = Vector3f(ThighRelHip2_X, ThighRelHip2_Y, ThighRelHip2_Z);
    uLINK[JID_RLEG_3].b         = Vector3f(ThighRelHip2_X, ThighRelHip2_Y, ThighRelHip2_Z)
                                  - uLINK[JID_RLEG_3].c + uLINK[JID_RLEG_2].c;
    uLINK[JID_RLEG_3].q         = 0;

    uLINK[JID_RLEG_4].name      = "rlj4";
    uLINK[JID_RLEG_4].eff_name  = "rle4";
    uLINK[JID_RLEG_4].sister    = 0;
    uLINK[JID_RLEG_4].child     = JID_RLEG_5;
    uLINK[JID_RLEG_4].mother    = JID_RLEG_3;
    uLINK[JID_RLEG_4].a         = Vector3f(1, 0, 0);
    uLINK[JID_RLEG_4].c         = Vector3f(0, 0.01, -0.045);
    uLINK[JID_RLEG_4].b         = Vector3f(ShankRelThigh_X, ShankRelThigh_Y, ShankRelThigh_Z)
                                  - uLINK[JID_RLEG_4].c + uLINK[JID_RLEG_3].c;
    uLINK[JID_RLEG_4].q         = 0;

    uLINK[JID_RLEG_5].name      = "rlj5";
    uLINK[JID_RLEG_5].eff_name  = "rle5";
    uLINK[JID_RLEG_5].sister    = 0;
    uLINK[JID_RLEG_5].child     = JID_RLEG_6;
    uLINK[JID_RLEG_5].mother    = JID_RLEG_4;
    uLINK[JID_RLEG_5].a         = Vector3f(1, 0, 0);
    uLINK[JID_RLEG_5].c         = Vector3f(0, 0, 0);
    uLINK[JID_RLEG_5].b         = Vector3f(AnkleRelShank_X, AnkleRelShank_Y, AnkleRelShank_Z)
                                  - uLINK[JID_RLEG_5].c + uLINK[JID_RLEG_4].c;
    uLINK[JID_RLEG_5].q         = 0;

    uLINK[JID_RLEG_6].name      = "rlj6";
    uLINK[JID_RLEG_6].eff_name  = "rle6";
    uLINK[JID_RLEG_6].sister    = 0;
    uLINK[JID_RLEG_6].child     = 0;
    uLINK[JID_RLEG_6].mother    = JID_RLEG_5;
    uLINK[JID_RLEG_6].a         = Vector3f(0, 1, 0);
    uLINK[JID_RLEG_6].c         = Vector3f(FootRelAnkle_X, FootRelAnkle_Y, FootRelAnkle_Z);
    uLINK[JID_RLEG_6].b         = Vector3f(FootRelAnkle_X, FootRelAnkle_Y, FootRelAnkle_Z)
                                  - uLINK[JID_RLEG_6].c + uLINK[JID_RLEG_5].c;
    uLINK[JID_RLEG_6].q         = 0;
    /** ------------------------------ legs end ----------------------- */

    /** head */
    uLINK[JID_HEAD_2].name      = "hj2";
    uLINK[JID_HEAD_2].eff_name  = "he2";
    uLINK[JID_HEAD_1].name      = "hj1";
    uLINK[JID_HEAD_1].eff_name  = "he1";

    /** ----------------------------- arms begin ---------------------- */
    uLINK[JID_LARM_1].name      = "laj1";
    uLINK[JID_LARM_1].eff_name  = "lae1";
    uLINK[JID_LARM_2].name      = "laj2";
    uLINK[JID_LARM_2].eff_name  = "lae2";
    uLINK[JID_LARM_3].name      = "laj3";
    uLINK[JID_LARM_3].eff_name  = "lae3";
    uLINK[JID_LARM_4].name      = "laj4";
    uLINK[JID_LARM_4].eff_name  = "lae4";

    uLINK[JID_RARM_1].name      = "raj1";
    uLINK[JID_RARM_1].eff_name  = "rae1";
    uLINK[JID_RARM_2].name      = "raj2";
    uLINK[JID_RARM_2].eff_name  = "rae2";
    uLINK[JID_RARM_3].name      = "raj3";
    uLINK[JID_RARM_3].eff_name  = "rae3";
    uLINK[JID_RARM_4].name      = "raj4";
    uLINK[JID_RARM_4].eff_name  = "rae4";
    /** ------------------------------ arms end ----------------------- */

    forwardKinematics(JID_ROOT);

    NAO_A               = (uLINK[JID_LLEG_4].p - uLINK[JID_LLEG_3].p).Length();
    NAO_B               = (uLINK[JID_LLEG_5].p - uLINK[JID_LLEG_4].p).Length();
    NAO_Dl              = uLINK[JID_LLEG_3].p - uLINK[JID_ROOT].p;
    NAO_Dr              = uLINK[JID_RLEG_3].p - uLINK[JID_ROOT].p;
    NAO_E               = - uLINK[JID_LLEG_6].c;

    /** cut a branch(sister) can make IK faster */
    // uLINK[JID_LLEG_1].sister = 0;
}

void Kinematic::setupRobotPartInfo()
{
    // NOTE to be completed
    mRobotPartInfo[PART_BODY].name  = "torso";
}

bool Kinematic::IK_leg(const Matrix& hip, float A, float B,
                 const Matrix& ankle, bool left)
{
    Matrix invHip = hip;
    invHip.InvertRotationMatrix();
    Matrix invAnkle = ankle;
    invAnkle.InvertRotationMatrix();

    Vector3f r = invAnkle.Rotate(hip.Pos() - ankle.Pos());
    float C = r.Length();
    float cosKneePitch = (C * C - A * A - B * B) / (2.0f * A * B);
    float kneePitch = 0.0f;

    if (cosKneePitch >= 1.0f)
    {
        kneePitch = 0.0f;
        std::cout << "cosKneePitch >= 1.0" << std::endl;
        return false;
    }
    else if (cosKneePitch <= -1.0f)
    {
        kneePitch = gPI;
        std::cout << "cosKneePitch <= -1.0" << std::endl;
        return false;
    }
    else
        kneePitch = gArcCos(cosKneePitch);

    kneePitch *= -1.0;

    float q6a = gArcSin((A / C) * gSin(gPI - kneePitch));
    float ankleRoll = -gArcTan2(r.x(), r.z());

    float anklePitch = gArcTan2(
                        r.y(),
                        gSign(r.z()) * gSqrt(r.x() * r.x() + r.z() * r.z())
                       ) - q6a;

    Matrix R = invHip * ankle;

    R.RotateY(-ankleRoll);
    R.RotateX(-anklePitch);
    R.RotateX(-kneePitch);

    float hipPitch      = 0.0f;
    float hipRoll       = 0.0f;
    float hipYaw        = 0.0f;
    float cosHipYaw     = 0.0f;
    float sinHipYaw     = 0.0f;
    float cosHipRoll    = 0.0f;
    float sinHipRoll    = 0.0f;

    if (left)
    {
        hipPitch = gArcTan2(R(2,1) + R(0,1), R(2,2) + R(0,2));
        hipPitch = hipPitch >  gHalfPI ? hipPitch - gPI :
                   hipPitch < -gHalfPI ? hipPitch + gPI : hipPitch;

        float cosHipPitch   = gCos(hipPitch);
        float addCSHipRoll  = (R(2,2) + R(0,2)) / cosHipPitch;

        cosHipYaw = (R(2,0) - R(0,0)) / addCSHipRoll;
        sinHipYaw = R(1,0) / (-0.7071 * addCSHipRoll);
        hipYaw = gArcTan2(sinHipYaw, cosHipYaw);
        hipYaw = -hipYaw; // special in left leg
        hipYaw = hipYaw >  gHalfPI ? hipYaw - gPI :
                 hipYaw < -gHalfPI ? hipYaw + gPI : hipYaw;

        cosHipYaw = cos(hipYaw);

        float subCSHipRoll = 2 * R(0,0) - cosHipYaw * addCSHipRoll;
        cosHipRoll = addCSHipRoll + subCSHipRoll;
        sinHipRoll = addCSHipRoll - subCSHipRoll;
        hipRoll = gArcTan2(sinHipRoll, cosHipRoll);
        hipRoll = hipRoll >  gHalfPI ? hipRoll - gPI :
                  hipRoll < -gHalfPI ? hipRoll + gPI : hipRoll;
    }
    else
    {
        hipPitch = gArcTan2(R(2,1) + R(0,1), R(2,2) + R(0,2));
        hipPitch = hipPitch >  gHalfPI ? hipPitch - gPI :
                   hipPitch < -gHalfPI ? hipPitch + gPI : hipPitch;

        float cosHipPitch   = gCos(hipPitch);
        float subCSHipRoll  = (R(2,2) - R(0,2)) / cosHipPitch;

        cosHipYaw = (R(2,0) + R(0,0)) / subCSHipRoll;
        sinHipYaw = R(1,0) / (0.7071 * subCSHipRoll);
        hipYaw = gArcTan2(sinHipYaw, cosHipYaw);
        hipYaw = hipYaw >  gHalfPI ? hipYaw - gPI :
                 hipYaw < -gHalfPI ? hipYaw + gPI : hipYaw;
        cosHipYaw = cos(hipYaw);

        float addCSHipRoll = 2 * R(0,0) - cosHipYaw * subCSHipRoll;
        cosHipRoll = addCSHipRoll + subCSHipRoll;
        sinHipRoll = addCSHipRoll - subCSHipRoll;
        hipRoll = gArcTan2(sinHipRoll, cosHipRoll);
        hipRoll = hipRoll >  gHalfPI ? hipRoll - gPI :
                  hipRoll < -gHalfPI ? hipRoll + gPI : hipRoll;
    }

    if (left)
    {
        mIKJointAngle[JID_LLEG_1]  = hipYaw;
        mIKJointAngle[JID_LLEG_2]  = hipRoll;
        mIKJointAngle[JID_LLEG_3]  = hipPitch;
        mIKJointAngle[JID_LLEG_4]  = kneePitch;
        mIKJointAngle[JID_LLEG_5]  = anklePitch;
        mIKJointAngle[JID_LLEG_6]  = ankleRoll;
    }
    else
    {
        mIKJointAngle[JID_RLEG_1] = hipYaw;
        mIKJointAngle[JID_RLEG_2] = hipRoll;
        mIKJointAngle[JID_RLEG_3] = hipPitch;
        mIKJointAngle[JID_RLEG_4] = kneePitch;
        mIKJointAngle[JID_RLEG_5] = anklePitch;
        mIKJointAngle[JID_RLEG_6] = ankleRoll;
    }

    return true;
}

bool Kinematic::IK_leg(const salt::Matrix& torso, const salt::Matrix& foot, bool left)
{
    uLINK[JID_ROOT].R = torso;
    uLINK[JID_ROOT].p = torso.Pos();

    Vector3f D      = left ? NAO_Dl : NAO_Dr;
    JointID to      = left ? JID_LLEG_6 : JID_RLEG_6;
    Matrix hip      = torso;
    hip.Pos()       = torso * D;
    Matrix ankle    = foot;
    ankle.Pos()     = foot * NAO_E;

    if (! IK_leg(hip, NAO_A, NAO_B, ankle, left))
    {
        std::cout << "analytic method failed: leg -- "
                          << left << std::endl;
        return false;
    }

    if (left)
    {
        uLINK[JID_LLEG_1].q = mIKJointAngle[JID_LLEG_1];
        uLINK[JID_LLEG_2].q = mIKJointAngle[JID_LLEG_2];
        uLINK[JID_LLEG_3].q = mIKJointAngle[JID_LLEG_3];
        uLINK[JID_LLEG_4].q = mIKJointAngle[JID_LLEG_4];
        uLINK[JID_LLEG_5].q = mIKJointAngle[JID_LLEG_5];
        uLINK[JID_LLEG_6].q = mIKJointAngle[JID_LLEG_6];
    }
    else
    {
        uLINK[JID_RLEG_1].q = mIKJointAngle[JID_RLEG_1];
        uLINK[JID_RLEG_2].q = mIKJointAngle[JID_RLEG_2];
        uLINK[JID_RLEG_3].q = mIKJointAngle[JID_RLEG_3];
        uLINK[JID_RLEG_4].q = mIKJointAngle[JID_RLEG_4];
        uLINK[JID_RLEG_5].q = mIKJointAngle[JID_RLEG_5];
        uLINK[JID_RLEG_6].q = mIKJointAngle[JID_RLEG_6];
    }

    forwardKinematics(JID_ROOT); // apply the joint angles before inverseKinematics
    if (! inverseKinematics(to, ankle))
    {
        std::cout << "numerical method failed: leg -- "
                          << left << std::endl;
        return false;
    }

    if (left)
    {
        mIKJointAngle[JID_LLEG_1] = uLINK[JID_LLEG_1].q;
        mIKJointAngle[JID_LLEG_2] = uLINK[JID_LLEG_2].q;
        mIKJointAngle[JID_LLEG_3] = uLINK[JID_LLEG_3].q;
        mIKJointAngle[JID_LLEG_4] = uLINK[JID_LLEG_4].q;
        mIKJointAngle[JID_LLEG_5] = uLINK[JID_LLEG_5].q;
        mIKJointAngle[JID_LLEG_6] = uLINK[JID_LLEG_6].q;
    }
    else
    {
        mIKJointAngle[JID_RLEG_1] = uLINK[JID_RLEG_1].q;
        mIKJointAngle[JID_RLEG_2] = uLINK[JID_RLEG_2].q;
        mIKJointAngle[JID_RLEG_3] = uLINK[JID_RLEG_3].q;
        mIKJointAngle[JID_RLEG_4] = uLINK[JID_RLEG_4].q;
        mIKJointAngle[JID_RLEG_5] = uLINK[JID_RLEG_5].q;
        mIKJointAngle[JID_RLEG_6] = uLINK[JID_RLEG_6].q;
    }
    return true;
}

void Kinematic::calcLegJointVel(const salt::Vector3f& vb, const salt::Vector3f& wb,
                          const salt::Vector3f& vt, const salt::Vector3f& wt,
                          bool left)
{
    int to      = left ? JID_LLEG_6 : JID_RLEG_6;
    float* vel  = mIKJointAngle.get();
    TIndex idx  = findRoute(to);
    int jsize   = idx.size();

    Vector3f vd, vw;
    vd = vt - vb - wb.Cross(uLINK[to].p - uLINK[1].p);
    vw = wt - wb;

    float v[6];
    v[0] = vd.x(); v[1] = vd.y(); v[2] = vd.z();
    v[3] = vw.x(); v[4] = vw.y(); v[5] = vw.z();

    // allot memory for Jacobian matrix
    float** J = new float*[6];
    for (int i = 0; i < 6; ++i)
    {
        J[i] = new float[jsize];
    }

    calcJacobian(J, idx);
    solve(vel, (const float **)J, (const float *)v, 6, jsize);

    for (int i = 0; i < 6; ++i)
    {
        delete [] J[i];
        J[i] = NULL;
    }
    delete [] J;
    J = NULL;
}
