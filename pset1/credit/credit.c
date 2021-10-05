#include <stdio.h>
#include <cs50.h>

int find_len_of_cc_number(long number);
void print_int_array(int aray[], int len);
int get_sum_of_addition_array(int aray[], int len);
int get_sum_of_multiplication_array(int aray[], int len);
void check_card_number_for_validity(int sum_of_both_arrays, int array_of_cc_numbers[], int cc_number_len);

int main(void)
{
    //get number from user
    long cc_number = get_long("long: ");
    
    //find out how many numbers are in the cc number
    int cc_number_len = find_len_of_cc_number(cc_number);
    
    //Create the array for the cc number. Creates the array backwords!!
    int array_of_cc_number[cc_number_len];
    long temp_user_cc_number = cc_number;
    for (int i = 0; i < cc_number_len; i++)
    {
        array_of_cc_number[i] = temp_user_cc_number % 10;
        temp_user_cc_number /= 10;
    }
    
    //check to see if the cc number is an odd number of digits 
    //if its odd add 1 to the length. This takes into account of the last number in the card.
    int array_of_digits_to_be_added_len = cc_number_len / 2; 
    if (cc_number_len % 2 == 1) 
    {
        array_of_digits_to_be_added_len++;
    }

    //create array of numbers to just be added
    int array_of_digits_to_be_added[array_of_digits_to_be_added_len];
    for (int i = 0; i < array_of_digits_to_be_added_len; i++)
    {
        array_of_digits_to_be_added[i] = array_of_cc_number[i * 2];
    }
    //get_sum_of_addition_array
    int sum_of_addition_array = get_sum_of_addition_array(array_of_digits_to_be_added, array_of_digits_to_be_added_len);

    //create array of numbers to be multiplied
    int array_of_digits_to_be_multiplied_len = cc_number_len / 2;
    int array_of_digits_to_be_multiplied[array_of_digits_to_be_multiplied_len];
    for (int i = 0; i < array_of_digits_to_be_multiplied_len; i++)
    {
        array_of_digits_to_be_multiplied[i] = array_of_cc_number[i * 2 + 1];
    }
    //get sum of multiplication array
    int sum_of_multipication_array = get_sum_of_multiplication_array(array_of_digits_to_be_multiplied, 
                                     array_of_digits_to_be_multiplied_len);

    //check to see if card is valid
    //add sum of addition array and sum of multiplication array together
    int sum_of_both_arrays = sum_of_addition_array + sum_of_multipication_array;
    //check the card number for validity
    check_card_number_for_validity(sum_of_both_arrays, array_of_cc_number, cc_number_len);
}

//print the arrary for debugging
void print_int_array(int aray[], int length_of_array)
{
    for (int i = 0; i < length_of_array; i++)
    {
        printf("%i", aray[i]);
    }
    printf("\n");
}

//find the length of the cc number given by the user
int find_len_of_cc_number(long number)
{
    long temp_user_cc_number = number;
    int cc_number_len = 0;
    do 
    {
        ++cc_number_len;
        temp_user_cc_number /= 10;
    }
    while (temp_user_cc_number);
    return cc_number_len;
}

// get the sum of the addition array
int get_sum_of_addition_array(int aray[], int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += aray[i];
    }
    return sum;
}

//get the sum of the multiplication array
int get_sum_of_multiplication_array(int aray[], int len)
{
    //multiply old array by 2
    int array_multiplied_by_2[len];
    for (int i = 0; i < len; i++)
    {
        array_multiplied_by_2[i] = aray[i] * 2;
    }
    //get len of new temp array
    int new_len = 0;
    for (int i = 0; i < len; i++)
    {
        if (array_multiplied_by_2[i] < 10)
        {
            new_len++;
        } 
        else
        {
            new_len += 2;
        }
    }
    // fill the array so that all the digits are singles
    int array_in_single_digits[new_len];
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (array_multiplied_by_2[i] < 10)
        {
            array_in_single_digits[j] = array_multiplied_by_2[i];
            j++;
        } 
        else if (array_multiplied_by_2[i] >= 10)
        {
            int temp = array_multiplied_by_2[i];
            array_in_single_digits[j] = temp % 10;
            j++;
            temp /= 10;
            array_in_single_digits[j] = temp % 10;
            j++;
        }
    }
    
    int sum = get_sum_of_addition_array(array_in_single_digits, new_len);
    return sum;
}

//check the card number for validity
void check_card_number_for_validity(int sum_of_both_arrays, int array_of_cc_numbers[], int cc_number_len)
{
    if (sum_of_both_arrays % 10 == 0)
    {
        if ((cc_number_len == 13 || cc_number_len == 16) && array_of_cc_numbers[cc_number_len - 1] == 4) // check for VISA  
        {
            printf("VISA\n");
        }
        else if (cc_number_len == 16 && array_of_cc_numbers[cc_number_len - 1] == 5 && (array_of_cc_numbers[cc_number_len - 2] == 1 
                 || array_of_cc_numbers[cc_number_len - 2] == 2 ||  array_of_cc_numbers[cc_number_len - 2] == 3 
                 ||  array_of_cc_numbers[cc_number_len - 2] == 4 ||  array_of_cc_numbers[cc_number_len - 2] == 5))
        {
            printf("MASTERCARD\n");
        }   
        else if (cc_number_len == 15 && array_of_cc_numbers[cc_number_len - 1] == 3 && (array_of_cc_numbers[cc_number_len - 2] == 4 
                 || array_of_cc_numbers[cc_number_len - 2] == 7))
        {
            printf("AMEX\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}