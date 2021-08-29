#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

using namespace std;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER  13
#define ESC 27


double accuracy=0.0001;
const int menu_lenght=20,menu_ammount=4;
const char *str_menu[menu_ammount]={"Solve system","Help","About","Exit"};
const char *pidmenu[menu_ammount+1]={"Exit to menu","Gausian method","Relaxation method","Kramer's rule","Matrix method"};
WORD menu_enabled=225, menu_disabled=6,header=11,error_color = 12;
COORD global_pos;

void druk_menu(HANDLE,COORD,int);
void about(HANDLE);
void help(HANDLE);
void solve(HANDLE);
int pid_menu(HANDLE,bool);
int gauss(double**,int,int);
int relax(double**,int,HANDLE);
int kramer(double**,int,HANDLE);
int matrix(double**,int,HANDLE);
double vyznachnyk(double**,int);


int main(){
	
bool end=false,enter=false;
int choice=0;
HANDLE main=GetStdHandle(STD_OUTPUT_HANDLE);
char menu_option;
COORD pos={10,10};

while(!end)
{
           
druk_menu(main,pos,choice);

switch(_getch())
{
      case LEFT:{
           if(choice>0)choice--;
           break;
           }
      case RIGHT:{
           if(choice<menu_ammount-1)choice++;
           break;
           }
      case ENTER:{
           enter=true;  
           }
}

if(enter)
{
    switch(choice)
    {
         case 0:{
              solve(main);
              druk_menu(main,pos,choice);
              break;
              }
              
         case 1:{
              help(main);
              system("pause");
              druk_menu(main,pos,choice);
              break;
              }
              
         case 2:{
              about(main);
              system("pause");
              druk_menu(main,pos,choice);
              break;
              }
              
         case 3:{
         end=true;
              }
    }
    enter=false;
}          
}


system("pause");
return 0;
}

void druk_menu(HANDLE h,COORD pos,int choice){
     SetConsoleTextAttribute(h,menu_disabled);
     system("cls");
     
     global_pos.Y=pos.Y;
     global_pos.X=pos.X;
     
     for(int i=0;i<menu_ammount;i++)
     {
             global_pos.X=pos.X+i*menu_lenght;
             SetConsoleCursorPosition(h,global_pos);
             cout<<str_menu[i];
     }
     
     global_pos.X=pos.X+choice*menu_lenght;
     SetConsoleCursorPosition(h,global_pos);
     
     SetConsoleTextAttribute(h,menu_enabled);
     cout<<str_menu[choice];
     SetConsoleTextAttribute(h,menu_disabled);
     
     
     global_pos.Y++;
     global_pos.X=pos.X;
     SetConsoleCursorPosition(h,global_pos);
}

void about(HANDLE h){
SetConsoleTextAttribute(h,header);
cout<<"This program was created by Oleksiy Panichek."; 
global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
cout<<"Student of IASA."<<endl;
global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
SetConsoleTextAttribute(h,menu_disabled);
}

void help(HANDLE h){
SetConsoleTextAttribute(h,header);
cout<<"To choose option use arrows and then enter to confirm ";
global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
cout<<"To start solving system choose option (Solve system) and press enter ";

global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
cout<<"Then enter size of system using arrows";

global_pos.Y+=2;
SetConsoleCursorPosition(h,global_pos);
cout<<"Then press enter to confirm changes";

global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
cout<<"Use arrows to get necessary koeficient and then pres enter->enter number->enter";

global_pos.Y+=2;
SetConsoleCursorPosition(h,global_pos);
cout<<"To save current system and carry on press esc";

global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
cout<<"Choose method to solve, for square matrix  - all methods aviliable, for non-square - only Gausian method";

global_pos.Y+=2;
SetConsoleCursorPosition(h,global_pos);


SetConsoleTextAttribute(h,error_color);
cout<<pidmenu[1];
global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
SetConsoleTextAttribute(h,header);

global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
cout<<"This method works with any matrix and gives an output of dependend variables";


global_pos.Y+=2;
SetConsoleCursorPosition(h,global_pos);

SetConsoleTextAttribute(h,error_color);
cout<<pidmenu[2];
SetConsoleTextAttribute(h,header);
global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
cout<<"Can be used for any square matrix with non-zero diagonal elements ";


global_pos.Y+=2;
SetConsoleCursorPosition(h,global_pos);


SetConsoleTextAttribute(h,error_color);
cout<<pidmenu[3];
SetConsoleTextAttribute(h,header);
global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
cout<<"Classic Kramer`s rule can be used only for square matrix with non-zero determinant";

global_pos.Y+=2;
SetConsoleCursorPosition(h,global_pos);

SetConsoleTextAttribute(h,error_color);
global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
cout<<pidmenu[4];
SetConsoleTextAttribute(h,header);
global_pos.Y++;

SetConsoleCursorPosition(h,global_pos);
cout<<"Requires the same as Kramer`s rule";
global_pos.Y++;
SetConsoleTextAttribute(h,menu_disabled);
SetConsoleCursorPosition(h,global_pos);


}

