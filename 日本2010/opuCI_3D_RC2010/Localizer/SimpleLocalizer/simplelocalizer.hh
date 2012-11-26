#ifndef _BATS_SIMPLELOCALIZER_HH_
#define _BATS_SIMPLELOCALIZER_HH_

#include "localizer.hh"
#include "normaldistribution3d.hh"

namespace bats
{

  class SimpleLocalizer : public Localizer
  {
	  friend class Singleton<Localizer>;

      Matrix9D d_localTransform;
      Matrix9D d_globalTransform;
      
      NormalDistribution3D d_locationsRaw[Types::NOBJECTS];
      NormalDistribution3D d_locationsLocal[Types::NOBJECTS];
      NormalDistribution3D d_locationsGlobal[Types::NOBJECTS];
      
      NormalDistribution3D d_velocitiesLocal[Types::NOBJECTS];
      NormalDistribution3D d_velocitiesGlobal[Types::NOBJECTS];
      
      SimpleLocalizer();
      SimpleLocalizer(SimpleLocalizer const& other); //NI
      SimpleLocalizer& operator=(SimpleLocalizer const* other); //NI

      static SimpleLocalizer *s_instance;

    public:
      virtual void init() {}
      
      virtual void update();

      virtual bool alive(Types::Object object) const {return true;}

      /** Return whether the  object is visible */
      virtual bool visible(Types::Object object) const {return true;}

      /** Get the last localization time */
      virtual double time() {return 0;}
      /** Get the delay seen in the object observation */
      virtual double perceptionDelay (Types::Object object) {return 0;}
      /** Get the last update of the object */
      virtual double getObjectLastUpdate (Types::Object object) {return 0;}

      /** Return whether the information about the object is reliable */
      virtual bool isReliableLocal(Types::Object object) const {return true;}
      
      /** Return whether the information about the object is reliable */
      virtual bool isReliableGlobal(Types::Object object) const {return true;}

      virtual Vector3D getObjectMovement (Types::Object object) {return Vector3D();}
      
      virtual NormalDistribution3D getLocationLocal(Types::Object object) { return d_locationsLocal[object]; }
      virtual NormalDistribution3D getVelocityLocal(Types::Object object) { return d_velocitiesLocal[object]; }

      virtual NormalDistribution3D getLocationGlobal(Types::Object object) { return d_locationsGlobal[object]; }
      virtual NormalDistribution3D getVelocityGlobal(Types::Object object) { return d_velocitiesGlobal[object]; }
      

      virtual Matrix9D getLocalTransformation() const { return d_localTransform; }
      virtual Matrix9D getGlobalTransformation() const { return d_globalTransform; }

     //static void initialize();
      //static SimpleLocalizer &getInstance();
  };
};

#endif

