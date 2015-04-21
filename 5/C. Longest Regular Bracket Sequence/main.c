#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

struct _link_t
{
	int position;
	struct _link_t *next;
};

typedef struct _link_t link_t;

typedef struct
{
	link_t *brackets;
	int counter;
	
}stack_t;

stack_t *init_stack();
void free_stack(stack_t *stack);
void push(stack_t *stack, int position);
void pop(stack_t *stack);
bool is_empty(stack_t *stack);
int top(stack_t *stack);

int main(int argc, char **argv)
{
	char character;
	int max_length = 0;
	int sub_numbers = 1;
	int earliest_position = -1;
	int position = 0;
	int length = 0;
	
	/* this stores opening brackets. */
	stack_t *up_brackets = init_stack();

/*	
	//########TEST##########
	push(up_brackets, 10);
	push(up_brackets, 20);
	push(up_brackets, 30);
	pop(up_brackets);
	
	link_t *tmp = up_brackets->brackets;
	while(tmp)
	{
		printf("%d\n", tmp->position);
		tmp = tmp->next;
	}
	
	printf("top: %d\n", top(up_brackets));
	
	if(is_empty(up_brackets))
		printf("stack is empty!!!\n");
	else
		printf("stack is NOT empty!!!\n");
	
	//########TEST##########
*/
	
	/* needless in codeforces
	if(up_brackets == NULL)
		return 1;
	*/
	
	
	/*
	 * just follow the tutorial...
	 * i did not figure it out yet...
	 */
	while((character = getchar()) != EOF)
	{
		if(character == '(')
			push(up_brackets, position);
			
		else if(!is_empty(up_brackets) && character == ')')
		{
			pop(up_brackets);
			
			length = is_empty(up_brackets) ? \
					position - earliest_position : \
					position - top(up_brackets);
			
			if(length > max_length)
			{
				max_length = length;
				sub_numbers = 1;
			}
			else if(length == max_length)
				++sub_numbers;
		}
		else
			earliest_position = position;
		
		++position;
	}
	
	printf("%d %d\n", max_length, sub_numbers);
	free_stack(up_brackets);
		
	return 0;
}

stack_t *init_stack()
{
	stack_t *new_stack;
	
	/* attempt to allocate memory for the stack structure. */
	
	/* needless in codeforces
	if((new_stack = malloc(sizeof(stack_t))) == NULL)
		return NULL;
	*/
	
	new_stack = malloc(sizeof(stack_t));
	
	new_stack->brackets = NULL;
	new_stack->counter = 0;
	
	return new_stack;
}

void push(stack_t *stack, int position)
{
	link_t *tmp = malloc(sizeof(link_t));
	tmp->position = position;
	tmp->next = stack->brackets;
	stack->brackets = tmp;
	
	++stack->counter;
}

void pop(stack_t *stack)
{
	if(is_empty(stack))
		return;
	
	link_t *tmp = stack->brackets;
	stack->brackets = tmp->next;
	free(tmp);
	
	--stack->counter;
}

bool is_empty(stack_t *stack)
{
	if(stack->counter <= 0)
	{
		stack->counter = 0;
		return true;
	}
	else
		return false;
}

int top(stack_t *stack)
{
	if(is_empty(stack))
		return 0;
		
	link_t *tmp = stack->brackets;
	return tmp->position;
}


void free_stack(stack_t *stack)
{
	link_t *tmp;
	link_t *links = stack->brackets;

	if(!is_empty(stack))
	{
		while(links)
		{
			tmp = links;
			links = links->next;
			free(tmp);
		}
	}
	
	free(stack);
}

