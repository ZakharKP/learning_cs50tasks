#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start;
    int end;
    int countY = 0;
    // TODO: Prompt for start size
    do{
        start = get_int("Please give me start size of lama's population\n");
        if (start < 9) printf("Try again Bro!(more or equal 9)\n");
    }while(start < 9);

    // TODO: Prompt for end size
    do{
        end = get_int("How much lama\'s do you want?\n");
        if (end < start) printf("Please give me reasonable number\n");
    }while(end < start);
    // TODO: Calculate number of years until we reach threshold
    while(start < end){
        start = start + start/3 - start/4;
        countY++;
    }
    // TODO: Print number of years
    printf("Years: %i", countY);
}