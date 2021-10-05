#include <stdio.h>
#include <cs50.h>

int get_short_range_int(int max);

int main(void)
{
    int max_height = 8;
    int height;
    //get user to give number between 1 and max_height
    height = get_short_range_int(max_height);
    
    //2d array
    //print the first # then \n
    //print the two ## then \n
    
    //print mario blocks acorrding to height
    int current_height = height;
    for (int i = 0; i < height; i++)
    {
        for (int k = 0 ; k < current_height - 1; k++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
        current_height--;
    }
}

int get_short_range_int(int max)
{
    int n;
    do
    {
        n = get_int("Please enter a number between 1 and %i:", max);
    }
    while (n < 1 || n > max);
    return n;
}