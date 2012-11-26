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

#ifndef WALK_H
#define WALK_H

#include "../Effectors/Effectors.h"
#include "Trajectory.h"

class Walk
{
friend class BhvBasicWalk;
friend class BhvBasicKick;
friend class RoleForward;
public:
    enum TPhase {
        PREPARE,
        FIRST_STEP,
        NORMAL_STEP,
        MARK_TIME_STEP,
        LAST_STEP,
        STOP
    };

public:
    Walk();
    ~Walk();


      

    static Walk& instance();

    bool mLeftFirstMove;
    
    void Prepare();
    
    void set(bool isPrepare);

    static const Walk& i(){return instance();}

    void Execute(double ang,double speed,ESide type);///action

    void setParam(const ModelParams modelParams,
                  const WalkParams walkParams, 
                  bool isPrepare=true );///action

    /** total steps finished */
    int getTotalStep() const { return mTotalStep; }

    /** whether left foot move first */
    bool IsLeftFootMoveFirst() const { return mLeftFirstMove; }

    /** whether left foot on the ground */
    bool IsLeftFootHold() const { return  mLeftFirstMove ? (mTotalStep % 2 == 1) :
                                                           (mTotalStep % 2 == 0); }

    void setWalkingSlowGain(float slowGain)
    {
        this->mWalkingSlowGain = slowGain;
    }
    TPhase getPhase(){return mPhase;}
    bool IsNormalStepDone();
    bool IsFirstStepDone();

    bool configureOmniDirection(double ang,double speed,ESide type);

    void Stop();
    bool setWalkPhase(Walk::TPhase phase);

     TPhase              mPhase;
    inline double getSpeed(){return mSpeed;}
    inline double getTurnAngle(){return mTurnAngle;}
    bool IsPrepareDone() ;
private:

    double mSpeed;
    double mTurnAngle;

    void   Walking( );
    ESide  mWalkSide;


    bool IsStopDone();

    void SwingArms() ;

    void FirstStep();

    void NormalStep();

    void NormalStepSide();

    bool IsNormalStepSideDone();

    void LastStep();
    bool IsLastStepDone();


    bool generalTrajectory();

    void ApplyJVel(bool left);

    void ApplyTrajectory(bool lefthold , salt::Matrix move);



protected:
    boost::shared_ptr<Trajectory>   mTrajectory;

    boost::shared_ptr<Kinematic>    mRobot;

    

    /** according to time */
    double              mPhaseTime;
    double              mPhaseStartTime;

    /** according to cycle */
    int                 mPhaseCycle;
    int                 mPhaseStartCycle;

    /** false: when inconsistent walk parameters exist,
        calculation of inverse kinematics will fail
    */
    bool                IsIKfailNow;

    int                 mTotalStep;

    float               mSteadyParam;

    salt::Matrix        mTorsoMatrix;

    salt::Matrix        mHoldFootMatrix;

    salt::Matrix        mMoveFootMatrix;

    /** general slow gain, the final one used */
    float               mSlowGain;
   
     /** special slow gain for walking (not prepare or stop) */
     float mWalkingSlowGain;

///me declare
     boost::shared_ptr<Effectors> mEffect;
     boost::shared_ptr<WorldModel> wm;
};


#endif // WALK_H
