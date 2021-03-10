#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //starting population size input, shold be greater than 9
    int pop_start;
    do
    {
        pop_start = get_int("Start size: ");
    }
    while (pop_start < 9);

    //final population size input should be greater than starting population
    int pop_end;
    do
    {
        pop_end = get_int("End size: ");
    }
    while (pop_end < pop_start);


    int pop_new = pop_start; //new annual population
    int n = 0; //number of years, must bre outside the while loop (scope)

    //calcualte the population change annually until it reachs the desired end
    while (pop_new < pop_end)
    {
        pop_new = pop_new + pop_new / 3 - pop_new / 4;
        n++; //increment years each time
    }
    // print the numbers of years
    printf("Years: %i\n", n);
}