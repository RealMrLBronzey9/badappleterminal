#include <stdio.h>
#include <stdlib.h>
#include "cbmp.h"
#include <string.h>
#include <windows.h>


// Separate script to make ascii text file of bad apple!!
// I used this Github project that helped me manipulate the bitmaps I created via ffmpeg
// If anybody wants to create their own frames.txt then I guess use ffmpeg to get a bunch of bitmaps for bad apple
// https://github.com/mattflow/cbmp

// Amount of bitmaps in the bitmap file
#define AMT_OF_BITMAPS 5258
#define FILEPATH_WIN "D:\\LowLevel\\C Projects\\BadAppleTerminal\\Bitmaps\\"

// Bitmaps are 144x108
#define BITMAP_WIDTH 144
#define BITMAP_HEIGHT 108

char GetASCII(int pixelAlpha);
void PasteFrame(BMP* bmp, char* frameBuffer, FILE* textFile);
char* GetBitmapFile(char* baseFile, int index);

int main(){

    // Variables
    FILE* textFile = NULL;   // File path
    BMP* bmp;   // Bitmap
    char* bitmapFile = malloc(50);  // Give 50 chars for the 

    // Var to store the ascii string of a frame
    char* frame = malloc(4001);

    // Create the file to store the ascii
    textFile = fopen("frames.txt", "w");

    // For every frame in bad apple!!, create a textfile with all bitmaps
    for (int i = 1; i < AMT_OF_BITMAPS; i++){
        // Get filepath of bitmap
        bitmapFile = GetBitmapFile(FILEPATH_WIN, i);

        // Open bitmap
        bmp = bopen(bitmapFile);
        PasteFrame(bmp, frame, textFile);
        printf("Pasting frame: %d\n", i);
    }

    free(frame);
    free(bitmapFile);
    getchar();
    return 0;
}

// Gets alpha of pixel and returns an ASCII char based on the light
char GetASCII(int pixelAlpha){
    if (pixelAlpha > 233)   
        return '@';

    else if(pixelAlpha > 212)
        return '$';

    else if(pixelAlpha > 191)
        return '#';
    
    else if(pixelAlpha > 170)
        return '*';
    
    else if(pixelAlpha > 149)
        return '!';
    
    else if(pixelAlpha > 128)
        return '=';
    
    else if(pixelAlpha > 107)
        return ';';
    
    else if(pixelAlpha > 86)
        return ':';
    
    else if(pixelAlpha > 65)
        return '~';
    
    else if(pixelAlpha > 44)
        return ',';
    
    else if(pixelAlpha > 23)
        return '.';
    
    else
        return '`';
    
}


// Gets the bitmap image index and prints the bitmap as ascii
void PasteFrame(BMP* bmp, char* frameBuffer, FILE* textFile){

    // CREATE ASCII STRING FROM BITMAP IMAGE
    int pixelAlpha;
    char pixelASCII;
    pixelASCII = '\0'; 
    frameBuffer[0] = '\0';
    // for loop for the height of bitmap image 
    for (int i = BITMAP_HEIGHT-1; i > 0; i -= 4){
        // for loop for the width of the bitmap image
        for (int j = 0; j < BITMAP_WIDTH; j += 2){
            // Get alpha of pixel
            pixelAlpha = get_pixel_alpha(bmp, j, i);    // From that Github project I slightly modified get_pixel_rgb into this function to just give me the red  
            
            // Get ascii for the pixel
            pixelASCII = GetASCII(pixelAlpha);

            // Append ascii of pixel to string
            strncat(frameBuffer, &pixelASCII, 1);
        }
        // Add newline after each row
        char newline[2] = "\n";
        strncat(frameBuffer, newline, 1);   
    }
    // Store the frame in the textfile
    fputs(frameBuffer, textFile);
}


char* GetBitmapFile(char* baseFile, int index){
    char str_index[10];
    size_t len;
    char* filepath;

    // Append index of bitmap into the main filepath
    snprintf(str_index, sizeof(str_index), "%d.bmp", index);    // Make index into a string str_index
    len = strlen(baseFile) + strlen(str_index) + 1;    // Length of FILEPATH definition and index str and 1 more byte for the \0
    filepath = malloc(len + 1);   
    strcpy(filepath, baseFile);   // Append FILEPATH to filepath
    strcat(filepath, str_index);    // Append str_index to filepath
    
    return filepath;
}