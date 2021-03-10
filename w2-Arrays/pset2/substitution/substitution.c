#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string encrypt(string plain, string key);
int key_check(string key);
string case_convert(string text, string type);

int main(int argc, string argv[])
{
// program argument checks
    //correct number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    //check key validity
    if (key_check(key) != 0)
    {
        printf("Key must contain 26 unique characters, letters only\n");
        return 1;
    }


    string plain = get_string("plaintext: ");

    //convert plaintest to ciphertext
    string cipher = encrypt(plain, key);

    printf("ciphertext: %s\n", cipher);

    return 0;

}


string encrypt(string plain, string key)
{
    int len = strlen(plain);

    string cipher = plain;

    //checks each character of ciphertext and converts it
    //to the equivilant array position in the key, while
    //adjusting for upper or lower case
    for (int i = 0; i < len; i++)
    {
        int c = (int)plain[i];

        if (c >= 65 && c <= 90) //uppercase
        {
            cipher[i] = toupper(key[(c - 65)]);
        }
        else if (c >= 97 && c <= 122) //lowercase
        {
            cipher[i] = tolower(key[(c - 97)]);
        }
        else
        {
            cipher[i] = (char)c;
        }
    }
    return cipher;
}

int key_check(string key)
{
    int len = strlen(key);

    // checks for correct length
    if (len != 26)
    {
        return 1;
    }

    int n = 0;

    for (int i = 0; i < len; i++)
    {
        int c = (int)key[i];

        //checks for non alpabetic characters
        if (!(c >= 65 && c <= 90) && !(c >= 97 && c <= 122))
        {
            n = n + 1;
        }

        for (int j = (i + 1); j < len; j++)
        {
            int d = (int)key[j];

            //checks for duplicate characters
            if (c == d)
            {
                n = n + 1;
            }
        }
    }

    //if only alpabetics characters return 0
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}