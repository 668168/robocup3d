#include "worldmodel.ih"

Vector3D WorldModel::getObjectMovement(Types::Object obj) const
{
  //Get absolute position of both
  Matrix4D invtransform = Math::getTransform(
                                  getObject(Types::FLAG1R).position.getMu(),
                                  getObject(Types::FLAG1L).position.getMu(),
                                  getObject(Types::FLAG2L).position.getMu());
  Matrix4D transform = invtransform.inverse();
  
  //Vlag tot bal relatief huidige 
  _debugLevel4("Object position: " << getObject(obj).position.getMu());
  _debugLevel4("Object transform: " << transform);
  Vector3D pos = transform *  getObject(obj).position.getMu();
  _debugLevel3("Position: " << pos);
  
  Matrix4D prevTransform = Math::getTransform(
                                getPrevObject(Types::FLAG1R).position.getMu(),
                                getPrevObject(Types::FLAG1L).position.getMu(),
                                getPrevObject(Types::FLAG2L).position.getMu()
                                ).inverse();
  Vector3D prevPos = prevTransform * getPrevObject(obj).position.getMu();
  _debugLevel3("PrevPosition: " << prevPos);

  Vector3D movement = pos - prevPos;
  _debugLevel3("Movement: " << movement);
  
  //Remove translation because
  invtransform.set(0, 3, 0);
  invtransform.set(1, 3, 0);
  invtransform.set(2, 3, 0);
  
  return invtransform * movement; //Movement in local transform
}
