// Cracks a given hashed password

#define _XOPEN_SOURCE

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void nesting_alpha_roll(string working_string, string password_to_hack, string salt,
                        int string_length, int current_level);
char alpha_one_up(char c);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string password_to_hack = argv[1]; // Enter pre-obtained hashed password.
        string salt = "50"; // Hard-coding per spec.

        // These represent the "passwords" we'll test, compare, and update until a match is found.
        char one[] = {'A', '\0'};
        char two[] = {'A', 'A', '\0'};
        char three[] = {'A', 'A', 'A', '\0'};
        char four[] = {'A', 'A', 'A', 'A', '\0'};
        char five[] = {'A', 'A', 'A', 'A', 'A', '\0'};

        nesting_alpha_roll(one, password_to_hack, salt, 1, 0);
        nesting_alpha_roll(two, password_to_hack, salt, 2, 0);
        nesting_alpha_roll(three, password_to_hack, salt, 3, 0);
        nesting_alpha_roll(four, password_to_hack, salt, 4, 0);
        nesting_alpha_roll(five, password_to_hack, salt, 5, 0);
        printf("This hashed password doesn't correspond to a 5-alpha plaintext password.\n");
    }
    else
    {
        printf("Fail - exactly one hashed password, please.\n");
        return 1;
    }
}

// For a given array of characters, encrypts into hash and compares to obtained hashed password.
// If the same, prints out the correct password. Otherwise, it rolls up alphabetically and tries again.
void nesting_alpha_roll(string working_string, string password_to_hack,
                        string salt, int string_length, int current_level)
{
    if (current_level == (string_length - 1))
    {
        do
        {
            // printf("%s  ", working_string);
            if (strcmp(password_to_hack, crypt(working_string, salt)) == 0)
            {
                printf("%s\n", working_string);
                exit(0);
            }
            working_string[current_level] = alpha_one_up(working_string[current_level]);
        }
        while (working_string[current_level] != 'A');

    }
    else
    {
        do
        {
            nesting_alpha_roll(working_string, password_to_hack, salt, string_length, (current_level + 1));
            working_string[current_level] = alpha_one_up(working_string[current_level]);
        }
        while (working_string[current_level] != 'A');
    }
}

// Returns the next consecutive character on the alpha roll
char alpha_one_up(char c)
{
    if (isalpha(c))
    {
        switch (c)
        {
            case 'Z':
                return 'a';
                break;

            case 'z':
                return 'A';
                break;

            default:
                c++;
                return c;
                break;
        }
    }
    else
    {
        printf("Error - gave non-alpha to alpha_one_up\n");
        return c;
    }

}