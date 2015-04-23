#include <stdio.h>
#include <stdlib.h>

typedef struct data
{
    int id;
    int front;
    int behind;
    
} data_l;

data_l *init_link();

int main(void)
{
    int n, i;
    scanf("%d", &n);
    data_l input_line[n];
    data_l sorted_line[n];
    
    for(i=0; i<n; i++)
    {
        scanf("%d %d", line[i].front, line[i].behind);
        
        if(input_line[i].front == 0)
        {
        	// second can be identify
        	input_line[1].id = input_line[i].behind;
        }
        if(input_line[i].behind == 0)
        {
        	// penultimate can be identify
        	input_line[n-1].id = input_line[i].front;
        }
    }
    
    return 0;
}
