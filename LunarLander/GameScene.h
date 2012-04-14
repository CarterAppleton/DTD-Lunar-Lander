//
//  GameScene.h
//  LunarLander
//
//  Created by Carter Appleton on 4/13/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#ifndef LunarLander_GameScene_h
#define LunarLander_GameScene_h

/* Initialize the game scene.
 */
void game_scene_init();

/* Update the game scene.
 */
void game_scene_update();

/* Display the game scene.
 */
void game_scene_display();

/* Respond to a key pressed
 */
void game_scene_keyboard_pressed(char c);

/* Respond to a key released
 */
void game_scene_keyboard_released(char c);


#endif
