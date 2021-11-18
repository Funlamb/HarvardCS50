#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int letter_cnt = 0;
    int word_cnt = 1;
    int sentence_cnt = 0;

    //Count letters, words, and sentences
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letter_cnt++;
        }
        else if (isspace(text[i]))
        {
            word_cnt++;
        } 
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?') 
        {
            sentence_cnt++;
        }
    }

    // L is the average number of letters per 100 words in the text.
    // S is the average number of sentences per 100 words in the text.
    float L = (float) letter_cnt / word_cnt * 100;
    float S = (float) sentence_cnt / word_cnt * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    //round float of index to an integer
    int grade_lvl = roundf(index);
    //display output per conditions
    if (grade_lvl < 1)
    {
        printf("Before Grade 1\n");
    } 
    else if (grade_lvl > 16)
    {
        printf("Grade 16+\n");
    } 
    else 
    {
        printf("Grade %i\n", grade_lvl);
        
    }
}