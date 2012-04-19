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
#include <string.h>
#include <time.h>

#include "lander.h"
#include "chipmunk.h"
#include "array.h"
#include "constants.h"
#include "drawing.h"
#include "SceneManager.h"

#if DRAW_TEXTURE
/* Stuffs for Textures
 */

typedef struct
{
    GLubyte* imageData;// Hold All The Color Values For The Image.
    GLuint bpp;// Hold The Number Of Bits Per Pixel.          
    GLuint width;// The Width Of The Entire Image.  
    GLuint height;// The Height Of The Entire Image. 
    GLuint texID;// Texture ID For Use With glBindTexture.  
    GLuint type;// Data Stored In * ImageData (GL_RGB Or GL_RGBA)
} Texture;

typedef struct
{
    GLubyte Header[12];// File Header To Determine File Type
} TGAHeader;

typedef struct
{
    GLubyte header[6];// Holds The First 6 Useful Bytes Of The File
    GLuint bytesPerPixel;// Number Of BYTES Per Pixel (3 Or 4)
    GLuint imageSize;// Amount Of Memory Needed To Hold The Image
    GLuint type;// The Type Of Image, GL_RGB Or GL_RGBA
    GLuint Height;// Height Of Image                 
    GLuint Width;// Width Of Image              
    GLuint Bpp;// Number Of BITS Per Pixel (24 Or 32)
} TGA;

TGAHeader tgaheader;// Used To Store Our File Header
TGA tga;// Used To Store File Information

// Uncompressed TGA Header
GLubyte uTGAcompare[12] = {0,0, 2,0,0,0,0,0,0,0,0,0};
// Compressed TGA Header
GLubyte cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};

#endif

/* The struct of the title scene.
 */

typedef struct gameScene
{
    cpSpace* space; //the physics space
    Array height_map; //the heightmap (terrain/landscape)
    Lander lander; //the lunar lander object
    int max_hit_speed;
    int game_over; //non-zero for game over, -1 for loss and 1 for win 
    int zoom;
    
    char letters[3];
    int current_letter;
    
    time_t start_time;
    
    int score;
    
#if DRAW_TEXTURE
    Texture* lander_tex;
#endif
    
} gameScene;

/* Make Gamescene a pointer
 */

typedef gameScene* GameScene;

/* Create the static instance of a Game Scene
 */

static GameScene scene;

/* Private Functions
 * Implemented at bottom of file
 */

void drawMultiplier(int amount, int x, int y);
void restart();

#if DRAW_TEXTURE
int LoadTGA(Texture * texture, char * filename);
#endif

/* Callback function so we know when the lander hits the moon
 * this will let us know the force of the collision so we can
 * decide if the game is won or lost.
 */

int landerHitMoon(cpArbiter *arb, cpSpace *space, void *data)
{    
    cpVect normal = cpArbiterGetNormal(arb, 0);
    
    //Simple crash test
    if(abs(landerSpeed(scene->lander)) >= scene->max_hit_speed && normal.x == 0)
    {
        scene->game_over = -1;
        scene->score = 0;
    }else
    {
        time_t end_time = time(NULL);
        int elapsed = end_time - scene->start_time;
        
        //Multiplier regions:
        /*
         drawMultiplier(5, 45, 145);
         drawMultiplier(2, 135, 55);
         drawMultiplier(5, 317, 178);
         drawMultiplier(2, 444, 110);
         */
        int x = landerPosition(scene->lander).x;
        int multiplier = 2;
        if((x < 90 && x > 0) || (x > 226 && x < 380))
            multiplier = 5;
        
        scene->score = (1000/elapsed) * multiplier;
            
        scene->game_over = 1;
    }
    
    return 1;
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
    
    //Add constraining rect
    shape = cpSpaceAddShape(scene->space, cpSegmentShapeNew(staticBody, cpv(0,0), cpv(0,DEFAULT_HEIGHT), 0.0f));
    cpShapeSetCollisionType(shape, NULL_TAG);
    shape->e = 0.0f; shape->u = 0.0f;
    
    shape = cpSpaceAddShape(scene->space, cpSegmentShapeNew(staticBody, cpv(0,DEFAULT_HEIGHT), cpv(DEFAULT_WIDTH/2,DEFAULT_HEIGHT+100), 0.0f));
    cpShapeSetCollisionType(shape, NULL_TAG);
    shape->e = 0.0f; shape->u = 0.0f;
    
    shape = cpSpaceAddShape(scene->space, cpSegmentShapeNew(staticBody, cpv(DEFAULT_WIDTH/2,DEFAULT_HEIGHT+100), cpv(0,DEFAULT_HEIGHT), 0.0f));
    cpShapeSetCollisionType(shape, NULL_TAG);
    shape->e = 0.0f; shape->u = 0.0f;
    
    shape = cpSpaceAddShape(scene->space, cpSegmentShapeNew(staticBody, cpv(DEFAULT_WIDTH,0), cpv(DEFAULT_WIDTH,DEFAULT_HEIGHT), 0.0f));
    cpShapeSetCollisionType(shape, NULL_TAG);
    shape->e = 0.0f; shape->u = 0.0f;
    
    
}

