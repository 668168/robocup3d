#include "search.ih"

/*
 targetのobjectのうち，
 見えているもの全てのベクトルの平均の方向にカメラを向ける
*/
void Search::moveCamera(std::vector<Types::Object> target)
{
  WorldModel& wm = WorldModel::getInstance();
  double neckang, headang;
  Vector3D straight(1,0,0);
  Vector3D targetPos(0,0,0);
  double visibleObjectNum = 0;

  double neckMax=-360, neckMin=360, headMax=-360, headMin=360;

  for(int i=0; i<target.size();i++){
    if(wm.visibleObject(target.at(i))){
      Vector3D pos = wm.getObjectPosition(target.at(i)).getMu().normalize();
      targetPos += pos;
      visibleObjectNum++;
      neckang = Vector3D(pos.getX(), pos.getY(), 0).angle(straight) * 180.0 / M_PI;
      if(pos.getY() < 0)
        neckang *= -1;
      headang = Vector3D(1, 0, pos.getZ()).angle(straight) * -180.0 / M_PI;
      if(neckMax < neckang) neckMax = neckang;
      if(neckMin > neckang) neckMin = neckang;
      if(headMax < headang) headMax = headang;
      if(headMin > headang) headMin = headang;
    }
  }
  targetPos /= visibleObjectNum;

  if(neckMax - neckMin < 120 )
    neckang = (neckMax + neckMin) / 2.;
  else{
    neckang =
      Vector3D(targetPos.getX(), targetPos.getY(), 0).angle(straight)
      / M_PI * 180.0;
    if(targetPos.getY() < 0)
      neckang *= -1;
  }
  if(headMax - headMin < 120 )
    headang = (headMax + headMin) / 2.;
  else{
    headang =
      Vector3D(1, 0, targetPos.getZ()).angle(straight)
      / M_PI * 180.0 / 3.0;
    headang *= -1;
  }
  wm.setNeckDir(neckang, headang);
}

void Search::moveCamera(Types::Object target)
{
  std::vector<Types::Object> tgt;
  tgt.push_back(target);

  moveCamera(tgt);
}

// 基本的にmoveCameraと同じ．ボールが見えない場合，前見えた方にカメラを向ける
void Search::moveCameraToBall(std::vector<Types::Object> targets)
{

  WorldModel& wm = WorldModel::getInstance();
  double neckang, headang;
  Vector3D straight(1,0,0);
  Vector3D targetPos(0,0,0);
  double visibleObjectNum = 0;

  // 見えてるObject全てを視界に入れるために要求される首の角度(degree)
  double neckMax=-360, neckMin=360, headMax=-360, headMin=360;

  targets.push_back(Types::BALL);

  for(int i=0; i<targets.size();i++){
    if(wm.visibleObject(targets.at(i)) || (Types::Object)i == Types::BALL)
    {
      Vector3D pos = wm.getObjectPosition(targets.at(i)).getMu().normalize();
      targetPos += pos;
      visibleObjectNum++;
      neckang = Vector3D(pos.getX(), pos.getY(), 0).angle(straight) * 180.0 / M_PI;
      if(pos.getY() < 0)
        neckang *= -1;
      headang = Vector3D(1, 0, pos.getZ()).angle(straight) * -180.0 / M_PI;
      if(neckMax < neckang) neckMax = neckang;
      if(neckMin > neckang) neckMin = neckang;
      if(headMax < headang) headMax = headang;
      if(headMin > headang) headMin = headang;
    }
  }
  targetPos /= visibleObjectNum;

  if(neckMax - neckMin < 120 )
    neckang = (neckMax + neckMin) / 2.;
  else{
    neckang =
      Vector3D(targetPos.getX(), targetPos.getY(), 0).angle(straight)
      / M_PI * 180.0;
    if(targetPos.getY() < 0)
      neckang *= -1;
  }
  if(headMax - headMin < 120 )
    headang = (headMax + headMin) / 2.;
  else{
    headang =
      Vector3D(1, 0, targetPos.getZ()).angle(straight)
      / M_PI * 180.0 / 3.0;
    headang *= -1;
  }
  wm.setNeckDir(neckang, headang);

}
