import csv
import sys

# don't need to change str to int you can just change it when you need to check it. 
# data.csv

# name,AGATC,AATG,TATC
# Alice,2,8,3
# Bob,4,1,5
# Charlie,3,2,5

# sequence.txt
# AAGGTAAGTTTAGAATATAAAAGGTGAGTTAAATAGAATAGGTTAAAATTAAAGGAGATCAGATCAGATCAGATCTATCTATCTATCTATCTATCAGAAAAGAGTAAATAGTTAAAGAGTAAGATATTGAATTAATGGAAAATATTGTTGGGGAAAGGAGGGATAGAAGG

def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
    
    suspects = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        top = reader.fieldnames
        for row in reader:
            suspects.append(row)

    # read the sequence.txt
    sequence = ''
    with open(sys.argv[2]) as file:
        for line in file:
            sequence = line
    print(sequence)

    # get Short strands we are look to find
    top.pop(0)
    print(top)
    dict_of_tests = dict.fromkeys(top, 0)
    # find matches in sequence
    for seq in top:
        # get length of seq we are checking
        length = len(seq)
        i = 0
        j = length
        chunks = [sequence[i:i+j] for i in range(0, len(sequence))]
        for item in chunks:
            if item == seq:
                # add to a dict of what was found
                dict_of_tests[seq] += 1
    print(dict_of_tests)

    # compare to suspects
    for sus in suspects:
        name = sus.pop("name")
        for item in sus:
            sus[item] = int(sus[item])
        print(sus)
        if sus == dict_of_tests:
            print(name)



if __name__ == "__main__":
    main()