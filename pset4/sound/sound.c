#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
typedef int16_t SAMPLE_SIZE;
const int HEADER_SIZE = 44;

int main(int argc, char* argv[])
{
    //Check correct usage
    if(argc != 4){
        printf("Usage: ./sound SOURCE DESTINATION FACTOR\n");
        return 1;//Testing git
    }
    
    //open file to change
    FILE *fileSource = fopen(argv[1], "r");
    if (fileSource == NULL)
    {
        printf("Could not open source file\n");
        return 1;
    }

    FILE *fileDestination = fopen(argv[2], "w");
    if (fileDestination == NULL)
    {
        printf("Could not open destination file.\n");
        return 1;
    }
    
    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    BYTE header[HEADER_SIZE];
    fread(header, sizeof(BYTE), HEADER_SIZE, fileSource);//write from the source file to the header
    fwrite(header, sizeof(BYTE), HEADER_SIZE, fileDestination);

    // TODO: Read samples from input file and write updated data to output file
    SAMPLE_SIZE buffer;
    while(fread(&buffer, sizeof(SAMPLE_SIZE), 1, fileSource) == 1){
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(SAMPLE_SIZE), 1, fileDestination);
    }

    //close the files
    fclose(fileSource);
    fclose(fileDestination);
    return 0;    
}
