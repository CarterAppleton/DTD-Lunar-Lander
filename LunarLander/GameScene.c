//
//  GameScene.c
//  LunarLander
//
//  Created by Carter Appleton on 4/13/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#include "GameScene.h"

#include <stdio.h>
#include <stdlib.h>

#include "lander.h"
#include "chipmunk.h"
#include "array.h"
#include "constants.h"
#include "drawing.h"

typedef struct gameScene
{
    cpSpace* space;
    Array height_map;
    Lander lander;
    int num_options;
} gameScene;


typedef gameScene* GameScene;

static GameScene scene;

void landerHitMoon(cpArbiter *arb, cpSpace *space, void *data)
{
    cpVect impulse = cpArbiterTotalImpulse(arb);
    
    cpFloat force = cpvlength(impulse);
    
    printf("IMPULSE: %f \n",force);
}

static void
addHeightMap(Array h, int totalWidth)
{
    cpFloat stepWidth = ((cpFloat)totalWidth) / ((cpFloat)h->count-1);
    
    cpBody *staticBody = scene->space->staticBody;
    cpShape *shape;
    
    for (int x = 0; x < h->count-1; x++)
    {
        int heightC = arrayValueAtIndex(x, h);
        int heightN = arrayValueAtIndex(x+1, h);
        
        shape = cpSpaceAddShape(scene->space, cpSegmentShapeNew(staticBody, cpv(x*stepWidth,heightC), cpv((x+1)*stepWidth,heightN), 0.0f));
        cpShapeSetCollisionType(shape, MOON_LAND_TAG);
        shape->e = 0.0f; shape->u = 0.5f;
    }
}

void game_scene_init()
{
    scene = malloc(sizeof(struct gameScene));
    
    //Init physics
    cpInitChipmunk();
    
    scene->space = cpSpaceNew();
    cpSpaceSetIterations(scene->space, 20);
    cpSpaceSetGravity(scene->space, cpv(0, -100));
    
    cpSpaceAddCollisionHandler(scene->space, LANDER_TAG, MOON_LAND_TAG, NULL, NULL, landerHitMoon, NULL, NULL);
    
    //Init heightmap
    scene->height_map = arrayMake(5);
    
    arrayAdd(40, scene->height_map);
    arrayAdd(50, scene->height_map);
    arrayAdd(80, scene->height_map);
    arrayAdd(10, scene->height_map);
    arrayAdd(90, scene->height_map);
    arrayAdd(90, scene->height_map);
    arrayAdd(50, scene->height_map);
    arrayAdd(20, scene->height_map);
    arrayAdd(30, scene->height_map);
    arrayAdd(40, scene->height_map);
    arrayAdd(20, scene->height_map);
    arrayAdd(10, scene->height_map);
    arrayAdd(60, scene->height_map);
    arrayAdd(40, scene->height_map);
    arrayAdd(30, scene->height_map);
    arrayAdd(80, scene->height_map);
    arrayAdd(10, scene->height_map);
    arrayAdd(90, scene->height_map);
    arrayAdd(90, scene->height_map);
    arrayAdd(20, scene->height_map);
    arrayAdd(20, scene->height_map);
    arrayAdd(30, scene->height_map);
    arrayAdd(60, scene->height_map);
    arrayAdd(20, scene->height_map);
    arrayAdd(10, scene->height_map);
    arrayAdd(50, scene->height_map);
    
    addHeightMap(scene->height_map, DEFAULT_WIDTH);
    
    scene->lander = landerMake(cpv(200, 200), 1.665, 0, 500, scene->space);
    
}

void game_scene_update()
{
    if(!scene)
        game_scene_init();
    
    landerUpdate(scene->lander);
	cpSpaceStep(scene->space, 1.0f/60.0f);
    
}

void game_scene_display()
{
    if(!scene)
        game_scene_init();
    
    landerDraw(scene->lander);
    
    char velocity[100];
    char force[100];
    char orientation[100];
    
    sprintf(velocity, "Velocity-Y: %f",landerSpeed(scene->lander));
    sprintf(force, "Force-Y: %f",scene->lander->thrust);
    sprintf(orientation, "Rotation: %d",scene->lander->orientation);
    
    Color c;
    if(landerSpeed(scene->lander) < -10)
        c = RGBAColor(1.0, 0.0, 0.0, 1.0);
    else
        c = RGBAColor(1.0, 1.0, 1.0, 1.0);
    
	drawString(0, DEFAULT_HEIGHT-50, velocity, c); 
    drawString(0, DEFAULT_HEIGHT-40, force, RGBAColor(1.0, 1.0, 1.0, 1.0)); 
    drawString(0, DEFAULT_HEIGHT-30, orientation, RGBAColor(1.0, 1.0, 1.0, 1.0)); 
    
    drawHeightMap(scene->height_map, DEFAULT_WIDTH);
}

void game_scene_keyboard_pressed(char c)
{
    switch (c) {
        case 'r':
            cpBodySetPos(scene->lander->body, cpv(200, 200));
            cpBodySetForce(scene->lander->body, cpvzero);
            cpBodySetVel(scene->lander->body, cpvzero);
            cpBodySetAngVel(scene->lander->body, 0);
            scene->lander->orientation = 0;
            break;
        case 'w':
            landerAdjustThrust(0.025, scene->lander);
            break;
        case 's':
            landerAdjustThrust(-0.025, scene->lander);
            break;
        case 'a':
            landerRotate(1, scene->lander);
            break;
        case 'd':
            landerRotate(-1, scene->lander);
            break;
        default:
            break;
    }
}

void game_scene_keyboard_released(char c)
{
    
}