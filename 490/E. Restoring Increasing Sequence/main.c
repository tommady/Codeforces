#include <stdio.h>
#include <string.h>

typedef enum {false, true} bool;

typedef struct data
{
    int element[10];
    int mark_pos[10];
    int elem_len;
    int mark_len;
    
} data_l;

int main()
{
    int n, i, j, k;
    scanf("%d", &n);
    
    data_l sequence[n];
    
    for(i=0; i<n; i++)
    {
        char tmp_element[10];
        
        scanf("%s", tmp_element);
        sequence[i].elem_len = strlen(tmp_element);
        
        // if the current element length is smaller than the previous one,
        // it means no answer.
        if(i!=0 && sequence[i-1].elem_len>sequence[i].elem_len)
        {
            printf("NO\n");
            return 0;
        }
        
        // finding question mark postions and record it.
        k = 0;
        for(j=0; j<sequence[i].elem_len; j++)
        {
            if(tmp_element[j] == '?')
            {
                sequence[i].element[j] = -1;
                sequence[i].mark_pos[k++] = j;
            }
            else
                sequence[i].element[j] = tmp_element[j] - '0';
        }
        sequence[i].mark_len = k;
        
        // start considering logic.
        for(j=0; j<sequence[i].mark_len; j++)
        {
            int mark_pos = sequence[i].mark_pos[j];
            
            // handle first element has question marks.
            // handle previous element's length is smaller than current element's.
            if(i==0 || sequence[i-1].elem_len < sequence[i].elem_len)
            {
                if(mark_pos == 0) sequence[i].element[mark_pos] = 1;
                else sequence[i].element[mark_pos] = 0;
            }
            // handle previous and current element's length are the same.
            else if(sequence[i-1].elem_len == sequence[i].elem_len)
            {
                if(mark_pos == 0)
                {
                    // 12226
                    // ?0000    ? should be 2.
                    if(sequence[i].element[mark_pos+1] < sequence[i-1].element[mark_pos+1])
                    {
                        sequence[i].element[mark_pos] = sequence[i-1].element[mark_pos] + 1;
                    }
                    // 12226        12226
                    // ?2227    or  ?3123   ? all should be 1.
                    else if(sequence[i].element[mark_pos+1] >= sequence[i-1].element[mark_pos+1])
                    {
                        sequence[i].element[mark_pos] = sequence[i-1].element[mark_pos];
                    }
                    else
                    {
                        printf("under mark_pos = 0, ERROR!\n");
                        return 1;
                    }
                }
                else
                {
                    bool found = false;
                    
                    for(k=0; k<mark_pos; k++)
                    {
                        if(sequence[i].element[k] > sequence[i-1].element[k])
                        {
                            sequence[i].element[mark_pos] = 0;
                            found = true;
                            break;
                        }
                    }
                    
                    if(!found)
                    {
                        if(sequence[i].element[mark_pos]==-1 && mark_pos!=sequence[i].elem_len-1)
                        {
                            sequence[i].element[mark_pos] = sequence[i-1].element[mark_pos];
                        }
                        else
                        {
                            sequence[i].element[mark_pos] = sequence[i-1].element[mark_pos] + 1;
                        }
                    }
                }
            }
            else
            {
                printf("under handle element, ERROR!\n");
                return 1;
            }
        }
    }
    
    printf("YES\n");
    
    for(i=0; i<n; i++)
    {
        for(j=0; j<sequence[i].elem_len; j++)
        {
            printf("%d", sequence[i].element[j]);
        }
        printf("\n");
    }

    return 0;
}
