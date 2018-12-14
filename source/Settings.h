#pragma once
#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#define PROJECT_NAME "Evolution Saved Me NX"

// Screen size: 1280x720
#define SWITCH_SCREEN_WIDTH 1280
#define SWITCH_SCREEN_HEIGHT 720

// Version of our Homebrew and if we want to set a debugmode for us. 
// We can disable it from here.
#define VERSION "1.0"
#define DEBUG_MODE false

// Some global variables for texts
#define TAP_TEXT_SIZE 40
#define MESSAGE_TEXT_SIZE 40
#define SCORE_TEXT_SIZE 16
#define VERSION_TEXT_SIZE 4


#define MONKEY_SIZE_PER_FRAME 96
#define BANANA_SIZE_PER_FRAME 96
#define FIRE_SIZE_PER_FRAME 96

#define FRAME_COUNTER_BANANA 9
#define FRAME_COUNTER_FIRE 9
#define FRAME_COUNTER_MONKEY 9

#define CELL_SIZE 100

#define LASER_TIME 180
#define MIN_LASER_TIME 70

#define MAX_BANANAS 3
#define MAX_RAYS 3

#define BANANATIMER 150
#define FIRETIMER 400
#define POWERUPTIME 250

#define SCORE_TO_ADD 1

#define MIN_TIME_TO_SPAWN_RAYS 50
#define MAX_TIME_TO_SPAWN_RAYS 200

#define DYINGTIME 70
#define DEADTIME 30

#define LOADING_DELAY 2 // IN SECONDS

#define WOW_SND_SCORE 20
#endif