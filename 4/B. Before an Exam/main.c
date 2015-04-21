#include <stdio.h>

int main(void)
{
    int days, sum_time, i, tmp;
    int sum_max = 0, sum_min = 0;
    
    scanf("%d %d", &days, &sum_time);
    int max[days+1], min[days+1];
    
    for(i=0; i<days; i++)
    {
        scanf("%d %d", &min[i], &max[i]);
        sum_max += max[i];
        sum_min += min[i];
    }
    
    if(sum_time<sum_min || sum_time>sum_max)
    {
        printf("NO\n");
    }
    else
    {
        printf("YES\n");
        sum_time -= sum_min;
        
        for(i=0; i<days; i++)
        {
            if(sum_time)
            {
                tmp = max[i] - min[i];
                if(sum_time > tmp)
                {
                    sum_time -= tmp;
                    printf("%d ", max[i]);
                }
                else
                {
                    printf("%d ", min[i]+sum_time);
                    sum_time = 0;    //using min time instead
                }
            }
            else
            {
                printf("%d ", min[i]);
            }
        }
    }
    
    return 0;
}
