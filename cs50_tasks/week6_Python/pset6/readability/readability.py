from cs50 import get_string
import re


def main():
    # get text
    text = get_string("Text: ")
    # let magic begin
    print_index(text)


# find index
def get_index(text):
    # words_index?
    words_index = 100.00/len(re.split(" ", text))
    # quantity of sentences in 100 words
    sentesces_index = len(re.findall("[!\.\?]", text)) * words_index
    # quantity of letters
    letter_index = len(re.findall("[a-zA-Z]", text)) * words_index
    # return index
    index = 0.0588 * letter_index - 0.296 * sentesces_index - 15.8
    return round(index)

# print index


def print_index(text):
    # get index
    index = get_index(text)
    # print result
    if index < 1:
        print("Before Grade 1n")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()