#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct queue_t
{
    int head;
    int tail;
    int dim;
    int memory[];
}queue_t;

queue_t *create_queue(int dim);
void delete_queue(queue_t *q);
bool is_empty_queue(queue_t *q);
void enqueue(queue_t *q, int elem);
int dequeue(queue_t *q);
int queue_head(queue_t *q);
void print_queue(queue_t *q);

void get_max_popes(int *Popes, int P_size, int N, int *max_p_size, int *first_pope, int *last_pope);


int main()
{
    int years, n_popes;
    scanf("%d",&years);
    scanf("%d",&n_popes);
    int *popes = malloc(sizeof(int)*n_popes);
    if (!popes)
        exit(-1);
    
    for (int i = 0; i < n_popes; i++)
        scanf("%d",&popes[i]);
    
    int max_p_size, first_pope, last_pope;

    get_max_popes(popes,n_popes,years,&max_p_size,&first_pope,&last_pope);
    printf("%d %d %d\n",max_p_size,first_pope,last_pope);
}

void get_max_popes(int *Popes, int P_size, int N, int *max_p_size, int *first_pope, int *last_pope)
{
    queue_t *QUEUE_indexes = create_queue(P_size);
    if (!QUEUE_indexes)
        exit(-1);
    
    enqueue(QUEUE_indexes,0);

    int first_pope_temp = 0;
    int first_pope_max = 0;
    int last_pope_max = 0;
    int num_popes_temp = 0;
    int num_popes_max = 0;

    for (int i = 1; i < P_size; i++)
    {
        while (Popes[queue_head(QUEUE_indexes)] + N - 1 < Popes[i])
        {
            first_pope_temp = dequeue(QUEUE_indexes);
            num_popes_temp = i-first_pope_temp;
            if (num_popes_temp > num_popes_max)
            {
                num_popes_max = num_popes_temp;
                first_pope_max = first_pope_temp;
                last_pope_max = i-1;
            }
        }
        enqueue(QUEUE_indexes,i);
    }

    *max_p_size = num_popes_max;
    *first_pope = Popes[first_pope_max];
    *last_pope = Popes[last_pope_max];

    delete_queue(QUEUE_indexes);
    
}

queue_t *create_queue(int dim)
{
    queue_t *q = calloc(1,sizeof(queue_t)+sizeof(int)*dim);
    q->dim = dim;
    q->head = -1;
    q->tail = -1;
    return q;
}

void delete_queue(queue_t *q)
{
    free(q);
}

bool is_empty_queue(queue_t *q)
{
    return q->head == -1;
}

bool is_full_queue(queue_t *q)
{
    return (q->head == q->tail + 1) || (q->head == 0 && q->tail == q->dim - 1);
}

void enqueue(queue_t *q, int elem)
{
    if (is_full_queue(q))
        return;
    else
    {
        if (q->head == -1)
            q->head = 0;
        q->tail = (q->tail + 1) % q->dim;
        q->memory[q->tail] = elem;
    }
}

int dequeue(queue_t *q)
{
    int element;
    if (is_empty_queue(q))
    {
        return -1;
    }
    else
    {
        element = q->memory[q->head];
        if (q->head == q->tail)
        {
        q->head = -1;
        q->tail = -1;
        }
        else
        {
            q->head = (q->head + 1) % q->dim;
        }
        return element;
  }
}

int queue_head(queue_t *q)
{
    return q->memory[q->head];
}

void print_queue(queue_t *q)
{
    int i;
    if (is_empty_queue(q))
        printf("Empty Queue\n");
    else
    {
        printf("Front -> %d\n", q->head);
        printf("Items -> ");
        for (i = q->head; i != q->tail; i = (i + 1) % q->dim)
        {
            printf("%d ", q->memory[i]);
        }
        printf("%d ", q->memory[i]);
        printf("\nRear -> %d \n", q->tail);
        printf("---\n");
    }
}