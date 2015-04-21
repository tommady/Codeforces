#include <stdio.h>

int main(void)
{
    int n, i, w;
    scanf("%d", &n);
    
    int children;
    int programmers[n];
    int mathematicians[n];
    int sportsmen[n];
    int programmer_counter = 0;
    int mathematician_counter = 0;
    int sportsman_counter = 0;
    
    for(i=0; i<n; i++)
    {
        scanf("%d", &children);
        if(children == 1)
        {
            programmers[programmer_counter] = i+1;
            programmer_counter++;
        }
        else if(children == 2)
        {
            mathematicians[mathematician_counter] = i+1;
            mathematician_counter++;
        }
        else
        {
            sportsmen[sportsman_counter] = i+1;
            sportsman_counter++;
        }
    }
    
    if(programmer_counter<=mathematician_counter && programmer_counter<=sportsman_counter)
        w = programmer_counter;
    else if(mathematician_counter<=programmer_counter && mathematician_counter<=sportsman_counter)
        w = mathematician_counter;
    else
        w = sportsman_counter;
    printf("%d\n", w);
    
    if(w != 0)
    {
        for(i=0; i<w; i++)
            printf("%d %d %d\n", programmers[i], mathematicians[i], sportsmen[i]);
    }

    return 0;
}
