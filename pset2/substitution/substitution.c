#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
// #include <iostream>

int print_usage(string a);
int check_key_for_duplecates(string a);

int main(int argc, string argv[])
{
    if (argc != 2)//throw out everything else and show the user use to use the program
    {
        return print_usage(argv[0]);
    }

    //create a string for ciphertext
    string key = argv[1]; //get key from argv[1]

    int len = strlen(key);
    printf("Len: %i\n", len);

    //check that argv is 26 letters long
    if (len != 26)
    {
        return print_usage(argv[0]);
    }

    //make sure every char in argv[1] is a letter
    for (int i = 0, n = len; i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key not letter %i", i);
            return print_usage(argv[0]); //return program if wrong key
        }
    }
    if (check_key_for_duplecates(key) != 0)
    {
        return print_usage(argv[0]);
    }
    
    string plaintext = get_string("Plain Text: ");
    int plaintext_len = strlen(plaintext);
    printf("ciphertext: ");
    //append correct letters to string
    for (int i = 0; i < plaintext_len; i++)
    {
        //check is uppercase
        if (isupper(plaintext[i]))//handle upper case letters
        {
            //replace with cipher
            printf("%c", toupper(key[plaintext[i] - 'A']));
        }
        else if (islower(plaintext[i]))//handle lower case letters
        {
            //replace with cipher
            printf("%c", tolower(key[plaintext[i] - 'a']));
        }
        //append all other charecters as they are: spaces, cammas, exclimations
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}

int print_usage(string a)
{
    printf("Usage: %s key\n", a);
    return 1;
}

int check_key_for_duplecates(string a)
{
    string check = a;
    //change all letters to capital letters
    for (int i = 0; i < 26; i++)
    {
        check[i] = toupper(check[i]);
    }
    int duplicates = 0;
    int count;
    for (int i = 0, n = strlen(check); i < n; i++)
    {  
        count = 1;  
        for (int j = i + 1; j < n; j++) 
        {  
            if (check[i] == check[j] && check[i] != ' ') 
            {  
                count++;
                duplicates++;
                //Set string[j] to 0 to avoid printing visited character  
                check[j] = '0';  
            }  
        }  
        //A character is considered as duplicate if count is greater than 1  
        if (count > 1 && check[i] != '0')
        {
            printf("%c\n", check[i]);  
        }
    }  
    printf("Number of dupes : %i\n", duplicates);
    printf("%s\n", check);
    if (duplicates == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}