void solve(HANDLE h)
{  
int n=2,m=2,choiceX=0,choiceY=0;
bool end=false;
int choice=0;
COORD pos;
SHORT P;
DWORD temp;
bool cycle_end=true;

SetConsoleCursorPosition(h,global_pos);

SetConsoleTextAttribute(h,header);
cout<<"Enter size of system, adjust n,m by arrows";
SetConsoleTextAttribute(h,menu_disabled);

global_pos.Y++;
pos.Y=global_pos.Y;
pos.X=global_pos.X;

// редагування кількості змінних(m) ,рівнянь (n).

while(!end)
{
	
SetConsoleCursorPosition(h,global_pos);
cout<<n<<"x"<<m<<"                            "<<endl;

switch(_getch())
{
	case UP:n++;break;
	case DOWN:if(n>2)n--;break;
	case RIGHT:if(m<10)m++;break;
	case LEFT:if(m>2)m--;break;
	case ENTER:end=true;
}
}

//виведення тексту про редагування змінних на екран.
global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
SetConsoleTextAttribute(h,header);
cout<<"Enter system koefficients choosing them by arrows and confirming choice by enter.";
global_pos.Y++;
SetConsoleCursorPosition(h,global_pos);
cout<<"To continue press esc while choosing koefficient"<<endl;
SetConsoleTextAttribute(h,menu_disabled);

global_pos.Y++;
pos.Y=global_pos.Y;
pos.X=global_pos.X;
SetConsoleCursorPosition(h,global_pos);


// створення динамічного масиву коефіцієнтів перед змінними.

double **a=new double*[n];

for(int i=0;i<n;i++)
{
	a[i]=new double[m+1];
}

double **a_temp = new double*[n];

for(int i=0;i<n;i++){
	a_temp[i]=new double[m+1];
	for(int k=0;k<m+1;k++){
		a_temp[i][k]=0;
	}
}


P=pos.Y;

while(cycle_end){
//виписка коефіцієнтів, отриманих під час минулої ітерації

for(int i=0;i<n;i++){
for(int k=0;k<m+1;k++){
		a[i][k]=a_temp[i][k];
	}
}

SetConsoleTextAttribute(h,menu_disabled);

//витирання зайвого сміття.

pos.X=0;
for(int i=m-1;i<=2*m+1;i++){
pos.Y=P+i;
SetConsoleCursorPosition(h,pos);
for(int i=0;i<120;i++){
	cout<<" ";
}

}

// вибір коефіцієнтів при змінних, їхнє редагування.

end=false;
while(!end)
{
	
	
global_pos.Y=P;
SetConsoleCursorPosition(h,global_pos);
SetConsoleTextAttribute(h,menu_disabled);
for(int i=0;i<n;i++){
	for(int j=0;j<80;j++){
		cout<<" ";
	}
}


for(int i=0;i<n;i++)
{
SetConsoleCursorPosition(h,global_pos);	
for(int k=0;k<m+1;k++)
{
if(k==choiceX && i==choiceY)
{
	SetConsoleTextAttribute(h,menu_enabled);
	cout<<a[i][k];
	SetConsoleTextAttribute(h,menu_disabled);
}else{
	cout<<a[i][k];
}

if(k<m-1)cout<<" x"<<k+1<<" + ";
if(k==(m-1))cout<<" x"<<k+1<<" = ";

}
cout<<" ;";
global_pos.Y++;
}


FillConsoleOutputCharacter(h,(TCHAR)' ',80,global_pos,&temp);
SetConsoleCursorPosition(h,global_pos);

switch(getch())
{
	case UP:
		if(choiceY>0)choiceY--;
		break;
	case DOWN:
		if(choiceY<n-1)choiceY++;
		break;
	case RIGHT:
		if(choiceX<m)choiceX++;
		break;
	case LEFT:
		if(choiceX>0)choiceX--;
		break;
	case ENTER:{
		SetConsoleCursorPosition(h,global_pos);
		FillConsoleOutputCharacter(h,(TCHAR)' ',200,global_pos,&temp);
		char* s=new char[40];
		bool log=false;
		cin.getline(s,80,'\n');
		
		if(s[0]!='-'&& !isdigit(s[0])){
			log = true;
		}
		
		for(int i=1;i<strlen(s);i++){
			if(!isdigit(s[i])&&s[i]!='.'){
				log=true;
				break;
			}
		}
		
		if(!log){
		a[choiceY][choiceX]=atof(s);
		}
		
		break;
		}
	case ESC:
	    end=true;
}
}


//переписування коефіцієнтів у масив,для збереження.

for(int i=0;i<n;i++){
	for(int k=0;k<m+1;k++){
		a_temp[i][k]=a[i][k];
	}
}



// відкриття підменю вибору методу.

int nchoice=pid_menu(h,n==m);

pos.X=0;
for(int i=1;i<=m;i++){
pos.Y=global_pos.Y+i;
FillConsoleOutputCharacter(h,(TCHAR)' ',120,pos,&temp);	
}


switch(nchoice)
{
	case 0:cycle_end=false;break;
	case 1:gauss(a,n,m);break;
	case 2:relax(a,n+1,h);break;
	case 3:kramer(a,n+1,h);break;
	case 4:matrix(a,n+1,h); break;
}

system("pause");

}
//вивільнення пам'яті.

for(int i=0;i<n;i++){
delete [] a_temp[i];
delete [] a[i];
}

delete [] a_temp;
delete [] a;
}

