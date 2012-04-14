//
//  SceneManager.h
//  LunarLander
//
//  Created by Carter Appleton on 4/13/12.
//  Copyright (c) 2012 Carter Appleton. All rights reserved.
//

#ifndef LunarLander_SceneManager_h
#define LunarLander_SceneManager_h

/* Initialize the title scene.
 */
void scene_manager_init();

/* Update the title scene.
 */
void scene_manager_update();

/* Display the title scene.
 */
void scene_manager_display();

/* Respond to a key pressed
 */
void scene_manager_keyboard_pressed(char c);

/* Respond to a key released
 */
void scene_manager_keyboard_released(char c);

/* Change the current scene
 */
void scene_manager_set_scene(int scene);

#endif
