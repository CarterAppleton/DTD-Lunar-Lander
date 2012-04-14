//
//  TitleScene.c
//  LunarLander
//
//  Created by Carter Appleton on 4/9/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#include "TitleScene.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SceneManager.h"
#include "drawing.h"
#include "fonts.h"

typedef struct titleScene
{
    int current_option;
    int num_options;
    int title_size;
    int options_size;
} titleScene;

typedef titleScene* TitleScene;

static TitleScene scene;

void title_scene_init()
{
    scene = (TitleScene) malloc(sizeof(struct titleScene));
    scene->current_option = 0;
    scene->num_options = 3;
    scene->title_size = 15;
    scene->options_size = 5;
}

void title_scene_update()
{
    if(!scene)
        title_scene_init();
}

void title_scene_display()
{
    if(!scene)
        title_scene_init();
    
    char* title = "Lunar Lander";
    Color c = RGBAColor(1.0, 1.0, 1.0, 1.0);
    drawString(-100, 0, title, c); 
    
    drawCAWord("lunar", scene->title_size, 130, 300);
    drawCAWord("lander", scene->title_size, 100, 200);
    
    drawCAWord("easy", scene->options_size, 150, 100);
    drawCAWord("medium", scene->options_size, 350, 100);
    drawCAWord("hard", scene->options_size, 250, 25);

    cpVect chosenRect;
    
    switch (scene->current_option) {
        case 0:
            chosenRect = cpv(100, 130);
            break;
        case 1:
            chosenRect = cpv(300, 130);
            break;
        case 2:
            chosenRect = cpv(200, 55);
            break;
        default:
            break;
    }
    
    drawRect(chosenRect, cpv(40,40), RGBAColor(1.0, 1.0, 1.0, 1.0));
}

void title_scene_keyboard_pressed(char c)
{
    switch (c) {
        case 'd': //right
            scene->current_option = (scene->current_option+1)%scene->num_options;
            break;
        case 'a': //left
            scene->current_option = (scene->current_option-1);
            
            if(scene->current_option < 0)
                scene->current_option = scene->num_options-1;
            break;
        case 13: //enter
            scene_manager_set_scene(1);
        default:
            break;
    }

}

void title_scene_keyboard_released(char c)
{
    //do nothing
}