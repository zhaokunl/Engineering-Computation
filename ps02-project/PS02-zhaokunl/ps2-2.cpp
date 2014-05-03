# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void Print(char board[])
{
    printf("Bingo!\n");
    
    for(int row=0; row<5; row++)
    {
       for(int clm=0; clm<5; clm++)
       {
            int index;
          long long currentTime;
            currentTime=time(NULL);
            srand((unsigned)time(NULL));
            index=rand();
            index=index%99;
         
          board[(row*5+clm)]=index;

           if(index>9){
            printf("%d",index);
            }
           if(index<10){ printf(" %d",index);
           }
           if(5>clm){
               printf("[ ]");
           }
            if(4>clm){
            printf("|");
            }
            }
        printf("\n");
        
        if(4>row)
        {
            printf("-----+-----+-----+-----+-----\n");
        }
        
    }
}


int CheckAllEqual(char a,char b,char c,char d,char e)
{
    if (' '!=a&&a==b&&b==c&&c==d&&d==e) {
        return 1;
    }
    else{
        return 0;
    }
}

char CheckWinner(char board[])
{
    if(0!=CheckAllEqual(board[0], board[1], board[2],board[3],board[4])||
       0!=CheckAllEqual(board[5], board[6], board[7],board[8],board[9])||
       0!=CheckAllEqual(board[10], board[11], board[12],board[13],board[14])||
       0!=CheckAllEqual(board[15], board[16], board[17],board[18],board[19])||
       0!=CheckAllEqual(board[20], board[21], board[22],board[23],board[24])||
       0!=CheckAllEqual(board[0], board[5], board[10],board[15],board[20])||
       0!=CheckAllEqual(board[1], board[6], board[11],board[16],board[21])||
       0!=CheckAllEqual(board[2], board[7], board[12],board[17],board[22])||
       0!=CheckAllEqual(board[3], board[8], board[13],board[18],board[23])||
       0!=CheckAllEqual(board[4], board[9], board[14],board[19],board[24])||
       0!=CheckAllEqual(board[0], board[6], board[12],board[18],board[24])||
       0!=CheckAllEqual(board[4], board[8], board[12],board[16],board[20]))
                        {
        return 1;
    }
    return 0;
}



int main(void){
    char board[25]={
        ' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' ',
        ' ',' ',' ',' ',' '
    };
    Print(board);
    
            
 /*           if(num>9){
                printf("%d",num);
            }
            if(num<10){ printf(" %d",num);
            }
            
            if(5>clm){
                printf("[ ]");
            }
            if(4>clm){
                printf("|");
            }
        }
        printf("\n");}*/

    
    
   char turn='X';
    for(;;){
            printf("Enter a number>");
            int x;
            scanf("%d",&x);
            int index=x;
//        int num;
       if(0<=x&&x<100)
    
       {
//                if(num=index)
                
                board[index]=turn;
                Print(board);
                if(0!=CheckWinner(board))
                {
                    printf("Bingo!\n");
                    break;
                }
            }
            else{
                printf("Enter a valid number.\n");
            }
        }
    }