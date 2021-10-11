#include <stdio.h>
#include <stdlib.h>
typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    //open and closing two files practice till I know how to do it by heart
    
    //check for 3 arguments
    if (argc != 3)
    {
        printf("usage: rec SOURCE DESTINATION");
        return 1;
    }
    
    //open source file
    FILE *fileSource;
    fileSource = fopen(argv[1], "r");
    if (!fileSource)
    {
        printf("Could not open source file.\n");
        return 2;
    }

    //open destination file
    FILE *fileDestination;
    fileDestination = fopen(argv[2], "w");
    if (!fileDestination)
    {
        printf("Could not open destination file.\n");
        fclose(fileSource);
        return 3;
    }

    BYTE buffer;
    while (fread(&buffer, sizeof(BYTE), 1, fileSource))
    {
        fwrite(&buffer, sizeof(BYTE), 1, fileDestination);
    }
    
    return 0;

}