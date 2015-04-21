#include <stdio.h>
#include <stdlib.h>

typedef struct data
{
    int id;
    int front;
    int behind;
    struct data *prev;
    struct data *next;
    
} data_l;

data_l *init_link();

int main(void)
{
    int n, i;
    scanf("%d", &n);
    data_l line_;
    data_l sorted_line[n];
    
    for(i=0; i<n; i++)
    {
        scanf("%d %d", line[i].front, line[i].behind);
        if(line[i].front == 0)
    }
    
    return 0;
}
