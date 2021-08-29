#include<stdio.h>
#include<stdlib.h>
#include <conio.h>

int n,i,k,largest,right,left,cp,cm;
double a[100000],temp;


void f1(int i,int n)
{
left=2*(i+1)-1;
right= 2*(i+1);
cp+=2;
largest =i;
if(a[left]>a[i]&&left<n)largest =left;


if(right <n && a[right]>a[largest])largest = right;

if(largest!=i)
{
 temp=a[i];
 a[i]=a[largest];
 a[largest]=temp;
 cm+=3;
 f1(largest,n);
}
};



void b1(int n)
{
     i=n/2;
     while(i>=0)
     {
     f1(i,n);
     i--;
     }
};

void heapsort(int n)
{
b1(n);

for(i=n-1,k=n;i>0;i--)
{
          temp=a[0];
          a[0]=a[i];
          a[i]=temp;
          cm+=3;
          k--;
          f1(0,k);
}
}; 

int main()
{
printf("Enter n: \n");
do
{
  scanf("%i",&n);
} while ( n>100000);

printf("1.Best case\n2.Random\n3.Worst case\n");
printf("-------------------\n");
do{
       scanf("%i",&cp);         
switch (cp){
		case 1: for(i=0;i<n;i++)a[i]=i; break;
		case 2: for(i=0;i<n;i++)a[i]=rand(); break;
        case 3: for(i=0;i<n;i++)a[i]=n-i;break;		
	}
} while (cp!=1 && cp!=2 && cp!=3); 

cp=0;
cm=0;

heapsort(n);

for (i=0;i<n;i++)
printf(" a[%i] = %lf \n",i,a[i]);

printf("%i     %i",cm,cp);
getch();
return 0;
}
