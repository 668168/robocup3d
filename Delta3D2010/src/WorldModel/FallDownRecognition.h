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

#ifndef FALLDOWNRECOGNITION_H
#define FALLDOWNRECOGNITION_H

#include <iostream>
#include <math.h>
#include "../Utility/Queue.h"
#include "../Perceptors/Perceptors.h"
#include "WorldModel.h"

class FallDownRecognition
{
public:
    FallDownRecognition();

    ~FallDownRecognition();

    static FallDownRecognition& instance();

    void        setDataToTheQueue(int cycle);

    GyrSense    getGeyro();

    float       GeyroMeasure();

    float       StandardDeviance();

    bool        isFallDown(int cyc, float Percent);

    float       YGeyroAvrage();

    float       XGeyroAvrage();

    EFallDir    SideFallDown(int cyc);

    float       FRPAvrage();

    float       CalculateDeviance(float   P);
    
    int         endStartCycle;
    
    int         firstStartCycle;
    
    int         timeLive;
    
    int         flag;
    
    bool        forceStop;
    
    


private:

    Queue       *Qu;

    Queue       *QuFront_back;

    Queue       *QuSideLeft_right;

    Queue       *QuFRP;

    GyrSense    mGyrSense;

    int         controlcycle;	

    Perceptors  *p;


};

#endif // FALLDOWNRECOGNITION_H