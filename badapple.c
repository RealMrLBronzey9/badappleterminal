#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "cbmp.h"
#include <string.h>

// To test my c skills, gonna make a bad apple!! terminal
// Used https://github.com/mattflow/cbmp github project to read the bitmaps
NBOTE to do!!1: increase resolution and make a luminencense of ascii chars (not just @ and `). Pre render it into strings (separate program and save it into a file) then play the terminal video
// NOTE TO SELF: Bitmaps created 24 fps bad apple!!
// Bitmaps are 144x108
#define BITMAP_WIDTH 144
#define BITMAP_HEIGHT 108

#define AMT_OF_BITMAPS 5258

// Filepaths for bitmaps
#define FILEPATH_LINUX  "/mnt/d/LowLevel/C Projects/BadAppleTerminal/Bitmaps/"
#define FILEPATH_WIN "D:\\LowLevel\\C Projects\\BadAppleTerminal\\Bitmaps\\"

#define BASE_FILEPATH "D:\\LowLevel\\C Projects\\BadAppleTerminal\\Bitmaps\\"

// Possibly 4 by 4 pixels per char ascii

// Functions
void ClearTerminal();   // Clears terminall
char GetASCII(int pixelAlpha);  // Gets alpha of pixel and returns an ASCII char
void PasteFrame();  // Gets the bitmap image file index and then prints the bitmap as ascii 

int main(){
    
    BMP* bmp;
    char* filepath;
    char str_index[10];
    size_t len;

    char* frame = malloc(3001);


    for (int i = 1; i < 5258; i++){

    // Open bitmap
    // Append index to the filepath
    str_index;
    snprintf(str_index, sizeof(str_index), "%d.bmp", i);    // Make index into a string str_index
    len = strlen(BASE_FILEPATH) + strlen(str_index) + 1;    // Length of FILEPATH definition and index str and 1 more byte for the \0
    filepath = malloc(len + 1);   
    strcpy(filepath, BASE_FILEPATH);   // Append FILEPATH to filepath
    strcat(filepath, str_index);    // Append str_index to filepath

    // Open the filepath and free the filepath pointer
    bmp = bopen(filepath);
    
    // Paste the frame
    PasteFrame(bmp, frame);
    Sleep(13);
    ClearTerminal();

    }

    // deallocate bmp and the filepath
    bclose(bmp);
    bmp = NULL;
    free(filepath);
    filepath = NULL;
    free(frame);
    frame = NULL;

    // Windows terminal needs this or it will immediately pause bruh
    printf("Program finished, press enter.");
    getchar();

    return 0;
}

// Gets the bitmap image index and prints the bitmap as ascii
void PasteFrame(BMP* bmp, char* frameBuffer){

    // CREATE ASCII STRING FROM BITMAP IMAGE
    int pixelAlpha;
    char pixelASCII;
    pixelASCII = '\0'; 
    frameBuffer[0] = '\0';
    // for looop for the height of bitmap image 
    // Increment by 4 to check the alpha of every 4 pixels
    for (int i = BITMAP_HEIGHT-1; i > 0; i -= 8){
        // for loop for the width of the bitmap image
        for (int j = 0; j < BITMAP_WIDTH; j += 4){
            // Get alpha of pixel
            pixelAlpha = get_pixel_alpha(bmp, j, i);
            
            // Get ascii for the pixel
            pixelASCII = GetASCII(pixelAlpha);

            // Append ascii of pixel to string
            strncat(frameBuffer, &pixelASCII, 1);
        }
        // Add newline after each row
        char newline[2] = "\n";
        strncat(frameBuffer, newline, 1);
    }
    // Print the bitmap
    printf("%s", frameBuffer);
    
}

// Gets alpha of pixel and returns an ASCII char
char GetASCII(int pixelAlpha){
    if (pixelAlpha > 0){
        return '@';
    }
    else{
        return '`';
    }
}


// Function to clear terminal 
void ClearTerminal(){

    // So this print statement clears the terminal
    printf("\033[2J");
    printf("\033[H");

}


