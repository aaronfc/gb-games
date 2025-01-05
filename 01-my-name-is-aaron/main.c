#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <rand.h>
#include <time.h>
#include <gbdk/console.h>

// With help from GPT-4o (heavy editing afterwards)
void printCenteredMessage(char message[]) {
	int messageStringLength = strlen(message);
	// Calculate x but make sure it's not negative
	int x = (DEVICE_SCREEN_WIDTH / 2) - (messageStringLength / 2);
	x = x < 0 ? 0 : x;
	int y = DEVICE_SCREEN_HEIGHT / 2;
	for(int i = 0; i < y; i++) {
		printf("\n");
	}
	for(int i = 0; i < x; i++) {
		printf(" ");
	}
	printf("%s", message);
}

// Initialize sound (perplexity)
void init_sound() {
    NR52_REG = 0x80; // Turn on the sound system
    NR50_REG = 0x77; // Set volume for both left and right channels
    NR51_REG = 0xFF; // Enable all sound channels
}

// Play mario coin (perplexity)
void play_coin_sound() {
    NR10_REG = 0x16; // Frequency sweep: fast upward sweep
    NR11_REG = 0x40; // Duty cycle (50%) and length of sound
    NR12_REG = 0x73; // Volume envelope: start at max volume, fade out quickly
    NR13_REG = 0x00; // Low bits of frequency
    NR14_REG = 0xC3; // High bits of frequency and trigger the sound
}

void main(void)
{
    // Initialize sound
    init_sound();

    // Multiple names array
    char *names[] = {"Aaron", "AroGigante", "Aro", "aaron"};
    int randomIndex = 0;
    const char *format = "My name's %s";
    char finalMessage[20] = "";

    // Infinite loop
    while(1) {
	// Clear screen
	cls();

	// Generate name randomly on every rendering
	randomIndex = rand() % 4;
	sprintf(finalMessage, format, names[randomIndex]);

	// Print the message and play sound
	printCenteredMessage(finalMessage);
	play_coin_sound();

	// Wait for vblank
	wait_vbl_done();

	// Wait 1 second
	delay(1000);
    }
}
