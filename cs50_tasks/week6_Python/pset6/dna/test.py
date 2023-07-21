import re

def main():
# list1 = []
# for match in re.finditer("AGATC", "GGGGAATATGGTTATTAAGTTAAAGAGAAAGAAAGATGTGGGTGATATTAATGAATGAATGAATGAATGAATGAATGAATGTTATGATAGAAGGATAAAAATTAAATAAAATTTTAGTTAATAGAAAAAGAATATATAGAGATCAGATCTATCTATCTATCTTAAGGAGAGGAAGAGATAAAAAAATATAATTAAGGAA"):
#    list1.append(match.end())

# print(list1)
    dna = result_DNA("AGATC", "GGGGAATATGGTTATTAAGTTAAAGAGAAAGAAAGATGTGGGTGATATTAATGAATGAATGAATGAATGAATGAATGAATGTTATGATAGAAGGATAAAAATTAAATAAAATTTTAGTTAATAGAAAAAGAATATATAGAGATCAGATCTATCTATCTATCTTAAGGAGAGGAAGAGATAAAAAAATATAATTAAGGAA")
    print(dna)

def result_DNA(code, person_code):
    matches = []
    finish = -1
    counter = 0
    for match in re.finditer(code, person_code):
        print(match)
        if finish == match.start():
            counter +=1
        else:
            counter = 1
        matches.append(counter)
        finish = match.end()
    if matches:
        counter = max(matches)
    return counter


main()