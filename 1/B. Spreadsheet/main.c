#include <stdio.h>
#include <string.h>

#define MAX_SIZE 32

const int radix = 26;

int main(void)
{
	int coordinates;
	
	scanf("%d", &coordinates);
	
	while(coordinates--)
	{
		char numbers[MAX_SIZE];
		int raw, column;
		
		scanf("%s", numbers);
		
		//in RxCx case
		if(sscanf(numbers, "R%dC%d", &raw, &column) == 2)
		{
			char tmp_col[MAX_SIZE];
			int i = 0;
			
			//convert column
			while(column)
			{
				tmp_col[i++] = ((column-1) % radix) + 'A';
				column = (column-1) / radix;
			}
			tmp_col[i] = '\0';
			
			//print column
			for(i = strlen(tmp_col)-1; i >= 0; --i)
				printf("%c", tmp_col[i]);
				
			printf("%d\n", raw);
		}
		//in BCxx case
		else
		{
			char *raw_ptr = numbers;
			
			//point raw to the right position and do the convert for column
			for(column = 0; *raw_ptr >= 'A'; ++raw_ptr)
				column = column * radix + (*raw_ptr ^ 64);
			
			printf("R%sC%d\n", raw_ptr, column);
		}
	}

	return 0;
}
