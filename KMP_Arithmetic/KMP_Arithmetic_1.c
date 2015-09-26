/* ----------------------------------------------------- */
/* Filename: Pi_Arithmetic_1.c */
/* Author: Lee.HJ */
/* Time: 2015年 9月16日 星期三 23时21分17秒 CST */
/* Describtion:  */
/* ----------------------------------------------------- */

/* Include --------------------------------------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Private define -------------------------------------- */
#define		MAX			100
#define		SUCCESS		1
#define		ERROR		0

/* Private typedef ------------------------------------- */
typedef struct String
{
	char data[MAX];
	int length;
}String;

typedef struct Number
{
	int place[MAX];
	int num;
}Number;

/* Private variables ----------------------------------- */

void Compute_Prefix_Function(String Target, int *Pi)
{
	int Max_T = Target.length;
	int k, q;

	Pi[0] = -1;
	k = -1;

	for( q=1; q<Max_T; q++ )
	{
		while( (k>-1)&&(Target.data[k+1]!=Target.data[q]) )
			k = Pi[k];
		if( Target.data[k+1] == Target.data[q] )
			k = k + 1;
		Pi[q] = k;
	}
}

int KMP_Matcher(String Target, String Match, Number *Local)
{
	int Max_T = Target.length; 
	int Max_M = Match.length;
	int Pi[Max_T];
	int q;
	int offset;

	memset(Pi, 0, Max_T);
	Compute_Prefix_Function(Target, Pi);

	for( q=0; q<Max_T; q++)		//put out the Pi
	{
		printf("%d ", Pi[q]);
	}
	printf("\n");

	q = -1;		//number of characters matched

	for(offset=0; offset<Max_M; offset++)	
	//scan the text from left to right
	{
		while( (q>-1)&&(Target.data[q+1] != Match.data[offset]) )
			q = Pi[q];		//next character does not match
		if( Target.data[q+1] == Match.data[offset] )
			q = q + 1;		//next character matches
		if( (q+1) == Max_T )		//is all of Target matched
		{
			(*Local).place[(*Local).num] = offset - Max_T + 1;
			(*Local).num ++;
			q = Pi[q];		//look for the next match
		}
	}
	return SUCCESS;
}

int main(void)
{
	String Target, Match;
	Number Local;
	int count;

	memset((void *)&Target, 0, sizeof(String)); 
	memset((void *)&Match, 0, sizeof(String));
	memset((void *)&Local, 0, sizeof(Number));
	
	//输入模式字符串
	fgets(Target.data, MAX, stdin);
	Target.data[strlen(Target.data) - 1] = '\0';
	Target.length = strlen(Target.data);

	//输入需匹配字符串
	fgets(Match.data, MAX, stdin);
	Match.data[strlen(Match.data) - 1] = '\0';
	Match.length = strlen(Match.data); 
	
	if(KMP_Matcher(Target, Match, &Local) == SUCCESS)
	{
		printf("number : %d\n", Local.num);
		for(count = 0; count < Local.num; count++)
		{
			printf("offset[%d] = %d\n", count, Local.place[count]);
		}   
	}   
	else
	{
	    printf("Match error!\n");
	}
	
	return 0;
}
