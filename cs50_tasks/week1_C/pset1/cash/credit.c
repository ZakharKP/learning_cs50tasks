#include<stdio.h>
#include <cs50.h>

/// values

/// get card number
long getCard()
{
    long num;
    do
    {
        num = get_long("Please input your card number \n");
        if (num < 0)
        {
            printf("Try another one");
        }
    }
    while (num < 0);
    return num;
}

/// how much numbers have card number
int howMuch(long num)
{
    int count = 0;
    while (num > 0)
    {
        num = num/10;
        count++;
    }
    return count;
}

/// we need first two numbers;
int firstNum (long num)
{
    while (num > 99)
    {
        num = num/10;
    }
    return num;
}

// check Luch's Algorytm
bool isOk(long num)
{
    int a, b, c;
    int code = 0;
    while (num > 0)
    {
        a = num % 10;
        num = num / 10;
        b = num % 10 * 2;
        c = b % 10;
        b = b/10;
        code = code + a + b + c;
        num = num/10;
    }
    int check = code % 10;
    return check == 0;
}

/// what kind of card
string whatCard (long num)
{
    int firstN = firstNum(num);
    int howM = howMuch(num);
    bool isValid = isOk(num);

    string visa = "VISA";
    string mastercard = "MASTERCARD";
    string amex = "AMEX";
    string other = "INVALID";
    if (howM == 15 && (firstN == 34 || firstN == 37) && isValid)
    {
        return amex;
    }
    else if (howM == 16 && (firstN > 50 && firstN < 56) && isValid)
    {
        return mastercard;
    }
    else if ((howM == 13 || howM == 16 )&& (firstN/10 == 4) && isValid)
    {
        return visa;
    }
    else return other;
}


int main (void)
{
    long card = getCard();
    printf("%s\n" , whatCard(card));

}
