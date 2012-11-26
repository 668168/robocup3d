#include "WorldModel.h"

#include "../Behavior/BhvBasicStandup.h"
#include <assert.h>



/**get Real Position. It just works for Flags **/
Vector3f WorldModel::getRealPos(const EVisionObject flag )const
{
    if(flag >= FLAG_1_L && flag <= GOAL_2_R)
    {
      TObjectToSenseMap::const_iterator iter =  mObjectToSenseMap.find(flag);
    return (Vector3f((*iter).second.realPos));
    }
    ////std::cout <<"Invalid Flag!"<<std::endl;
    return (Vector3f(-1000.0,-1000.0,-1000.0));
}

///*******************************localize**************************

void WorldModel::Realpos()
{
   ETeamSide side=getTeamSide();
//   std::cout<<"team side ="<<side<<std::endl;
   int i,j;
   int array[8]={0};
   for (int i=FLAG_1_L  ; i<=GOAL_2_R ; ++i)
   {
      EVisionObject tmpvision = EVisionObject(i);
      if( 10 <=  getConfidence(mObjectToSenseMap[tmpvision] ) )
      {
          array[i]=1;
          //std::cout<<"flag "<<i<<std::endl;
      }
    }
    seTxy(array);
    mMyPos = Vector3f(x,y, Mathematics::Rad2Deg(  Mathematics::normalizeAngle(  Mathematics::Deg2Rad(z) )     )      );
}


