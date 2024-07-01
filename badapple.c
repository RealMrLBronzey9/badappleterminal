#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

// To test my c skills, gonna make a bad apple!! terminal
// Used https://github.com/mattflow/cbmp github project to read the bitmaps

// NOTE TO SELF: Bitmaps created 24 fps bad apple!!
#define FILEPATH_TEXT "D:\\LowLevel\\C Projects\\BadAppleTerminal\\frames.txt"
#define FRAME_LINES 27  // Each frame has 27 lines
#define AMT_OF_BITMAPS 5258
#define LENGTH_OF_LINE 74



// Functions
void ClearTerminal();   // Clears terminall

int main(){
    
    // Add code to open text file and print each frame of bad apple ascii

    // Variables
    FILE* textFile = NULL;
    char* frame = malloc(3001);
    char frameLine[80];

    memset(frame, 0 ,3001); // Init buffer to null chars

    // Open textfile
    textFile = fopen(FILEPATH_TEXT, "r");

    // Check if textfile is not read or if mem allocation of frame has failed
    if(textFile == NULL){
        printf("ERROR: Text file not read!");
        getchar();
        return 1;
    }
    else if(frame == NULL){
        printf("ERROR: frame failed to allocate memory!!");
        getchar();
        return 1;
    }


    // Get frame lines and append to the frame
    for (int i = 0; i < AMT_OF_BITMAPS - 1; i++){   // Frame number (index)
        for (int j = 0; j < FRAME_LINES; j++){  // Frame lines
            fseek(textFile, (LENGTH_OF_LINE*FRAME_LINES*i)+(LENGTH_OF_LINE*j), SEEK_SET);
            fgets(frameLine, 80, textFile);
            strncat(frame, frameLine, 81);
        }

        // Print frame
        printf("%s", frame);
        memset(frame, 0 ,3001); // Init buffer to null chars
        Sleep(50);
        ClearTerminal();

    }
    


    // Finish program by freeing memories
    free(frame);
    getchar();

    return 0;
}

// Function to clear terminal 
void ClearTerminal(){

    // So this print statement clears the terminal
    printf("\033[2J");
    printf("\033[H");

}


