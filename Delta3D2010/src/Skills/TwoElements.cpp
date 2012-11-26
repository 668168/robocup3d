
#include "TwoElements.h"
 
TwoElements::TwoElements():point(T)
{
	T[0]=0;
	T[1]=0;
}

TwoElements& TwoElements::instance()
{
	static TwoElements sTwoElements;
	return sTwoElements;
} 

TwoElements::~TwoElements()
{
}

float TwoElements::Befor(){
    if(point != T)
       return *(point-1);
    else
       return *(T+1);
}

float* TwoElements::Location(){
    return   point;
}

void TwoElements::Add(float item){
    if(point!= T+1){
        point ++;
       *(point) = item;
    }else {
    point = T;
    *point = item;
    }

}
