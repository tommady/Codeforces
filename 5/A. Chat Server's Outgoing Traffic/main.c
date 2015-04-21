#include <stdio.h>
#include <string.h>

#define MAX_SIZE 126

int main()
{
    int users = 0, bytes = 0, colon_position, commands_length;
    char commands[MAX_SIZE];
    
    while(fgets(commands, MAX_SIZE, stdin))
    {
        commands_length = strlen(commands);
        
        if(commands[0] == '+')
        {
            users++;
        }
        else if(commands[0] == '-')
        {
            users--;
        }
        else
        {
            colon_position = 0;
            while(colon_position < commands_length)
            {
                if(commands[colon_position] == ':')
                {
                    break;
                }
                colon_position++;
            }
            bytes += (commands_length-colon_position-2)*users;
        }
    }
    
    printf("%d\n", bytes);
    return 0;
}
