#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <rand.h>
#include <time.h>
#include <gbdk/console.h>
#include <gb/drawing.h>

// Game scenes enum
enum GameScene {
    NONE,
    WELCOME,
    GAMEPLAY
};

// Global game state
enum GameScene currentScene = NONE;
uint8_t joypadKey = 0;

void welcome_scene(void)
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

void gameplay_scene(void)
{
    if (currentScene != GAMEPLAY) {
	// Clear screen
	cls();

	// Draw board
	color(BLACK, WHITE, SOLID);
	box(10, 10, 110, 110, M_NOFILL);
	line(10, 10, 110, 110);
	line(10, 110, 110, 10);
	line(60, 10, 60, 110);
	line(10, 60, 110, 60);

	// Draw light grey circle at the center
	color(LTGREY, WHITE, SOLID);
	circle(60, 60, 5, M_FILL);

	// Draw dark grey circle at the right
	color(DKGREY, WHITE, SOLID);
	circle(110, 60, 5, M_FILL);

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
