#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
Dato un insieme di stringhe, si trovi il prefisso in comune più lungo 
 
Esempio:  
 
Input  : {"apple", "ape", "april", “applied”} 
Output : "ap"
*/

char *max_prefix(char **strings, int start_index, int end_index, int *prefix_size);
int calculate_max_common_prefix(char *s1, int s1_size, char *s2, int s2_size);

int main(){

    char *strings[] = {"apple", "ape", "april", "applied"};
    int n_strings = sizeof(strings)/sizeof(strings[0]);

    int length;
    char *result = max_prefix(strings,0,n_strings-1,&length);
    for (int i = 0; i < length; i++)
    {
        printf("%c",result[i]);
    }
    printf("\n");
    
    
    
}

char *max_prefix(char **strings, int start_index, int end_index, int *prefix_size){

    if (start_index == end_index)
    {
        *prefix_size = strlen(strings[start_index]);
        return strings[start_index];
    }

    int center_index = (start_index + end_index)/2;
    int p1_size, p2_size;
    char *p1 = max_prefix(strings,start_index,center_index,&p1_size);
    char *p2 = max_prefix(strings,center_index+1,end_index,&p2_size);
    *prefix_size = calculate_max_common_prefix(p1,p1_size,p2,p2_size);
    return p1;

}

int calculate_max_common_prefix(char *s1, int s1_size, char *s2, int s2_size){

    int min_s_size = s1_size < s2_size ? s1_size : s2_size;
    int i = 0;
    while (i < min_s_size)
    {
        if (s1[i] != s2[i])
        {
            break;
        }
        i++;
    }

    return i;

}