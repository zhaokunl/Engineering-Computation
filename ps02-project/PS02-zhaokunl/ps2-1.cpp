# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void Print(char board[])
{
    printf("Tick-Tac-Toe\n");
    for(int row=0; row<3; ++row)
    {
        for(int clm=0; clm<3; ++clm)
        {
            int index=row*3+clm;
            printf("%c", board[index]);
if(2>clm)
{
    printf("|");
}
        }
        printf("\n");
        if(2>row)
        {
            printf("-+-+-\n");
        }
    }
}

int CheckAllEqual(char a,char b,char c)
{
    if (' '!=a&&a==b&&b==c) {
        return 1;
    }
    else{
        return 0;
    }
}

int isFull(char board[]){
    int i;
    for(i=0;i<9;i++){
        if(board[i]==' '){
            return 0;
        }
    }
 return 1;
}

char CheckWinner(char board[])
{
    if(0!=CheckAllEqual(board[0], board[1], board[2])||
       0!=CheckAllEqual(board[3], board[4], board[5])||
       0!=CheckAllEqual(board[6], board[7], board[8])||
       0!=CheckAllEqual(board[0], board[3], board[6])||
       0!=CheckAllEqual(board[1], board[4], board[7])||
       0!=CheckAllEqual(board[2], board[5], board[8])||
       0!=CheckAllEqual(board[0], board[4], board[8])||
       0!=CheckAllEqual(board[2], board[4], board[6]))
    {
        return 1;
    }
    return 0;
}



int main(void){
            char board[9]={
        
        ' ',' ',' ',
        ' ',' ',' ',
        ' ',' ',' '
    };
    Print(board);
    char turn='X';
    for(;;){
        int index;
        if('X'==turn){
        printf("%c's turn.\n",turn);
        printf("Enter X and Y>");
        int x,y;
        scanf("%d%d",&x,&y);
        int index=y*3+x;
        
            if(0<=x&&x<3&&0<=y&&y<3&&' '==board[index])
        {    board[index]=turn;
            Print(board);
            if(0!=CheckWinner(board))
            {
                printf("%c wins!\n",turn);
                break;
            }
            if(isFull(board)==1)
            {
                printf("Draw!\n");
                break;
        }
        }
        else{
            printf("Enter an empty location.\n");
        }
            turn='O';
        }
        if('O'==turn){
            printf("It's the computer's turn.\n");
            long long currentTime;
            currentTime=time(NULL);
            srand((unsigned)time(NULL));
            index=rand();
            index=index%8;
            if (board[index]==' '){
                board[index]=turn;
                Print(board);
                if(0!=CheckWinner(board))
                {
                    printf("%c wins!\n",turn);
                    break;
                }
                if(isFull(board)==1){
                    printf("Draw!\n");
                    break;
            }
        }
            turn='X';
        }
    }
    }