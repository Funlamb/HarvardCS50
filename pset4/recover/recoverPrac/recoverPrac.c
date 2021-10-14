#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    //check for correct amount of arguments
    if(argc != 2){
        printf("usage: rec FILE");
    }

    //undelete a .raw memory card
    //Open the file
    FILE *sourceFile = fopen(argv[1], "r");
    if (!sourceFile)
    {
        printf("Could not open source file\n");
        return 1;
    }
    
    //jpgs start with 0xff 0xd8 0xFF 0xe0
    FILE *outputFile = NULL;
    int outputFileNumber = 0;
    const int BLOCK_SIZE = 512;
    unsigned char buffer[BLOCK_SIZE];
    while(fread(buffer, BLOCK_SIZE, 1, sourceFile)){
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
            if(outputFileNumber != 0){
                fclose(outputFile);
            }
            char fileName[8];
            sprintf(fileName, "%03i.jpg", outputFileNumber);
            outputFile = fopen(fileName, "w");
            outputFileNumber++;
        }
        if(outputFile){
            fwrite(buffer, BLOCK_SIZE, 1, outputFile);
        }
    }
    return 0;
}