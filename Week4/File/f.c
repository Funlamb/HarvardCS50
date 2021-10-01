// C program to read particular bytes
// from the existing file
#include <stdio.h>
#include <stdlib.h>
  
// Maximum range of bytes
#define MAX 1000
typedef uint8_t BYTE;

// Filename given as the command
// line argument
int main(int argc, char* argv[])
{
    //Check for proper usage
    if(argc != 3){
        printf("Usage: copy SOURCE DESTINATION\n");
        return 1;
    }
    
    //Pointer to read the file
    FILE *fileInput;
    fileInput = fopen(argv[1], "r");
    if (fileInput == NULL) //Test that we opened the file
    {
        printf("No such file\n");
        return 2;
    }
    
    //print to the terminal
    char ch;
    while((ch = fgetc(fileInput)) != EOF){
        printf("%c", ch);
    }

    //open a file to write too
    FILE *fileOutput = fopen(argv[2], "w");
    if(fileOutput == NULL){
        fclose(fileInput);
        printf("Could not open file to write\n");
        return 3;
    }

    //Set the pointer back to the begining of the file
    fseek(fileInput, 0, SEEK_SET);
    BYTE buffer;
    while(fread(&buffer, sizeof(BYTE), 1, fileInput)){
        fwrite(&buffer, sizeof(BYTE), 1, fileOutput);
    }

    //close the files to avoid a memmory leek
    fclose(fileInput);
    fclose(fileOutput);

    printf("\n");
    return 0;
}