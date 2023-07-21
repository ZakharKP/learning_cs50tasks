#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// try to readability test is the Coleman-Liau index.
//The Coleman-Liau index of a text is designed to output what (U.S.)
//grade level is needed to understand the text. The formula is:

//index = 0.0588 * L - 0.296 * S - 15.8

//Here, L is the average number of letters per 100 words in the text,
//and S is the average number of sentences per 100 words in the text.

int let = 0, spases = 0, symbols = 0;
void getSymb(string text);
int getIndex(string text);
void printIndex(string text);

int main (void)
{
    string text = get_string("Text: ");
    printIndex(text);
}

void printIndex(string text)
{
    int index = getIndex(text);
    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n" , index);
    }
}

int getIndex(string text)
{
    float index;
    getSymb(text);
    float inL, inS, ind;
    ind = 100.00 / (spases + 1);
    inL = let * ind;
    inS = symbols * ind;
    index = 0.0588 * inL - 0.296 * inS - 15.8;


    return round(index);
}

void getSymb(string text)
{
    int n = strlen(text);
    for(int i = 0; i < n; i++)
    {
        char c = text[i];
        if(isalpha(c)) let++;
        if(isspace(c)) spases++;
        if(c == '.' || c == '!' || c == '?') symbols++;
    }
}