int pid_menu(HANDLE h,bool logic)
{
	int choice = 0;
    COORD pos;
    bool end = false;
    int n=menu_ammount-2;
    if(logic)n=menu_ammount+1;
    
    pos.X=global_pos.X;
    pos.Y=global_pos.Y;
    SetConsoleCursorPosition(h,pos);
    
    while(!end){
    for(int i=0;i<n;i++)
    {
            pos.X=global_pos.X+i*menu_lenght;
            SetConsoleCursorPosition(h,pos);
            cout<<pidmenu[i];
    }
    
    pos.X=global_pos.X+choice*menu_lenght;
    SetConsoleCursorPosition(h,pos);
    SetConsoleTextAttribute(h,menu_enabled);
    cout<<pidmenu[choice];
    SetConsoleTextAttribute(h,menu_disabled);
    cout<<endl;
    
    switch(_getch())
    {
	case RIGHT:if(choice<n-1)choice++;break;
	case LEFT:if(choice>0)choice--;break;
	case ENTER:end=true;
    }
    
	}
return choice;
}
    
int gauss(double **a,int n,int m){
int  int_temp;
int* b = new int[m]; //масив для реєстрації порядку змінних.
double alpha; //використовується як тимчасова змінна для обміну і стала, на яку множаться коефіцієнти у методі Гаусса.
double* temp =new double;; // вказівник для обміну рядків.
bool prapor=true; //прапорець для реєстрації успішного обміну рядків.
int size; //містимить значення найменшої з величин: n або m.

(n<m)?size=n:size=m;

for(int i=0;i<m;i++)b[i]=i+1;

for(int k=0;k<size;k++)
{
while(a[k][k]==0 && k<size){
	for(int j=k+1;j<n;j++)
	if(a[j][k]!=0)
		{
		temp=a[j];
		a[j]=a[k]; //обмін місцями рядків.
		a[k]=temp;
		
		prapor=false; //прапорець успішного обміну.
		}
	
	if(prapor)
	{	
		prapor = false;
		
		for(int j=k;j<m-1;j++){
		
		for(int i=0;i<n;i++)
		{
		alpha=a[i][j];
		a[i][j]=a[i][j+1]; // зміна стовпців.
		a[i][j+1]=alpha;
		
		if(a[i][j+1] && j!=m)prapor=true;
		}	
		int_temp=b[j];
		b[j]=b[j+1];     // зміна порядку.
		b[j+1]=int_temp;
		}
	}
	
	if(!prapor)
	{
		for(int i=0;i<m;i++)
		if(a[k][m]!=0){
			prapor =true;
			break;
		}
		
		if(!prapor && a[k][m]!=0)
		{
			cout<<"No solution"<<endl;
			
			temp=NULL;
			delete[] b;
			delete temp;
			return 0;
		}
		if(!prapor){
		temp=a[n-1];
		a[n-1]=a[k];
		a[k]=temp;
		n--;
		(n<m)?size=n:size=m;
		prapor=true;
		}
		
	}	
}

for(int i=k+1;i<n;i++)
{
alpha=a[i][k]/a[k][k];
for(int j=k;j<m+1;j++)
{
	a[i][j]-=alpha*a[k][j];	 //віднімаємо від кожного коеф. з одного рядка  - коеф. з іншого.
}
}

}

//зворотній хід

for(int k=size-1;k>0;k--)
{
for(int i=k-1;i>=0;i--)
{
alpha=a[i][k]/a[k][k];
for(int j=0;j<m+1;j++)
{
	a[i][j]-=alpha*a[k][j];	 //віднімаємо від кожного коеф. з одного рядка  - коеф. з іншого.
}
}

//поділ рядків на число, коефіцієнт перед першою невідомою.

for(int i=0;i<n;i++){
	
if(a[i][i])alpha=a[i][i];
for(int j=0;j<m+1;j++)
{
if(a[i][j]<accuracy && a[i][j]>-accuracy)a[i][j]=0;
a[i][j]/=alpha;
}
}
}

//перевірка на відсутність розв'язків.

prapor=false;

for(int i=0;i<n;i++)
{

for(int j=0;j<m;j++)
if(a[i][j])prapor=true;

if(!prapor && a[i][m]!=0)
{
cout<<"No solutions"<<endl;
temp=NULL;
delete temp;
return 0;
}
prapor = false;
}
//виписка результатів.

prapor=false; 			// для перевірки випадку, коли єдиний вільний член - нуль.
for(int i=0;i<size;i++)
{
cout<<"x"<<b[i]<<" = ";
for(int k=i+1;k<m;k++)
{
	if(a[i][k]!=0){
	cout<<(-a[i][k])<<" x"<<b[k];
	
	
		if(k<m-1&& a[i][k+1]<0)cout<<"+";
		else if(k==m-1 && a[i][m]>0)cout<<"+";

	prapor=true;
	}


}
	if(a[i][m]!=0 || !prapor)cout<<a[i][m];
	cout<<";";
	cout<<endl;
}

temp=NULL;
delete temp;
return 0;

}

