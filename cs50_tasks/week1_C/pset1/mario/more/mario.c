#include<stdio.h>
#include <cs50.h>


int height()
{
// insetr size
    int a;
    do
    {
        a = get_int("Bro! Say How Much steps you want to give Mario for running?\n");
        if ( a < 1 || a > 8)
        {
            printf("Don't be so foul Bro!\n");
        }
    }
    while (a < 1 || a > 8);

    return a;
}
// Draw Columns
void drawColumns(int steps)
{

    int spases = steps - 1;
    int bricks = 1;
    for (int i = 0; i < steps; i++)
    {
// draw first column
        int x = spases;
        int y = bricks;
        while(x > 0)
        {
            printf(" ");
            x--;
        }

        while (y > 0)
        {
            printf("#");
            y--;
        }
// draw seckond column
        printf("  ");
        y = bricks;
        while (y > 0)
        {
            printf("#");
            y--;
        }
        printf("\n");
        spases--;
        bricks++;

    }
}

int main(void)
{
    printf("Hello Bro!!!\n");
    drawColumns(height());

}