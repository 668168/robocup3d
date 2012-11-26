#include "worldmodel.ih"

static double border = 70.0;

bool WorldModel::onMyBelly()
{
  /*
    bool onmybelly =  d_footForces[0].getY() < -8 
    && d_footForces[1].getY() < -8
    && d_gyro.length() < 2.0;
    
    //    if(onmybelly)
    //std::cout << "\033[32m ON MY BELLY \033[0m" << std::endl;

    return onmybelly;
//    return maybeDown && d_gyro.length() < 3.0;
*/
  return d_fieldNormal.getY() < sin(-border/180.0*M_PI);//-0.7 && d_gyro.length() < 2.0;
}


bool WorldModel::onMyBack()
{ 
  /*
    bool onmyback =  d_footForces[0].getY() > 8 
    && d_footForces[1].getY() > 8 
    && d_gyro.length() < 2.0;

    //    if(onmyback)
    // std::cout << "\033[1;31m ON MY BACK \033[0m" << std::endl;
    return onmyback;
  */
  return d_fieldNormal.getY() > sin(border/180.0*M_PI);// && d_gyro.length() < 2.0;
}


bool WorldModel::onMySide()
{

  return fabs(d_fieldNormal.getX()) > sin(border/180.0*M_PI);// && d_gyro.length() < 1.0;
}