/**  set global X , Y  **/
void WorldModel::seTxy(int array[])
{ 
       int i=-1 ,j=-1 ;
       Vector3f vector; 
       double tmpx, tmpy,tmpx1,tmpy1 ,tmpz,tmptheta=0,c_length;
       std::vector<double> all(13);
      if(array[0]==1 && array[1]==1)
       {
         i=0; j=1;
         tmptheta=seTij(i,j);
         

          c_length=length(mObjectToSenseMap[FLAG_1_R].realPos,mObjectToSenseMap[FLAG_1_L].realPos);
///          std::cout <<"c_lentgh####"<<c_length<<std::endl;
          all=seTreal(FieldLength,"c");


         tmpy=seTh(FieldLength,tmptheta);
         tmpx=seTx("i",tmpy);
         tmpx1=seTx("j",tmpy);
         if(mObjectToSenseMap[tmpvisionj].distance-mObjectToSenseMap[tmpvisioni].distance>(0))
          {
               
//             x=(FieldLength / 2-tmpx1);
//             y=FieldWidth/2-seTy("j",tmpx1);
                tmpz=all[5]*(-1);
                z=tmpz-all[11]+90;
                x=FieldLength / 2-all[7] ;
                y=FieldWidth/2-all[3];
           }
         else
          {
//             x=tmpx-FieldLength / 2;
//             y=FieldWidth/2-seTy("i",tmpx);
               z=all[4]-all[9]+90;
               x=all[6]-FieldLength / 2;
               y=FieldWidth/2-all[3];
          }
         z=z-getHJoint(JID_HEAD_1).angle;
         std::cout<<"0,1###"<<"x= "<<x<<std::endl<<"y=" <<y<< std::endl;
         std::cout<<"0,1###"<<"z= "<<z<<"tmpz###"<<tmpz<<"theta###"<<mObjectToSenseMap[tmpvisioni].theta<< std::endl; 
       }


     else if(array[2]==1 && array[3]==1)
       {
         i=2; j=3; 
         tmptheta=seTij(i,j);
            
          c_length=length(mObjectToSenseMap[FLAG_2_R].realPos,mObjectToSenseMap[FLAG_2_L].realPos);
          std::cout <<"c_lentgh####"<<c_length<<std::endl;
          all=seTreal(FieldLength,"c");
            
            tmpy=seTh(FieldLength,tmptheta);
//          tmpy1=seTy(
         tmpx=seTx("i",tmpy);
         tmpx1=seTx("j",tmpy);
        if(mObjectToSenseMap[tmpvisionj].distance-mObjectToSenseMap[tmpvisioni].distance>(0))
          {
               
//             x=(FieldLength / 2-tmpx1);
//             y=FieldWidth/2-seTy("j",tmpx1);
                tmpz=all[5];
                z=tmpz-all[11]+270;
                x=FieldLength/2-all[7];
                y=all[3]-FieldWidth / 2;
           }
         else
          {
//             x=tmpx-FieldLength / 2;
//             y=FieldWidth/2-seTy("i",tmpx);
               tmpz=all[4]*(-1);
               z=tmpz-all[9]+270;
               x=all[6]-FieldLength/ 2;
               y=all[3]-FieldWidth/ 2;
          }
       
        // x=((FieldLength / 2-tmpx1)+(tmpx-FieldLength / 2))/2;
         //y=tmpy-FieldWidth/2;
         z=z-getHJoint(JID_HEAD_1).angle;
         std::cout<<"2,3###"<<"x= "<<x<<std::endl<<"y=" <<y<<sinDeg(tmptheta)<< std::endl<<"H#####"<<tmpy<<std::endl;
         //tmpz=atan2Deg(tmpx1,tmpy);
         //z=tmpz-mObjectToSenseMap[tmpvisionj].theta+270;
         std::cout<<"2,3###"<<"z= "<<z<<"tmpz###"<<tmpz<<"theta###"<<mObjectToSenseMap[tmpvisionj].theta<< std::endl; 
       }
   
     else if(array[0]==1 && array[2]==1)
       {
         i=0 ; j=2;
         tmptheta=seTij(i,j);
        
          c_length=length(mObjectToSenseMap[FLAG_1_R].realPos,mObjectToSenseMap[FLAG_2_R].realPos);
///          std::cout <<"c_lentgh####"<<c_length<<std::endl;
          all=seTreal(FieldWidth,"c");

         tmpx=seTh(FieldWidth,tmptheta);
         tmpy=seTx("j",tmpx);
         tmpy1=seTx("i",tmpx);
        if (mObjectToSenseMap[tmpvisioni].distance-mObjectToSenseMap[tmpvisionj].distance>(0))
          {
            y=all[7]-FieldWidth/2;
            z=all[5]-all[11];
            x=all[3]-FieldLength / 2;
          }
        else
          {
            y=all[6]*(-1)+FieldWidth/2;
            tmpz=all[4]*(-1);
            z=tmpz-all[9];
            x=all[3]-FieldLength / 2;
            
          }

         z=180+z;
         z=z-getHJoint(JID_HEAD_1).angle;
         std::cout<<"0,2###"<<"x= "<<x<<std::endl<<"y=" <<y<< std::endl;
         std::cout<<"0,2###"<<"z= "<<z<< std::endl;
        }
    
      else if(array[1]==1 && array[3]==1)
       {
          i=1 ; j=3;
          tmptheta=seTij(i,j);
          
          c_length=length(mObjectToSenseMap[FLAG_1_R].realPos,mObjectToSenseMap[FLAG_2_R].realPos);
///          std::cout <<"c_lentgh####"<<c_length<<std::endl;
          all=seTreal(FieldWidth,"c");
          
          tmpx=seTh(FieldWidth,tmptheta);
          tmpy=seTx("j",tmpx);
          tmpy1=seTx("i",tmpx);
          x=FieldLength / 2-all[3]; 
          if(mObjectToSenseMap[tmpvisioni].distance-mObjectToSenseMap[tmpvisionj].distance>(0))
            {
              y=all[7]-FieldWidth/2;
              tmpz=all[5]*(-1);
              z= tmpz-all[11];
              x=FieldLength / 2-all[3];
///             cout<<"ZZZ"<<z<<std::endl;
             }
           else
             {
              y=all[6]*(-1)+FieldWidth/2;
              x=FieldLength / 2-all[3];
              z=all[4]-all[9];
///              cout<<"ZZ"<<z<<std::endl;
             }
//          tmpz=atan2Deg(tmpy1,tmpx);
//               z=tmpz-mObjectToSenseMap[tmpvisioni].theta;
        z=z-getHJoint(JID_HEAD_1).angle;
        if(z<0)
        z+=360;
//         for (int i=0; i<=12;i++)
//          std::cout<<std::endl<<i<<"####"<<all[i]<<std::endl;
        std::cout<<"1,3###"<<"x= "<<x<<std::endl<<"y=" <<y<<sinDeg(tmptheta)<< std::endl;
        std::cout<<"1,3###"<<"z= "<<z<<"tmpz###"<<tmpz<<"theta###"<<mObjectToSenseMap[tmpvisioni].theta<< std::endl;
       }
     
     else if(array[0]==1 && array[4]==1)
       {
         i=0 ; j=4 ;
         tmptheta=seTij(i,j);
        
          c_length=length(mObjectToSenseMap[FLAG_1_L].realPos,mObjectToSenseMap[GOAL_1_L].realPos);
///          std::cout <<"c_lentgh####"<<c_length<<std::endl;
          all=seTreal(FieldWidth/2-GoalWidth/2,"i");

         tmpx=seTh((FieldWidth/2.0f-GoalWidth/2.0f),tmptheta);
         tmpy=seTx("i",tmpx);
         tmpy1=seTx("j",tmpx);
         if(mObjectToSenseMap[tmpvisioni].distance-mObjectToSenseMap[tmpvisionj].distance>(-.5))
           {
             x=all[3]-FieldLength/2;
             y=FieldWidth/2-all[6];
             tmpz=all[4]*(-1);
             z=tmpz-all[9];
             z=180+z;
           }
         else
           {
              x=all[3]-FieldLength/2;
              y=all[7]+(GoalWidth/2);
              tmpz=all[5]-all[11];
              z=180+tmpz;
           }
           z=z-getHJoint(JID_HEAD_1).angle;
         std::cout<<"0,4###"<<"x= "<<x<<std::endl<<"y=" <<y<<sinDeg(tmptheta)<< std::endl;
         std::cout<<"0,4###"<<"z= "<<z<<"tmpz###"<<tmpz<<"theta###"<<mObjectToSenseMap[tmpvisioni].theta<< std::endl;
       }
      else if(array[2]==1 && array[6]==1)
       {
         i=2 ; j=6 ;
         tmptheta=seTij(i,j);
         
          c_length=length(mObjectToSenseMap[FLAG_1_L].realPos,mObjectToSenseMap[GOAL_1_L].realPos);
///          std::cout <<"c_lentgh####"<<c_length<<std::endl;
          all=seTreal(FieldWidth/2-GoalWidth/2,"i");

         tmpx=seTh((FieldWidth/2.0f-GoalWidth/2.0f),tmptheta);
         tmpy=seTx("i",tmpx);
         tmpy1=seTx("j",tmpx);
         if(mObjectToSenseMap[tmpvisioni].distance-mObjectToSenseMap[tmpvisionj].distance>(-.5))
           {
              x=all[3]-FieldLength / 2;
              y=all[6]-FieldWidth/2;
              z=180+all[4]-all[9];
            }
         else
            {
              
              x=all[3]-FieldLength / 2;
              y=all[7]*(-1)+(-GoalWidth/2);
              tmpz=all[5]*(-1);
              z=180+tmpz-all[11];
            }
         z=z-getHJoint(JID_HEAD_1).angle;
         std::cout<<"2,6###"<<"x= "<<x<<std::endl<<"y=" <<y<<sinDeg(tmptheta)<< std::endl;
         std::cout<<"2,6###"<<"z= "<<z<<"tmpz###"<<tmpz<<"theta###"<<mObjectToSenseMap[tmpvisioni].theta<< std::endl;

       }

    else if(array[1]==1 && array[5]==1)
       {
          i=1 ; j=5;
          tmptheta=seTij(i,j);
          
         c_length=length(mObjectToSenseMap[FLAG_1_L].realPos,mObjectToSenseMap[GOAL_1_L].realPos);
///          std::cout <<"c_lentgh####"<<c_length<<std::endl;
          all=seTreal(FieldWidth/2-GoalWidth/2,"i");

          tmpx=seTh((FieldWidth/2.0f-GoalWidth/2.0f),tmptheta);
          tmpy=seTx("i",tmpx);
          tmpy1=seTx("j",tmpx);
          if(mObjectToSenseMap[tmpvisioni].distance-mObjectToSenseMap[tmpvisionj].distance>(-.5))
            {
              x=FieldLength / 2-all[3];
              y=FieldWidth/2-all[6];
             z=all[4]-all[9];
            }
          else
            {
              x=FieldLength / 2-all[3];
              y=all[7]+(GoalWidth/2);
              tmpz=all[5]*(-1);
              z=tmpz-all[11];
            }
          z=z-getHJoint(JID_HEAD_1).angle;
          if( z<0 )
          z+=360;
          std::cout<<"1,5###"<<"x= "<<x<<std::endl<<"y=" <<y<<sinDeg(tmptheta)<< std::endl;
          std::cout<<"1,5###"<<"z= "<<z<<std::endl<<"tmpz###"<<tmpz<<std::endl<<"theta###"<<mObjectToSenseMap[tmpvisioni].theta<< std::endl;
       }
      
     else if(array[3]==1 && array[7]==1)
        { i=3 ; j=7;
          tmptheta=seTij(i,j);
         
          c_length=length(mObjectToSenseMap[FLAG_1_L].realPos,mObjectToSenseMap[GOAL_1_L].realPos);
///          std::cout <<"c_lentgh####"<<c_length<<std::endl;
          all=seTreal(FieldWidth/2-GoalWidth/2,"i");
         
          tmpx=seTh((FieldWidth/2.0f-GoalWidth/2.0f),tmptheta);
          tmpy=seTx("i",tmpx);
          tmpy1=seTx("j",tmpx);
          if(mObjectToSenseMap[tmpvisioni].distance-mObjectToSenseMap[tmpvisionj].distance>(-.5))
            {
              x=FieldLength / 2-all[3];
              y=all[6]-FieldWidth/2;
              tmpz=(-1)*all[4];
              z=tmpz-all[9];
            }
          else
            {
              x=FieldLength / 2-all[7];
              y=all[7]*(-1)+(-GoalWidth/2);
              z=all[5]-all[11];
            }
          z=z-getHJoint(JID_HEAD_1).angle;
          if( z<0 )
          z+=360;
          std::cout<<"3,7###"<<"x= "<<x<<std::endl<<"y=" <<y<<sinDeg(tmptheta)<< std::endl;
          std::cout<<"3,7###"<<"z= "<<z<<"tmpz###"<<tmpz<<"theta###"<<mObjectToSenseMap[tmpvisioni].theta<< std::endl;
          }

      else if (array[4]==1 && array[6]==1)
        {
          i=4 ; j=6;
          tmptheta=seTij(i,j);
          
          c_length=length(mObjectToSenseMap[GOAL_1_L].realPos,mObjectToSenseMap[GOAL_2_L].realPos);
///          std::cout <<"c_lentgh####"<<c_length<<std::endl;
          all=seTreal(GoalWidth,"i");

          tmpx=seTh(GoalWidth,tmptheta);
          tmpy=seTx("j",tmpx);
          tmpy1=seTx("i",tmpx);
          if(mObjectToSenseMap[tmpvisionj].distance-mObjectToSenseMap[tmpvisioni].distance>(0))
           {
             y=all[7]+(-GoalWidth/2);
             tmpz=all[5];
             z=180+(tmpz-all[11]);
            }
          else
            {
             y=all[6]*(-1.0)+(GoalWidth/2);
             tmpz=all[4]*(-1);
             z=180+(tmpz-all[9]);
             }
          x=all[3]-FieldLength/2;
          z=z-getHJoint(JID_HEAD_1).angle;
          std::cout<<"4,6###"<<"x= "<<x<<std::endl<<"y=" <<y<< std::endl;
          std::cout<<"4,6###"<<"z= "<<z<<"tmpz###"<<tmpz<< std::endl;
        }
      
     else if (array[5]==1 && array[7]==1)
        {
          i=5 ; j=7;
          tmptheta=seTij(i,j);
          
          c_length=length(mObjectToSenseMap[GOAL_1_R].realPos,mObjectToSenseMap[GOAL_2_R].realPos);
///          std::cout <<"c_lentgh####"<<c_length<<std::endl;
          all=seTreal(GoalWidth,"i");

          tmpx=seTh(GoalWidth,tmptheta);
          tmpy=seTx("j",tmpx);
          tmpy1=seTx("i",tmpx);
///          std::cout<<"tmpy && tmpy1= "<<tmpy<<" "<<tmpy1<<endl;
          if(mObjectToSenseMap[tmpvisioni].distance-mObjectToSenseMap[tmpvisionj].distance>(0))
           {
             y=all[6]*(-1)+(GoalWidth/2);
             tmpz=all[4];
             z=tmpz-all[9];
           }
          else
           {
             y=all[7]+(-GoalWidth/2);
             tmpz=all[5]*(-1);
             z=tmpz-all[11];
            }
          x=FieldLength/2-all[3];
          z=z-getHJoint(JID_HEAD_1).angle;
          if( z<0 )
          z+=360;
          std::cout<<"5,7###"<<"z= "<<z<<"tmpz###"<<tmpz<<std::endl;
          std::cout<<"5,7###"<<"x= "<<x<<std::endl<<"y=" <<y<< std::endl<<"sin####"<<sinDeg(tmptheta)<<std::endl<<"tmpx###"<<tmpx;
        }
        

}

