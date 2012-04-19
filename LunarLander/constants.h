//
//  constants.h
//  LunarLander
//
//  Created by Carter Appleton on 4/4/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#ifndef LunarLander_constants_h
#define LunarLander_constants_h

//Collision Constants
#define LANDER_TAG 15
#define MOON_LAND_TAG 14
#define ASTEROID_TAG 12

//Drawing Constants
#define SLEEP_TICKS 16
#define DEFAULT_WIDTH 640.0
#define DEFAULT_HEIGHT 480.0

//Lander Constants
#define MAX_ORIENTATION 3
#define MAX_THRUST 1.8f
#define INITIAL_THRUST 1.64f
#define INITIAL_P_X DEFAULT_WIDTH/2
#define INITIAL_P_Y DEFAULT_HEIGHT+5

//World constants
#define GRAVITY -100

//Testing / Editing constants
#define DEBUG 0
#define EDIT_LANDSCAPE 0
#define DRAW_TEXTURE 0

//Landscape array
#define DEFALUT_ARRAY_LENGTH 100
static int default_array[DEFALUT_ARRAY_LENGTH] = {151,155,151,145,141,136,125,125,125,128,125,116,105,101,97,90,84,72,48,39,39,39,39,39,39,43,49,54,57,58,54,51,51,47,41,43,58,88,112,140,154,163,169,176,180,181,182,167,161,161,161,161,174,181,182,187,188,183,174,155,151,141,135,128,124,101,92,91,91,91,91,91,91,95,97,94,89,78,72,70,73,81,91,96,101,108,109,114,124,136,147,176,217,229,235,236,235,243,245,246};

#endif
