#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

typedef struct work_t
{
    int index;
    int time;
    int fine;
    float time_fine;
}work_t;

work_t WORK_MAX = {
    .index = INT_MAX,
    .time = INT_MAX,
    .fine = INT_MAX,
    .time_fine = INT_MAX
};

void merge(work_t *A, int start, int center,int end, int *num_op);
void merge_sort_t_f(work_t *A, int start, int end, int *num_op);

void create_work(work_t *work, int index, int time, int fine);
void print_work(work_t work);
void print_works(work_t *A, int A_size);

#define MAX_WORKS 1000

int main(){

    work_t works[MAX_WORKS];
    int n_works = 0;
    int n_tests;

    int temp_time;
    int temp_fine;
    //INPUT
    scanf("%d",&n_tests);
    for (int i = 0; i < n_tests; i++)
    {
        scanf("%d",&n_works);
        for (int j = 0; i < n_works; i++)
        {
            scanf("%d %d",&temp_time, &temp_fine);
            create_work(&works[i],i+1,temp_time,temp_fine);
        }

        merge_sort_t_f(works,0,n_works-1,NULL);
    
        for (int i = 0; i < n_works; i++)
        {
            printf("%d ",works[i]);
        }
        
    }
    
}


void merge(work_t *A, int start, int center,int end, int *num_op){
    

    int n1 = center-start+1;
    int n2 = end-center;
    int op_count = 0;
    
    work_t *L =malloc(sizeof(work_t)*(n1+1));
    work_t *R =malloc(sizeof(work_t)*(n2+1));

    for(int i = 0; i < n1; i++)
        L[i] = A[i + start];
    
    L[n1] = WORK_MAX;
    
    for(int i = 0; i < n2; i++)
        R[i] = A[i + center+1];

    R[n2] = WORK_MAX;

    int l_index = 0;
    int r_index = 0;
    for(int i=start;i <= end; i++){
        
        if(L[l_index].time_fine <= R[r_index].time_fine){
            A[i] = L[l_index];
            l_index++;
        }
        else{
            A[i] = R[r_index];
            r_index++;
            if(L[l_index].time_fine != WORK_MAX.time_fine)
                op_count += n1-l_index;
                
        }
        
    }
    

    if(num_op)
        *num_op += op_count;

    free(L);
    free(R);
}

void merge_sort_t_f(work_t *A, int start, int end, int *num_op){
    
    if(start < end){
        
        int center = (start + end)/2;
        merge_sort_t_f(A,start,center, num_op);
        merge_sort_t_f(A, center+1,end, num_op);
        merge(A,start,center,end, num_op);
        
    }

}

void create_work(work_t *work, int index, int time, int fine){
    work->index = index;
    work->fine=fine;
    work->time=time;
    work->time_fine = (float)time/(float)fine;
}

void print_work(work_t work){
    printf("{index = %d, time = %d, fine = %d, time_fine = %f}",work.index,work.time,work.fine,work.time_fine);
}

void print_works(work_t *A, int A_size){
    printf("[ ");
    for (int i = 0; i < A_size; i++)
    {
        print_work(A[i]);
        printf(" ");
    }
    printf(" ]\n");
    
}