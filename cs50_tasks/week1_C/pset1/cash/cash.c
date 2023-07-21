#include<stdio.h>
#include <cs50.h>


int quatro = 25;
int ten = 10;
int fife = 5;
int uno = 1;

int count = 0;

int sum()
{
    float f;
    do
    {
        f = (get_float("How much money do you need?\n")*100)/100;
        if (f < 0) 
        {
            printf("Don't be so boran BRO!!!\n");
        }
    
    }
    while (f < 0);

    return f * 10000 / 100;
}

int isMax(int sum, int c)
{

    while (sum >= c)
    {
        sum = sum - c;
        count++;
    }
    return sum;
}

void coin(int sum)
{
    int cQ = isMax(sum, quatro);
    int cT = isMax(cQ, ten);
    int cF = isMax(cT, fife);
    int cU = isMax(cF, uno);
}

int main(void)
{
    printf("Hello BRO!!!\n");
    coin(sum());
    printf("Take your %i coins BRO!!!", count);
}