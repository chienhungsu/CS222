#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* current $ amount */ 
int global_bank;
//global_status[0]: won
//global_status[1]: lost
//global_status[2]: bet-for
//global_status[3]: bet-against
int global_status[4];
/* rolling number1 and 2 */
int global_num1, global_num2; 
/* function prototype */
int rolling(int *arr,int *arr1);
int playing();
int beginning();
int ending();
/*define file pointer */
FILE *fp;

//This program only allows bet in integer.

int main() 
{

	int i;
/*	while loop condition	*/
	int keep_playing = 1;

/*	initialize the current $	*/
	global_bank=100;

/*	initialize the win, lose, bet-for, bet-against number=0 */
	for(i=0; i<4; i++)
	{
		global_status[i]=0;
	}

	beginning();


	while(keep_playing == 1)
	{
	    playing();

/*	print the enter '1' to keep playing	*/
		printf("\nEnter '1' to keep playing. ");
/*	get the keyboar input to store in keep_playing */
		scanf("%d", &keep_playing);
/* if playing condition not equal to 1 */
		if(keep_playing != 1)
		{
			keep_playing = 0;
		}
	}

	ending();



	return 0;


}

/* function to read the value from file */
int beginning()
{
/*	open the file */
	fp=fopen("write.txt","r");
/*	load the number of win, lose, bet-for, bet-against, last time $ amount */
	fscanf(fp,"%d\n",&global_status[0]);
	fscanf(fp,"%d\n",&global_status[1]);
	fscanf(fp,"%d\n",&global_status[2]);
	fscanf(fp,"%d\n",&global_status[3]);
	fscanf(fp,"%d\n",&global_bank);
/*	print the four value five out 	*/
	printf("win:%d		lose:%d 	bet-for:%d		bet-against:%d\n",global_status[0],global_status[1],global_status[2],global_status[3]);
/*	close the file	*/
	fclose(fp);
	return 0;
}

/*	function to print the five values and store the value to file */	
int ending()
{
/*	print the current value, win, lose, bet-for, bet-against	*/
	printf("curent value:%d		win:%d		lose:%d 	bet-for:%d		bet-against:%d\n",global_bank,global_status[0],global_status[1],global_status[2],global_status[3]);
/*	open the file	*/
	fp=fopen("write.txt","w");
/*	write the five values in to variables	*/
	fprintf(fp,"%d\n",global_status[0]);
	fprintf(fp,"%d\n",global_status[1]);
	fprintf(fp,"%d\n",global_status[2]);
	fprintf(fp,"%d\n",global_status[3]);
	fprintf(fp,"%d\n",global_bank);
/*	close the file	*/
	fclose(fp);
	return 0;
}

