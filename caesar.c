// Encrypts a user's message with Caesar's code.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_encrypted_string(string s, int n);
char encrypt_letter(char c, char d, int m);

int main(int argc, string argv[])
{
    // Start by rejecting all attempts to execute with either no or 2+ arguments for the key.
    if (argc == 2)
    {
        // Variables:
        // "k" - the key, i.e. number of rotations (pulled from command line)
        // "plain_text" - the user's message to encrypt (from user prompt during execution)
        int k = (atoi(argv[1]) % 26);
        string plain_text = get_string("plaintext: ");

        // Encrypt and print the user's string using a key of k rotations.
        printf("ciphertext: ");
        print_encrypted_string(plain_text, k);
        printf("\n");
    }
    else
    {
        printf("Fail :*(\n");
        return 1;
    }
}

// Encrypts and prints a string using a key of n rotations.
void print_encrypted_string(string s, int n)
{
    for (int i = 0; i < strlen(s); i++)
    {
        char plain_letter = s[i];

        // 'Z' is the turn-around point for upper-case letters.
        if (isupper(plain_letter))
        {
            printf("%c", encrypt_letter(plain_letter, 'Z', n));
        }

        // 'z' is the turn-around point for lower-case letters.
        else if (islower(plain_letter))
        {
            printf("%c", encrypt_letter(plain_letter, 'z', n));
        }

        // non-letters are passed through.
        else
        {
            printf("%c", plain_letter);
        }

    }
}

// Encrypts a letter with a key of m rotations; rolls back in ASCII by 26 characters every time you hit character d.
char encrypt_letter(char c, char d, int m)
{
    if (c + m > d)
    {
        return c - 26 + m;
    }
    else
    {
        return c + m;
    }
}