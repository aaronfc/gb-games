#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <rand.h>
#include <time.h>
#include <gbdk/console.h>

// Constants
#define INACTIVE_JOYPAD_THRESHOLD 100

// Game scenes enum
enum GameScene {
    NONE,
    WELCOME,
    GAMEPLAY
};

// Global game state
enum GameScene currentScene = NONE;
uint8_t joypadKey = 0;

void welcome_scene()
{
    // Render only when entering the scene
    if (currentScene != WELCOME) {
	// Clear screen
	cls();

	// Print welcome message
	printf("Welcome to the game!\n");
	printf("Press start to begin\n");

	// Track new scene
	currentScene = WELCOME;
    }

    // Read input
    joypadKey = joypad();

    if (joypadKey & J_START) {
	// Wait for the key to be released
	waitpadup();
	// Change scene
	gameplay_scene();
    }
}

void gameplay_scene()
{
    if (currentScene != GAMEPLAY) {
	// Clear screen
	cls();

	// Print welcome message
	printf("Gameplay scene\n");
	printf("Press start to go back\n");

	// Track new scene
	currentScene = GAMEPLAY;
    }

    // Read input
    joypadKey = joypad();

    if (joypadKey & J_START) {
	// Wait for the key to be released
	waitpadup();
	// Change scene
	welcome_scene();
    }
}

void main(void)
{
    // Initialize stuff
    // Nothing yet.

    // Infinite loop
    while(1) {

	// Do stuff
	switch(currentScene) {
	    case NONE:
		// Initialize...
		// Nothing yet

		// Change to welcom scene
		welcome_scene();
		break;

	    case WELCOME:
		welcome_scene();
		break;

	    case GAMEPLAY:
		gameplay_scene();
		break;
	}

	// Wait for vblank
	wait_vbl_done();
    }
}
