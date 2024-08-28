#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"

struct bit_flags //known type
{
    int size;
    //size is the number of bits the user cares about or checked
    //in on.
    int capacity;
    //cpacity is the number of integers the dynamic array can hold
    int* data;
};
typedef struct bit_flags Bit_Flags;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
    //malloced space for the array we want and casting to the known type
    int num;
    num = number_of_bits / (sizeof(int) * 8);

    Bit_Flags* pBits = (Bit_Flags*)malloc(sizeof(Bit_Flags));
    if (pBits != NULL)
    {
        pBits->size = number_of_bits;
        pBits->capacity = ((number_of_bits / num) + 1) * num;
        pBits->data = malloc(sizeof(int) * (number_of_bits % num) + 1);
        if (pBits->data != NULL)
        {
            for (int i = 0; i <= pBits->capacity; i++)
            {
                pBits->data[i] = 0;
            }
        }
        else
        {
            free(pBits);
            return NULL;
        }
    }
    return (BIT_FLAGS)pBits;
}


Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    //cast to the known type 
    Bit_Flags* pBit_Flags = (Bit_Flags*)hBit_flags;
    // find out what INTEGER they want
    int number;
    int bit;
    int* temp = NULL;
    number = flag_position / (sizeof(int) * 8);
    bit = flag_position % (sizeof(int) * 8);

    if (pBit_Flags->capacity > flag_position)
    {
        int compare = 0;
        compare = 1 << bit;
        pBit_Flags->data[number] = pBit_Flags->data[number] | compare;
        if (flag_position > pBit_Flags->size)
        {
            pBit_Flags->size = flag_position;
        }
        if (flag_position > pBit_Flags->capacity)
        {
            pBit_Flags->capacity = (sizeof(int) * 8)+(number * (sizeof(int) * 8));
        }
        

        if (pBit_Flags->size > number)
        {
            pBit_Flags->size++;
        }

        return SUCCESS;
    }

   
    //IS THE INTEGER IN THE DATA STRUCTURE??
    //No, RESIZE!!
    if (pBit_Flags->capacity < flag_position)
    {
        temp = (int*)malloc(sizeof(int) * number);
        if (temp == NULL)
        {
            return FAILURE;
        }
        //copy over integers from pervious array
        for (int i = 0; i < pBit_Flags->capacity / (sizeof(int) * 8); i++)
        {
            temp[i] = pBit_Flags->data[i];
        }
        free(pBit_Flags->data);
        pBit_Flags->data = temp;

        int compare = 0;
        compare = 1 << bit;
        pBit_Flags->data[number] = pBit_Flags->data[number] | compare;
        pBit_Flags->size = flag_position;
        pBit_Flags->capacity = (sizeof(int) * 8)+(number * (sizeof(int) * 8));
        return SUCCESS;
    }
    else
    {
        int compare = 0;
        compare = 1 << bit;
        pBit_Flags->data[number] = pBit_Flags->data[number] | compare;
        pBit_Flags->size = flag_position;
        return SUCCESS;
    }

    return FAILURE;
    //THEN FIGURE OUT WHICH POINT IN THE ARRAY THEY WANT AND COMPARE THEM
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    //cast to the known type 
    Bit_Flags* pBit_Flags = (Bit_Flags*)hBit_flags;

    int number;
    int bit;
    Bit_Flags* temp;
    number = flag_position / (sizeof(int) * 8);
    bit = flag_position % (sizeof(int) * 8);
    
    if (pBit_Flags->capacity < number)
    {
        int expand;
        expand = number - pBit_Flags->capacity;
        pBit_Flags->capacity = pBit_Flags->capacity - expand;
        temp = (Bit_Flags*)malloc(sizeof(int) * pBit_Flags->capacity);
        if (temp == NULL)
        {
            return FAILURE;
        }
        //copy over integers from pervious array
        for (int i = 0; i < pBit_Flags->capacity; i++)
        {
            temp->data[i] = pBit_Flags->data[i];
        }
        free(pBit_Flags->data);

        int compare = 0;
        compare = 1 << bit;
        compare = ~compare;
        temp->data[number] = temp->data[number] & compare;
        pBit_Flags->size = pBit_Flags->size - 1;
        return SUCCESS;
    }
    int compare = 0;
    compare = 1 << bit;
    compare = ~compare;
    pBit_Flags->data[number] = pBit_Flags->data[number] & compare;
    pBit_Flags->size = pBit_Flags->size - 1;
    return SUCCESS;
        
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    //cast to the known type 
    Bit_Flags* pBit_Flags = (Bit_Flags*)hBit_flags;
    int value = flag_position / (sizeof(int) * 8);
    if (pBit_Flags->capacity < value)
    {
        return -1;
    }    
    
    int split = flag_position / (sizeof(int) * 8);
    int versus = pBit_Flags->data[split] >> flag_position;
    int compare = 1 & versus;
    return compare;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
    //cast to the known type 
    Bit_Flags* pBit_Flags = (Bit_Flags*)hBit_flags;
    int value = pBit_Flags->size;
    return value;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
    //cast to the known type 
    Bit_Flags* pBit_Flags = (Bit_Flags*)hBit_flags;
    return pBit_Flags->capacity;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
    Bit_Flags* pBit_Flags = (Bit_Flags*)*phBit_flags;
    free(pBit_Flags->data);
    free(pBit_Flags);
    *phBit_flags = NULL;
}
