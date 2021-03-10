#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int read_index(float L, float S); //performs coleman Liau index calculation
int sents(string text); //calculates the number of sentences in a string
int words(string text); //calcualtes the number of words in a string
int letters(string text); //calculates the number of letters in a string


int main(void)
{
    string text = get_string("Text: ");

    int num_s = sents(text);
    int num_w = words(text);
    int num_l = letters(text);

    // printf("Sentences: %i\n", num_s);
    // printf("Words: %i\n", num_w);
    // printf("Letters: %i\n", num_l);

    float S = 100.0 * num_s / num_w;
    float L = 100.0 * num_l / num_w;

    // printf("S: %f\n", S);
    // printf("L: %f\n", L);

    int level = read_index(L, S);

    if (level >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", level);
    }
}

int read_index(float L, float S)
{
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}

int sents(string text)
{
    int len = strlen(text);
    int sents = 0;

    for (int i = 0; i < len; i++)
    {
        int c = (int)(text[i]);
        if (c == 33 || c == 46 || c == 63) // counts the number of times '.', '!', or '?' is used
        {
            sents = sents + 1;
        }
    }

    return sents;
}

int words(string text)
{
    int len = strlen(text);
    int words = 1; // must start at 1 as the number of spaces == number of words + 1

    for (int i = 0; i < len; i++)
    {
        int c = (int)(text[i]);
        if (c == 32) // counts the number of spaaces
        {
            words = words + 1;
        }
    }

    return words;
}

int letters(string text)
{
    int len = strlen(text);
    int letters = 0;

    for (int i = 0; i < len; i++)
    {
        int c = (int)(tolower(text[i])); //converts all letters to lower case to make conditions easier
        if (c >= 97 && c <= 122) //checks if between ascii values for a to z
        {
            letters = letters + 1;
        }
    }

    return letters;
}