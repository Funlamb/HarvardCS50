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

    short buffer;
    while (fread(&buffer, 1, 1, fileSource))
    {
        fprintf(fileDestination, "%x ", buffer);
        // fwrite(&buffer, sizeof(short), 1, fileDestination);
    }
    
    fclose(fileSource);
    fclose(fileDestination);
    return 0;
}