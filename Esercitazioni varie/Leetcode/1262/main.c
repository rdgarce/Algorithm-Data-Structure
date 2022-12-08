#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX(one, two) ((one) >= (two) ? (one) : (two))

int maxSumDivThree(int* nums, int numsSize);
int max_sum_div_three_(int* nums, int numsSize, int index, int p_sum, int *memo);

int main()
{
    int nums[] = {
                4,1,5,3,1
        };
    int numsSize = sizeof(nums)/sizeof(nums[0]);
    printf("%d\n",maxSumDivThree(nums,numsSize));
}

int maxSumDivThree(int* nums, int numsSize){

    int *memo = malloc(sizeof(int)*numsSize*3);
    if(!memo)
        return -1;
    
    memset(memo,-1,sizeof(int)*numsSize*3);

    return max_sum_div_three_(nums, numsSize, 0, 0, memo);
}

int max_sum_div_three_(int* nums, int numsSize, int index, int p_sum, int *memo)
{
    // Caso base
    if (index == numsSize-1)
    {
        /* code */
    }
    
}