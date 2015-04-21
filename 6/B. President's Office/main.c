#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128

typedef struct _node
{
    char desk_color;
    struct _node* next;
    
}node_t;

node_t* create_node(char);
void insert_node(node_t*, node_t*);
void free_list(node_t*);
int check_list(node_t*, char);


int main(void)
{
    int n, m, i, j;
    int deputies_counter = 0;
    char c; //president's desk
    char empty_cell = '.';
    char matrix[MAX_SIZE][MAX_SIZE];
    node_t* deputies = create_node('\0');
    
    scanf("%d %d %c", &n, &m, &c);

    for(i=0; i<n; i++)
    {
        scanf("%s", matrix[i]);
    }
    
    for(i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
        {
            if(matrix[i][j] == c)
            {
                if(i-1 >= 0) //check above position
                {
                    if(matrix[i-1][j] != empty_cell && matrix[i-1][j] != c)
                    {
                        if(check_list(deputies, matrix[i-1][j]))
                        {
                            insert_node(deputies, create_node(matrix[i-1][j]));
                            deputies_counter++;
                        }
                    }
                }
                if(i+1 < n) //check below position
                {
                    if(matrix[i+1][j] != empty_cell && matrix[i+1][j] != c)
                    {
                        if(check_list(deputies, matrix[i+1][j]))
                        {
                            insert_node(deputies, create_node(matrix[i+1][j]));
                            deputies_counter++;
                        }
                    }
                }
                if(j-1 >= 0) //check left position
                {
                    if(matrix[i][j-1] != empty_cell && matrix[i][j-1] != c)
                    {
                        if(check_list(deputies, matrix[i][j-1]))
                        {
                            insert_node(deputies, create_node(matrix[i][j-1]));
                            deputies_counter++;
                        }
                    }
                }
                if(j+1 < m) //check right position
                {
                    if(matrix[i][j+1] != empty_cell && matrix[i][j+1] != c)
                    {
                        if(check_list(deputies, matrix[i][j+1]))
                        {
                            insert_node(deputies, create_node(matrix[i][j+1]));
                            deputies_counter++;
                        }
                    }
                }
            }
        }
    }
    
    free_list(deputies);
    printf("%d\n", deputies_counter);
    
    return 0;
}

node_t* create_node(char desk_color)
{
    node_t* n = malloc(sizeof(node_t));
    n->desk_color = desk_color;
    n->next = NULL;
    
    return n;
}

void insert_node(node_t* head, node_t* n)
{
    n->next = head->next;
    head->next = n;
}

void free_list(node_t* list)
{
    node_t* tmp;
    
    while(list)
    {
        tmp = list;
        list = list->next;
        free(tmp);
    }
    
    free(list);
}

int check_list(node_t* list, char desk_color)
{
    int is_duplicate = 1;
    node_t* current = list;
    
    while(current)
    {
        if(current->desk_color == desk_color)
        {
            is_duplicate = 0;
            break;
        }
        
        current = current->next;
    }
    
    return is_duplicate;
}