int relax(double**a,int m,HANDLE h){
int n=m-1,i_m,count;
double**g = new double*[n];

for(int i=0;i<n;i++){
	g[i]=new double [n];
	for(int j=0;j<n;j++){
		g[i][j]=a[i][j];
	}
}

double* x = new double [n];
double* nx = new double [n];  //створюємо динамічні масиви x, xn.
double alpha; //тимчасова змінна для зберігання найбільшої нев'язки.
DWORD temp;


alpha=vyznachnyk(g,n);

for(int i=0;i<n;i++)
delete[] g[i];


delete [] g;

if(alpha==0){
	SetConsoleTextAttribute(h,error_color);
	cout<<"Can`t be solved by this method"<<endl;
	SetConsoleTextAttribute(h,menu_disabled);
			
			delete [] nx;
			delete[] x;
			return 1;
}


for(int i=0;i<n;i++){
	if(a[i][i]==0){
			SetConsoleTextAttribute(h,error_color);
			cout<<"Can`t be solved by this method"<<endl;
			SetConsoleTextAttribute(h,menu_disabled);
			
			delete [] nx;
			delete[] x;
			return 1;
	}
}

//початкове наближення (0 0 0 0 ... 0)
for(int i=0;i<n;i++)
{
    nx[i]=0; 
}

// у масив x вписуємо початкове значення нев'язок.
for(int i=0;i<n;i++){
          x[i]=a[i][n];
for(int j=0;j<n;j++){
    if(i!=j)x[i]-=a[i][j]*nx[j];
}
      x[i]/=a[i][i]; // поділ на діагональний елемент відповідної нев'язки.
    	x[i]-=nx[i]; // віднімання поточного значення змінної 
}	

clock_t start =clock();	

do{ 
count=0;
i_m=0;   

     for(int k=0;k<n;k++){
        if(fabs(x[k])>fabs(x[i_m])){
        		i_m=k;
			}
		}
		
		alpha =x[i_m];
		
		//додаємо різницю нев'язки
		for(int k=0;k<n;k++){
			x[k]-=a[k][i_m]*alpha/a[k][k];
		}
		
			//підраховуємо кількість нев'язок, менших за точність.
		for(int k=0;k<n;k++){
			if(fabs(x[k])<accuracy)count++;
		}
		nx[i_m]+=alpha;
		x[i_m]=0;
		
		double time=clock()-start;
		
		if(time>10000){
			SetConsoleTextAttribute(h,error_color);
			cout<<"Can`t be solved by this method: (too many operations, try another method)"<<endl;
			SetConsoleTextAttribute(h,menu_disabled);
			delete [] nx;
			delete[] x;
            return 0;
		}
}while(count < n);
 
for(int i=0;i<n;i++)
cout<<"x"<<i+1<<" = "<<nx[i]<<"; "<<endl;


delete [] nx;
delete[] x;
return 0;

}

