#ifndef _BATS_LOCALIZER_HH_
#define _BATS_LOCALIZER_HH_

//#include <Eigen/Core>
//#include <Eigen/Geometry>

#include "vector3.hh"
#include "matrix9.hh"

#include "normaldistribution3d.hh"
#include "types.hh"

#include "singleton.hh"

namespace bats
{
  struct ObjectInfo : RefAble
  {
    NormalDistribution3D locVelLocal;
    NormalDistribution3D locVelGlobal;
    bool alive;
    bool visible;
  };
  
  struct PlayerInfo : ObjectInfo
  {
    Vector3D locLArmLocal;
    Vector3D locRArmLocal;
    Vector3D locLFootLocal;
    Vector3D locRFootLocal;

    Vector3D locLArmGlobal;
    Vector3D locRArmGlobal;
    Vector3D locLFootGlobal;
    Vector3D locRFootGlobal;
    
    bool lArmVisible;
    bool rArmVisible;
    bool lFootVisible;
    bool rFootVisible;
  };
  /** The localizer interface

    Localization is done using a class with an interface compatible with this
    one. The specialized version (like SimpleLocalizer) should be placed in the
    Singleton of the Localizer type, which then returns the interface compatible
    specialized class.

    Example: SLocalizer::initialize<SimpleLocalizer>();

    Localizers (and other modules of the library) consider three coordinate
    frames:
    - Agent frame. The origin is at the center of the agent's torso. The
    positive x-axis points to his right (left shoulder to right shoulder), the
    positive y-axis to his front and the positive z-axis upwards (from center of
    torso to head). This is the frame used by AgentModel.
    - Local frame. The origin is at the center of the agent's torso. The
    positive x-axis points to his right, parallel to the field, the positive
    y-axis points to his front, parallel to the field and the positive z-axis
    points upwards, perpendicular to the field. So, this frame is sensitive to
    rotation in the plane parallel to the field, but not to rotation in a
    vertical plane. This frame is most useful for determining positions and
    directions relative to the agent.
    - Global frame. The origin is at the center of the field. The positive
    x-axis points from the origin to the opponent's goal, the positive y-axis to
    the left when facing the opponent's goal and the positive z-axis points
    upward, perpendicular to the field.
  */
  class Localizer
  {
    public:
      /** Called to initialize the Localizer */
      virtual void init() = 0;

      /** Called when an update needs to be done */
      virtual void update() = 0;

      rf<ObjectInfo> getObjectInfo(Types::Object object) const { return d_objectInfos[object]; }
      
      bool alive(Types::Object object) const { return d_objectInfos[object]->alive; }

      /** Return whether the  object is visible */
      bool visible(Types::Object object) const { return d_objectInfos[object]->visible; }

      NormalDistribution3D getLocVelLocal(Types::Object object) const { return d_objectInfos[object]->locVelLocal; }
      
      NormalDistribution3D getLocVelGlobal(Types::Object object) const { return d_objectInfos[object]->locVelGlobal; }
      
      /** Get the location estimate of an object in the local frame */
      virtual NormalDistribution3D getLocationLocal(Types::Object object) = 0;
      /** Get the velocity estimate of an object in the local frame */
      virtual NormalDistribution3D getVelocityLocal(Types::Object object) = 0;

      /** Get the location estimate of an object in the global frame */
      virtual NormalDistribution3D getLocationGlobal(Types::Object object) = 0;
      /** Get the velocity estimate of an object in the global frame */
      virtual NormalDistribution3D getVelocityGlobal(Types::Object object) = 0;


      /** Get the local transformation matrix
       *
       * This matrix describes the transformation from the local frame to the
         agent frame, i.e. the axes of the agent frame in terms of the local
         frame. Multiplication of a vector in the agent frame with this matrix
         results in the location of that vector with respect to the local frame.
       */
      virtual Matrix9D getLocalTransformation() const = 0;

      /** Get the global transformation matrix
       *
       * This matrix describes the transformation from the global frame to the
         agent frame, i.e. the axes of the agent frame in terms of the global
         frame. Multiplication of a vector in the agent frame with this matrix
         results in the location of that vector with respect to the global
         frame.
       */
      virtual Matrix9D getGlobalTransformation() const = 0;


      /*
        Function to tell the localizer that we know our position for sure,
        for example after we have beamed to somewhere.
      */
      virtual void setGlobalPosition(Vector3D &position) { };

    
    protected:
      rf<ObjectInfo> d_objectInfos[Types::NOBJECTS];
  };

  typedef Singleton<Localizer> SLocalizer;

}

#endif

