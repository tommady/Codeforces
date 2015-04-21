#include <stdio.h>
#include <stdlib.h>

/*
 * using double linked list for storing memory usage,
 */

typedef struct _node
{
    int identifier;
    int bytes;
    int start;
    int end;
    struct _node* next;
    struct _node* prev;

}node_t;

node_t* create_node(int, int);
void insert_node(node_t*, node_t*);
int remove_node(node_t*, int);
void free_list(node_t*);
void defragment(node_t*);
int detect_alloc(node_t*, int, int);


int main(void)
{
    int t, m;
    int n; // in alloc this means bytes, in erase this means identifier
    int identifier = 1;
    char operation[16];
    node_t* head = create_node(0, -1014);
    node_t* tail = create_node(0, -1013);
    
    scanf("%d %d", &t, &m);
    
    head->start = 0;
    head->end = 0;
    tail->start = m+1;
    tail->end = m+1;
    
    head->next = tail;
    tail->prev = head;


    while(t--)
    {
        scanf("%s", operation);
        
        if(operation[0] == 'd') //defragment
            defragment(head);
        else
        {
            scanf("%d", &n);
            
            if(operation[0] == 'a') //alloc
            {
                if(detect_alloc(head, n, identifier))
                {
                    printf("%d\n", identifier);
                    identifier++;
                }
                else
                    printf("NULL\n");
            }
            else if(operation[0] == 'e') //erase
            {
                if(n >=1 && remove_node(head, n))
                {
                }
                else
                    printf("ILLEGAL_ERASE_ARGUMENT\n");
            }
        }
    }
    
    free_list(head);
    
    return 0;
}


node_t* create_node(int bytes, int identifier)
{
    node_t* n = malloc(sizeof(node_t));
    
    n->identifier = identifier;
    n->bytes = bytes;
    n->next = NULL;
    n->prev = NULL;
    
    return n;
}

void insert_node(node_t* tail, node_t* n)
{
    n->prev = tail->prev;
    n->next = tail;
    tail->prev->next = n;
    tail->prev = n;
    
    n->start = n->prev->end + 1;
    n->end = n->start + n->bytes - 1;
}

int remove_node(node_t* head, int identifier)
{
    int found = 0;
    node_t* current = head->next;
    
    while(current->identifier != -1013)
    {
        if(current->identifier == identifier)
        {
            current->identifier = 0;
            found = 1;
            break;
        }
        
        current = current->next;
    }

    return found;
}

void free_list(node_t* head)
{
    node_t* tmp;
    
    while(head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void defragment(node_t* head)
{
    node_t* current = head->next;
    
    while(current->identifier != -1013)
    {
        if(current->identifier == 0)
        {
            node_t* tmp = current;
            
            current->prev->next = current->next;
            current->next->prev = current->prev;
            
            current = current->next;
            free(tmp);
        }
        else
        {
            current->start = current->prev->end + 1;
            current->end = current->start + current->bytes - 1;
            
            current = current->next;
        }
    }
}

int detect_alloc(node_t* head, int bytes, int identifier)
{
    int allocable = 0;
    node_t* current = head;
    
    while(current->identifier != -1013)
    {
        //detect removed space case.
        if(current->identifier == 0)
        {
            //detect the section free space.
            if((
            (current->end - current->prev->end) +\
            (current->next->start - current->start) -\
            (current->bytes)) >= bytes)
                allocable = 1;
        }
        
        //detect the free space while two used spaces case.
        else
        {
            //detect right side.
            if((current->next->start - current->end - 1) >= bytes)
                allocable = 2;
        }
        
        if(allocable)
        {
            if(allocable == 1)
            {
                current->bytes = bytes;
                current->start = current->prev->end + 1;
                current->end = current->start + bytes - 1;
                current->identifier = identifier;
            }
            else if(allocable == 2)
                insert_node(current->next, create_node(bytes, identifier));
                
            break;
        }
        
        current = current->next;
    }
    
    return allocable;
}


