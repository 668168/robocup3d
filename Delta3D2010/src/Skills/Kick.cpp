// //
// // C++ Implementation: Kick
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
// #include "Kick.h"
// #include "../WorldModel/WorldModel.h" 
// 
// Kick::Kick()
// {
//    mSlowGain    = 0.3f;
//    mTorsoMatrix.Identity();
//    mHoldFootMatrix.Identity();
//    mMoveFootMatrix.Identity();
// 
// }
// 
// Kick& Kick::instance()
// {
//     static Kick sKick;
//     return sKick;
// }
// 
// void Kick::execute(bool isLeftHold)
// {
//     kicking();
//     mLeftHold = isLeftHold;
//     cout<<" Kick Phase = "<<mPhase<<endl;
//     switch ( mPhase )
//     {
//        case (PREPARE):
//            cout<<"Walk: Prepare execute"<<endl;
//            prepare();
//            break;
//        case (SHOOT):
//            cout<<"Walk: Shoot execute"<<endl;
//            shoot();
//            break;
//        case (FINAL):
//            cout<<"Walk: Final execute"<<endl;
//            final();
//            break;
//        default:
//            break;
//     }
// }
// 
// void Kick::kicking()
// {
//     if (FINAL == mPhase && isFinalDone() )
//     {
//        cout <<"Kick:Final Done"<<endl;
//        mPhase = PREPARE;
//        mStartPhaseCycle = WorldModel::i().getCurrentCycle();
//        return;
//     }
// 
//     if (PREPARE ==  mPhase && isPrepareDone())
//     {
//        mPhase = SHOOT;
//        mStartPhaseCycle = WorldModel::i().getCurrentCycle();
//        return;
//     }
// //     static const float fTlorans =5.0;
// //     const WorldModel& wm = WorldModel::i();
// //     bool bIsStop = (wm.getGyr().x > -fTlorans && wm.getGyr().x < fTlorans &&
// //                     wm.getGyr().y > -fTlorans && wm.getGyr().y < fTlorans &&
// //                     wm.getGyr().z > -fTlorans && wm.getGyr().z < fTlorans );
// 
//     if (SHOOT == mPhase && isShootDone() /*&& bIsStop*/)
//     {
//        cout<<"Kick is Done"<<endl;
//        mPhase = FINAL;
//        mStartPhaseCycle = WorldModel::i().getCurrentCycle();
//        return;
//     }
// }
// 
// bool Kick::isDone()
// {
//     return (SHOOT == mPhase && isShootDone());
// }
// void Kick::prepare()
// {
//     cout<<"Prepare Kick execute "<<endl;
//     /*
//     mSlowGain = 0.2f;
//     getPrepareMatrix();
//     if (! Kinematic::instance().IK_leg(mTorsoMatrix, mHoldFootMatrix, lefthold))
//     {
//         cout<<"soti Prepare 1"<<endl;
//         return ;
//     }
//     ApplyJVel(lefthold);
// 
//     if (! Kinematic::instance().IK_leg(mTorsoMatrix, mMoveFootMatrix, !lefthold))
//     {
//         cout<<"soti Prepare 2"<<endl;
//         return ;
//     }
//     ApplyJVel(!lefthold);
//      */
// 
// //     /*
//     float rAngles[12] ={   0.0 ,  0.01,
//                          -17.7 ,-20.36,
//                          27.99 , 11.93,
//                         -81.21 ,-94.44,
//                          53.23 , 75.14,
//                          17.71 , 20.37 };
//     float lAngles[12] ={   0.0 ,  0.01,
//                          20.36 ,  17.7,
//                          11.93 , 27.99,
//                         -94.44 ,-81.21,
//                          75.14 , 53.23,
//                         -20.37 ,-17.71 };
//     for (int i = 0;i<12;++i)
//     {
//         if (mLeftHold)
//             Effectors::instance().calculateVel(static_cast<EJointID>(i+JID_LLEG_1),
//                                                rAngles[i] , 5);
//         else
//             Effectors::instance().calculateVel(static_cast<EJointID>(i+JID_LLEG_1),
//                                                lAngles[i] , 5);
//     }
// //     */
// }
// 
// 
// bool Kick::isPrepareDone()
// {
//     return WorldModel::i().isStable();
//    /*
//     bool lefthold = false;
//     getPrepareMatrix();
//     float ld, rd;
//     boost::shared_array<float> IKJointAngle = Kinematic::instance().getIKJointAngle();
//     if (! Kinematic::instance().IK_leg(mTorsoMatrix, mHoldFootMatrix, lefthold)) 
//         return false;
//     ld = gRadToDeg(gAbs(Effectors::instance().mJointAngle[JID_LLEG_4] -
//                         IKJointAngle[JID_LLEG_4]));
// 
//     if (! Kinematic::instance().IK_leg(mTorsoMatrix, mMoveFootMatrix, ! lefthold)) 
//         return false;
//     rd = gRadToDeg(gAbs(Effectors::instance().mJointAngle[JID_RLEG_4] -
//                         IKJointAngle[JID_RLEG_4]));
// 
//     return (ld < 1.5 && rd < 1.5);
//        */
// //       /*
//     float rAngles[12] ={  0.0 ,  0.01,
//                        -17.7 ,-20.36,
//                        27.99 , 11.93,
//                       -81.21 ,-94.44,
//                        53.23 , 75.14,
//                        17.71 , 20.37 };
// 
//     float lAngles[12] ={   0.0 ,  0.01,
//                          20.36 ,  17.7,
//                          11.93 , 27.99,
//                         -94.44 ,-81.21,
//                          75.14 , 53.23,
//                         -20.37 ,-17.71 };
// 
//     const float telorans = 0.5;
//     WorldModel& wm = WorldModel::instance();
//     cout <<"in prepare check"<<endl;
//     for (int i=0;i<12;++i   )
//     {
//         if (mLeftHold)
//         {
//            cout <<" joint "<<i<<" :"<<rAngles[i]-telorans<<"< "<< wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle <<" <"<< rAngles[i]+telorans<<endl;
// 
//            if (!(wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle > rAngles[i]-telorans &&
//                  wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle < rAngles[i]+telorans))
//                return false;
//         }
//         else
//         {
//            cout <<" joint "<<i<<" :"<<lAngles[i]-telorans<<"< "<< wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle <<" <"<< lAngles[i]+telorans<<endl;
//            if (!(wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle > lAngles[i]-telorans &&
//                  wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle < lAngles[i]+telorans))
//                return false;
//         }
//     }
// 
//     return true;
// //       */
// }
// 
// 
// 
// void Kick::shoot()
// {
//     cout<<"Shoot Kick execute "<<endl;
//     bool lefthold = mLeftHold;
//     mSlowGain = 0.01f;
//     getShootMatrix();
// 
// //     /*
//     if (! Kinematic::instance().IK_leg(mTorsoMatrix, mHoldFootMatrix, lefthold))
//     {
//         cout <<"soti shoot 1"<<endl;
//         return ;
//     }
//     ApplyJVel(lefthold);
// 
//      if (! Kinematic::instance().IK_leg(mTorsoMatrix, mMoveFootMatrix, !lefthold))
//      {
//          cout <<"soti shoot 2"<<endl;
//          return ;
//      }
//      ApplyJVel(!lefthold);
// //         */
//       /*
//      float angles[12] ={0.0,0.01,-11.82,-14.03,2.01,35.81,-0.06,-60.52,-1.95,24.71,11.82,14.03 };
//     for (int i = 0;i<12;++i)
//     {
//         Effectors::instance().calculateVel(static_cast<EJointID>(i+JID_LLEG_1),angles[i] , 20000);
//     }
//      */
// }
// 
// bool Kick::isShootDone()
// {
//     //return WorldModel::i().isStable();
// //     return (WorldModel::i().getCurrentCycle() - mStartPhaseCycle > 20);
// 
//    float rAngles[12] ={  0.0 ,  0.01,
//                       -11.82 ,-14.03,
//                         2.01 , 35.81,
//                        -0.06 ,-60.52,
//                        -1.95 , 24.71,
//                        11.82 , 14.03 };
// 
//    float lAngles[12] ={ 0.01 ,   0.0,
//                        14.03 , 11.82,
//                        35.81 ,  2.01,
//                       -60.52 , -0.06,
//                        24.71 , -1.95,
//                       -14.03 ,-11.82  };
// 
//     const float telorans = 0.2;
//     WorldModel& wm = WorldModel::instance();
//     cout <<"in shoot check"<<endl;
//     for (int i=0;i<12;++i   )
//     {
//         if (mLeftHold)
//         {
//            cout <<" joint "<<i<<" :"<<rAngles[i]-telorans<<"< "<<
//                   wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle <<" <"<<
//                   rAngles[i]+telorans<<endl;
// 
//            if (!(wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle > rAngles[i]-telorans &&
//                  wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle < rAngles[i]+telorans))
//                return false;
//         }
//         else
//         {
//            cout <<" joint "<<i<<" :"<<lAngles[i]-telorans<<"< "<<
//                   wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle <<" <"<<
//                   lAngles[i]+telorans<<endl;
// 
//            if (!(wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle > lAngles[i]-telorans &&
//                  wm.getHJoint(static_cast<EJointID>(i+JID_LLEG_1)).angle < lAngles[i]+telorans))
//                return false;
//         }
//     }
//     cout <<"***********************"<<endl;
//     return true;
// }
// 
// void Kick::final()
// {
//     cout<<"Final Kick execute "<<endl;
//     Effectors::instance().calculateVel(JID_LARM_1, -45.0, 20);
//     Effectors::instance().calculateVel(JID_RARM_1, -45.0, 20);
// 
//     bool lefthold =true;
//     mSlowGain = 0.3f;
//     getFinalMatrix();
//     if (! Kinematic::instance().IK_leg(mTorsoMatrix, mHoldFootMatrix, lefthold))
//     {
//         cout <<"soti Final 1"<<endl;
//         return ;
//     }
//     ApplyJVel(lefthold);
// 
//      if (! Kinematic::instance().IK_leg(mTorsoMatrix, mMoveFootMatrix, !lefthold))
//      {
//          cout <<"soti Final 2"<<endl;
//          return ;
//      }
//      ApplyJVel(!lefthold);
// }
// 
// bool  Kick::isFinalDone        (             )
// {
//     return WorldModel::instance().isStable();
//     bool lefthold = false;
//     getFinalMatrix();
//     float ld, rd;
//     boost::shared_array<float> IKJointAngle = Kinematic::instance().getIKJointAngle();
//     if (! Kinematic::instance().IK_leg(mTorsoMatrix, mHoldFootMatrix, lefthold)) 
//         return false;
//     ld = gRadToDeg(gAbs(Effectors::instance().mJointAngle[JID_LLEG_4] -
//                         IKJointAngle[JID_LLEG_4]));
// 
//     if (! Kinematic::instance().IK_leg(mTorsoMatrix, mMoveFootMatrix, ! lefthold)) 
//         return false;
//     rd = gRadToDeg(gAbs(Effectors::instance().mJointAngle[JID_RLEG_4] -
//                         IKJointAngle[JID_RLEG_4]));
// 
//     return (ld < 1.5 && rd < 1.5 );
// }
// 
// void Kick::ApplyJVel(bool left)
// {
//     Effectors& eff = Effectors::instance();
//     boost::shared_array<float> IKJointAngle = Kinematic::instance().getIKJointAngle();
//     if (left) // left foot
//     {
//         eff.mJointVel[JID_LLEG_1] = (IKJointAngle[JID_LLEG_1] -
//                                          eff.mJointAngle[JID_LLEG_1])/ mSlowGain ;
// 
//         eff.mJointVel[JID_LLEG_2] = (IKJointAngle[JID_LLEG_2] -
//                                          eff.mJointAngle[JID_LLEG_2])/ mSlowGain ;
// 
//         eff.mJointVel[JID_LLEG_3] = (IKJointAngle[JID_LLEG_3] -
//                                          eff.mJointAngle[JID_LLEG_3])/ mSlowGain ;
// 
//         eff.mJointVel[JID_LLEG_4] = (IKJointAngle[JID_LLEG_4] -
//                                          eff.mJointAngle[JID_LLEG_4])/ mSlowGain ;
// 
//          eff.mJointVel[JID_LLEG_5] = (IKJointAngle[JID_LLEG_5] -
//                                           eff.mJointAngle[JID_LLEG_5])/ mSlowGain ;
// 
//         eff.mJointVel[JID_LLEG_6] = (IKJointAngle[JID_LLEG_6] -
//                                          eff.mJointAngle[JID_LLEG_6])/ mSlowGain ;
//     }
//     else // right foot
//     {
//         eff.mJointVel[JID_RLEG_1] = (IKJointAngle[JID_RLEG_1] -
//                                          eff.mJointAngle[JID_RLEG_1])/ mSlowGain ;
// 
//         eff.mJointVel[JID_RLEG_2] = (IKJointAngle[JID_RLEG_2] - 
//                                          eff.mJointAngle[JID_RLEG_2])/ mSlowGain ;
// 
//         eff.mJointVel[JID_RLEG_3] = (IKJointAngle[JID_RLEG_3] -
//                                          eff.mJointAngle[JID_RLEG_3])/ mSlowGain ;
// 
//         eff.mJointVel[JID_RLEG_4] = (IKJointAngle[JID_RLEG_4] -
//                                          eff.mJointAngle[JID_RLEG_4])/ mSlowGain ;
// 
//          eff.mJointVel[JID_RLEG_5] = (IKJointAngle[JID_RLEG_5] -
//                                           eff.mJointAngle[JID_RLEG_5])/ mSlowGain ;
// 
//         eff.mJointVel[JID_RLEG_6] = (IKJointAngle[JID_RLEG_6] -
//                                          eff.mJointAngle[JID_RLEG_6])/ mSlowGain ;
//     }
// }
// 
// void Kick::getPrepareMatrix()
// {
//     mTorsoMatrix.Identity();
//     mHoldFootMatrix.Identity();
//     mMoveFootMatrix.Identity();
//     salt::Vector3f torsoPos(0.055, 0.0, 0.3199),
//                    holdPos(0.06, 0.0, 0.015),
//                    movePos(-0.045, -0.05, 0.05);
//     mTorsoMatrix.Pos() = torsoPos;
//     mHoldFootMatrix.Pos() = holdPos;
//     mMoveFootMatrix.Pos() = movePos;
// }
// 
// void Kick::getShootMatrix()
// {
//     mTorsoMatrix.Identity();
//     mHoldFootMatrix.Identity();
//     mMoveFootMatrix.Identity();
//     salt::Vector3f torsoPos(-0.035, -0.032, 0.3801),
//                    holdPos(-0.045, 0.0, 0.015),
//                    movePos(0.065, 0.02, 0.05);
//     if (!mLeftHold)
//     {
//        torsoPos = Vector3f( 0.035,-0.032, 0.3801);
//        holdPos  = Vector3f( 0.045,   0.0,  0.015);
//        movePos  = Vector3f(-0.065,  0.02,   0.05);
//     }
//     mTorsoMatrix.Pos()    = torsoPos;
//     mHoldFootMatrix.Pos() = holdPos;
//     mMoveFootMatrix.Pos() = movePos;
// }
// 
// void Kick::getFinalMatrix()
// {
//     mTorsoMatrix.Identity();
//     mHoldFootMatrix.Identity();
//     mMoveFootMatrix.Identity();
//     salt::Vector3f torsoPos(0.0, 0.0, 0.3301),
//                    holdPos(-0.055, 0.0, 0.015),
//                    movePos(0.055 , 0.0, 0.015);
//     mTorsoMatrix.Pos()    = torsoPos;
//     mHoldFootMatrix.Pos() = holdPos;
//     mMoveFootMatrix.Pos() = movePos;
// }
// 
// void Kick::reset()
// {
//     mTorsoMatrix.Identity();
//     mHoldFootMatrix.Identity();
//     mMoveFootMatrix.Identity();
//     mPhase = FINAL;
//     mSlowGain    = 0.3f;
//     mStartPhaseCycle =WorldModel::i().getCurrentCycle();
//     mLeftHold =true;
// }
// 
// 
// /*
// 
// mSlowGain = 0.01f;
// 
// salt::Vector3f torsoPos(-0.055, 0.0, 0.3201),
//                    holdPos(-0.045, 0.0, 0.015),
//                    movePos(0.045, -0.04, 0.05);
// 
// salt::Vector3f torsoPos(-0.035, -0.02, 0.3801),
//                    holdPos(-0.045, 0.0, 0.015),
//                    movePos(0.045, 0.1, 0.05);
// 
// 
// prepare:
// salt::Vector3f torsoPos(-0.055, 0.0, 0.3199),
//                    holdPos(-0.06, 0.0, 0.015),
//                    movePos(0.045, -0.05, 0.05);
// shoot:
// salt::Vector3f torsoPos(-0.035, -0.032, 0.3801),
//                    holdPos(-0.045, 0.0, 0.015),
//                    movePos(0.065, 0.02, 0.05);
// 
// 
// back prepare
//   salt::Vector3f torsoPos(-0.055, 0.0, 0.3199),
//                    holdPos(-0.06, 0.0, 0.015),
//                    movePos(0.045, 0.02, 0.02);
// 
// back shoot
// t::Vector3f torsoPos(-0.035, -0.032, 0.3801),
//                    holdPos(-0.045, 0.0, 0.015),
//                    movePos(0.045, -0.15, 0.07);
// 
// 
// 
// 
//                     uLINK[JID_LLEG_5].p
// 
// */