int playing()
{
/*	declare and initialize the all value to 0	*/
	int bet_money=0;
	//int add=0;
	int way=0;
	int first_roll=0;
	int second_roll=0;
	int double_bet=0;
	int way_okay = 0;
	int balance_okay = 0;
/*	declare and initialize the rolling to 1	*/
	int keep_rolling = 1;
/*	declare and initialize the keeping rolling input	*/
	int enter_one = 1;
	printf("\nCurrent money in bank: %d. ", global_bank);

/* while way_okay=0 starting the while loop	*/
	while(! way_okay)
	{
		printf("\nBet for yourself - please input 1. Bet against yourself - please input 2: ");
		scanf("%d",&way);
		if(way!=1 && way !=2)
		{
			printf("\nInput error.");
		}
		else
		{
			way_okay = 1;
		}
	}

	balance_okay=0;
	while(! balance_okay)
	{
		printf("\nHow much money do you want to bet (Minimum:5) ? ");
/*	get the keyboard value betmoney	*/
		scanf("%d",&bet_money);		
/*	set the condition bet-money can't be smaller than 5 and bigger current value	*/
		if(bet_money <5 || global_bank < bet_money )
		{
			printf("\nError. Not enough money in bet, or not enough money in bank.");
		}
		else
		{
			global_bank = global_bank - bet_money;
			balance_okay=1;
		}
	}
	

/* call the rolling function and store the value to first_roll	*/
	first_roll = rolling(&global_num1,&global_num2);	
/*	set condition bet for yourself true then keep going, otherwise bet against*/
	if(way==1)
	{
		printf("\nYou rolled %d",first_roll);
		global_status[2]=global_status[2]+1;
/*	win condition	*/
		if(first_roll==7 || first_roll==11)
		{
			printf("\nYou won.");
			global_bank = global_bank +  (bet_money*2);
			global_status[0]=global_status[0]+1;
		}
/*	lose condition	*/
		else if(first_roll==2 ||first_roll==3 || first_roll==12)
		{
			printf("\nYou lost.");
			global_status[1]=global_status[1]+1;
		} 
/*	otherwise condition	*/
		else 
		{
/*		ensure the $amount is bigger than bet money	*/
			if(global_bank >= bet_money)
			{
			    printf("\nEnter '1' to double the bet, or other number to pass.");
/*	get the value double or not	*/
				scanf("%d",&double_bet);	
/*	double condition	*/
				if(double_bet==1)
				{
					global_bank = global_bank - bet_money;
					bet_money=bet_money*2;
				}
			}
/*	$amount is smaller than bet money	*/
			else
			{
				printf("\nYou don't have enought money in bank to double the bet. Continue.");
			}

			while(keep_rolling)
			{
				printf("\nEnter '1' to roll. ");
				scanf("%d",&enter_one);	
				second_roll=rolling(&global_num1,&global_num2);
				if(second_roll == first_roll)
				{	
					printf("\nYou rolled %d. You won. Bet: %d", second_roll, bet_money);
					global_status[0]=global_status[0]+1;
					global_bank = global_bank +  (bet_money*2);
					keep_rolling=0;
				}	
				else if(second_roll == 7)
				{
					printf("\nYou rolled 7. You lost. Bet: %d" , bet_money);
					global_status[1]=global_status[1]+1;
					keep_rolling=0;
				}
				else
				{
					printf("\nYou rolled %d. Keep rolling", second_roll);
					keep_rolling = 1;
				}
			}
		}
	}

	else if(way==2)

	{
		printf("\nYou rolled %d",first_roll);
		global_status[3]=global_status[3]+1;
		if(first_roll==2 || first_roll==3 || first_roll==12)
		{
			printf("\nYou won.");
			global_bank = global_bank +  (bet_money*2);
			global_status[0]=global_status[0]+1;
		}
		else if(first_roll==7 ||first_roll==11 )
		{
			printf("\nYou lost.");
			global_status[1]=global_status[1]+1;
		} 
		else 
		{
			if(global_bank >= bet_money)
			{
			    printf("\nEnter '1' to double the bet, or other number to pass.");
				scanf("%d",&double_bet);	
				if(double_bet==1)
				{
					global_bank = global_bank - bet_money;
					bet_money=bet_money*2;
				}
			}
			else
			{
				printf("\nYou don't have enought money in bank to double the bet. Continue.");
			}

			while(keep_rolling)
			{
				printf("\nEnter '1' to roll. ");
				scanf("%d",&enter_one);	
				second_roll=rolling(&global_num1,&global_num2);
				if(second_roll == 7)
				{	
					printf("\nYou rolled 7. You won. Bet: %d" , bet_money);
					global_status[0]=global_status[0]+1;
					global_bank = global_bank +  (bet_money*2);
					keep_rolling=0;
				}	
				else if(second_roll == first_roll)
				{
					
					printf("\nYou rolled %d. You lost. Bet: %d", second_roll, bet_money);
					global_status[1]=global_status[1]+1;
					keep_rolling=0;
				}
				else
				{
					printf("\nYou rolled %d. Keep rolling", second_roll);
					keep_rolling = 1;
				}
			}
		}

	}

	return 0;
}

/*	function rolling to create the two dices, pass the values by address reference and return dice total by return value */
int rolling(int *arr,int *arr1)
{
	int dice=0,a1,a2;
	srand(time(NULL)); 
	a1 = rand()%6+1;
	a2 = rand()%6+1;
	*arr=a1;
	*arr1=a2;
	dice=a1+ a2;
	printf("\nFirst dice: %d. Second dice: %d", a1, a2);
	return (dice);
}

