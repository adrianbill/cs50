#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //prompt user for input
    string name = get_string("What is your name?\n");
    printf("Hello, %s\n", name);
}