int kramer(double** a,int n,HANDLE h){
double system_vyzn;// визначник матриці коефіцієнтів.
double* vyzn= new double[n-1]; //створення масиву визначників для кожної змінної.
double temp; //змінна для обміну.
double **t = new double* [n-1];

for(int i=0;i<n-1;i++)
t[i]= new double[n];

for(int i=0;i<n-1;i++)
for(int j=0;j<n;j++)
t[i][j]=a[i][j];


system_vyzn=vyznachnyk(a,n-1);


//перевірка на розв'язність методом Крамера.
if(system_vyzn==0){

SetConsoleTextAttribute(h,error_color);
cout<<"Can`t be solved using Kramer`s rule!"<<endl;
SetConsoleTextAttribute(h,menu_disabled);

for(int i=0;i<n-1;i++)
delete [] t[i];

delete[] t;
delete[] vyzn;

return 1;
}

for(int k=0;k<n-1;k++)
{
	
//запис з масиву t у масив a, для відновлення втрачених значень.
for(int i=0;i<n-1;i++)
for(int j=0;j<n;j++)
a[i][j]=t[i][j]; 


// заміна k-ого стовпця значеннями вільних членів.
for(int i=0;i<n-1;i++)
a[i][k]=t[i][n-1];



vyzn[k]=vyznachnyk(a,n-1);
		
}

for(int k=0;k<n-1;k++)
cout<<"x"<<k+1<<" = "<<vyzn[k]/system_vyzn<<";"<<endl;

// вивільнення пам'яті. 
for(int i=0;i<n-1;i++)
delete [] t[i];

delete[] t;
delete[] vyzn;
return 0;
}   

