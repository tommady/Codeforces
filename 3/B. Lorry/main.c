#include <stdio.h>
#include <stdlib.h>

struct vehicle
{
	int serial_number;
	int capacity;
	struct vehicle *previous;
	struct vehicle *next;
};

typedef struct vehicle node;
typedef enum {false, true} bool;

int insert_node(node *head, node *tail, \
				 int number, int capacity, \
				 int counter, bool is_smallest);

int main(void)
{
	int water_vehicles;
	int lorry_capacity;
	int serial_number = 1;
	int smallest_kayak = 9999;
	int smallest_catamaran = 9999;
	int kayak_counter = 0;
	int catamaran_counter = 0;
	
/*
 *initializing kayak linked list
 */
	node *kayak_head, *kayak_tail;
	kayak_head = malloc(sizeof(node));
	kayak_tail = malloc(sizeof(node));
	
	kayak_head->previous = NULL;
	kayak_head->next = kayak_tail;
	kayak_tail->previous = kayak_head;
	kayak_tail->next = NULL;
	
/*
 *initializing catamaran linked list
 */
	node *catamaran_head, *catamaran_tail;
	catamaran_head = malloc(sizeof(node));
	catamaran_tail = malloc(sizeof(node));
	
	catamaran_head->previous = NULL;
	catamaran_head->next = catamaran_tail;
	catamaran_tail->previous = catamaran_head;
	catamaran_tail->next = NULL;
	
/*
 * initializing used vehicle linked list
 */
 	node *used_vehicle_head;
 	used_vehicle_head = malloc(sizeof(node));
 	used_vehicle_head->next = NULL;
 	used_vehicle_head->previous = NULL;
	
	
	node *kayak_current;
	node *catamaran_current;
	node *used_vehicle_current;
	
	scanf("%d %d", &water_vehicles, &lorry_capacity);
	
	
	/*
	 * read informations then store in linked lists
	 */
	while(water_vehicles--)
	{
		int vehicle_type, vehicle_capacity;
		bool is_smallest = false;
		
		scanf("%d %d", &vehicle_type, &vehicle_capacity);
		
		if(vehicle_type == 1)
		{
			if(vehicle_capacity <= smallest_kayak)
			{	
				smallest_kayak = vehicle_capacity;
				is_smallest = true;
			}
			
			kayak_counter = insert_node(kayak_head, \
										kayak_tail, \
										serial_number, \
										vehicle_capacity, \
										kayak_counter, \
										is_smallest);
		}
		else
		{
			if(vehicle_capacity <= smallest_catamaran)
			{
				smallest_catamaran = vehicle_capacity;
				is_smallest = true;
			}
			
			catamaran_counter = insert_node(catamaran_head, \
											catamaran_tail, \
											serial_number, \
											vehicle_capacity, \
											catamaran_counter, \
											is_smallest);
		}
		
		++serial_number;
	}
	
	/*
	 * let the tails point back to the links who has value,
	 * because I use two-way linked lists and there has a tmp tail
	 * to record, now data reads done, so point the tail to right position.
	 */
	node *tmp_kayak_tail = kayak_tail;
	node *tmp_catamaran_tail = catamaran_tail;
	
	kayak_tail = tmp_kayak_tail->previous;
	catamaran_tail = tmp_catamaran_tail->previous;
	
	free(tmp_kayak_tail);
	free(tmp_catamaran_tail);
	
	
	/*
	 * start the logic to consider which should put into lorry.
	 */
	while(lorry_capacity)
	{
		kayak_current = kayak_head->next;
		catamaran_current = catamaran_head->next;
		
		if(lorry_capacity == 1)
		{
			if(kayak_counter)
			{
				add_used_list(kayak);
				--lorry_capacity;
				--kayak_counter;
			}
		}
		else
		{
			//normal consider if two kayak capacities are bigger than
			//one catamaran capacity, then use them.
			if(kayak_counter > 1 && catamaran_counter)
			{
				node *kayak_current_next = kayak_current->next;
				int two_kayak_capacity = \
					kayak_current->capacity + kayak_current_next->capacity;
				
				if(two_kayak_capacity > catamaran_current->capacity)
				{
					add_used_list(kayak);
					add_used_list(kayak);
					lorry_capacity -= 2;
					kayak_counter -= 2;
				}
				else
				{
					add_used_list(catamaran);
					lorry_capacity -= 2;
					--catamaran_counter;
				}
			}
			//if one kayak capacity *2 bigger than one catamaran capacity,
			//use it.
			else if(kayak_current->capacity*2 >  catamaran_current->capacity)
			{
				add_used_list(kayak);
				--lorry_capacity;
				--kayak_counter;
			}
			else
			{
				add_used_list(catamaran);
				lorry_capacity -= 2;
				--catamaran_counter;
			}
		}
	}
	
	
/*
 ***************TEST***************
 */
	printf("In kayak:\n");
	kayak_current = kayak_head->next;
	while(kayak_current)
	{
		printf("number:%d -> capacity:%d\n", kayak_current->serial_number, kayak_current->capacity);
		kayak_current = kayak_current->next;
	}
		
	printf("In catamaran:\n");
	catamaran_current = catamaran_head->next;
	while(catamaran_current)
	{
		printf("number:%d -> capacity:%d\n", catamaran_current->serial_number, catamaran_current->capacity);
		catamaran_current = catamaran_current->next;
	}
	
/*
 ***************TEST***************
 */
	
	return 0;
}

void insert_node(node *head, node *tail, \
				 int number, int capacity, \
				 int counter, bool is_smallest)
{
	node *tmp_node;
	
	tmp_node = malloc(sizeof(node));
	tmp_node->serial_number = number;
	tmp_node->capacity = capacity;
	
/*
 *if the capacity is smaller or equal to smallest number,
 *add to the tail of list directly
 */
	if(is_smallest)
	{
		node *tail_pre = tail->previous;
		tail->previous = tmp_node;
		tail_pre->next = tmp_node;
		
		tmp_node->next = tail;
		tmp_node->previous = tail_pre;
	}
	else
	{
		node *current = head->next;
		
		while(current && current->next)
		{
			if(tmp_node->capacity > current->capacity)
			{
				node *current_pre = current->previous;
				current->previous = tmp_node;
				current_pre->next = tmp_node;
				
				tmp_node->next = current;
				tmp_node->previous = current_pre;
			}
			
			current = current->next;
		}
	}
	
	++counter;
	return counter;
}

