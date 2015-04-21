#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char start_point[4];
	char end_point[4];
	char x_go_where;
	char y_go_where;
	
	int distance_x, distance_y;
	
	scanf("%s%s", start_point, end_point);
	
	distance_x = (int)start_point[0] - (int)end_point[0];
	distance_y = (int)start_point[1] - (int)end_point[1];
	
	x_go_where = (distance_x < 0) ? 'R':'L';
	y_go_where = (distance_y < 0) ? 'U':'D';
	
	distance_x = abs(distance_x);
	distance_y = abs(distance_y);
	
	printf("%d\n", (distance_x>distance_y) ? distance_x:distance_y);
	
	while(distance_x || distance_y)
	{
		if(distance_x)
		{
			--distance_x;
			printf("%c", x_go_where);
		}
		
		if(distance_y)
		{
			--distance_y;
			printf("%c", y_go_where);
		}
		
		printf("\n");
	}
	
	return 0;
}

