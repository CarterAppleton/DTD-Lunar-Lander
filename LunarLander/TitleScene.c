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
#include "GameScene.h"
#include "constants.h"

/* The struct of the title scene.
 */

typedef struct titleScene
{
    int current_option; //which option is selected
    int num_options;    //the total number of options
    int title_size;     //the size of the title text
    int options_size;   //the size of the options text
} titleScene;

/* Make TitleScene a pointer
 */

typedef titleScene* TitleScene;

/* Create the static instance of a Title Scene
 */

static TitleScene scene = NULL;

/* Private functions
 */

void draw_highscores();
void draw_highscore(int num, int score, char* name, int x, int y);

/* Initialize the static title scene
 */

void title_scene_init()
{
    scene = (TitleScene) malloc(sizeof(struct titleScene));
    scene->current_option = 0;
    scene->num_options = 3;
    scene->title_size = 15;
    scene->options_size = 5;
}

/* Update the title scene
 */

void title_scene_update()
{
    //If the title scene doesn't exist, create it
    if(!scene) title_scene_init();
}

void title_scene_display()
{
    //If the title scene doesn't exist, create it
    if(!scene) title_scene_init();
    
    draw_highscores();
    
    //Set the color to draw with
    Color c = RGBAColor(1.0, 1.0, 1.0, 1.0);
    glColor_from_color(c);
    
    //Draw tht title
    drawCAWord("lunar", scene->title_size, 130-70, 300);
    drawCAWord("lander", scene->title_size, 100-70, 200);
    
    //Draw the options
    //drawCAWord("easy", scene->options_size, 150, 100);
    //drawCAWord("medium", scene->options_size, 350, 100);
    drawCAWord("play", scene->options_size, 250-70, 100);

    //Draw the rectangle that shows which option is selected
    cpVect chosenRect = cpv(200-70, 130);;
    
    /*
    switch (scene->current_option) {
        case 0:
            chosenRect = cpv(100, 130);
            break;
        case 1:
            chosenRect = cpv(300, 130);
            break;
        case 2:
            chosenRect = cpv(200, 130);
            break;
        default:
            break;
    }*/
    
    drawRect(chosenRect, cpv(40,40), RGBAColor(1.0, 1.0, 1.0, 1.0));
}

/* Respond to a key press 
 */

void title_scene_keyboard_pressed(char c)
{
    switch (c) {
        case 'd': //right -> increase the current option
            scene->current_option = (scene->current_option+1)%scene->num_options;
            break;
        case 'a': //left -> decrease the current option
            scene->current_option = (scene->current_option-1);
            
            if(scene->current_option < 0)
                scene->current_option = scene->num_options-1;
            break;
        case 13: //enter -> select the current option
            scene_manager_set_scene(1);
            restart();
            break;
        default:
            break;
    }

}

/* Respond to a key release 
 */

void title_scene_keyboard_released(char c)
{
    //do nothing
}

/* Private Functions
*/

void draw_highscores()
{
    char** highscorers = scene_manager_highscorers();
    int* highscores = scene_manager_highscores();
    
    int y = DEFAULT_HEIGHT-50;
    
    for(int i=0; i<scene_manager_numscores(); i++)
    {
        if(highscores[i] == 0)
            break;
        
        draw_highscore(i+1, highscores[i], highscorers[i], DEFAULT_WIDTH-100, y);
        y-=100;
    }
}

void draw_highscore(int num, int score, char* name, int x, int y)
{
    char the_name[4];
    sprintf(the_name, "%c%c%c",name[0],name[1],name[2]);
    
    char the_score[100];
    sprintf(the_score, "%d",score);
    int score_length = (score ==0) ? 1 : (int) log10f(score) + 1;
    
    char the_rank[3];
    sprintf(the_rank, "%d.",num);

    
    drawCAWord(the_score, scene->options_size, DEFAULT_WIDTH - score_length*5*scene->options_size, y-scene->options_size*6);
    
    drawCAWord(the_rank, scene->options_size, x - 5*scene->options_size, y);
    drawCAWord(the_name, scene->options_size, x+5*scene->options_size, y);
    
    
}