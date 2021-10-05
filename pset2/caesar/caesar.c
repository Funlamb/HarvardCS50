#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int print_usage(string a);

int main(int argc, string argv[])
{
    if (argc != 2)//throw out everything else and show the user use to use the program
    {
        return print_usage(argv[0]);
    }
    
    int key_len = strlen(argv[1]); //get length of argument 1
        
    //make sure every char in argv[1] is a number
    for (int i = 0; i < key_len; i++)
    {
        if (!isdigit(argv[1][i])) 
        {
            return print_usage(argv[0]); //return program if NaN found
        }
    }
    
    int key = atoi(argv[1]); //turn the key into an int  
    key %= 26; // mod it by 26 so that it will wrap properly if needed

    //get user message
    string message = get_string("Your message: ");
    int message_len = strlen(message);
    
    // print the plaintext and cihpertext
    // printf("plaintext:  %s\n", message);
    printf("ciphertext: ");
    
    for (int i = 0; i < message_len; i++)
    {
        if (isupper(message[i]))//handle upper case letters
        {
            if (message[i] + key < 'Z')
            {
                printf("%c", message[i] + key);
            } 
            else 
            {
                printf("%c", message[i] + key - 26);
            }
        } 
        else if (islower(message[i]))//handle lower case letters
        {
            if (message[i] + key < 'z')
            {
                printf("%c", message[i] + key);
            } 
            else //handle all other characters
            {
                printf("%c", message[i] + key - 26);
            }
        } 
        else 
        {
            printf("%c", message[i]);
        }
    }
    printf("\n");
}

int print_usage(string a)
{
    printf("Usage: %s key\n", a);
    return 1;
}