/**set flag i & flag j **/
double WorldModel::seTij(int i, int j)
{
 double tmptheta=0;
 tmpvisioni = EVisionObject(i);
 tmpvisionj = EVisionObject(j);
// tmpvision1i=mObjectToSenseMap[tmpvisioni].distance
//  mObjectToSenseMap[tmpvisioni].distance=sqrt(pow(mObjectToSenseMap[tmpvisioni].distance,2)-pow((mObjectToSenseMap[tmpvisioni].distance*sinDeg(mObjectToSenseMap[tmpvisioni].phi)),2));
//  mObjectToSenseMap[tmpvisionj].distance=sqrt(pow(mObjectToSenseMap[tmpvisionj].distance,2)-pow((mObjectToSenseMap[tmpvisionj].distance*sinDeg(mObjectToSenseMap[tmpvisionj].phi)),2));
 tmptheta=abs(mObjectToSenseMap[tmpvisioni].theta-mObjectToSenseMap[tmpvisionj].theta);
 tmptheta=180-tmptheta;
 return tmptheta;

}

/**set X **/
double WorldModel::seTy(char c[], double tmp)
{
  if(c=="i")
    return (sqrt((mObjectToSenseMap[tmpvisioni].distance*mObjectToSenseMap[tmpvisioni].distance)-(tmp*tmp)));
  else
    return (sqrt((mObjectToSenseMap[tmpvisionj].distance*mObjectToSenseMap[tmpvisionj].distance)-(tmp*tmp)));
}

