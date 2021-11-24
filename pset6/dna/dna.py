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
        SRTs = reader.fieldnames
        for row in reader:
            suspects.append(row)

    # read the sequence.txt
    sequence = ''
    with open(sys.argv[2]) as file:
        for line in file:
            sequence = line

    # get Short strands we are look to find
    SRTs.pop(0)
    dict_of_tests = dict.fromkeys(SRTs, 0)
    
    for SRT in SRTs:
        # get length of seq we are checking
        SRT_length = len(SRT)
        # find first match
        i = 0
        max_SRT_count = 0
        curr_SRT_count = 0
        while i < len(sequence):
            # if matched go to next set
            if SRT == sequence[i:i+SRT_length]:
                i += SRT_length
                curr_SRT_count += 1
                if curr_SRT_count > max_SRT_count:
                    max_SRT_count = curr_SRT_count
            # else continue to next letter
            else:
                curr_SRT_count = 0
                i += 1
        dict_of_tests[SRT] = max_SRT_count
    print(guilty_sus(suspects, dict_of_tests))

# Must find the longest length of STRs. Not total number of matches. 
def guilty_sus(suspects, dict_of_srt):
    name = "No match"
    # compare to suspects
    # find matches in sequence
    for sus in suspects:
        name_of_sus = sus.pop("name")
        for item in sus:
            sus[item] = int(sus[item])
        if sus == dict_of_srt:
            name = name_of_sus
    # print(suspects)
    # print(dict_of_srt)
    return name

if __name__ == "__main__":
    main()