int matrix(double** a,int m,HANDLE hand){
double* temp; //змінна для обміну.
double alpha; //змінна для обміну.
int n=m-1;
double **b = new double * [n];


//виділення пам'яті під масив b, що у майбутньому стане оберненою матрицею.

for(int k=0;k<n;k++)
b[k]= new double[n];


// заповнення масиву b значеннями з масиву a.

for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
b[i][j]=a[i][j];


alpha=vyznachnyk(b,n);



	if(alpha==0)
	{
			SetConsoleTextAttribute(h,error_color);
			cout<<"This method can`t be used! "<<endl;
			SetConsoleTextAttribute(h,menu_disabled);
			temp=NULL;
			
			
			for(int i=0;i<n;i++)
			delete[] b[i];
			
			delete[] b;
			delete temp;
			return 1;
	}	
	
// заповнення масиву b значеннями 1 або 0,  як одиничну матрицю.

for(int i=0;i<n;i++)
for(int k=0;k<n;k++)
{
	if(k==i)b[i][k]=1;
	else{
		b[i][k]=0;   
	}
}



for(int k=0;k<n;k++){
while(a[k][k]==0 && k<n){
	for(int j=k+1;j<n;j++)
		{
		temp=a[j];
		a[j]=a[k]; //обмін місцями рядків.
		a[k]=temp;
		
		temp=b[j];
		b[j]=b[k]; //обмін місцями рядків у оберненій матриці.
		b[k]=temp;
		}
}

for(int i=k+1;i<n;i++)
{
alpha=a[i][k]/a[k][k];
for(int j=0;j<n;j++)
{
	a[i][j]-=alpha*a[k][j];	 //віднімаємо від кожного коеф. з одного рядка  - коеф. з іншого.
	b[i][j]-=alpha*b[k][j];
}
}

}

//зворотній хід

for(int k=n-1;k>0;k--)
{
for(int i=k-1;i>=0;i--)
{
alpha=a[i][k]/a[k][k];
for(int j=0;j<n;j++)
{
	a[i][j]-=alpha*a[k][j];	 //віднімаємо від кожного коеф. з одного рядка  - коеф. з іншого.
	b[i][j]-=alpha*b[k][j];
}
}

//поділ рядків на число, коефіцієнт перед першою невідомою.

for(int i=0;i<n;i++){
	
if(a[i][i])alpha=a[i][i];
for(int j=0;j<n;j++)
{
if(a[i][j]<accuracy && a[i][j]>-accuracy)a[i][j]=0;
a[i][j]/=alpha;

if(b[i][j]<accuracy && b[i][j]>-accuracy)b[i][j]=0;
b[i][j]/=alpha;
}
}

}  

double res; // змінна для збереження поточного результату, поточної змінної.

for(int i=0;i<n;i++)
{
	res=0;
	
	for(int j=0;j<n;j++)
	{
	res+=b[i][j]*a[j][n];
	}

	cout<<"x"<<i+1<<" = "<<res<<";"<<endl;
}

temp=NULL;

//вивільнення пам'яті.
for(int j=0;j<n;j++)
delete [] b[j];

delete[] b;
delete temp;
return 0;

}
    
double vyznachnyk(double * a[], int n){
	double res=1,alpha; // змінна для збереження результату і сталої для приведення визначника до трикутного вигляду.
	double* temp =new double; //вказівник для зміни місцями стовпців.
	bool prapor=true;
	
	// зведедення визначника до трикутного вигляду еквівалентними перетвореннями системи рядків та стовпчиків.
for(int k=0;k<n;k++){
	while(a[k][k]==0){
	prapor=true;
		
	for(int j=k+1;j<n;j++)
	if(a[j][k]!=0)
		{
		temp=a[j];
		a[j]=a[k]; //обмін місцями рядків.
		a[k]=temp;
		
		prapor=false; //прапорець успішного обміну.
		
		res*=(-1); // зміна знаку визначника ( результату).
		}
	
	if(prapor)
	{	
		for(int j=k;j<n-1;j++)
		{
		if(a[k][j+1]!=0){
		for(int i=0;i<n;i++)
		{
		alpha=a[i][j];
		a[i][j]=a[i][j+1]; // зміна стовпців.
		a[i][j+1]=alpha;
		}	
		
		res*=(-1); //зміна знаку визначника з причини переставлення стовпців. 
		prapor =false;
		break;
		}
	}
	}
	
	
	if(prapor)
	{
	temp=NULL;
	delete temp; // нульовий рядок  - означає нульовий визначник,отже, змінна результату =0.
	res=0;
	return res; 
	}	
	
	
}


for(int i=k+1;i<n;i++){
	alpha=a[i][k]/a[k][k];
	for(int j=k;j<n;j++)
	{
	a[i][j]-=alpha*a[k][j];	 //віднімаємо від кожного коеф. з одного рядка  - коеф. з іншого.
	}
}	

}

for(int k=0;k<n;k++)
res*=a[k][k]; //добуток елементів на діагоналі.


temp=NULL;	
delete temp;
return res;
}                        






