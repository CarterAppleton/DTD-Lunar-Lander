//
//  SceneManager.c
//  LunarLander
//
//  Created by Carter Appleton on 4/13/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#include "SceneManager.h"

#include <stdio.h>
#include <stdlib.h>

#include "TitleScene.h"
#include "GameScene.h"

/* Set the types of scenes
 */

typedef enum 
{
    title_scene = 0,
    game_scene,
} Scene;

/* The struct for the scene Manager
 * we have an int for whatever scene is being
 * displayed and an int for the total number 
 * of scenes
 */

typedef struct sceneManager
{
    Scene current_scene; //the current scene
    int num_scenes;      //the total number of scenes
    
    int total_num_highscores;
    char** high_score_holders;
    int* high_scores;
} sceneManager;

/* Make SceneManager a pointer
 */

typedef sceneManager* SceneManager;

/* Create the static instance of a Scene Manager
 */

static SceneManager scene_manager = NULL;

/* Initialize the static scene manager
 */

void scene_manager_init()
{
    scene_manager = malloc(sizeof(struct sceneManager));
    
    scene_manager->current_scene = title_scene;
    scene_manager->num_scenes = 2;
    
    scene_manager->total_num_highscores = 5;
    scene_manager->high_score_holders = malloc(sizeof(char*) * scene_manager->total_num_highscores);
    scene_manager->high_scores = calloc(scene_manager->total_num_highscores,sizeof(int));
    
    for(int i=0; i<scene_manager->total_num_highscores; i++)
    {
        scene_manager->high_scores[0] = 0;
        scene_manager->high_score_holders[i] = malloc(sizeof(char) * 3);
        for(int j=0; j<3; j++)
            scene_manager->high_score_holders[i][j] = '?';
    }
}

/* Update the scene manager struct 
 * This just forwards the update to the current scene.
 */

void scene_manager_update()
{
    //If the scene manager doesn't exist, create it
    if(!scene_manager) scene_manager_init();
    
    //Forward the update call to the current scene
    switch (scene_manager->current_scene) 
    {
        case title_scene:
            title_scene_update();
            break;
        case game_scene:
            game_scene_update();
            break;
        default:
            break;
    }
}

/* Display the scene manager struct 
 * This just forwards the display call to the current scene.
 */

void scene_manager_display()
{
    //If the scene manager doesn't exist, create it
    if(!scene_manager) scene_manager_init();
    
    //Forward the display call to the current scene
    switch (scene_manager->current_scene) 
    {
        case title_scene:
            title_scene_display();
            break;
        case game_scene:
            game_scene_display();
            break;
        default:
            break;
    }
}

/* Respond to a key press 
 * This just forwards the press to the current scene.
 */

void scene_manager_keyboard_pressed(char c)
{
    //Forward the press call to the current scene
    switch (scene_manager->current_scene) 
    {
        case title_scene:
            title_scene_keyboard_pressed(c);
            break;
        case game_scene:
            game_scene_keyboard_pressed(c);
            break;
        default:
            break;
    }
}

/* Respond to a key release 
 * This just forwards the release to the current scene.
 */

void scene_manager_keyboard_released(char c)
{
    //Forward the release call to the current scene
    switch (scene_manager->current_scene) 
    {
        case title_scene:
            title_scene_keyboard_released(c);
            break;
        case game_scene:
            game_scene_keyboard_released(c);
            break;
        default:
            break;
    }
}

/* Set the current scene 
 * This can be called by any scene because SceneManager is a 
 * static instance.
 */

void scene_manager_set_scene(int scene)
{
    //Make sure the scene is in the corrent range
    if(scene < 0 || scene >= scene_manager->num_scenes)
        return;
    
    //Change the scene
    scene_manager->current_scene = scene;
}

int scene_manager_add_highscore(int score, char* name)
{
    int i;
    
    for(int i = 0; i<scene_manager->total_num_highscores; i++)
        printf("%d, ",scene_manager->high_scores[i]);
    printf("\n");
    
    for(i=0; i<scene_manager->total_num_highscores; i++)
    {
        if(scene_manager->high_scores[i] < score)
        {
            for(int j=scene_manager->total_num_highscores-1; j>i; j--)
            {
                scene_manager->high_scores[j] = scene_manager->high_scores[j-1];

                for(int k=0; k<3; k++)
                    scene_manager->high_score_holders[j][k] = scene_manager->high_score_holders[j-1][k];
            }
            
            scene_manager->high_scores[i] = score;
            
            for(int k=0; k<3; k++)
                scene_manager->high_score_holders[i][k] = name[k];
            
            break;
        }
    }

    
    return i;
}

/* Check is high score
 */
int scene_manager_is_highscore(int score)
{
    for(int i=0; i<scene_manager->total_num_highscores; i++)
        if(scene_manager->high_scores[i] < score)
            return 1;
    
    return 0;
}

char** scene_manager_highscorers()
{
    return scene_manager->high_score_holders;
}

int* scene_manager_highscores()
{
    return scene_manager->high_scores;    
}

int scene_manager_numscores()
{
    return scene_manager->total_num_highscores;    
}
