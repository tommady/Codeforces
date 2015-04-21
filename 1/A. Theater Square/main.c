#include <stdio.h>

int main(void)
{
	int n = 0;
	int m = 0;
	int a = 0;
	
	scanf("%d %d %d", &n, &m, &a);
	
	long long int weigh = (m+a-1) / a;
	long long int length = (n+a-1) / a;
	
	printf("%I64d\n", weigh * length);
	
	return 0;
}
