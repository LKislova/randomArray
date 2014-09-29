#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


void randomArray(int *result, int minValue, int maxValue);
void randomArraysAnalysis(int *orderedIndex, int **equalIndexes, int minValue, int maxValue);

void randomArray(int *result, int minValue, int maxValue)
{
    int size = (maxValue - minValue) + 1;
    int nextIsUnique = 1;
    int nextValue;
    int i, j;
    for (i = 0; i < size; i++)
    {
        do
        {
            nextValue = minValue + rand()%size;
            nextIsUnique = 1;
            for (j = 0; j < i; j++)
            {
                if (nextValue == result[j])
                {
                    nextIsUnique = 0;
                }
            }
        }
        while (nextIsUnique == 0);
        result[i] = nextValue;
    }
    return;
}
int main()
{
    int A=0;
    int **B = NULL;
    int i;
    int Max = 10;
    int Min = 5;
    int Mas[6];
    randomArray(Mas, Min, Max);
    for (i = 0; i < 6; i++)
    {
        printf("%d, ", Mas[i]);
    }
    printf("\n");
    randomArray(Mas, Min, Max);
    for (i = 0; i < 6; i++)
    {
        printf("%d, ", Mas[i]);
    }
    randomArraysAnalysis(&A, B, Min, Max);
    return 0;

}
void randomArraysAnalysis (int *orderedIndex, int **equalIndexes, int minValue, int maxValue)
{
    int size = (maxValue - minValue) + 1;
    int i;
    int j;
    int unuqueValue = 0;
    int **many_arrays = calloc(1, sizeof(int *));
    int *one_array;
    do
    {
        one_array = calloc(size, sizeof(int));
        unuqueValue =0;
        randomArray (one_array, minValue, maxValue);
        many_arrays[orderedIndex[0]] = one_array;

        for (i=1; i<size; i++)
        {
            if ((one_array[i]- one_array[i-1]) == 1)
            {
                unuqueValue ++;
            }
        }
        orderedIndex[0] ++;
        if(unuqueValue != (size-1))
        {
            many_arrays = realloc(many_arrays, (orderedIndex[0]+1)*sizeof(int *));
        }

    }
    while (unuqueValue != (size-1));
    printf("\n");
    for (i = 0; i < orderedIndex[0]; i++)
    {
        printf("%d: ", i);

        for (j = 0; j < size; j++)

        {

            printf("%d; ", many_arrays[i][j]);

        }
        printf("\n");
    }
    int **same_arrays = NULL;
    int *same_array = NULL;
    int same_array_length = 0;
    int same_arrays_length = 0;
    int *same_array_lengths = NULL;
    int IsIndexChecked[orderedIndex[0]];
    for (i = 0; i < orderedIndex[0]; i++)
    {
        if (IsIndexChecked[i])
        {
            continue;
        }
        else
        {
            IsIndexChecked[i] = 1;
        }
        same_array = NULL;
        same_array_length = 0;
        for (j = (i+1); j < orderedIndex[0]; j++)
        {
            if (IsIndexChecked[j])
            {
                continue;
            }
            if (memcmp(many_arrays[i], many_arrays[j], size*sizeof(int)) == 0)
            {
                IsIndexChecked[j] = 1;
                if (same_array == NULL)
                {
                    same_array = calloc(2, sizeof(int));
                    same_array[0] = i;
                    same_array[1] = j;
                    same_array_length = 2;
                }
                else
                {
                    same_array_length++;
                    same_array = realloc(same_array, same_array_length*sizeof(int));
                    same_array[same_array_length - 1 ] = j;
                }
            }
        }
        if (same_array_length > 0)
        {
            same_arrays_length ++;
            if (same_arrays == NULL)
            {
                same_arrays = calloc(1, sizeof(int *));
                same_array_lengths = calloc( 1, sizeof( int));
            }
            else
            {
                same_arrays = realloc(same_arrays, same_arrays_length *sizeof(int *));
                same_array_lengths = realloc(same_array_lengths, same_arrays_length *sizeof(int));
            }
            same_arrays[same_arrays_length - 1] = same_array;
            same_array_lengths[same_arrays_length-1] = same_array_length;
        }
    }

    equalIndexes = same_arrays;

    printf("\n");
    printf("\n");
    for (i = 0; i < same_arrays_length; i++)
    {

        for (j = 0; j < same_array_lengths[i]; j++)

        {
            printf("%d; ", equalIndexes[i][j]);

        }
        printf("\n");
    }

}





