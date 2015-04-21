#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 34
#define HASHTABLE_SIZE 256

typedef struct _list_t
{
	char *string;
	int counter;
	struct _list_t *next;
	
} list_t;

typedef struct _hash_table_t
{
	int size;	   /* the size of the table */
	list_t **table; /* the table elements */
	
} hash_table_t;

typedef enum {false, true} bool;

hash_table_t *create_hash_table(int size);
unsigned int hash(hash_table_t *hashtable, char *str);
int add_string(hash_table_t *hashtable, char *str);
void free_table(hash_table_t *hashtable);

int main(int argc, char **argv)
{
	int n, i, result;
	char name[MAX_STR_SIZE];
	hash_table_t *tbl;

	// initial
	tbl = create_hash_table(MAX_STR_SIZE);
	
	scanf("%d", &n);
	
	for(i = 0; i < n; ++i)
	{
		scanf("%s", name);
		result = add_string(tbl, name);
		
		if (result == 0)
			printf("OK\n");
		else
			printf("%s%d\n", name, result);
	}
	
	free_table(tbl);
	
	return 0;
}

hash_table_t *create_hash_table(int size)
{
	int i;
	hash_table_t *new_table;
	
	/* invalid size for table */
	if (size < 1)
		return NULL;

	/* Attempt to allocate memory for the table structure */
	if ((new_table = malloc(sizeof(HASHTABLE_SIZE))) == NULL) {
		return NULL;
	}
	
	/* Attempt to allocate memory for the table itself */
	if ((new_table->table = malloc(sizeof(list_t *) * size)) == NULL) {
		return NULL;
	}

	/* Initialize the elements of the table */
	for(i=0; i<size; i++)
		new_table->table[i] = NULL;

	/* Set the table's size */
	new_table->size = size;

	return new_table;
}

unsigned int hash(hash_table_t *hashtable, char *str)
{
	unsigned int hashval;
	
	/* we start our hash out at 0 */
	hashval = 0;

	/* for each character, we multiply the old hash by 31 and add the current
	 * character.  Remember that shifting a number left is equivalent to 
	 * multiplying it by 2 raised to the number of places shifted.  So we 
	 * are in effect multiplying hashval by 32 and then subtracting hashval.  
	 * Why do we do this?  Because shifting and subtraction are much more 
	 * efficient operations than multiplication.
	 */
	for(; *str != '\0'; ++str)
		hashval = *str + (hashval << 5) - hashval;

	/* we then return the hash value mod the hashtable size so that it will
	 * fit into the necessary range
	 */
	return hashval % hashtable->size;
}

int add_string(hash_table_t *hashtable, char *str)
{
	list_t *list;
	unsigned int hashval = hash(hashtable, str);

	/* Go to the correct list based on the hash value and see if str is
	 * in the list.  If it is, return return a pointer to the list element.
	 * If it isn't, the item isn't in the table, so return NULL.
	 */
	for(list = hashtable->table[hashval]; list != NULL; list = list->next) {
		if (strcmp(str, list->string) == 0)
		{
			++list->counter;
			return list->counter;
		}
	}

	/* Attempt to allocate memory for list */
	if ((list = malloc(sizeof(list_t))) == NULL)
		return -1;
	
	/* Insert into list */
	list->string = strdup(str);
	list->counter = 0;
	list->next = hashtable->table[hashval];
	hashtable->table[hashval] = list;

	return 0;
}

void free_table(hash_table_t *hashtable)
{
	int i;
	list_t *list, *temp;

	if (hashtable == NULL)
		return;

	/* Free the memory for every item in the table, including the 
	 * strings themselves.
	 */
	for(i = 0; i < hashtable->size; ++i) {
		list = hashtable->table[i];
		
		while(list != NULL) {
			temp = list;
			list = list->next;
			free(temp->string);
			free(temp);
		}
	}

	/* Free the table itself */
	free(hashtable->table);
	free(hashtable);
}
