#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#define N 100000

int main()
{
	int n, i,k;
	double cm=0,cp=0;
	int arr1[N], arr2[N];
	int *a = arr1, *b = arr2, *t;
	printf("Enter size:\n");
	do{
	scanf("%d", &n);
} while(n<1 || n>N);

	printf("1.Best case\n2.Random case\n3.Worst case\n ");
	do{
	scanf("%d", &k);
	
		switch (k)
		{
		case 1:
			for (i = 0; i < n; i++) {
				arr1[i] = i + 1;
				printf("%d ", arr1[i]);
			}
			break;
		case 2:
			srand(time(NULL));
			for (i = 0; i < n; i++) {
				arr1[i] = rand() % 100;
				printf("%d ", arr1[i]);
			}
			break;
		case 3:
			for (i = 0; i < n; i++) {
				arr1[i] = n - i;
				printf("%d ", arr1[i]);
			}
			break;
		}
	} while(k!=1 && k!=2 && k!=3);


		int size1 = 1, size2 = 1, l, r, j, m;
		while (size1 < n) {
			l = 0;
			r = l + size1;
			k = 0;
			while (l < n && r < n && k < n) {
				i = l;
				j = r;
				while ((i < l + size1) && (j < r + size2)) {
					if (a[i] < a[j])
						b[k++] = a[i++];
					else b[k++] = a[j++];
					
					cm++;
					cp++;
				}

				while (i < l + size1)
				{
					b[k++] = a[i++];
					cm++;
				}
				while (j < r + size2)
				{
				
					b[k++] = a[j++];
					cm++;
				}

				l += size1 + size2;
				if (l + size1 < n) {
					r += size1 + size2; 
					if (r + size1 < n) size2 = size1;
					else size2 = n - r;
				}
				else
					for (m = l; m < n; m++)
					{
						b[k++] = a[m];
						cm++;
					}
			}

			size1 = 2 * size1;
			size2 = size1;
			if (size1 < n && size1 + size2 > n)
				size2 = n - size1;

			t = a;
			a = b;
			b = t;
		}

		printf("\nSorted array:\n");
		for (i = 0; i < n; i++)
			printf("%d ", a[i]);
			
		printf("\nactions_on_elements= %.0lf, copies=%.0lf",cm,cp);
		getch();
		
		
		return 0;
}

