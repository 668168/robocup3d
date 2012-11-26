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

#ifndef KINEMATIC_H
#define KINEMATIC_H

//#include <zeitgeist/node.h>
#include "../salt/matrix.h"
#include "../Utility/Types.h"
#include <vector>
#include <boost/shared_array.hpp>


namespace oxygen {
    class Joint;
    class UniversalJoint;
    class HingeJoint;
};

class WorldModel;

class Kinematic
{
    friend class WorldModel;
    friend class Kick;
public:
    static Kinematic& instance();
    static const Kinematic& i(){ return instance();}
    typedef std::vector<int> TIndex;

    struct Link {
        std::string name;	///the joint name
        std::string eff_name;  ///the effector name
        int id;
        int twin;             /// used for universal joint
        int sister;
        int child;		///the child node on tree
        int mother;		///the parent of joint on tree
        salt::Vector3f a;     /// axis
        salt::Vector3f b;     /// relative position to mother's anchor
        salt::Vector3f c;     /// geometry center in local coordinate system
        float q;              /// joint angle
        float dq;
        float ddq;
        float m;
        salt::Vector3f p;
        salt::Matrix   R;
        salt::Vector3f v;	///velocity
        salt::Vector3f w;

        Link() : name("<unnamed>"), eff_name("<unnamed>"),
                 id(0), twin(0), sister(0), child(0), mother(0), q(0.0f) {}
    };

    struct RobotPartInfo {
        std::string     name; ///name of part
        salt::Vector3f  p;   ///position
        salt::Matrix    R;  ///rotate
    };

    Kinematic();
    ~Kinematic();

    bool init();

    void updateLink(const salt::Matrix& mat);

    boost::shared_array<Kinematic::Link> getLink() const;

    boost::shared_array<Kinematic::RobotPartInfo> getRobotPartInfo() const;

/** mapping from joint id to joint hinge sense object */
    THingeJointSenseMap mHingeJointSenseMap;

    boost::shared_array<float> getIKJointAngle() const;

    boost::shared_array<float> getIKJointVel() const;

    salt::Matrix getRobotPartMatrix(RobotPart part) const;

    salt::Vector3f getRobotPartPos(RobotPart part) const;

    RobotPart getRobotPartMin() const { return PART_MIN; }

    RobotPart getRobotPartMax() const { return PART_MAX; }

    JointID getJointMin() const { return JID_MIN; }

    JointID getJointMax() const { return JID_MAX; }

    void printLink(int j);

    bool IK_leg(const salt::Matrix& torso, const salt::Matrix& foot, bool left);

    void calcLegJointVel(const salt::Vector3f& vb, const salt::Vector3f& wb,
                                 const salt::Vector3f& vt, const salt::Vector3f& wt,
                                 bool left) ;

protected:
    void setupLinks();

    void setupRobotPartInfo() ;

    void setupJointIDMap();

    /** A*x = B, size: A--row*column, x--colunm*1, B--row*1 */
    static bool solve(float* X, const float** A, const float* B, int row, int column);

    static void calcVWerr(float err[6], const salt::Matrix& ref, const salt::Matrix& now);

    TIndex findRoute(int to);

    void forwardKinematics(int j);

    bool inverseKinematics(int to, const salt::Matrix& target);

    void calcJacobian(float** J, const TIndex& idx);

    void forwardVelocity(int j);

    bool IK_leg(const salt::Matrix& hip, float A, float B,
                        const salt::Matrix& ankle, bool left) ;

protected:
    boost::shared_array<Link> uLINK;

    boost::shared_array<RobotPartInfo> mRobotPartInfo;

    /** joint angle calculated by IK */
    boost::shared_array<float> mIKJointAngle;

    /** joint velocities calculated by IK */
    boost::shared_array<float> mIKJointVel;

    JointID     JID_MIN;

    JointID     JID_MAX;

    RobotPart   PART_MIN;

    RobotPart   PART_MAX;


    /** mapping from joint id to joint hinge sense object */
    TUniversalJointSenseMap mUniversalJointSenseMap;

    /** mapping from object name to joint id */
    TJointIDMap mJointIDMap;
private:
        /** foots */
    float FootLength;
    float FootWidth;
    float FootHeight;
    float FootMass;

    float FootRelAnkle_X;
    float FootRelAnkle_Y;
    float FootRelAnkle_Z;

    /** ankles */
    float AnkleRelShank_X;
    float AnkleRelShank_Y;
    float AnkleRelShank_Z;

    /** shanks */
    float ShankLength;
    float ShankWidth;
    float ShankHeight;
    float ShankMass;

    float ShankRelThigh_X;
    float ShankRelThigh_Y;
    float ShankRelThigh_Z;

    /** thighs */
    float ThighLength;
    float ThighWidth;
    float ThighHeight;
    float ThighMass;

    float ThighRelHip2_X;
    float ThighRelHip2_Y;  //set 0.005 to check the tri-angle algorithm
    float ThighRelHip2_Z;

    /** hips */
    float Hip1Axis_X ;
    float Hip1Axis_Y ;
    float Hip1Axis_Z ;

    float Hip1RelTorso_X;
    float Hip1RelTorso_Y;
    float Hip1RelTorso_Z;

    float Hip2RelHip1_X;
    float Hip2RelHip1_Y;
    float Hip2RelHip1_Z;

    /** torso */
    float TorsoLength;
    float TorsoWidth;
    float TorsoHeight;
    float TorsoMass;

    float TorsoInitX;
    float TorsoInitY;
    float TorsoInitZ;

    /** distance and vector */
    float NAO_A;
    float NAO_B;
    salt::Vector3f NAO_Dl;
    salt::Vector3f NAO_Dr;
    salt::Vector3f NAO_E;
};
#endif // KINEMATIC_H
