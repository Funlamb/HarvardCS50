"""program that computes the approximate grade level needed to comprehend some text"""
from cs50 import get_string
import re
import string

text = get_string("Text: ")

word_count = len(text.split())

letter_count = 0
# Calculate number of letters
for words in text:
    for letter in words:
        if letter in string.ascii_letters:
            letter_count += 1

sentance_count = 0
# Calculate number of senteances
for words in text:
    for punctuation in words:
        if punctuation in [".", "?"]:
            sentance_count += 1

# Number of letters per 100 words
L = float(letter_count / word_count) * 100

# Number of sentences per 100 words
S = sentance_count / word_count * 100

grade = 0.0588 * L - 0.296 * S - 15.8
if grade > 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print("Grade " + str(int(round(grade, 0))))