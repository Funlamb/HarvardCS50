#import <stdio.h>
#import <cs50.h>
#import <math.h>

int get_coin_count(float change_due);

int main(void)
{
    //promt user for a positive float value
    float change_due;
    do
    {
        change_due = get_float("Give us your change:\n");
    }
    while (change_due <= 0.0);

    int coin_count = get_coin_count(change_due);//get coin_count using our created function
    printf("%i\n", coin_count);

}

int get_coin_count(float change_due)
{
    //get change in int to avoid rounding errors
    int change_due_int = (int) round(change_due * 100);

    int coin_count = 0; //Keep track of the number of coins we will give back
    //find out how many quarters
    int quarter = 25;
    while (change_due_int >= quarter)
    {
        coin_count++;
        change_due_int -= quarter;
    }
    int dime = 10;
    while (change_due_int >= dime)
    {
        coin_count++;
        change_due_int -= dime;
    }
    int nickle = 5;
    while (change_due_int >= nickle)
    {
        coin_count++;
        change_due_int -= nickle;
    }
    int penny = 1;
    while (change_due_int >= penny)
    {
        coin_count++;
        change_due_int -= penny;
    }
    return coin_count;
}