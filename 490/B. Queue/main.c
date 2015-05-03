#include <stdio.h>
#include <stdlib.h>

typedef struct data
{
    int id;
    int front;
    int behind;
    struct data *next;
    
} data_l;

data_l *init_link(int front, int behind, int id);
void add_link(data_l *head, data_l *new_link);
void pop_link(data_l *link);
void delet_all(data_l *head);

int main(void)
{
    int n, i;
    scanf("%d", &n);

    data_l sorted_line[n];
    
    // initialize sorted_line with id = -1;
    for(i=0; i<n; i++)
    {
    	sorted_line[i].id = -1;
    }
    
    // need to be found list
    data_l *ntbf_list = init_link(-1, -1, -1);
    
    for(i=0; i<n; i++)
    {
    	int front, behind;
        scanf("%d %d", &front, &behind);
        
        if(front == 0)
        {
        	// second can be identify
        	sorted_line[1].id = behind;
        }
        else if(behind == 0)
        {
        	// penultimate can be identify
        	sorted_line[n-2].id = front;
        }
        else
        {
        	add_link(ntbf_list, init_link(front, behind, 0));
        }
    }
    
    // looping the need to be found list for matching id.
    // TODO: change sorted_line to double linked list and change the search logic
    data_l *tmp = ntbf_list->next;
    while(tmp != NULL)
    {
    	for(i=0; i<n; i++)
    	{
    		if(sorted_line[i].id == -1)
    		{
				if(tmp->front == sorted_line[i].id)
				{
					sorted_line[i+1].id = tmp->behind;
					pop_link(tmp);
				}
				else if(tmp->behind == sorted_line[i].id)
				{
					sorted_line[i-1].id = tmp->front;
					pop_link(tmp);
				}
    		}
    	}
    	
    	tmp = tmp->next;
    }
    
    for(i=0; i<n; i++)
    {
    	printf("%d ", sorted_line[i].id);
    }
    printf("\n");
    
    delet_all(ntbf_list);
    
    return 0;
}

data_l *init_link(int front, int behind, int id)
{
	data_l *new_link = calloc(1, sizeof(data_l));
	new_link->id = id;
	new_link->front = front;
	new_link->behind = behind;
	new_link->next = NULL;
	
	return new_link;
}

void add_link(data_l *head, data_l *new_link)
{
	data_l *tmp = head->next;
	head->next = new_link;
	new_link->next = tmp;
}

void pop_link(data_l *link)
{
	// not really pop the link, but change the value to let the loop void search.
	link->id = -1;
	link->front = -1;
	link->behind = -1;
}

void delet_all(data_l *head)
{
	data_l *tmp;
	
	while(head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
