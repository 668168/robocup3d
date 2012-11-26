/*
 *  Little Green BATS (2008), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	November 1, 2008
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _BATS_AGENTMODEL_HH_
#define _BATS_AGENTMODEL_HH_

#include <vector>
#include <map>

#include "../Matrix4D/matrix4d.hh"
#include "../Vector3/vector3.hh"
#include "../Distribution1/NormalDistribution1/normaldistribution1.hh"
#include "../RefAble/refable.hh"
#include "../Ref/rf.hh"
#include "../Singleton/singleton.hh"
#include "../Types/types.hh"
#include "../Math/math.hh"

namespace bats
{
  class XMLNode;
  
  /**
   *  The AgentModel
   */
  class AgentModel
  {
  public:
    
    struct Joint;
    
    /**
     * Body part information
     */
    struct BodyPart : public RefAble
    {
      virtual ~BodyPart() {}
      
      /// Name of body part
      std::string name;
      
      /// Transformation matrix of body part
      Matrix4D transform;

    };

    /**
     * Limb information
     */
    struct Limb : public BodyPart
    {
      /// Weight of limb
      double weight;
      
      /// Weight of limb divided by the robot's total weight
      double relativeWeight;
      
      /// Dimensions of limb
      Vector3D size;
      
      /// List of joints attached to this limb
      std::vector<rf<Joint> > joints;
    };
    
    /**
     * Joint information
     */
    struct Joint : public BodyPart
    {
      /// Axis of joint in local coordinate system
      Vector3D axis;
      
      /// Name of joint's angle perceptor as used by server
      std::string perceptor;
      
      /// Name of joint's motor as used by server
      std::string effector;
      
      /// Whether this joint is part of a universal joint
      bool universal;
      
      /// The index (0, 1) of this joint if it is part of a universal joint
      unsigned ujindex;

      /// Joint angle
      NormalDistribution1D angle;
      
      /// Body part connected by this joint
      rf<BodyPart> bodyPart;
      
      /// Anchor points of joint on body parts, relative to their center
      std::pair<Vector3D,Vector3D> anchors;
      
      /// @returns the joint's axis direction vector in the global coordinate system
      Vector3D getAxisVec() const
      {
        return transform * axis;
      }
    };

     /**
      *  Directions the agent could be falling in
      */
    enum FallDirection
    {
      NOT_FALLING = 0,
      FALL_TO_FRONT,
      FALL_TO_BACK,
      FALL_TO_LEFT,
      FALL_TO_RIGHT
    };
  
  private:

    std::string d_rsg;
    unsigned d_unum;
    
    rf<BodyPart> d_torso;
    double d_weight;
    Vector3D d_COM;
    
    Vector3D d_footForceCenters[2];
    Vector3D d_footForces[2];
    
    Vector3D d_gyro;
    
    FallDirection d_fallDirection;

    std::map<std::string, Types::Joint> d_jointNameMap;
    std::map<Types::Joint, rf<Joint> > d_joints;
    
    std::map<std::string, Types::BodyPart> d_limbNameMap;
    std::map<Types::BodyPart, rf<Limb> > d_limbs;
    

    // The modeled maximum kicking distance of the agent.
    NormalDistribution1<double> d_kickMaxDistance;

    // The modeled maximum kicking speed of the agent.
    NormalDistribution1<double> d_kickMaxSpeed;

    /** Recursive method to traverse XML to initialize body model
     *
     * @param node Current body part configuration node
     * @param playerClass The agent's player class
     * @param joint Joint current body part should be connected to
     * @returns Mass accumulated by this body part and recursive calls
     */
    double initBody(XMLNode& node, std::string playerClass, rf<Joint> joint);
    
    void updatePosture();
    void updateCOM();
    void checkDirectionOfFall();

  public:
    AgentModel();
    virtual ~AgentModel() {}
    
    /**
     * Initialize the agent's body description.
     *
     * This method uses Conf to acquire the model data.
     */
    void initBody();

    /**
     * Update the model of the agent.
     */
    void update();

    /**
     * @returns the name of the Ruby Scene Graph (rsg) file that the simulator uses for this agent.
     */
    std::string getRSG() const { return d_rsg; }
    
    /**
     * Set the uniform number of this agent. Only use before initializing the body description.
     */
    void setUnum(unsigned int const unum);
    /**
     * @returns the uniform number of this agent. This number is updated when a number is requested from and given by the simulator.
     */
    unsigned getUnum() const { return d_unum; }
    
    /**
     * Inverse of getJointName
     * @returns the translation of a joint name into a Types::Joint enumeration value, Types::NJOINTS when joint does not exist.
     */
    Types::Joint getJointID(std::string const& joint) { return d_jointNameMap.find(joint) != d_jointNameMap.end() ? d_jointNameMap[joint] : Types::NJOINTS; }
    
    /**
     * Inverse of getJointID
     * @returns the translation of a Types::Joint enumeration value into a string.
     */
    std::string getJointName(Types::Joint const id) const;
    
    /**
     * @returns the information of joint @a joint
     */
    rf<Joint> getJoint(Types::Joint joint) { return d_joints[joint]; }

    /**
     * @returns the information of body part @a part
     */
    rf<Limb> getBodyPart(Types::BodyPart part) { return d_limbs[part]; }

    /**
     * @returns the force vector measured by the Force Resistance Perceptor (FRP) of the food on side @a side
     */
    Vector3D getFootForce(Types::Side side) const { return d_footForces[side]; }
    
    /**
     * @returns the center where the force measured by the Force Resistance Perceptor (FRP) of the food on side @a side acts upon.
     */
    Vector3D getFootForceCenter(Types::Side side) const { return d_footForceCenters[side]; }
    
    /**
     * @returns the gyroscopic sensor measurements
     */
    Vector3D const &getGyro() const { return d_gyro; }
    
    /**
     * @returns the location of the Center Of Mass (COM) of the robot, relative to the center of its torso.
     */
    Vector3D const &getCOM() const { return d_COM; }
    
    /**
     *  @returns true when the agent lies on its belly.
     */
    bool onMyBelly();

    /**
     *  @returns true when the agent lies on its back.
     */
    bool onMyBack();

    /**
     *  @returns true when the agent stands on its feet.
     */ 
    bool onMyFeet();

    /**
     *  @returns true when the agent lies on one of its sides.
     */
    bool onMySide();

    /** See whether the agent is down or not
     * @param check Whether you want to check if the agent is down or if he is standing
     */
    bool isDown(bool check = true) const;
    
    /**
     * @returns FallDirection (enum) in which direction the agent is falling
     */
    FallDirection getDirectionOfFall()
    {
      return d_fallDirection;
    }
    
  };

  typedef Singleton<AgentModel> SAgentModel;
}

#endif
