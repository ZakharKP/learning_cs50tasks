#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
int fName = 0;
int SIZEBUFFER = 512;
bool isJpegStart(BYTE buffer[SIZEBUFFER]);
void recover(FILE *input, BYTE buffer[SIZEBUFFER]);
void writeJPG(FILE *input, FILE *ourJPG, BYTE buffer[SIZEBUFFER]);
void createAndStartWritingNewJPG(FILE *input, BYTE buffer[SIZEBUFFER], int callPosithion);


int main(int argc, char *argv[])
{
    //Check argv
    if(argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //open & check file
    FILE *input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Start recovering
    BYTE buffer[SIZEBUFFER];
    recover(input, buffer);
    //close input File
    fclose(input);
    return 0;
}

//start recover FILE
void recover(FILE *input, BYTE buffer[SIZEBUFFER])
{
    while(fread(buffer,sizeof(BYTE), SIZEBUFFER, input))
    {
        if(isJpegStart(buffer))
        {
            //create JPG file and start writing
            createAndStartWritingNewJPG(input, buffer, 1);
        }
    }
    return;
}

///check is JPG?
bool isJpegStart(BYTE buffer[SIZEBUFFER])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        return true;
    else
        return false;
}

// create new JPG file & start writing
void createAndStartWritingNewJPG(FILE *input, BYTE buffer[SIZEBUFFER], int callPosithion)
{
    // create file Name
    char *fileName = malloc(8);
    sprintf(fileName, "%03i.jpg", fName);
    //up count of filesNames
    fName++;
    //create & check new JPG file
    FILE *newJPG = fopen(fileName, "w");
    if(newJPG == NULL)
    {
        printf("Could not open file.\n");
        exit(1);
    }
    // free malloc
    free(fileName);
    //start writing
    writeJPG(input,  newJPG, buffer);
    //close FIRST jpg file
    if(callPosithion == 1) fclose(newJPG);

    return;
}
// write files
void writeJPG(FILE *input, FILE *ourJPG, BYTE buffer[SIZEBUFFER])
{
    //write buffer which we have
    fwrite(buffer, sizeof(BYTE), SIZEBUFFER, ourJPG);
    while(fread(buffer,sizeof(BYTE), SIZEBUFFER, input))
    {
        //chek is new buffer - start of JPG
        if(isJpegStart(buffer))
        {

            //close THIS jpg File
            fclose(ourJPG);
            // create and start writing of new JPG
            createAndStartWritingNewJPG(input, buffer, 0);
        }
        //if no - proceed writing
        else
        {
        fwrite(buffer, sizeof(BYTE), SIZEBUFFER, ourJPG);
        }
    }
    return;
}