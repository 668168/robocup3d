// //
// // C++ Interface: BhvBasicKick
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
 #ifndef BHV_BASIC_KICK_H
 #define BHV_BASIC_KICK_H
 
 #include "SoccerBehavior.h"
 #include "BhvBasicWalk.h"
 #include "../Skills/Kick.h"
 #include "../Effectors/AngularMotor.h"
 
 class BhvBasicKick: public SoccerBehavior {
 
private:
      
     bool  isBallKickable()const;

     bool  isNewKick()const;

     bool  isKickDone()const;

     bool  isLeftHold()const;

     void  reset();

     static unsigned int mStartCycle;

     static unsigned int mLastCycleRun;

     static bool  mIsLeftHold;

     const VisionSense&        ball;


public:
        
     std::string start(int cycle);
     BhvBasicKick():ball(WorldModel::instance().getPolarBallPos())
     { }

     virtual bool  execute();
 };

#endif