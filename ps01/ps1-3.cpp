#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void)
{
	int number;
	long long currentTime;
	printf("24-780 Engineering Computation Problem Set 1-3-Virtual Fortune Cookie\n");	
	
	printf("Press the ENTER key to see your fortune for today>");
	getchar();
	
	currentTime=time(NULL);
	srand((unsigned)time(NULL));
		
	number=rand();
	number=number%4;

		if (number==0)
		{
		printf("Genius only means hardworking whole one's life.\n");
		}
		if (number==1)
		{
			printf("All things are difficult before they are easy.\n");
		}
		if (number==2)
		{
		printf("My heart is in the work.\n");
		}
		if (number==3)
		{
			printf("The shortest answer is doing.\n");
		}
		if (number==4)
		{
			printf("Nothing seek,nothing find.\n");
		} 

	printf("Press the ENTER key to close the program>");
	getchar();
	return 0;
}
