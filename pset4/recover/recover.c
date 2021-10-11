#include <stdio.h>
#include <stdlib.h>
typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    //open and closing two files practice till I know how to do it by heart
    //check for 3 arguments
    if(argc != 3){
        printf("Usage: copy SOURCE DESTINATION\n");
    }

    //open the file
    FILE *fileSource;
    fileSource = fopen(argv[1], "r");
    if(fileSource == NULL){
        printf("Could not open source file.\n");
    }

    //create a destination file
    FILE *fileDestination;
    fileDestination = fopen(argv[2], "w");
    if (fileDestination == NULL){
        fclose(fileSource);
        printf("Could not open destination file.\n");
        return 3;
    }

    //copy source to destination
    BYTE buffer;
    while(fread(&buffer, sizeof(BYTE), 1, fileSource)){
        fwrite(&buffer,sizeof(BYTE), 1, fileDestination);
    }

    //close files
    fclose(fileSource);
    fclose(fileDestination);

    return 0;

}