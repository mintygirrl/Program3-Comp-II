#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"
#include "status.h"

/**********************************************************************
Program: Program 3
Author: Fallon Weiss
Date: 7/22/24
Time spent: 7 days.
Purpose: The purpose of this program is to take a list of user input 
numbers from 0 to 2,000,000,000 and sort them, taking account of any
duplicate numbers and printing them in secquential order after the user
types '-1'.
***********************************************************************/


int main(int argc, char* argv[]) 
{
    BIT_FLAGS unique_numbers = bit_flags_init_number_of_bits(32);
    int userdata = 0;
    int i = 0;

    // Read numbers from standard input
    while (1) 
    {
        scanf("%d", &userdata);
        if (userdata >= 0)
        {
            bit_flags_set_flag(unique_numbers, userdata);
        }
        //else
        //{
            //fprintf(stderr, "Invalid number %d ignored. Please enter numbers within the range 0 to 2,000,000,000.\n", userdata);
        //}
        if (userdata == -1)
        {
            break;
        }
    }

    printf("\n");

    while(bit_flags_get_size(unique_numbers) > i)
    {
        if (bit_flags_check_flag(unique_numbers, i))
        {
            printf("%d\n", i);
        }
        i++;
    }

    bit_flags_destroy(&unique_numbers);
    
    return 0;
}
