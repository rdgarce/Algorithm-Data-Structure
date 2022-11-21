#include <stdio.h>
#include <stdbool.h>

#define MAX_CHIMPS 50000
#define MAX_QUERIES 25000

int binary_search(int *A, int start, int end, int elem);
void printArray(int *A, int len);

int main()
{

    int chimps[MAX_CHIMPS];
    int queries[MAX_QUERIES];
    int n_chimps;
    int n_queries;

    scanf("%d",&n_chimps);
    for (int i = 0; i < n_chimps; i++)
    {
        scanf("%d",&chimps[i]);
    }
    
    scanf("%d",&n_queries);
    for (int i = 0; i < n_queries; i++)
    {
        scanf("%d",&queries[i]);
    }

    int index1, index2;

    for (int i = 0; i < n_queries; i++)
    {   
        index1 = binary_search(chimps,0,n_chimps-1,queries[i]);
        if (chimps[index1] == queries[i])
        {
            index2 = index1 + 1;
            index1 = index1 - 1;
            printf("%d %d\n",chimps[index1], chimps[index2]);
        }
        else{
            index2 = index1;
            bool trovato = false;
            while (index2<n_chimps && !trovato)
            {
                index2++;
                if (chimps[index2] > queries[i])
                {
                    trovato = true;
                }
            }
            if (trovato)
            {
                printf("%d %d\n",chimps[index1], chimps[index2]);
            }
            else
            {
                printf("%d X\n",chimps[index1]);
            }
            
            
        }
        

    }
    
    
    /*
    for (int i = 0; i < n_queries; i++)
    {
        index1 = binary_search(chimps,0,n_chimps-1,queries[i]);
        printf("%d\n",index1);
        
        index2 = (index1 < n_chimps-1) && index1 != -1 ? index1 + 1 : -1;

        index1 != -1 ? printf("%d ",chimps[index1]) : printf("X ");
        index2 != -1 ? printf("%d\n",chimps[index2]) : printf("X\n");
        
        
        
    }
    */
    
    
}

/*
* Return the index of highest element <= of [elem] in the ordered [A] vector
* starting from the [start] index to the [end] index,
* or -1 if no element <= [elem] is present in [A]
*/
int binary_search(int *A, int start, int end, int elem)
{

    if (end == start)
        if (A[start] <= elem)
            return start;
        else
            return -1;
    
    int center = (start + end)/2 + 1;
    
    if (A[center] <= elem)
        return binary_search(A,center,end,elem);
    else if(A[center] > elem)
        return binary_search(A,start,center-1,elem);
    

}

void printArray(int *A, int len){
    
    printf("[ ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ",A[i]);
    }
    printf("]\n");
    
}