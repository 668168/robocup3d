/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "FallDownRecognition.h"

FallDownRecognition::FallDownRecognition():
endStartCycle(10000),firstStartCycle(10000),timeLive(1000),flag(0)
{
    forceStop = false;
    Qu = new Queue();
    QuFront_back = new Queue();
    QuSideLeft_right = new Queue();
    QuFRP = new Queue();
    p  = new Perceptors();
}


FallDownRecognition::~FallDownRecognition()
{
}

FallDownRecognition& FallDownRecognition::instance()
{
    static FallDownRecognition sFallDownRecognition;
    return sFallDownRecognition;
}


void        FallDownRecognition::setDataToTheQueue ( int cycle )
{
    if ( controlcycle!=cycle )
    {
        Qu->removedQueue ( GeyroMeasure() );
        QuFront_back->removedQueue ( getGeyro().x );
        QuSideLeft_right->removedQueue ( getGeyro().y );
        QuFRP->removedQueue ( WorldModel::instance().getFRP ( FID_RF ).f_z + WorldModel::instance().getFRP ( FID_LF ).f_z );

    }
    controlcycle=cycle;
}

GyrSense    FallDownRecognition::getGeyro()
{
    return       WorldModel::i().getGyr();

}

float        FallDownRecognition::GeyroMeasure()
{
    float temp;
    temp = sqrt ( pow ( getGeyro().x,2 ) +pow ( getGeyro().y,2 ) +pow ( getGeyro().y,2 ) );
    return temp;
}

float         FallDownRecognition::StandardDeviance()
{
    float temp;
    temp = abs ( abs ( Qu->AvrageQueue()-Qu->MaxQueue() )-abs ( Qu->AvrageQueue()-Qu->MinQuue() ) );
//std::cout<< '\n' <<'\n' << temp <<'\n'<<'\n';
    return temp;
}

float        FallDownRecognition::XGeyroAvrage()
{
    float tepm;
    tepm = QuFront_back->AvrageQueue();
    return tepm;
}

float        FallDownRecognition::YGeyroAvrage()
{
    float temp;
    temp = QuSideLeft_right->AvrageQueue();
    return temp;
}

float        FallDownRecognition::FRPAvrage()
{
    float temp;
    temp = QuFRP->AvrageQueue();

    return temp;
}

float         FallDownRecognition::CalculateDeviance ( float   P )
{
    float temp,Bound ;
    if ( P > 100 ) P = 100;
    if ( P < 0 )   P = 0;
    Bound = abs ( FDR_BALANCEFACTOR_START - FDR_BALANCEFACTOR_END );
    temp = Bound/100;
    temp = ( P*temp ) + FDR_BALANCEFACTOR_START;
    return temp;
}

bool    FallDownRecognition::isFallDown ( int cyc, float
                                        Percent )
{
 if (!forceStop)
 {float temp1,temp2;
    setDataToTheQueue ( cyc );
    temp1 = StandardDeviance();
    temp2 = CalculateDeviance ( Percent );
    if ( FRPAvrage() > FDR_FRPBALANCEMAX )
            return  false;
        else
             return  true;
 }else
     return !forceStop;
}

EFallDir    FallDownRecognition::SideFallDown ( int cyc )
{
    float temp;
    setDataToTheQueue ( cyc );
    temp = StandardDeviance();
    if ( abs ( XGeyroAvrage() ) >abs ( YGeyroAvrage() ) && XGeyroAvrage() > 0 )
        return  FALL_BACK;
    else if ( abs ( XGeyroAvrage() ) >abs ( YGeyroAvrage() ) && XGeyroAvrage() < 0 )
        return  FALL_FRONT;
    else if ( abs ( XGeyroAvrage() ) <abs ( YGeyroAvrage() ) && XGeyroAvrage() > 0 )
        return  FALL_LEFT;
    else
        return  FALL_RIGHT;
}
