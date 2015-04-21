#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER 1000000
#define MIN(x, y) (x < y ? x : y)

struct path_info
{
	char character;
	struct path_info *previous;
	struct path_info *next;
};

typedef struct path_info path;

void add_path(path *path_head, path *path_tail, char character);

int main(void)
{
	int n; //size of the matrix
	int i, j;
	
	scanf("%d", &n);
	int pow2[n+2][n+2];
	int pow5[n+2][n+2];
	int zero_i = -1;
	int zero_j = -1;
	
	memset(pow2, 0, sizeof(pow2));
	memset(pow5, 0, sizeof(pow5));
	
	//init pow2 and pow5 matrix borderline with MAX_NUMBER
	for(i = 2; i <= n; ++i)
	{
		pow2[i][0] = MAX_NUMBER;
		pow5[i][0] = MAX_NUMBER;
		pow2[0][i] = MAX_NUMBER;
		pow5[0][i] = MAX_NUMBER;
	}
	
	//calculate every element's 2 and 5 factors number
	for(i = 1; i <= n; ++i)
	{
		int number;
		int pow2_counter = 0;
		int pow5_counter = 0;
		
		for(j = 1; j <= n; ++j)
		{
			scanf("%d", &number);
			
			pow2_counter = 0;
			pow5_counter = 0;
			
			if(number == 0)
			{
				pow2[i][j] = MAX_NUMBER;
				pow5[i][j] = MAX_NUMBER;
				zero_i = i;
				zero_j = j;
			}
			else
			{
				while(number % 2 == 0)
				{
					++pow2_counter;
					number /= 2;
				}
				
				while(number % 5 == 0)
				{
					++pow5_counter;
					number /= 5;
				}
			
				pow2[i][j] = MIN(pow2[i-1][j], pow2[i][j-1]) + pow2_counter;
				pow5[i][j] = MIN(pow5[i-1][j], pow5[i][j-1]) + pow5_counter;
			}
		}
	}
	
	//find the path
	path *path_head;
	path *path_tail;
	path *path_current;
	
	path_head = malloc(sizeof(path));
	path_head->character = '\0';
	
	path_tail = malloc(sizeof(path));
	path_tail->character = '\0';
	
	path_head->next = path_tail;
	path_head->previous = NULL;
	path_tail->next = NULL;
	path_tail->previous = path_head;
	
	i = 1;
	j = 1;
	
	//if there is at least 1 zero number in the matrix
	//and there is no non-zero path...
	if(zero_i != -1 && MIN(pow2[n][n], pow5[n][n]))
	{
		printf("1\n");
		
		//print a way to 0 point
		for(i = 1; i < zero_i; ++i)
			printf("D");
		for(j = 1; j < zero_j; ++j)
			printf("R");
		
		//print a way to end from 0 point
		for(i = zero_i; i < n; ++i)
			printf("D");
		for(j = zero_j; j < n; ++j)
			printf("R");
		
		printf("\n");
	}
	else
	{
		i = n;
		j = n;
		
		printf("%d\n", MIN(pow2[n][n], pow5[n][n]));
		
		if(pow2[n][n] < pow5[n][n])
		{
			while(i > 1 || j > 1)
			{
				if(pow2[i-1][j] < pow2[i][j-1])
				{
					--i;
					add_path(path_head, path_tail, 'D');
				}
				else
				{
					--j;
					add_path(path_head, path_tail, 'R');
				}
			}
		}
		else
		{
			while(i > 1 || j > 1)
			{
				if(pow5[i-1][j] < pow5[i][j-1])
				{
					--i;
					add_path(path_head, path_tail, 'D');
				}
				else
				{
					--j;
					add_path(path_head, path_tail, 'R');
				}
			}
		}
		
		//print out the path
		path_current = path_tail->previous;
		
		while(path_current && path_current->previous)
		{
			printf("%c", path_current->character);
			path_current = path_current->previous;
		}
		
		printf("\n");
	}

	return 0;
}

void add_path(path *path_head, path *path_tail, char character)
{
	path *path_current = malloc(sizeof(path));
	path_current->character = character;
	
	path *path_tail_pre = path_tail->previous;
	
	path_current->next = path_tail;
	path_current->previous = path_tail_pre;
	
	path_tail_pre->next = path_current;
	path_tail->previous = path_current;
}