/* Initialize the static game scene
 */

void game_scene_init()
{
    scene = malloc(sizeof(struct gameScene));
    
    scene->max_hit_speed = 10;
    scene->game_over = 1;
    scene->zoom = 0;
    scene->current_letter = 0;
    scene->letters[0] = 'a';
    scene->letters[1] = 'a';
    scene->letters[2] = 'a';
    scene->score = 0;
    scene->start_time = time (NULL);

#if DRAW_TEXTURE
    scene->lander_tex = malloc(sizeof(Texture*));
    LoadTGA(scene->lander_tex, "lander.tga");

    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, scene->lander_tex->width, scene->lander_tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE,scene->lander_tex->imageData);
    glBindTexture(GL_TEXTURE_2D, scene->lander_tex->texID);    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
#endif
    
    //Init physics
    cpInitChipmunk();
    
    scene->space = cpSpaceNew();
    cpSpaceSetIterations(scene->space, 20);
    cpSpaceSetGravity(scene->space, cpv(0, GRAVITY));
    
    //Add a handler for the function landerHitMoon so we know when the lander and landscape collide
    cpSpaceAddCollisionHandler(scene->space, LANDER_TAG, MOON_LAND_TAG, landerHitMoon, NULL, NULL, NULL, NULL);
    
    //Init heightmap
    scene->height_map = arrayMakeFromArray(DEFALUT_ARRAY_LENGTH, default_array);
    
    //Add the heightmap to the physics space
    addHeightMap(scene->height_map, DEFAULT_WIDTH);
    
    //Create the lander
    //landerMake(starting_position, starting_thrust, starting_orientation, starting_fuel, physics_space);
    scene->lander = landerMake(cpv(INITIAL_P_X, INITIAL_P_Y), INITIAL_THRUST, 0, 500, scene->space);
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
        
        //Check if we need to zoom
        GLfloat stepWidth = ((GLfloat)glutGet(GLUT_WINDOW_WIDTH)) / (scene->height_map->count-1);
        int index = landerPosition(scene->lander).x / stepWidth;
        
        //printf("%f \n",landerPosition(scene->lander).y - arrayValueAtIndex(index, scene->height_map));
        if(landerPosition(scene->lander).y - arrayValueAtIndex(index, scene->height_map) < 150)
            scene->zoom = 1;
        else 
            scene->zoom = 0;
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
    
    if(!scene->game_over)
    {
        cpVect p = landerPosition(scene->lander);
        cpVect lp = landerPosition(scene->lander);
        
        GLfloat width = DEFAULT_WIDTH/4;
        GLfloat height = DEFAULT_HEIGHT/4;
        
        if(lp.x - width < 0)
            lp.x = width;
        else if(lp.x + width > DEFAULT_WIDTH)
            lp.x = DEFAULT_WIDTH-width;
        
        if(lp.y - height < 0)
            lp.y = height;
        else if(lp.y + height > DEFAULT_HEIGHT)
            lp.y = DEFAULT_HEIGHT;
        
        glLoadIdentity();
        
        if(scene->zoom)
            glOrtho(lp.x-width, lp.x+width, lp.y-height, lp.y+height, -1.0, 1.0);
        else
            glOrtho(0, DEFAULT_WIDTH, 0, DEFAULT_HEIGHT, -1.0, 1.0);
        
        //Draw the score for regions
        drawMultiplier(2, 135, 55);
        drawMultiplier(5, 45, 145);
        drawMultiplier(5, 317, 178);
        drawMultiplier(2, 444, 110);
        
        //Draw the lander
#if !DRAW_TEXTURE
        landerDraw(scene->lander);
        
#else
        //Image lander
        glPushMatrix(); 
        {
            Color c = RGBAColor(1.0, 1.0, 1.0, 1.0);
            glColor_from_color(c);
            
            glTexImage2D(GL_TEXTURE_2D, 0, 3, scene->lander_tex->width, scene->lander_tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE,scene->lander_tex->imageData);
            glBindTexture(GL_TEXTURE_2D, scene->lander_tex->texID);    
            
            glEnable(GL_TEXTURE_2D);
            
            glTranslatef(p.x, p.y, 0.0f);
            glRotatef(landerAngle(scene->lander)*360.0f/M_PI, 0.0f, 0.0f, 1.0f);

            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(-5, -5);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(-5, 5);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(5, 5);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(5, -5);
            glEnd();
            
            glDisable(GL_TEXTURE_2D);
            
        }
        glPopMatrix();  
#endif
        //Draw the landscape
        drawHeightMap(scene->height_map, DEFAULT_WIDTH);
        
        Color c;
        
        char velocity_x[100];
        char velocity_y[100];
        char force[100];
        char orientation[100];
        
        sprintf(velocity_y, "velocity-y: %f",landerSpeed(scene->lander));
        sprintf(velocity_x, "velocity-x: %f",landerHorizontalSpeed(scene->lander));
        sprintf(force, "force-y: %f",scene->lander->thrust);
        sprintf(orientation, "rotation: %d",scene->lander->orientation);
        
#if DEBUG
        //Draw the information strings
        
        if(landerSpeed(scene->lander) < -10)
            c = RGBAColor(1.0, 0.0, 0.0, 1.0);
        else
            c = RGBAColor(1.0, 1.0, 1.0, 1.0);
        
        if(scene->zoom)
        {   
            drawString(lp.x-width/2, lp.y+height-50, velocity_y, c); 
            drawString(lp.x-width/2, lp.y+height-40, force, RGBAColor(1.0, 1.0, 1.0, 1.0)); 
            drawString(lp.x-width/2, lp.y+height-30, orientation, RGBAColor(1.0, 1.0, 1.0, 1.0)); 
        }else {
            drawString(0, DEFAULT_HEIGHT-50, velocity, c); 
            drawString(0, DEFAULT_HEIGHT-40, force, RGBAColor(1.0, 1.0, 1.0, 1.0)); 
            drawString(0, DEFAULT_HEIGHT-30, orientation, RGBAColor(1.0, 1.0, 1.0, 1.0)); 
        }
#endif
        
        c = RGBAColor(1.0, 1.0, 1.0, 1.0);
        glColor_from_color(c);
        
        if(scene->zoom)
        {   
            if(abs(landerSpeed(scene->lander)) >= scene->max_hit_speed)
            {
                c = RGBAColor(1.0, 0.0, 0.0, 1.0);
                glColor_from_color(c);
                
                drawCAWord("warning", 3, lp.x-17.5*3, lp.y+50);
                drawCAWord("too fast", 2, lp.x-20*2, lp.y+36);
            }
            
            drawCAWord(velocity_y, 1, lp.x-width, lp.y+height-20);
            
            c = RGBAColor(1.0, 1.0, 1.0, 1.0);
            glColor_from_color(c);
            
            drawCAWord(velocity_x, 1, lp.x-width, lp.y+height-10);
            drawCAWord(orientation, 1, lp.x-width, lp.y+height-30);
            
        }else {
            drawCAWord(velocity_x, 1, 0, DEFAULT_HEIGHT-10);
            drawCAWord(velocity_y, 1, 0, DEFAULT_HEIGHT-20);
            drawCAWord(orientation, 1, 0, DEFAULT_HEIGHT-30);
        } 
        
        
    }else //Game is over
    {
        glLoadIdentity();
        glOrtho(0, DEFAULT_WIDTH, 0, DEFAULT_HEIGHT, -1.0, 1.0);
        
        Color c = RGBAColor(1.0, 1.0, 1.0, 1.0);
        glColor_from_color(c);
        
        if(scene->game_over > 0) //WON!!
        {
            char letter1[2];
            char letter2[2];
            char letter3[2];
            sprintf(letter1, "%c",scene->letters[0]);
            sprintf(letter2, "%c",scene->letters[1]);
            sprintf(letter3, "%c",scene->letters[2]);
            
            char score[100];
            sprintf(score, "%d",scene->score);
            
            int score_length = (scene->score ==0) ? 1 : (int) log10f(scene->score) + 1;

            drawCAWord(score, 10, DEFAULT_WIDTH/2 - (score_length*5)/2*10, DEFAULT_HEIGHT-60);

            drawCAWord("success", 10, DEFAULT_WIDTH/2 - 17.5*10, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3);
            drawCAWord("click to play again", 5, DEFAULT_WIDTH/2 - 47.5*5, 50);

            if(scene_manager_is_highscore(scene->score))
            {
                drawRect(cpv(DEFAULT_WIDTH/2 - 25*10, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3-25), cpv(500, 150), RGBAColor(1.0, 1.0, 1.0, 0.2));
                
                c = RGBAColor(1.0, 1.0, 1.0, 1.0);
                glColor_from_color(c);
                
                drawCAWord("highscore!", 5, DEFAULT_WIDTH/2 - 25*5, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3-75);
                
                int shift = 50;
                drawCAWord("name:", 10, DEFAULT_WIDTH/2 - 25*10 +shift - 5, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3-150);
                
                drawCAWord(letter1, 10, DEFAULT_WIDTH/2+shift, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3-150);
                drawCAWord(letter2, 10, DEFAULT_WIDTH/2 + 50+shift, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3-150);
                drawCAWord(letter3, 10, DEFAULT_WIDTH/2 + 100+shift, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3-150);
                
                c = RGBAColor(1.0, 0.2, 1.0, 1.0);
                glColor_from_color(c);
                
                switch (scene->current_letter) {
                    case 0:
                        drawCAWord(letter1, 10, DEFAULT_WIDTH/2+shift, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3-150);
                        break;
                    case 1:
                        drawCAWord(letter2, 10, DEFAULT_WIDTH/2 + 50+shift, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3-150);
                        break;
                    case 2:
                        drawCAWord(letter3, 10, DEFAULT_WIDTH/2 + 100+shift, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3-150);
                        break;
                    default:
                        break;
                }
            }
            


        }
        else //LOST :(
        {
            drawCAWord("failure", 10, DEFAULT_WIDTH/2 - 17.5*10, DEFAULT_HEIGHT-DEFAULT_HEIGHT/3);
            drawCAWord("click to play again", 5, DEFAULT_WIDTH/2 - 47.5*5, 50);

        }
    }
    
  

}

