#include "guardgoal.ih"

void GuardGoal::update()
{
//  std::cout << " -> GuardGoal::update()" << std::endl;
  Behavior::update();

  WorldModel &wm = WorldModel::getInstance();

  Vector3D ball  = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D vBall = wm.getObjectVector(Types::BALL).getMu();

  Vector3D goal1 = wm.getObjectPosition(Types::GOAL1US).getMu();
  Vector3D goal2 = wm.getObjectPosition(Types::GOAL2US).getMu();

  Vector3D goal1t = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D goal2t = wm.getObjectPosition(Types::GOAL2THEM).getMu();

  if (goal1.getY() < goal2.getY()) {
    d_goalL = goal1;
    d_goalR = goal2;
  } else {
    d_goalL = goal2;
    d_goalR = goal1;
  }

  Vector3D goalLT, goalRT;

  if (goal1t.getY() < goal2t.getY()) {
    goalLT = goal1t;
    goalRT = goal2t;
  } else {
    goalLT = goal2t;
    goalRT = goal1t;
  }

  Vector3D vect = (goalLT - d_goalL).normalize();
  Vector3D vectH = (d_goalR - d_goalL).normalize();
  Vector3D midGoal = (d_goalL + d_goalR)/2.0;

  /*
  cerr << "a = " << d_goalL << endl;
  cerr << "|a| = " << d_goalL.normalize() << endl;
  cerr << "b = " << (d_goalL-d_goalR) << endl;
  cerr << "|b| = " << (d_goalL-d_goalR).normalize() << endl;
  cerr << "Dot = " << d_goalL.normalize().dotProduct((d_goalL-d_goalR).normalize()) << endl;

  double alpha = acos(d_goalL.normalize().dotProduct((d_goalL-d_goalR).normalize()));
  double beta  = acos(goal1t.normalize().dotProduct((goalLT-goalRT).normalize()));

  cerr << "alpha = " << alpha << ", beta = " << beta << endl;

  // Our position!
  d_ownPos = Vector3D(d_goalL.length()*sin(alpha),d_goalL.length()*cos(alpha),0.0);

  cerr << "ownpos = " << d_ownPos << endl;

  Vector3D ownPos2(goalLT.length()*sin(beta),goalLT.length()*cos(beta),0.0);

  cerr << "ownpos2 = " << ownPos2 << endl;

  if (ownPos2.length() > (d_goalL-goalLT).length()) {
    d_ownPos = -d_ownPos;
  }

  cerr << "ownpos = " << d_ownPos << endl;
  
  cerr << "fieldLength = " << (d_goalL-goalLT).length() << endl;

  cerr << "goalX = " << d_goalL.getX() << endl;

  cerr << "goalW = " << (d_goalL - d_goalR).length() << endl;

  */

  double minDist = 1000000.0;
  Types::Object minObj = Types::SELF;

  Vector3D opponent;

  // Find opponent that is closest to the ball.
  for (unsigned i = Types::OPPONENT1; i < Types::OPPONENT5; ++i) {

    if (wm.isObjectAlive((Types::Object)i)) {
      Vector3D pos = wm.getObjectPosition((Types::Object)i).getMu();

      //      cerr << "Opponent position: " << pos << endl;

      double dist = (pos - ball).length();

      if (minDist > dist) {
        minObj   = (Types::Object)i;
        minDist  = dist;
        opponent = pos;
      }
    }
  }

  // Find the vector from the opponent to the ball.
  Vector3D opBall = opponent - ball;

  //  cerr << "BALLOPLENGTH: " << opBall.length() << endl;

  if (vBall.length() > 1.5) {

    //    d_ballEndPos = (midGoal + vect*2.0) + vectH*(ball.getY() - ball.getX()/vBall.getX() * vBall.getY());

    // Calculate the position of the ball when it arrive at the goal line.
    d_ballEndPos = Vector3D(0.0, ball.getY() - ball.getX()/vBall.getX() * vBall.getY(), 0.0);

  } else if (opBall.length() < 4.5) {

    //    d_ballEndPos = (midGoal + vect*2.0) + vectH*(ball.getY() - ball.getX()/opBall.getX() * opBall.getY());

    // The position of the ball if it is kick by the opponent.
    d_ballEndPos = Vector3D(0.0, ball.getY() - ball.getX()/opBall.getX() * opBall.getY(), 0.0);

    /*
     *  This can be made more precise. Because the opponent
     *  will always have to stand a little to the right or left of the ball
     *  to kick it.
     */

    /*
    cerr << "Ball = " << ball << endl;
    cerr << "vBall = " << vBall << endl;
    cerr << "opBall = " << opBall << endl;
    cerr << "opponent = " << opponent << endl;
    cerr << "BallEndPos = " << d_ballEndPos << endl;
    */
  } else {

    // Otherwise we want to stand in the middle of the goal.
    d_ballEndPos = (midGoal + vect*2.0);
    d_ballEndPos.setZ(0.0);

    //    d_ballEndPos = -d_ownPos + Vector3D(1.0,(d_goalR.getY() - d_goalL.getY())/2.0,0);

  }

}
