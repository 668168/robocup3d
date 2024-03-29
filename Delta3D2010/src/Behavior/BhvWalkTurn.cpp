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

#include "BhvWalkTurn.h"
#include "BhvBasicTurn.h"

bool BhvWalkTurn::execute()
{
  WorldModel & wm = WorldModel::instance();
  static Vector3f lastPos = mTargetPos;
  if (((abs(lastPos.x() - mTargetPos.x())) < 0.1) || ((abs(lastPos.x() - mTargetPos.x())) < 0.1))
  {    
    mTargetPos = lastPos;
  }
  else
  {
    lastPos = mTargetPos;
  }
  Vector2f myPos(wm.getMyPos().x(),wm.getMyPos().y());
  Vector2f target2f(wm.getMyPos().x(),wm.getMyPos().y());
  float angleTarget = wm.getMyAngle2Point(mTargetPos) ;
  float distTarget  = (target2f - myPos).Length();
  static const float speicalAngle = 20.0;
  static const float speicalDist = 2.0;
  if (! isAriveTo(target2f))
  {
    if( angleTarget > 80.0 || (angleTarget > speicalAngle && distTarget < speicalDist))
      return BhvBasicTurn(angleTarget).execute();
    Walk::instance().Execute()
      
  }
  

}

bool  BhvWalkTurn::isAriveTo(const Vector2f& point )const
{
  static const float telorans = 0.1;
  Vector3f myPos = WorldModel::instance().getMyPos();
  float x = myPos.x();
  float y = myPos.y();
  bool ret= ((x > (point.x() - telorans)) && (x < (point.x() + telorans)) &&
             (y > (point.y() - telorans)) && (y < (point.y() + telorans)) );
  cout<<"in BhvDribble::isAriveTo :ariveto = "<<ret<<" posMe.x = "<<x<<" posMe.y = "<<y<<" point.x="<<point.x() <<" point.y="<<point.y()<<endl;
  return ret;
}
