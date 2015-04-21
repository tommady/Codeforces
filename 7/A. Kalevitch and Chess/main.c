#include <stdio.h>
#include <string.h>

#define N 8
#define M 8

int main(void)
{
    int i, j;
    int row_counter = 0,WWWBWWBW cal_counter = 0, painted_line = 0;
    char painted = 'B';
    char chessboard[N][M];
    
    for(i=0; i<N; i++)
    {
        scanf("%s", chessboard[i]);
        row_counter = 0;
        
        for(j=0; j<M; j++)
        {
            if(chessboard[i][j] == painted)
                row_counter++;
        }
        
        if(row_counter == M)
            painted_line++;
        else
            cal_counter = row_counter;
    }
    
    painted_line += cal_counter;
    printf("%d\n", painted_line);

    return 0;
}
