#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int number_of_couples(int n);
int number_of_couples_dp_solver(int n, int *memo);
int number_of_couples_v2(int n);

int main(){

    printf("%d\n",number_of_couples(6));
    printf("%d\n",number_of_couples_v2(6));

}

/*
* Given a group of [n] elements, with [n] >= 0,
* returns the total number of ways in which 
* the [n] elements can remain single or can be paired,
* or -1 if an error occurred
*/
int number_of_couples(int n)
{

    int *memo = malloc(sizeof(int)*n);
    if (!memo)
        return -1;

    memset(memo,0,sizeof(int)*n);
    
    return number_of_couples_dp_solver(n, memo);

}

int number_of_couples_dp_solver(int n, int *memo)
{

    if (n <= 2)
        return n;
    
    if (memo[n-1] > 0)
        return memo[n-1];
    
    int result = number_of_couples_dp_solver(n-1,memo) + (n-1)*number_of_couples_dp_solver(n-2,memo);
    memo[n-1] = result;
    return result;

}

/*
* Given a group of [n] elements, with [n] >= 0,
* returns the total number of ways in which 
* the [n] elements can remain single or can be paired,
* or -1 if an error occurred
*/
int number_of_couples_v2(int n)
{
    if (n <= 2)
        return n;
    
    int memo[2] = {1,2};
    int result;

    for (int i = 3; i <= n; i++)
    {
        result  = memo[1] + (i-1)*memo[0];
        memo[0] = memo[1];
        memo[1] = result;
    }
    return result;
    
}