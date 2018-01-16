#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Variables:
    long long ccnumber = 0;             // The number the user enters
    int brand = 0;                      // 0 = invalid, 1 = Visa, 2 = American Express, 3 = MasterCard
    int sum_rights = 0;                 // The sum of the right hand digits of each pair of digits
    int sum_lefts = 0;                  // Same, but for the left hand digits
    int add_to_sum_lefts = 0;           // Which sum are you adding to. 0 = sum_rights, 1 = sum_lefts.


    // Step 1: Get a value. Only accept long long values; re-prompt for other formats.
    ccnumber =
        get_long_long("Number: ");

    // Step 2: Once you have a number, run some basic checks to see if it meets basic
    // specs for a credit card. Return invalid if not formatted correct. (Do this step
    // (first to save recursion steps for invalid cards and to finalize brand variable
    // variable before we start changing it to check with Luhn's test.)
    if  (
        ((ccnumber >= 4000000000000) && (ccnumber <= 4999999999999))
        ||
        ((ccnumber >= 4000000000000000) && (ccnumber <= 4999999999999999))
    )
    {
        brand = 1;
    }

    else if (
        ((ccnumber >= 340000000000000) && (ccnumber <= 349999999999999))
        ||
        ((ccnumber >= 370000000000000) && (ccnumber <= 379999999999999))
    )
    {
        brand = 2;
    }

    else if  ((ccnumber >= 5100000000000000) && (ccnumber <= 5599999999999999))
    {
        brand = 3;
    }

    else
    {
        printf("INVALID\n");
    }

    //Step 3: If it's formatted like a major brand, run the Luhn test.
    if (brand != 0)
    {
        while (ccnumber != 0)
        {
            switch (add_to_sum_lefts)
            {
                case 0:
                    sum_rights = sum_rights + (ccnumber % 10);
                    ccnumber = ccnumber / 10;
                    add_to_sum_lefts++;
                    break;
                case 1:
                    sum_lefts = sum_lefts + ((2 * (ccnumber % 10)) % 10) + ((2 * (ccnumber % 10)) / 10);
                    ccnumber = ccnumber / 10;
                    add_to_sum_lefts--;
                    break;
                default:
                    printf("Your test failed!\n");
            }
        };

        if ((sum_lefts + sum_rights) % 10 == 0)
        {
            switch (brand)
            {
                case 1:
                    printf("VISA\n");
                    break;
                case 2:
                    printf("AMEX\n");
                    break;
                case 3:
                    printf("MASTERCARD\n");
                    break;
            }
        }

        else
        {
            printf("INVALID\n");
        }
    }
}