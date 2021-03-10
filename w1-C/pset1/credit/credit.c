#include <cs50.h>
#include <stdio.h>

void invalid(void);
int luhn(long number);
int return_digit(long number, int digits, int place);

int main(void)
{
    // prompt user for credit card number
    long number = get_long("Number: ");

    // filters out zero and negative numbers
    if (number <= 0)
    {
        invalid();
    }
    else
    {
        int digits = luhn(number);

        if (digits == 0)
        {
            invalid();
        }
        else
        {
            // returns the first digit
            int d1 = return_digit(number, digits, 1);

            // returns the seconf digit
            int d2 = return_digit(number, digits, 2);

            // combines first two digits for easier comparison against AMEX and MasterCard conditions
            int d1_2 = 10 * d1 + d2; // com

            // checks number against company constraints
            if ((d1_2 == 34 || d1_2 == 37) && digits == 15)
            {
                printf("AMEX\n");
            }
            else if ((d1_2 >= 51 && d1_2 <= 55) && digits == 16)
            {
                printf("MASTERCARD\n");
            }
            else if (d1 == 4 && (digits == 13 || digits == 16))
            {
                printf("VISA\n");
            }
            else
            {
                invalid();
            }
        }
    }
}




//prints invalid
void invalid(void)
{
    printf("INVALID\n");
}




// performs luhn's algorythm and returns the number of digits if valid
int luhn(long number)
{
    int count = 1;
    int length = 0;
    long digit;
    long holder;
    long place = number;
    int sum = 0, sumd2;

    while (place > 0)
    {
        holder = place;
        place = place / 10;
        digit = holder - place * 10;
        int d1 = 0, d2 = 0;

        if (count % 2 == 0)
        {
            d1 = (digit * 2) / 10;
            d2 = (digit * 2) - (d1 * 10);

            sum = sum + d1 + d2;
        }
        else
        {
            sum = sum + digit;
        }

        ++count;

    }

    sumd2 = sum - (sum / 10 * 10);

    if (sum % 10 != 0)
    {
        return 0;
    }
    else
    {
        return count - 1;
    }
}

int return_digit(long number, int digits, int place) // returns the value of the the digit in locatino idicated by "place"
{
    long reducer = 1;

    for (int i = digits - place; i > 0; --i) // determines how much to devide the number by
    {
        reducer = reducer * 10;
    }

    int digit = (number / reducer) - 10 * (number / reducer / 10); // removes any digits to the left of the desired digit

    return digit;
}