//
//  lander.h
//  LunarLander
//
//  Created by Carter Appleton on 4/3/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#ifndef LunarLander_lander_h
#define LunarLander_lander_h

#include "chipmunk.h"

typedef struct lander
{
    cpBody* body;
    cpShape* shape;
    cpFloat thrust; // range: 0 -> 5
    int fuel;
    int orientation; // range: -3 -> 3
} lander;
typedef lander* Lander;

Lander landerMake(cpVect position, cpFloat thrust, int orientation, int fuel, cpSpace* inSpace);
void landerFree(Lander l, cpSpace* space);

void landerUpdate(Lander l);
void landerDraw(Lander l);

void landerRotate(int direction, Lander l); //-1 counterclockwise, 1 clockwise
void landerAdjustThrust(cpFloat direction, Lander l); //-1 decrease, 1 increase

cpFloat landerSpeed(Lander l);
cpVect landerPosition(Lander l);

#endif
