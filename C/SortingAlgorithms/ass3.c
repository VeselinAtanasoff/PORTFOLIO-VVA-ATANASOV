#include <stdio.h>
#include <time.h>
#include <string.h>
/* 3rd part of Assignment 1 SD */
void heapify(int arr[], int n, int i) 
{ 
    int temp, maximum, left_index, right_index; 
  
    // currently assuming i postion to 
    // be holding the largest value 
    maximum = i; 
  
    // right child index 
    right_index = 2 * i + 2; 
  
    // left child index 
    left_index = 2 * i + 1; 
  
    // if left index value is grater than the current index 
    // value 
    if (left_index < n && arr[left_index] > arr[maximum]) 
        maximum = left_index; 
  
    // if right index value is grater than the current index 
    // value 
    if (right_index < n && arr[right_index] > arr[maximum]) 
        maximum = right_index; 
  
    // checking if we needed swaping the elements or not 
    if (maximum != i) { 
        temp = arr[i]; 
        arr[i] = arr[maximum]; 
        arr[maximum] = temp; 
        heapify(arr, n, maximum); 
    } 
}

static void alg1(int *arr, int n)
{
	//Heap sort
	int temp, i; 
  
	// building the heap 
	for (i = n / 2 - 1; i >= 0; i--) 
		heapify(arr, n, i); 
  
	// extracting elements from the heap 
	for (i = n - 1; i > 0; i--) { 
		temp = arr[0]; 
		arr[0] = arr[i]; 
		arr[i] = temp; 
		heapify(arr, i, 0); 
	}
}

static void alg2(int *arr, int n)
{
	//Bubble sort
	int temp, i, j;
	for (i = 0; i < n-1; i++)      
	{
		for (j = 0; j < n-i-1; j++) 
		{
			if (arr[j] > arr[j+1]) 
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int getMax(int arr[], int n) 
{ 
	int max = arr[0]; 
	for (int i = 1; i < n; i++) 
		if (arr[i] > max) 
			max = arr[i]; 
	return max; 
}

void countSort(int arr[], int n, int exp) 
{ 
	int output[n]; 
	int i, count[10] = {0}; 

	for (i = 0; i < n; i++) 
		count[ (arr[i]/exp)%10 ]++; 

	for (i = 1; i < 10; i++) 
		count[i] += count[i - 1]; 

	for (i = n - 1; i >= 0; i--) 
	{ 
		output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
		count[ (arr[i]/exp)%10 ]--; 
	} 

	for (i = 0; i < n; i++) 
		arr[i] = output[i]; 
}

static void alg3(int *arr, int n)
{
	//Radix sort
	int m = getMax(arr, n);
	for (int exp = 1; m/exp > 0; exp *= 10) 
		countSort(arr, n, exp);
	
}

static void read_in_arrays_to_sort(int *arr1, int *arr2, int *arr3, int n1, int n2, int n3)
{
	for(int i=0; i<n1; i++)
	{
		scanf("%d", &arr1[i]);
	}
	for(int i=0; i<n2; i++)
	{
		scanf("%d", &arr2[i]);
	}
	for(int i=0; i<n3; i++)
	{
		scanf("%d", &arr3[i]);
	}

}

static void write_to_file(int *arr1, int *arr2, int *arr3, int n1, int n2, int n3, char *filename)
{
	FILE *f= fopen(filename, "w");
	if(f==NULL)
	{
		printf("Error in creating output file %s", filename);
		return;
	}
	for(int i=0; i<n1; i++)
	{
		fprintf(f, "%d ", arr1[i]);
	};
	fprintf(f, "\n");
	for(int i=0; i<n2; i++)
	{
		fprintf(f, "%d ", arr2[i]);
	}
	fprintf(f, "\n");
	for(int i=0; i<n3; i++)
	{
		fprintf(f, "%d ", arr3[i]);
	}
	fclose(f);

}

static void execute_algorithm(int *arr, int n, void (*sort_alg)())
{
	clock_t t;
	double time_taken;
	t = clock();
	sort_alg(arr,n);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Time needed to sort %d elements was %f seconds\n", n, time_taken);
}

static void copy_input_arrays(int *arr1, int *arr2, int *arr3, int *sarr1, int *sarr2, int *sarr3, int n1, int n2, int n3)
{
	memcpy(arr1, sarr1, n1*sizeof(int));
	memcpy(arr2, sarr2, n2*sizeof(int));
	memcpy(arr3, sarr3, n3*sizeof(int));
}

int main() {
	/* Don't touch main */
  
	const int n1 = 10;
	const int n2 = 1000;
	const int n3 = 10000;
	int arr1[n1];
	int arr2[n2];
	int arr3[n3];
	int sarr1[n1];
	int sarr2[n2];
	int sarr3[n3];

	read_in_arrays_to_sort(sarr1, sarr2, sarr3, n1, n2, n3);
	copy_input_arrays(arr1, arr2, arr3, sarr1, sarr2, sarr3, n1, n2, n3);	

	printf("Execution of the first alg1 algorithm\n");

	execute_algorithm(arr1, n1, alg1);
	execute_algorithm(arr2, n2, alg1);
	execute_algorithm(arr3, n3, alg1);
	write_to_file(arr1, arr2, arr3, n1, n2, n3, "out_alg1");

	copy_input_arrays(arr1, arr2, arr3, sarr1, sarr2, sarr3, n1, n2, n3);	

	printf("Execution of the second alg2 algorithm\n");

	execute_algorithm(arr1, n1, alg2);
	execute_algorithm(arr2, n2, alg2);
	execute_algorithm(arr3, n3, alg2);
	write_to_file(arr1, arr2, arr3, n1, n2, n3, "out_alg2");

	copy_input_arrays(arr1, arr2, arr3, sarr1, sarr2, sarr3, n1, n2, n3);	

	printf("Execution of the third alg3 algorithm\n");

	execute_algorithm(arr1, n1, alg3);
	execute_algorithm(arr2, n2, alg3);
	execute_algorithm(arr3, n3, alg3);
	write_to_file(arr1, arr2, arr3, n1, n2, n3, "out_alg3");
	return 0;
}