/**set hight**/
double WorldModel::seTh(double length,double tmptheta)
{
 return (sinDeg(tmptheta)*mObjectToSenseMap[tmpvisioni].distance*mObjectToSenseMap[tmpvisionj].distance/length);
}
/**set tmp Y **/
double WorldModel::seTx(char a[] , double tmpy)
{
 double tmp;
 if (a=="i")
  { 
    tmp=(mObjectToSenseMap[tmpvisioni].distance*mObjectToSenseMap[tmpvisioni].distance)-(tmpy*tmpy);
   //std::cout<<"tmpx^2###"<<tmp<<std::cout;
    if(tmp<0)
    tmp=tmp*(-1);
    return sqrt(tmp);
  }
 if (a=="j")
  { 
    tmp=(mObjectToSenseMap[tmpvisionj].distance*mObjectToSenseMap[tmpvisionj].distance)-(tmpy*tmpy);
    //std::cout<<"tmpx^2###"<<tmp<<std::cout;
   if(tmp<0)
    tmp=tmp*(-1);
    return sqrt(tmp);
  }

}
double  WorldModel::length (Vector3f a, Vector3f b)
{
  Vector3f tmp;
  tmp.x()=a.x()-b.x();
  tmp.y()=a.y()-b.y();
  tmp.z()=a.z()-b.z();
  if( tmp.x()<tmp.y() )
    return abs(tmp.y()); //sqrt(pow(tmp.y(),2)+pow(tmp.z(),2));
  else
    return abs(tmp.x()); //sqrt(pow(tmp.x(),2)+pow(tmp.z(),2)); 
}
std::vector<double> WorldModel::seTreal (double c_length, char c[])
{
  double costheta, tmpz=0.35 ,tmpz1=0.35;
  if(c=="g")
   {
    tmpz=0.45;
    tmpz1=0.45;
   }
  if(c=="i")
   tmpz1=0.45;
  std::vector <double> vector1(13);
  vector1[0]=sqrt(pow(mObjectToSenseMap[tmpvisioni].distance,2)-pow(0.8-tmpz,2));//A
  vector1[1]=sqrt(pow(mObjectToSenseMap[tmpvisionj].distance,2)-pow(0.8-tmpz1,2));//B
  costheta=(pow(vector1[0],2)+pow(vector1[1],2)-pow(c_length,2))/(2*vector1[0]*vector1[1]);//cos theta
///  std::cout<<"cost####"<<costheta<<std::endl;
  vector1[2]=acosDeg(costheta);//theta
  vector1[3]=(vector1[0]*vector1[1]*sinDeg(180-vector1[2]))/c_length;//h=x=tmpx
  vector1[4]=acosDeg(vector1[3]/vector1[0]);//theta A
  vector1[5]=acosDeg(vector1[3]/vector1[1]);//theta B
  vector1[6]=sinDeg(vector1[4])*vector1[0];//y=tmpy A
  vector1[7]=sinDeg(vector1[5])*vector1[1];//y=tmpy B
  //vector1[6]=sqrt(pow(vector1[0],2)-pow(vector1[3],2));
  //vector1[7]=sqrt(pow(vector1[1],2)-pow(vector1[3],2));
  vector1[8]=sinDeg(mObjectToSenseMap[tmpvisioni].theta)*sinDeg(90-mObjectToSenseMap[tmpvisioni].phi);
  vector1[9]=asinDeg(vector1[8]);//tmpz A
  vector1[10]=sinDeg(mObjectToSenseMap[tmpvisionj].theta)*sinDeg(90-mObjectToSenseMap[tmpvisionj].phi);
  vector1[11]=asinDeg(vector1[10]);//tmpz B
  vector1[12]=vector1[5]*(-1);
///  for (int i=0; i<=12;i++)
///          std::cout<<std::endl<<i<<"####"<<vector1[i]<<std::endl;

  return vector1;
}  
