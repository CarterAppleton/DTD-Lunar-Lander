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

typedef enum 
{
    title_scene = 0,
    game_scene,
} Scene;

typedef struct sceneManager
{
    Scene current_scene;
    int num_scenes;
} sceneManager;

typedef sceneManager* SceneManager;

static SceneManager scene_manager;

void scene_manager_init()
{
    scene_manager = malloc(sizeof(struct sceneManager));
    
    scene_manager->current_scene = title_scene;
    scene_manager->num_scenes = 2;
}

void scene_manager_update()
{
    if(!scene_manager)
        scene_manager_init();
    
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

void scene_manager_display()
{
    if(!scene_manager)
        scene_manager_init();
    
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

void scene_manager_keyboard_pressed(char c)
{
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

void scene_manager_keyboard_released(char c)
{
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

void scene_manager_set_scene(int scene)
{
    if(scene < 0 || scene >= scene_manager->num_scenes)
        return;
    
    scene_manager->current_scene = scene;
}
