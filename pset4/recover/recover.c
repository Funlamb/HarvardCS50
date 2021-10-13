#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //open and closing two files practice till I know how to do it by heart

    //check for 3 arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    //open source file
    FILE *fileSource;
    fileSource = fopen(argv[1], "r");
    if (!fileSource)
    {
        printf("Could not open source file.\n");
        return 0;
    }

    //open destination file
    // FILE *fileDestination;
    // fileDestination = fopen(argv[2], "w");
    // if (!fileDestination)
    // {
    //     printf("Could not open destination file.\n");
    //     fclose(fileSource);
    //     return 3;
    // }

    const int BLOCK_SIZE = 512;
    unsigned char buffer[BLOCK_SIZE];
    int image_counter = 0;
    FILE *output = NULL;
    while (fread(&buffer, BLOCK_SIZE, 1, fileSource))
    {
        //Find if block starts a new jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (image_counter != 0 && output != NULL)
            {
                fclose(output);
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", image_counter);
            output = fopen(filename, "w");
            image_counter++;
            // printf("Found 0xFF in front of 512 block. Number: %i\n", image_counter);
        }
        // fwrite(&buffer, sizeof(short), 1, fileDestination);
        if (output != NULL)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, output);
        }
    }

    fclose(fileSource);
    // fclose(fileDestination);
    return 0;
}