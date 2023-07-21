import csv
import sys
import re


def main():

    # Check there are arguments in command line
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # read base of DNA
    base = []
    # keys of dictionary
    keys = []
    with open(sys.argv[1], "r") as dna_base:
        reader = csv.DictReader(dna_base)
        for person in reader:
            # make dna values ineger
            for i in list(person):
                if i != "name":
                    # incert key value
                    if str(i) not in keys:
                        keys.append(str(i))
                    # make value integer
                    person[i] = int(person[i])
            base.append(person)

    # read person DNA
    file_person = open(sys.argv[2], "r")
    person_code = str(file_person.read())
    file_person.close()

    # write dna code of person
    person_DNA = {}
    for code in keys:
        person_DNA[str(code)] = result_DNA(str(code), person_code)

    # find name
    name = find_person(person_DNA, base)

    # print name
    print(name)

# check person


def check_person(person, person_DNA):
    for i in list(person):
        if i != "name":
            if person[i] != person_DNA[str(i)]:
                return False
    return True


# find person


def find_person(person_DNA, base):
    for person in base:
        if check_person(person, person_DNA) == True:
            return person["name"]
    return "No match"


# count person DNA


def result_DNA(code, person_code):
    matches = []
    finish = -1
    counter = 0
    # find all mathes idex
    for match in re.finditer(code, person_code):
        if finish == match.start():
            counter += 1
        else:
            counter = 1
        matches.append(counter)
        finish = match.end()
    if matches:
        counter = max(matches)
    return counter


main()