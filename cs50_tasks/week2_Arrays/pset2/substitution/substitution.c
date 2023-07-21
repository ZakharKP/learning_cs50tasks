#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


bool checkKey(string key);
string convert (string key, string text);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        exit(1);
    }
    bool check = checkKey(argv[1]);
    if(!check) exit(1);


    string text = get_string("plaintext: ");
    string out = convert(argv[1], text);
    printf("ciphertext: %s\n", out);

}

//Check Key
bool checkKey(string key)
{
    int n = strlen(key);
    if(n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            if(!isalpha(key[i]))
            {
                printf("Key must only contain alphabetic characters.\n");
                return false;
            }
            for(int j = i+1; j < n; j++)
            {
                if(tolower(key[i]) == tolower(key[j]))
                {
                printf("Key must not contain repeated characters.\n");
                return false;
                }
            }
        }
    }
    return true;
}

string convert (string key, string text)
{
    char abc[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int x = strlen(key);
    int y = strlen(text);
    string conver = text;
    for(int j = 0; j < y; j++)
    {
        for(int i = 0; i < x; i++)
        {
            if(tolower(abc[i]) == tolower(text[j]))
            {
            if(isupper(text[j])) text[j] = toupper(key[i]);
            else text[j] = tolower(key[i]);
            break;
            }
        }
    }
    return conver;
}