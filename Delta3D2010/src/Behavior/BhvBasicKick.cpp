// //
// // C++ Implementation: BhvBasicKick
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
 #include "BhvBasicKick.h"
#include "../Skills/SuperKick.h"
// 
// unsigned int BhvBasicKick::mStartCycle;
// 
// unsigned int BhvBasicKick::mLastCycleRun;
// 
// bool  BhvBasicKick::mIsLeftHold;
// 
bool BhvBasicKick::execute()
{

}
// 
// bool BhvBasicKick::isNewKick() const
// {
//     /// minus 2 becuse maybe skiping is happen
//     cout <<"in isNewKick :"<< mLastCycleRun << " < " << ( WorldModel::i().getCurrentCycle() - 4 )<<endl;
//     return ( mLastCycleRun < ( WorldModel::i().getCurrentCycle() - 4 ));
// }
// 
// bool BhvBasicKick::isLeftHold() const
// {
//     return mIsLeftHold;
// }
// 
// bool BhvBasicKick::isKickDone() const
// {
//     static const int KickTime = 200;
//     return ( (WorldModel::i().getCurrentCycle() - mStartCycle) < KickTime );
// }
// 
// void BhvBasicKick::reset()
// {
// //    Kick::instance().reset();
// }
// 
// bool BhvBasicKick::isBallKickable()const
// {
//     static const float DistanceTelorans = 0.1;
// 
//     static const float AngleTelorans = 15.0;
// 
//     if ( isNewKick() )
//     {
//        cout << "in ball kicable newKick (" << ball.distance <<" <= "<< MaxKickableDistance <<
//                ") && ("<< abs(ball.theta) << " < "<< 60.0f<<") "<<endl;
//        return ( (ball.distance <= MaxKickableDistance) && (abs(ball.theta) < 60.0f) );
//     }
//     else
//     {
//        cout << "in ball kicable normal (" << ball.distance <<
//                " <= "<< (MaxKickableDistance + DistanceTelorans) <<
//                ") && ("<< abs(ball.theta) << " < "<< (60.0f + AngleTelorans)<<") "<<endl;
// 
//        return ( (ball.distance <= (MaxKickableDistance + DistanceTelorans) ) &&
//                 (abs(ball.theta) < (60.0f + AngleTelorans)) );
//     }
//     return false;
// }
// 
// 
// 
// /*    cout<<"iCycle & wm.getCurrentCycle()  : "<<iCycle <<" & "<< wm.getCurrentCycle() <<endl;
// //     if (iCycle <= wm.getCurrentCycle() -10)/// select 10 for maybe skiping
// //     {
// //        bIsWalkStoped   = false;
// //        fNormalDistance = MaxKickableDistance - deltaKickDistance;
// //     }
// 
//     iCycle = wm.getCurrentCycle();
// 
//     cout<<"fNormalDisttance = "<<fNormalDistance<<endl;
// 
//     if (ball.distance > fNormalDistance || Kick::instance().isKickDone())
//     {
//        cout <<"Distance to ball : "<<ball.distance<<" Walk performed "<<endl;
//        fNormalDistance = MaxKickableDistance - deltaKickDistance;
//        bIsWalkStoped =false;
// //       BhvBasicWalk(Vector2f(0.0,0.0)).execute();
//        return false;
//     }
// 
//     fNormalDistance = MaxKickableDistance;
//     static const float fTlorans =0.2;
//     bool bIsStop = (wm.getGyr().x > -fTlorans && wm.getGyr().x < fTlorans &&
//                     wm.getGyr().y > -fTlorans && wm.getGyr().y < fTlorans &&
//                     wm.getGyr().z > -fTlorans && wm.getGyr().z < fTlorans );
//     if (walk.IsPrepareDone() && bIsStop)
//     {
//         cout <<"Distance to ball : "<<ball.distance<<" prepare walk done "<<endl;
//         bIsWalkStoped =true;
//     }
// 
//     if (!bIsWalkStoped )
//     {
//        walk.Prepare();
//        cout <<"Distance to ball : "<<ball.distance<<
//               " prepare walk execute & iCycle ="<<iCycle<<endl;
//        return true;
//     }
//     else
//     {
//        cout <<"Distance to ball : "<<ball.distance<<" Kick Execute "<<endl;
//        Kick::instance().execute(bLeftHold);
//        return true;
//     }
// 
//     if (Kick::instance().isKickDone())
//     {
//        cout <<"Distance to ball : "<<ball.distance<<" Kick done "<<endl;
//        bIsWalkStoped =false;
//        fNormalDistance =MaxKickableDistance;
//        return true;
//     }
//     return false;*/