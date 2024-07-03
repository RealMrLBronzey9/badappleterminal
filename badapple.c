#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

// To test my current c skills, gonna make a bad apple!! terminal program
// It is terribly slow and lots of flickering
// If anybody wants to run this for some reason, you gotta change FILEPATH_TEXT to where your frames.txt is and also you gotta create frames.txt using the maketxt.c
// Used https://github.com/mattflow/cbmp Github project to read the bitmaps

// NOTE TO SELF: Bitmaps created 24 fps bad apple!!
#define FILEPATH_TEXT "./frames.txt" // Replace with filepath of frames

#define AMT_OF_BITMAPS 5258

#define FRAME_LINES 27 // Each frame has 27 lines
#define LENGTH_OF_LINE 73

#define FRAME_SIZE (FRAME_LINES * LENGTH_OF_LINE)

// Functions
void CursorHome();
void ClearTerminal();

int main()
{
	// Add code to open text file and print each frame of bad apple ascii

	// Variables
	FILE *textFile = NULL;
	char frame[FRAME_SIZE + 1];

	// Open textfile
	textFile = fopen(FILEPATH_TEXT, "r");

	// Check if textfile is not read or if mem allocation of frame has failed
	if (textFile == NULL) {
		printf("ERROR: Text file not read!");
		getchar();
		return 1;
	}

	// Set stdout to fully buffered
	int stdout_buffer_size = FRAME_SIZE * 3; // Kinda arbitrary value
	char *stdout_buffer = malloc(stdout_buffer_size);
	setvbuf(stdout, stdout_buffer, _IOFBF, stdout_buffer_size);

	ClearTerminal();

	// Get frame lines and append to the frame
	for (int i = 0; i < AMT_OF_BITMAPS - 1; i++) { // Frame number (index)

		fread(frame, 1, FRAME_SIZE, textFile);
		frame[FRAME_SIZE] = '\0';

		// Print frame
		CursorHome();
		printf("%s", frame);
		fflush(stdout);
		Sleep(30);
	}

	// Finish program by freeing memories
	free(stdout_buffer);
	getchar();

	return 0;
}

// Move cursor to the beginning of the terminal
void CursorHome()
{
	printf("\033[0;0H");
}

// Removes all characters from the terminal
void ClearTerminal()
{
	printf("\033[2J");
}
