// //
// // C++ Interface: Kick
// //
// // Description: 
// //
// //
// // Author: delta3d team 2009 <deltateams2009@gmail.com>, (C) 2009
// //
// // Copyright: See COPYING file that comes with this distribution
// //
// //
// 
// 
// #ifndef KICK_H
// #define KICK_H
// 
// #include "../Effectors/Effectors.h"
// #include "../WorldModel/WorldModel.h"
// 
// class Kick
// {
// friend class BhvBasicKick;
// public:
//     enum TPhase{
//          FINAL,
//          PREPARE,
//          SHOOT
//     };
//     Kick();
//     ~Kick(){};
// 
//     static Kick& instance                 (              );
// 
//     static const Kick& i                  (              ){return instance();}
// 
//     void   execute                        ( bool  isLeftHold);
// 
//     bool   isDone();
// 
//     void   reset();
// 
// private:
// 
//     bool                isShootDone        (             );
// 
//     bool                isPrepareDone      (             );
// 
//     bool                isFinalDone        (             );
// 
//     float               mSlowGain;
// 
//     TPhase              mPhase;
// 
//     int                 mStartPhaseCycle;
// 
//     bool                mLeftHold;
// 
//     void                getPrepareMatrix   (             );
// 
//     void                getShootMatrix     (             );
// 
//     void                getFinalMatrix     (             );
// 
//     void                kicking            (             );
// 
//     void                prepare            (             );
// 
//     void                shoot              (             );
// 
//     void                final              (             );
// 
//     salt::Matrix        mTorsoMatrix;
// 
//     salt::Matrix        mHoldFootMatrix;
// 
//     salt::Matrix        mMoveFootMatrix;
// 
//     void                ApplyJVel          ( bool left    );
// };
// 
// #endif