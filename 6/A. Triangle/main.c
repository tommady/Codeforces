#include <stdio.h>

int is_triangle(int a, int b, int c)
{
    return (a+b>c) && (a+c>b) && (b+c>a);
}

int is_segment(int a, int b, int c)
{
    return (a+b==c) || (a+c==b) || (b+c==a);
}

int main(void)
{
    int a, b, c, d;
    int triangle = 0, segment = 0;
    
    scanf("%d %d %d %d", &a, &b, &c, &d);
    
    triangle = triangle || is_triangle(a,b,c);
    triangle = triangle || is_triangle(a,b,d);
    triangle = triangle || is_triangle(a,c,d);
    triangle = triangle || is_triangle(b,c,d);
    
    segment = segment || is_segment(a,b,c);
    segment = segment || is_segment(a,b,d);
    segment = segment || is_segment(a,c,d);
    segment = segment || is_segment(b,c,d);
    
    if(triangle)
        printf("TRIANGLE\n");
    else if(segment)
        printf("SEGMENT\n");
    else
        printf("IMPOSSIBLE\n");
    

    return 0;
}
