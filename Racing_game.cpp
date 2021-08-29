#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


using namespace std;

bool gov;
const int l=5,h=26;
int x,a[l],score;
enum edir{STOP=0,LEFT,RIGHT};
edir direction;

void setup();
void logic();
void map();
void in();

int main()
{
setup();
while(!gov)
{
	map();
	in();
	logic();
}

system("cls");
cout<<"Game Over:"<<endl;
cout<<"Your score: "<<score<<endl;
getch();
return 0;	
}

void setup()
{
	gov=false;
	x=(l-1)/2;
	for(int i=0;i<l;i++)
		a[i]=0;
	direction=STOP;
}

void logic()
{
	switch(direction)
	{
	case 1 :{
		if(x>0)x--;
		break;
	}
	case 2: {
		if(x<l-1)x++;
		break;
	}
	}
	srand(time(NULL));
	for(int i=0;i<l;i++)
		a[i]+=rand()%2;
	
	for(int i=0;i<l;i++)
		if(i==x && a[i]==(h-1))
			gov=true;
		
	for(int i=0;i<l;i++)
		if(a[i]>=h)
			a[i]=0;	
	score++;
	direction=STOP;
}

void map()
{
system("cls");
for(int k=0;k<h;k++){
for(int i=0;i<l;i++)
	{
		
		if(k==a[i])cout<<"-0-";
		else{
			if(k==(h-1) && i==x)cout<<"-^-";
			else{
			cout<<"   ";	
			}
		}
	}
cout<<endl;
}
}

void in()
{
	if(_kbhit())
	{
		switch(_getch())
		{
			case 'a':{
				direction = LEFT;
				break;
			}
			case 'd':{
				direction = RIGHT;
				break;
			}
			default:{
				direction = STOP;
				break;
			}
		}
	}
}
