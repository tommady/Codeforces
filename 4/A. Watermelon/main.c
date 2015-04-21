#include <stdio.h>

int main(void)
{
    int w;
    
    scanf("%d", &w);
    
    if(w&1 || w < 3)
        printf("NO");
    else
        printf("YES");

    return 0;
}
