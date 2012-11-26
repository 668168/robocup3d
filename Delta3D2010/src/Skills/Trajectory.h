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

#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "../Utility/Spline.h"

#include "../Perceptors/Perceptors.h"
#include "../Utility/Types.h"
//#include <zeitgeist/class.h>


/** \class Trajectory produces the trajectories
 *  for walking. It plans the positions of hip
 *  and ankle according to this paper
 *  'Planning walking patterns for a biped robot'.
 *  It has been expanded into three dimesion.
 */
class Trajectory
{
friend  class BhvBasicWalk;
friend  class Walk;
public:
                        Trajectory                  (                        );

                        ~Trajectory                 (                        );

    static Trajectory&  instance                    (                        );

    static const Trajectory& i                      (                        ){return instance();}

    bool                general                     (                        );

    inline bool         ModelInited                 (                        ) const { return mModelInit; }

    void                setParams                   (WalkParams    walk);

    void                initModelParams             (ModelParams   model);

    /** matrix of normal trajectory */
    bool                getTrajectoryMatrix         (float         t,
                                                     salt::Matrix& torso,
                                                     salt::Matrix& holdfoot,
                                                     salt::Matrix& movefoot,
                                                     bool          lefthold  );

    /** matrix of start trajectory */
    bool                getStartTrajectoryMatrix   (float         t,
                                                    salt::Matrix& torso,
                                                    salt::Matrix& holdfoot,
                                                    salt::Matrix& movefoot,
                                                    bool          lefthold   );

    /** matrix of end trajectory */
    bool                getEndTrajectoryMatrix     (float t,
                                                    salt::Matrix& torso,
                                                    salt::Matrix& holdfoot,
                                                    salt::Matrix& movefoot,
                                                    bool lefthold            );

    /** return step size */
    float               getDs                      (                         ) const { return Ds; }

    /** return time of walking cycle */
    float               getTc                      (                         ) const { return Tc; }

    /** return time of double support phase */
    float               getTd                      (                         ) const { return Td; }

    /** return time of start phase */
    float               getTs                      (                         ) const { return Ts; }

    /** return time of end phase */
    float               getTe                      (                         ) const { return Te; }

protected:
    /** trajectory produced in 2D
     */
    float             getHipX                    (float         t,
                                                    int           der = 0   ) const;

    float             getHipZ                    (float         t,
                                                    int           der = 0   ) const;

    float             getHipTheta                (float         t,
                                                    int           der = 0   ) const;

    float             getFootX                   (float         t,
                                                    int           der = 0   ) const;


    float             getFootZ                (float         t,
                                                    int           der = 0   ) const;


    float             getFootTheta                (float         t,
                                                    int           der = 0   ) const;


    /** calculate matrx of trajectory :
     *  hip, holdfoot and movefoot
     */
    void              calTrajectoryMatrix(float t);

    void              calStartTrajectoryMatrix(float t);

    void              calEndTrajectoryMatrix(float t);

    void              calWalkTrajectoryMatrix(bool lefthold);

public:
    bool              mModelInit;

    salt::Vector3f    mDs3D;

    int               k;

    /** step length */
    float             Ds;

    /** walking cycle */
    float             Tc;

    /** double support time of walking cycle */
    float             Td;

    /** when foot reach the highest point in z axis */
    float             Tm;

    float             Qgs;

    float             Qb;

    float             Qf;

    float             Qge;

    float             Xed;

    float             Xsd;

    /** hip.z */
    float             Hnor;

    float             Lan;

    float             Laf;

    float             Lab;

    float             Lao;

    float             Lth;

    float             Lsh;

    float             Hgs;

    float             Hge;

    /** foot's highest point in z axis */
    float             Hao;

    /** start phase time */
    float             Ts;

    /** end phase time */
    float             Te;

    /** turn angle */
    float             mTurnAngle;

    float             TorsoRot_X;

    float             TorsoRelHip_Z;

    float             FootOffset_X;

    /** normal phase */
    Spline            foot_x;
    Spline            foot_z;
    Spline            foot_theta;
    Spline            hip_x;
    Spline            hip_z;

    /** start phase */
    Spline            foot_start_x;
    Spline            foot_start_z;
    Spline            foot_start_theta;
    Spline            hip_start_x;
    Spline            hip_start_z;

    /** end phase */
    Spline            foot_end_x;
    Spline            foot_end_z;
    Spline            foot_end_theta;
    Spline            hip_end_x;
    Spline            hip_end_z;

    salt::Matrix      mHoldAnkleMatrix;
    salt::Matrix      mMoveAnkleMatrix;
    salt::Matrix      mHipMatrix;

    salt::Matrix      mHoldFootMatrix;
    salt::Matrix      mMoveFootMatrix;
    salt::Matrix      mTorsoMatrix;
};

#endif // TRAJECTORY_H
