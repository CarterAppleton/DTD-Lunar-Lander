//
//  lander.c
//  LunarLander
//
//  Created by Carter Appleton on 4/3/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "lander.h"
#include "drawing.h"

#include "constants.h"



cpFloat radiansFromOrientation(int orientation)
{
    cpFloat radiansPerOrientation = M_PI/10/MAX_ORIENTATION;
        
    return orientation * radiansPerOrientation + M_PI/2;
}

Lander landerMake(cpVect position, cpFloat thrust, int orientation, int fuel, cpSpace* inSpace)
{
    Lander l = malloc(sizeof(struct lander));
    
    const cpFloat radius = 10.0f;
    const cpFloat mass = 1.0f;
    
    l->body = cpSpaceAddBody(inSpace, cpBodyNew(mass, cpMomentForCircle(mass, radius, 0, cpvzero)));
    cpBodySetPos(l->body, position);
    cpBodySetAngle(l->body, radiansFromOrientation(orientation));
    cpBodySetVelLimit(l->body, 20);
    
    l->shape = cpSpaceAddShape(inSpace, cpCircleShapeNew(l->body, radius/2, cpvzero));
    cpShapeSetCollisionType(l->shape, LANDER_TAG);
    cpShapeSetElasticity(l->shape, 0.0f);
    cpShapeSetFriction(l->shape, 0.5f);
    
    l->fuel = fuel;
    l->thrust = thrust;
    l->orientation = orientation;
    
    return l;
}

void landerFree(Lander l, cpSpace* space)
{
    cpSpaceRemoveBody(space, l->body);
    cpSpaceRemoveShape(space, l->shape);
    
    free(l);
}

void landerUpdate(Lander l)
{
    cpVect force = cpvmult(cpvforangle(radiansFromOrientation(l->orientation)), l->thrust);
    cpBodyApplyImpulse(l->body, force, cpvzero);
}

void landerDraw(Lander l)
{
    drawCircle(l->body->p, cpvtoangle(l->body->rot), cpCircleShapeGetRadius(l->shape), RGBAColor(0, 0, 0, 0), RGBAColor(1.0, 1.0, 1.0, 0.05));
    glColor_from_color(RGBAColor(1.0, 1.0, 1.0, 1.0));
    drawLander(l->body->p, cpvtoangle(l->body->rot), cpCircleShapeGetRadius(l->shape)*1.8, l->thrust);
}

void landerRotate(int direction, Lander l) //-1 counterclockwise, 1 clockwise
{
    if(abs(l->orientation + direction) >= MAX_ORIENTATION)
        return;
    
    l->orientation += direction;
    
    cpBodySetAngle(l->body, radiansFromOrientation(l->orientation));
}

void landerAdjustThrust(cpFloat direction, Lander l) //-1 decrease, 1 increase
{
    if(l->thrust + direction >= MAX_THRUST)
    {
        l->thrust = MAX_THRUST;
        return;
    }

    if((l->thrust + direction) < 0)
    {
        l->thrust = 0;
        return;
    }
    
    l->thrust += direction;    
}

cpFloat landerSpeed(Lander l)
{
    return l->body->v.y;
}

cpFloat landerHorizontalSpeed(Lander l)
{
    return l->body->v.x;
}

cpVect landerPosition(Lander l)
{
    return l->body->p;
}

cpFloat landerAngle(Lander l)
{
    return cpvtoangle(l->body->rot);
}

void landerSetThrust(Lander l, cpFloat thrust)
{
    l->thrust = thrust;
}
