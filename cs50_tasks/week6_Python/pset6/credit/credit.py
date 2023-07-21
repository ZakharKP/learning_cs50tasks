from cs50 import get_string
import re


def main():

    # get_card_number
    card = get_card()

    # let's start magik
    print(whitch_card(card))


# get card number


def get_card():
    while True:
        card = get_string("Please Input Card number: ")
        # check if the it is a number
        if re.match("\d*$", card):
            break
        else:
            print("Try again")
    # return card number
    return card


# check if it's a real card


def is_ok(card):
    # reverce our card number
    card = card[::-1]
    # implement control sum as 0 and index
    control = 0
    index = 0
    # start Luch's Algorytm
    for i in card:
        if index % 2 == 0:
            control += int(i)
        else:
            a = int(i)*2
            b = a % 10
            a = int(a / 10)
            control += a + b
        index += 1
    return (control % 10) == 0

# check what kind of card it is


def whitch_card(card):
    # take firs two number's of card number
    firstN = card[:2]
    firstN = int(firstN)
    # take card long
    howM = len(card)
    # check if it's a real card
    is_valid = is_ok(card)
    # implement card names
    visa = "VISA"
    mastercard = "MASTERCARD"
    amex = "AMEX"
    other = "INVALID"
    # chek whith kind of card it is
    if howM == 15 and (firstN == 34 or firstN == 37) and is_valid:
        return amex
    elif howM == 16 and (firstN > 50 and firstN < 56) and is_valid:
        return mastercard
    elif (howM == 13 or howM == 16) and (int(firstN/10) == 4) and is_valid:
        return visa
    else:
        return other


main()
