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

#ifndef EFFECTORS_H
#define EFFECTORS_H

#include "../Connection/Connection.h"
#include "../WorldModel/WorldModel.h"
#include "../Skills/Kinematic.h"
#include "../Formation/Formation.h"

#include <errno.h>
#include <signal.h>
#include <iostream>
#include <vector>

#include "../salt/vector.h"
#include "../salt/gmath.h"
#include <boost/shared_array.hpp>

class Effectors{
private:
    boost::shared_array <std::string> mEffectorName;
    void setupEffName();

public:
   Effectors                   (                                            );
   ~Effectors                  (                                            );

    static Effectors& instance (                                            );

    static const Effectors& i  ()
    {
       return instance();
    }

    void                        calculateVel       (EJointID                  id,
                                                    float                     angle,
                                                    float                     maxVel                );

    void                        setActionCommand   (                                                );

    void                        updateJointAngle   (const boost::shared_array<Kinematic::Link> link );

    std::string                 mActionCommand;

    bool                        mIsDone;

    boost::shared_array<float>  mJointAngle;

    boost::shared_array<float>  mJointVel;

    boost::shared_ptr<Connection> con;

};

#endif // EFFECTORS_H
