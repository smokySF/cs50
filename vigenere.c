// Encrypt's a password with Vigenere's code.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> // for exit
#include <string.h>

void build_vigenere_key_code(string key_word, int key_code_length, int key_code[]);
int transform_to_vigenere_digit(char plain_character);
void encrypt_and_print_string(string plain_text, int key_code[], int key_code_length);
char encrypt_letter(char c, int m);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // Vigenere keyword from command line argument
        string key_word = argv[1];
        // Length of keyword
        int key_code_length = strlen(argv[1]);
        // Array representing the Vigenere values of each consecutive keyword letter
        int key_code[key_code_length];

        build_vigenere_key_code(key_word, key_code_length, key_code);
        string plain_text = get_string("plaintext: ");
        printf("ciphertext: ");
        encrypt_and_print_string(plain_text, key_code, key_code_length);
        printf("\n");
    }
    else
    {
        printf("Fail - Exactly one keyword, please!\n");
        return 1;
    }
}

// Updates a given array to represent a Vigenere key code (array of rotation values) from a given keyword (string).
void build_vigenere_key_code(string key_word, int key_code_length, int key_code[])
{
    for (int i = 0; i < key_code_length; i++)
    {
        // The ith character of the keyword
        char plain_character = key_word[i];

        // If alpha, transform into corresponding Vigenere integer. Otherwise, exit program.
        if (isalpha(plain_character))
        {
            key_code[i] = transform_to_vigenere_digit(plain_character);
        }
        else
        {
            printf("Fail - Keyword should only contain letters.\n");
            exit(1);
        }
    }
}

// Transforms an alpha character into its corresponding Vignere integer (i.e. number of rotations it implies).
int transform_to_vigenere_digit(char plain_character)
{
    if isupper(plain_character)
    {
        return plain_character - 'A';
    }
    else if islower(plain_character)
    {
        return plain_character - 'a';
    }
    else
    {
        return plain_character;
    }

}

// Encrypts and prints a plain_text string using a key code of Vigenere transformations.
void encrypt_and_print_string(string plain_text, int key_code[], int key_code_length)
{
    // The current location in the keycode
    int location_in_key_code = 0;

    for (int i = 0; i < strlen(plain_text); i++)
    {
        // The ith character in given plain_text string.
        char plain_letter = plain_text[i];

        // If alpha, encrypt according to Vigenere transformation + rotate Vigenere keycode. Otherwise, pass through the character.
        if (isalpha(plain_letter))
        {
            printf("%c", encrypt_letter(plain_letter, key_code[location_in_key_code]));
            if (location_in_key_code + 1 == key_code_length)
            {
                location_in_key_code = 0;
            }
            else
            {
                location_in_key_code++;
            }
        }
        else
        {
            printf("%c", plain_letter);
        }
    }
}

// Encrypts a letter with a key of m rotations; rolls back in ASCII by 26 characters every time you hit character d.
char encrypt_letter(char c, int m)
{
    if (isupper(c))
    {
        if (c + m > 'Z')
        {
            return c - 26 + m;
        }
        else
        {
            return c + m;
        }
    }
    else if (islower(c))
    {
        if (c + m > 'z')
        {
            return c - 26 + m;
        }
        else
        {
            return c + m;
        }
    }
    else
    {
        eprintf("Error in encrypt_letter");
        return c;
    }

}