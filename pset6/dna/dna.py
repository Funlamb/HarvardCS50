import csv
import sys

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
    
    # create a dict of suspects
    suspects = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        # get our SRTs to test
        SRTs = reader.fieldnames
        # get our list of suspects
        for row in reader:
            suspects.append(row)

    # read the sequence.txt
    sequence = ''
    with open(sys.argv[2]) as file:
        for line in file:
            sequence = line

    # get Short strands we are look to find
    # pop the name bacuse we will never find a name in a DNA strand
    SRTs.pop(0)
    dict_of_SRTs = dict.fromkeys(SRTs, 0)
    
    for SRT in SRTs:
        # get length of seq we are checking
        SRT_length = len(SRT)
        # find first match
        # keep track of the maximum length of SRTs in a strand
        max_SRT_count = 0
        curr_SRT_count = 0
        # use a while loop to loop through DNA and go through indivdual letters or sets if we found a match
        i = 0
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
        dict_of_SRTs[SRT] = max_SRT_count
    print(guilty_sus(suspects, dict_of_SRTs))

# Must find the longest length of STRs. Not total number of matches. 
def guilty_sus(suspects, dict_of_srt):
    # start name off as no match in case we do not find a match
    name = "No match"
    # compare to suspects
    for sus in suspects:
        # pop the so that the dicts only campare the SRTs
        name_of_sus = sus.pop("name")
        # change items in the sus to ints
        for item in sus:
            sus[item] = int(sus[item])
        #compare dicts
        if sus == dict_of_srt:
            name = name_of_sus
    return name

if __name__ == "__main__":
    main()