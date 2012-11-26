#include "goodpositionangle.ih"

#define RIGHT 1
#define LEFT -1
#define CENTER 10

typedef int Direction;

rf<Behavior::Goal> GoodPositionAngle::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal>   goal = new Goal();
  rf<OrNode>  dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();
  Vector3D goalPos, targetPos;
  Vector3D straight(1,0,0);
  double angle;
  Direction whichtoTurn;

  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  ballPos.setZ(0.0);

  Vector3D Goal1them = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D Goal2them = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  Vector3D Goal1us   = wm.getObjectPosition(Types::GOAL1US).getMu();
  Vector3D Goal2us   = wm.getObjectPosition(Types::GOAL2US).getMu();

  Vector3D Flag1them = wm.getObjectPosition(Types::FLAG1THEM).getMu();
  Vector3D Flag2them = wm.getObjectPosition(Types::FLAG2THEM).getMu();
  Vector3D Flag1us   = wm.getObjectPosition(Types::FLAG1US).getMu();
  Vector3D Flag2us   = wm.getObjectPosition(Types::FLAG2US).getMu();

  bool canseeGoal1 = wm.visibleObject(Types::GOAL1THEM);
  bool canseeGoal2 = wm.visibleObject(Types::GOAL2THEM);
  bool canseeFlag1 = wm.visibleObject(Types::FLAG1THEM);
  bool canseeFlag2 = wm.visibleObject(Types::FLAG2THEM);

  bool canseeGoal1us = wm.visibleObject(Types::GOAL1US);
  bool canseeGoal2us = wm.visibleObject(Types::GOAL2US);
  bool canseeFlag1us = wm.visibleObject(Types::FLAG1US);
  bool canseeFlag2us = wm.visibleObject(Types::FLAG2US);

  Vector3D toe =
    ( wm.getBodyConnectionPosition(Types::BC_RTOE)
      + wm.getBodyConnectionPosition(Types::BC_LTOE)) / 2.0;

  if(wm.allObjectPosAvailable())
  { // 全オブジェクトが推測できるとき
    goalPos = (Goal1them + Goal2them ) / 2.0 ;
    // goalPos.setZ(0.0);

    targetPos = ballPos + (ballPos - goalPos).normalize() * 0.2;
    // targetPos.setZ(0.0);

  }
  else
  { // 推測できない＝オブジェクトが一つしか見えないとき
    if(canseeFlag1 || canseeFlag1us)
    { // フラグ1が見える
      whichtoTurn = RIGHT;
    }
    else if(canseeFlag2 || canseeFlag2us)
    { // フラグ2が見える
      whichtoTurn = LEFT;
    }

    else // フィールドのオブジェが何も見えない時
    {
      if(wm.getObjectLastUpdate(Types::FLAG1US) >  wm.getObjectLastUpdate(Types::FLAG2US))
      {
        // std::cout << "GPA:: yakekusojjaaaaaaaaaaaa left@_@" << std::endl;
        whichtoTurn = LEFT;
      }
      else
      {
        // std::cout << "GPA:: yakekuso! right@_@" << std::endl;
        whichtoTurn = RIGHT;
      }

      // whichtoTurn = CENTER;
    }

    // 目的地を定める
    switch(whichtoTurn){
    case RIGHT:
      targetPos = ballPos + Vector3D(ballPos.getY(), -1 * ballPos.getX(), 0).normalize() * 0.3;
      break;
    case LEFT:
      targetPos = ballPos + Vector3D(-1 * ballPos.getY(), ballPos.getX(), 0).normalize() * 0.3;
      break;
    case CENTER:
      targetPos = Vector3D(1, 0, 0);
    default:
      break;
    }
  }

  if(step == 0) // goodposition
  {
    con->addVar("Pos", targetPos - toe);
    wm.setDebugPointWithLabel(targetPos, "GoodPosAngle_TGT");
  }
  else if (step == 1) // turn to
  {
    if(!wm.visibleObject(Types::BALL))
      angle = 90;
    else
    {
      // ballPos.setZ(0);
      // angle = getAngleWithStraight(ballPos);
      angle = getAngleWithStraight(goalPos);
    }
    con->addVar("Angle", angle, angle);
//  con->addVar("WalkTo", 0, 0);
  }

  return goal;
}










