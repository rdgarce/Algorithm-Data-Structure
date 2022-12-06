#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct stack_t
{
    int index;
    int dim;
    int memory[];
}stack_t;

stack_t *create_stack(int dim);
void delete_stack(stack_t *s);
void empty_stack(stack_t *s);
bool is_empty(stack_t *s);
void stack_push(stack_t *s, int elem);
bool stack_pop(stack_t *s, int *elem);
int stack_head(stack_t *s);

int max_pal_sub_seq(char *string, size_t s_size, bool *removed, unsigned int n_removed);
bool is_palindrome(char *string, size_t s_size, bool *removed, unsigned int n_removed);

int main()
{
    bool removed[50] = {false};
    printf("%d\n",max_pal_sub_seq("ilahiubbal",10,&removed,0));
}

int max_pal_sub_seq(char *string, size_t s_size, bool *removed, unsigned int n_removed)
{
    // Caso base: Ho trovato un palindromo, quindi ritorno la lunghezza e la salvo
    if (is_palindrome(string,s_size,removed,n_removed))
    {
        // Devo anche fare memoization
        return s_size-n_removed;
    }

    unsigned int max_length = 0;
    unsigned int temp_length;

    for (int i = 0; i < s_size; i++)
    {
        if (removed[i])
            continue;
        
        removed[i] = true;
        temp_length = max_pal_sub_seq(string,s_size,removed,n_removed+1);
        removed[i] = false;
        if (temp_length > max_length)
            max_length = temp_length;
    }

    // Memoization del risultato trovato e lo ritorno
    return max_length;
}

bool is_palindrome(char *string, size_t s_size, bool *removed, unsigned int n_removed)
{
    unsigned int actual_size = s_size - n_removed;

    if (actual_size % 2 != 0)
    {
        int count = 0;
        int index = -1;
        while (count <= actual_size/2 && index < (int)s_size)
        {
            index++;
            if (!removed[index])
                count++;
        }
        removed[index] = true;
        bool res = is_palindrome(string,s_size,removed,n_removed+1);
        removed[index] = false;
        return res;         
    }
    
    int dummy;
    stack_t *stack = create_stack(s_size);

    for (int i = 0; i < s_size; i++)
    {
        if (removed[i])
            continue;
        
        if (string[i] == stack_head(stack))
            stack_pop(stack,&dummy);
        else
            stack_push(stack,string[i]);
    }

    if (is_empty(stack))
    {
        delete_stack(stack);
        return true;
    }
    else
    {
        delete_stack(stack);
        return false;
    }
}

stack_t *create_stack(int dim)
{
    stack_t *s = calloc(1,sizeof(stack_t)+sizeof(int)*dim);
    s->index = 0;
    s->dim = dim;
    return s;
}

void delete_stack(stack_t *s)
{
    free(s);
}

void empty_stack(stack_t *s)
{
    s->index = 0;
}

bool is_empty(stack_t *s)
{
    return s->index == 0;
}

void stack_push(stack_t *s, int elem)
{
    s->memory[s->index] = elem;
    s->index = s->index + 1;
}

bool stack_pop(stack_t *s, int *elem)
{
    if (is_empty(s))
        return false;
    
    s->index = s->index - 1;
    *elem = s->memory[s->index];
    return true;
}

int stack_head(stack_t *s)
{
    return s->memory[s->index-1];
}