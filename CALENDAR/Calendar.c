#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define LT 218
#define RT 191
#define CROSS 197
#define HL 196
#define VL 179
#define TT 194
#define BT 193
#define LST 195
#define RST 180
#define LB 192
#define RB 217

#define BS 8
#define SPACE 32

#define DIM 7
#define WIDTH 5
#define HEIGHT 1

#define TOT_COLS 80
#define TOT_LINES 25

#define ESC 27
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define UP 72

#define isleap(y) (((y)%4 == 0 && (y)%100 != 0) || ((y)%400 == 0)) ? 5 : 1

void MakeBox(int R, int C);
void gotoxy(int x, int y);
int day_of_the_week(int y, int m, int d);
void DispCalendar(int month, int year, int R, int C);
void Calendar(int month, int year, int R, int C);

int main()
{
	int R, C, C1;
	int date, month, year;
	C = (TOT_COLS - ((WIDTH * DIM) + (DIM + 1))) / 2;
	R = (TOT_LINES - ((HEIGHT * DIM) + (DIM + 1))) / 2;

	year = 2021;
	month = 2;
	
	Calendar(month, year, R, C);
	
	printf("\n\n\n\n\n");
	
	
	return 0;
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int day_of_the_week(int y, int m, int d) 
{ 
    // array with leading number of days values 
    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
      
    // if month is less than 3 reduce year by 1 
    if (m < 3) 
        y -= 1; 
      
    return ((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7); 
}

void MakeBox(int R, int C)
{	
	int ctr1, ctr2, ctr3;
	
	//FIRST LINE
	gotoxy(C, R);
	printf("%c", LT);
	
	for(ctr2 = 0; ctr2 < DIM; ctr2++)
	{
		for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
		{
			printf("%c", HL);
		}
		printf("%c", TT);
	}
	
	printf("%c%c", BS, RT);
	
	//MIDDLE LINES
	for(ctr3 = 0; ctr3 < DIM; ctr3++)
	{
		R++;
		gotoxy(C, R);
		
		for(ctr2 = 0; ctr2 <= DIM; ctr2++)
		{
			printf("%c", VL);
			for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
			{
				printf("%c", SPACE);
			}
		}
		
		R++;
		gotoxy(C, R);
			
		printf("%c", LST);
		for(ctr2 = 0; ctr2 < DIM; ctr2++)
		{
			for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
			{
				printf("%c", HL);
			}
			printf("%c", CROSS);
		}
		printf("%c%c", BS, RST);
	}
	
	//LAST LINE
	gotoxy(C, R);
	printf("%c", LB);
	
	for(ctr2 = 0; ctr2 < DIM; ctr2++)
	{
		for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
		{
			printf("%c", HL);
		}
		printf("%c", BT);
	}
	
	printf("%c%c", BS, RB);
	
	return;
}

void DispCalendar(int month, int year, int R, int C)
{
	system("cls");
	MakeBox(R, C);
	
	char * WeekName[7] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
	int MonthMax[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char * MonthName[13] = {" ","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
	int ctr, ctr2, C1;
	
	if(isleap(year) == 5)
		MonthMax[2] = 29;
	else
		MonthMax[2] = 28;
	
	gotoxy(C + 17, R - 2);
	printf("%s  %d", MonthName[month], year);
	//DATE
	int DateCount = 1;
	
	//WEEK NAME
	R++; C1 = C + 2;
	gotoxy(C1, R);
	
	printf("%s", WeekName[0]);
	for(ctr = 1; ctr < DIM; ctr++)
	{
		C1+=6;
		gotoxy(C1,R);
		printf("%s", WeekName[ctr]);	
	}
		
	//PRINTING DATE
	R += 2; C1 = C + 3;
	gotoxy(C1, R);
	
	int DateCondition = day_of_the_week(year,month,DateCount);
	
	C1 = C1 + (DateCondition * 6);
	gotoxy(C1, R);

	for(ctr2 = 0; ctr2 < DIM - 1, DateCount < MonthMax[month] +1; ctr2++)
	{
		gotoxy(C1, R);
		for(ctr = 0; ctr < DIM - DateCondition; ctr++)
		{
			
			if (DateCount < MonthMax[month] +1 )
				printf("%02d", DateCount++);//DateCount++;
			else
				break;
			
			C1 += 6;
			gotoxy(C1, R);
			
		}
		DateCondition = 0;
		R += 2;
		C1 = C + 3;	
	}
	return;
}

void Calendar(int month, int year, int R, int C)
{
	DispCalendar(month, year, R, C);
	
	int ch = 0;

	while(ch != ESC)
	{
		ch = getch();
		while(ch != ESC)
		{
			ch = getch();
			
			switch(ch)
			{
				case LEFT : {
					
					month--;
					if(month == 0)
					{
						month = 12;
						year--;
					}
					DispCalendar(month, year, R, C);
					
					break;
				}
				
				case RIGHT : {
					
					month++;
					if(month == 13)
					{
						month = 1;
						year++;
					}
					DispCalendar(month, year, R, C);
					
					break;
				}
				
				case DOWN : {
					
					year++;
					DispCalendar(month, year, R, C);
					
					break;
				}
				case UP : {
					
					year--;
					DispCalendar(month, year, R, C);
					
					break;
				}
			}
		}
	}
		
	return;
}
