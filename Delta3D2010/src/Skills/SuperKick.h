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

#ifndef KICK_H
#define KICK_H

#include "../Effectors/Effectors.h"
#include "../WorldModel/WorldModel.h"
//me added
#include "../Skills/Walk.h"
class SuperKick
{
friend class BhvBasicKick;
public:
    
   SuperKick();
   
   ~SuperKick(){};

    static SuperKick& instance                 (              );

    static const SuperKick& i                  (              ){return instance();}

    void   execute                        ( bool  isLeftHold);
    
    inline bool isKickDone(){return mKickDone;}
    inline void setKickDone(const bool &bDone){mKickDone = bDone;}

private:
  static bool mKickDone;
  static bool mPrepare;
  static bool mPrepareDone; 
   bool 		prepare();
  
   void 		importShootJoint(shootJoint& Shoot,bool leftFoot);

   int 			Kicking(std::string &cmd,bool);

   string 		fix();

   string resetJointShoot(int nextcycle); 
   
   string moveJoint(string j, double val);
   
   boost::shared_ptr<WorldModel> WM;
   
   stringstream S;
   

};

#endif // KICK_H
