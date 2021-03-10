#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // do-while to ensure input is between 0 and 9
    int width; //initialize variable
    do
    {
        width = get_int("How wide is the base?: "); // get input from user
    }
    while ((width < 1) || (width > 8));


    // Outer for loop for changing rows
    int i;
    for (i = 1; i <= width; ++i)
    {
        int j;
        int length = width + i + 1; //initialize variable for number of columns

        // inner for loop to print columns
        for (j = 0; j <= length; ++j)
        {

            // conditions when spaces are needed
            if ((j < width - i) || (j == width) || (j == width + 1))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}