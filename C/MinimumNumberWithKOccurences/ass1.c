#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
/* 1st part of Assignment 1 SD */

int compare(const void *a, const void *b);
int get_minimum_number_with_k_occurences(int array[], int n, int k);

int main()
{
	/* this is code to measure the time of your algorithm, please don't touch it */

	clock_t t;
	double time_taken;

	t = clock();

	/* read here the stdin to get the values of N, a1...an and K
	 * and store them
	 *
	 * for this you can use scanf e.g. like this:
	 *
	 * int n;
	 * scanf("%d", &n);
	 */
	int n;
	scanf("%d", &n);

	int array[n];

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &array[i]);
	}

	int k;
	scanf("%d", &k);

	int outcome = 0;
	outcome = get_minimum_number_with_k_occurences(array, n, k);

	/* implement her your code e.g. like this
	 * outcome = get_minimum_number_with_k_occurences( choose your own arguments );
	 */

	/* this is the (performance) test code, please don't touch it */

	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("minimum number of K occurences is %d\n", outcome);
#ifdef TEST_TIME
	printf("time needed was %f seconds\n", time_taken);
#endif
	return 0;
}

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int get_minimum_number_with_k_occurences(int array[], int n, int k)
{
	qsort(array, n, sizeof(int), compare);
	int min = 0;
	int lastNumber = array[0];
	int count = 1;
	int i = 0;
	int j = 1;
	if (k == 1)
	{
		min = array[0];
	}
	else
	{
		while (count != k)
		{
			if (array[i] == array[j])
			{
				count++;
				if (count == k)
				{
					if (array[j + 1] == array[i])
					{
						count = 1;
						lastNumber = array[j];
						i = j;
						j++;
					}
				}
			}
			else
			{
				lastNumber = array[j];
				count = 1;
			}
			i++;
			j++;
			min = lastNumber;
		}
	}

	return min;
}