/* ----------------------------------------------------- */
/* Filename: Simple_Arithmetic_1.c */
/* Author: Lee.HJ */
/* Time: 2015年 9月16日 星期三 23时24分57秒 CST */
/* Describtion:  */
/* ----------------------------------------------------- */

/* Include --------------------------------------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Private define -------------------------------------- */
#define		MAX		100

#define		SUCCESS	1
#define		ERROR	0

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

/* Import: Target: Model string
 *		   Match: Matched string
 *		   *Local: Local of model in matched string
 * Return: 1: Success
 *		   0: Fail
 * Instruction: 朴素字符串匹配算法
 */
int Simple_A(String Target, String Match, Number *Local)
{
	int offset, count_T, count_M, max_T, max_M;

	offset = 0;
	count_T = 0;
	count_M = 0;
	max_T = Target.length;
	max_M = Match.length;

	for( ; offset <= (max_M - max_T); offset++)
	{
		for( count_M = offset, count_T = 0; 
				count_T < max_T; count_M++, count_T++)
		{
			if( Target.data[count_T] != Match.data[count_M] )
				break;
		}
		if( count_T == max_T )
		{
			(*Local).place[(*Local).num] = offset;
			(*Local).num++;
		}
	}

	return SUCCESS;
}

/*
 *
 */

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

	if(Simple_A(Target, Match, &Local) == SUCCESS)
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
	
	//printf("%d\n", Target.length);

	return 0;
}

