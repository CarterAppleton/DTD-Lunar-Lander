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

/* The struct of the title scene.
 */

typedef struct gameScene
{
    cpSpace* space; //the physics space
    Array height_map; //the heightmap (terrain/landscape)
    Lander lander; //the lunar lander object
    float max_hit_speed;
    int game_over; //non-zero for game over, -1 for loss and 1 for win 
} gameScene;

/* Make Gamescene a pointer
 */

typedef gameScene* GameScene;

/* Create the static instance of a Game Scene
 */

static GameScene scene;

/* Callback function so we know when the lander hits the moon
 * this will let us know the force of the collision so we can
 * decide if the game is won or lost.
 */

void landerHitMoon(cpArbiter *arb, cpSpace *space, void *data)
{
    /*
    cpVect impulse = cpArbiterTotalImpulse(arb);
    cpFloat force = cpvlength(impulse);
    printf("IMPULSE: %f \n",force);
     */
    
    //Simple crash test
    if(landerSpeed(scene->lander) > scene->max_hit_speed)
        scene->game_over = -1;
    else
        scene->game_over = 1;
}

/* Add the height map to the physics space
 */

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

/* Initialize the static game scene
 */

void game_scene_init()
{
    scene = malloc(sizeof(struct gameScene));
    
    scene->max_hit_speed = 10;
    scene->game_over = 0;
    
    //Init physics
    cpInitChipmunk();
    
    scene->space = cpSpaceNew();
    cpSpaceSetIterations(scene->space, 20);
    cpSpaceSetGravity(scene->space, cpv(0, -100));
    
    //Add a handler for the function landerHitMoon so we know when the lander and landscape collide
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
    
    //Add the heightmap to the physics space
    addHeightMap(scene->height_map, DEFAULT_WIDTH);
    
    //Create the lander
    //landerMake(starting_position, starting_thrust, starting_orientation, starting_fuel, physics_space);
    scene->lander = landerMake(cpv(200, 200), 1.665, 0, 500, scene->space);
}

/* Update the game scene
 */

void game_scene_update()
{
    //If the game scene doesn't exist, create it
    if(!scene) game_scene_init();
    
    //If the game isn't over
    if(!scene->game_over)
    {
        //Update the lander
        landerUpdate(scene->lander);
        
        //Update the physics space
        cpSpaceStep(scene->space, 1.0f/60.0f);
    }
    
    //If the game is over
    else
    {
        
    }
}

/* Display the game scene
 */

void game_scene_display()
{
    //If the game scene doesn't exist, create it
    if(!scene) game_scene_init();
    
    //Draw the lander
    landerDraw(scene->lander);
    
    //Draw the information strings
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
    
    //Draw the landscape
    drawHeightMap(scene->height_map, DEFAULT_WIDTH);
}

/* Respond to a key press 
 */

void game_scene_keyboard_pressed(char c)
{
    switch (c) {
        case 'r': //restart
            cpBodySetPos(scene->lander->body, cpv(200, 200));
            cpBodySetForce(scene->lander->body, cpvzero);
            cpBodySetVel(scene->lander->body, cpvzero);
            cpBodySetAngVel(scene->lander->body, 0);
            scene->lander->orientation = 0;
            scene->game_over = 0;
            break;
        case 'w': //increase thrust
            landerAdjustThrust(0.025, scene->lander);
            break;
        case 's': //decrease thrust
            landerAdjustThrust(-0.025, scene->lander);
            break;
        case 'a': //rotate left
            landerRotate(1, scene->lander);
            break;
        case 'd': //rotate right
            landerRotate(-1, scene->lander);
            break;
        default:
            break;
    }
}

/* Respond to a key release 
 */

void game_scene_keyboard_released(char c)
{
    //do nothing
}