/* Respond to a key press 
 */

void game_scene_keyboard_pressed(char c)
{    
    switch (c) {
        case 'r': //restart
            restart();
            break;
        case 'w': //increase thrust
            if(scene->game_over > 0)
            {
                scene->letters[scene->current_letter] = ((int)scene->letters[scene->current_letter]) - 1;

                if(scene->letters[scene->current_letter] < 97)
                    scene->letters[scene->current_letter] = 122;
                
            }else if(!scene->game_over)
            {
                landerAdjustThrust(0.025, scene->lander);
            }
            
            break;
        case 's': //decrease thrust

            if(scene->game_over > 0)
            {
                scene->letters[scene->current_letter] += 1;
                
                if(scene->letters[scene->current_letter] > 122)
                    scene->letters[scene->current_letter] = 97;
                
            }else if(!scene->game_over)
            {
                landerAdjustThrust(-0.025, scene->lander);
            }
            break;
        case 'a': //rotate left
            if(scene->game_over > 0)
            {
                scene->current_letter--;
                
                if(scene->current_letter < 0)
                    scene->current_letter = 2;
            }else if(!scene->game_over)
            {
                landerRotate(1, scene->lander);
            }
            break;
        case 'd': //rotate right
            if(scene->game_over > 0)
            {
                scene->current_letter = (scene->current_letter+1)%3;
            }else if(!scene->game_over)
            {
                landerRotate(-1, scene->lander);
            }
            break;
        case 13: //enter -> select the current option
            if(scene->game_over != 0)
            {
                scene_manager_set_scene(0);
                
                if(scene_manager_is_highscore(scene->score))
                    scene_manager_add_highscore(scene->score, scene->letters);
            }
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

/* Private Function implementations
 */

void restart()
{
    //If the game scene doesn't exist, create it
    if(!scene) game_scene_init();
    
    cpBodySetPos(scene->lander->body, cpv(INITIAL_P_X, INITIAL_P_Y));
    cpBodySetForce(scene->lander->body, cpvzero);
    cpBodySetVel(scene->lander->body, cpvzero);
    cpBodySetAngVel(scene->lander->body, 0);
    cpBodySetAngle(scene->lander->body, 0);
    landerSetThrust(scene->lander, INITIAL_THRUST);
    scene->lander->orientation = 0;
    scene->game_over = 0;    
    scene->zoom = 0;
    scene->current_letter = 0;
    scene->letters[0] = 'a';
    scene->letters[1] = 'a';
    scene->letters[2] = 'a';
    scene->score = 0;
    scene->start_time = time (NULL);
}

void drawMultiplier(int amount, int x, int y)
{
    Color c = RGBAColor(1.0, 1.0, 1.0, 1.0);
    glColor_from_color(c);
    
    drawCircle(cpv(x+2, y+2.5), 10, 7.5, RGBAColor(1.0, 1.0, 1.0, 0.5), RGBAColor(0.0, 0.0, 0.0, 1.0));

    c = RGBAColor(1.0, 1.0, 1.0, 0.5);
    glColor_from_color(c);
    
    char string[2];
    
    sprintf(string, "%d",amount);
    
    drawCAWord(string, 1, x, y);
}

#if DRAW_TEXTURE

/* Texture loading THANK YOU NEHE
*/

// Load An Uncompressed TGA!
int LoadUncompressedTGA(Texture * texture, char * filename, FILE * fTGA)
{
    // Attempt To Read Next 6 Bytes
    if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)
    {
        return 0;// Return False
    }
    
    texture->width = tga.header[1] * 256 + tga.header[0];// Calculate Height
    texture->height = tga.header[3] * 256 + tga.header[2];// Calculate The Width
    texture->bpp = tga.header[4];// Calculate Bits Per Pixel
    tga.Width = texture->width;// Copy Width Into Local Structure
    tga.Height = texture->height;// Copy Height Into Local Structure
    tga.Bpp = texture->bpp;// Copy Bpp Into Local Structure
    
    // Make Sure All Information Is Valid
    if((texture->width <= 0) || (texture->height <= 0) || ((texture->bpp != 24) && (texture->bpp !=32)))
    {
        return 0;// Return False
    }
    
    if(texture->bpp == 24)// Is It A 24bpp Image?
        texture->type= GL_RGB;// If So, Set Type To GL_RGB
    else// If It's Not 24, It Must Be 32
        texture->type= GL_RGBA;// So Set The Type To GL_RGBA
    
    tga.bytesPerPixel = (tga.Bpp / 8);// Calculate The BYTES Per Pixel
    // Calculate Memory Needed To Store Image
    tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);
    
    // Allocate Memory
    texture->imageData = (GLubyte *)malloc(tga.imageSize);
    if(texture->imageData == NULL)// Make Sure It Was Allocated Ok
    {
        return 0;// If Not, Return False
    }
    
    // Attempt To Read All The Image Data
    if(fread(texture->imageData, 1, tga.imageSize, fTGA) != tga.imageSize)
    {
        return 0;// If We Cant, Return False
    }
    
    // Start The Loop
    for(GLuint cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
    {
        // 1st Byte XOR 3rd Byte XOR 1st Byte XOR 3rd Byte
        texture->imageData[cswap] ^= texture->imageData[cswap+2] ^=
        texture->imageData[cswap] ^= texture->imageData[cswap+2];
    }
    
    fclose(fTGA);// Close The File
    return 1;// Return Success
}

// Load A TGA File!
int LoadTGA(Texture * texture, char * filename)
{
    FILE * fTGA;// Declare File Pointer
    fTGA = fopen(filename, "rb");// Open File For Reading
    
    if(fTGA == NULL)// If Here Was An Error
    {
        return 0;// Return False
    }
    
    // Attempt To Read The File Header
    if(fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)
    {
        return 0;// Return False If It Fails
    }
    
    // If The File Header Matches The Uncompressed Header
    if(memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)
    {
        // Load An Uncompressed TGA
        return LoadUncompressedTGA(texture, filename, fTGA);
    }
    // If The File Header Matches The Compressed Header
    /*else if(memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)
    {
        // Load A Compressed TGA
        LoadCompressedTGA(texture, filename, fTGA);
    }*/
    else// If It Doesn't Match Either One
    {
        return 0;// Return False
    }
    
    return 0;
}

#endif