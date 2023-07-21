#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool checkKey(string key);
string caesar(int key, string text);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        exit(1);
    }
    bool check = checkKey(argv[1]);
    if(!check)
    {
        printf("Usage: %s key\n", argv[0]);
        exit(1);
    }

    string text = get_string("plaintext: ");
    int key = atoi(argv[1]);
    string out = caesar(key, text);
    printf("ciphertext: %s\n", out);

}

//Check Key
bool checkKey(string key)
{
    int n = strlen(key);
    for(int i = 0; i < n; i++)
    {
        if(!isdigit(key[i]))
        {
            return false;
        }

    }

    return true;
}

string caesar(int key, string text)
{
    int x = strlen(text);
    for(int i = 0; i < x; i++)
    {

        if(isalpha(text[i]))
        {
            char abci = toupper(text[i]) - 65;
            char ceassym = ((abci + key) % 26) + 65;

            if(isupper(text[i])) text[i] = toupper(ceassym);
            else text[i] = tolower(ceassym);
        }


    }
    return text;
}