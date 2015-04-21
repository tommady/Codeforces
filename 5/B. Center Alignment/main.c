#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1024

typedef struct
{
    char string[MAX_SIZE];
    int length;
}data;


int main(void)
{
    data line[MAX_SIZE];
    int max_length = 0, closing_left = 1, line_counter = 0;
    int i, j, k;
    
    while(fgets(line[line_counter].string, MAX_SIZE, stdin))
    {
        line[line_counter].length = strlen(line[line_counter].string);
        line[line_counter].string[line[line_counter].length-1] = '\0';
        
        if(line[line_counter].length > max_length)
        {
            max_length = line[line_counter].length;
        }
        
        line_counter++;
    }
    
    //print the top floor
    for(i=0; i<max_length+1; i++)
        printf("*");
    printf("\n");
    
    for(i=0; i<line_counter; i++)
    {
        printf("*");
        
        j = max_length - line[i].length;
        
        //center
        if(!(j%2))
        {
            for(k=0; k<j/2; k++)
                printf(" ");

            printf("%s", line[i].string);
            
            for(k=0; k<j/2; k++)
                printf(" ");
        }
        else
        {
            if(closing_left)
            {
                for(k=0; k<j/2; k++)
                    printf(" ");

                printf("%s", line[i].string);
                
                for(k=0; k<j/2+1; k++)
                    printf(" ");
                
                closing_left = 0;
            }
            else
            {
                for(k=0; k<j/2+1; k++)
                    printf(" ");

                printf("%s", line[i].string);
                
                for(k=0; k<j/2; k++)
                    printf(" ");
                
                closing_left = 1;
            }
        }
        
        printf("*\n");
    }
    
    //print the bottom floor
    for(i=0; i<max_length+1; i++)
        printf("*");
    printf("\n");
    
    return 0;
}
