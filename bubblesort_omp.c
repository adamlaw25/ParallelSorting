// Jiahao Luo jxl1305
// Jeremy Chan jsc126

// bubble sort omp

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h> 
#define TEST 0

void merge(int* a, int* b, int left, int mid, int right);
void swap(int *xp, int *yp);
void bubbleSort(int* a, int left, int right);

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]); // Array size
    int P = atoi(argv[2]); // Number of threads

    const int SIZE = N * sizeof(int); // size for the array
	int* a = malloc(SIZE);
	int* b = malloc(SIZE);

	srand(time(NULL));
	int i;
	// Fill array 
    for (i = 0; i < N; i++){
	    a[i] = rand();
        //a[i] = i + 1;
        //a[i] = N - i;
    }

    if (TEST){
        for(i = 0; i < N; i++){
            printf("%d ",a[i]);
        }
        printf("\n");
    }

    int subarrayLength =  N / P;

    // set omp number of threads
	omp_set_num_threads(P);

	struct timeval start_time, stop_time, elapsed_time;  // timers
	gettimeofday(&start_time,NULL); // Unix timer

	#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		int l = tid * subarrayLength;
		int r = l + subarrayLength - 1;
		if (tid < P - 1) // All but the last thread
			bubbleSort(a, l, r);
		else // Last thread
			bubbleSort(a, l, N - 1);
	}

    for (i = 1; i <= P - 2; i++) { // All but the last subarray
		int middle = i * subarrayLength;
		merge(a, b, 0, middle, middle + subarrayLength - 1);
	}
	merge(a, b, 0, (P - 1) * subarrayLength, N - 1); // Last subarray

	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
	printf("%f\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
 
	if (TEST){
        for(i = 0; i < N; i++){
            printf("%d ",a[i]);
        }
        printf("\n");
    }

	free(a);
	free(b);
    return 0;
}


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void bubbleSort(int* a, int left, int right)
{
   int i, j;
   for (i = left; i < right; i++)      
  
       for (j = left; j < right - i ; j++) 
           if (a[j] > a[j+1])
              swap(&a[j], &a[j+1]);
}
 
// Merge two subarrays
void merge(int* a, int* b, int left, int mid, int right) {
    int i, left_end, count, tmp_pos;
    left_end = mid - 1;
    tmp_pos = left;
    count = right - left + 1;
 
	// Main merge
    while ((left <= left_end) && (mid <= right)) {
        if (a[left] <= a[mid]) {
            b[tmp_pos] = a[left];
			tmp_pos++;
            left++;
        } else {
            b[tmp_pos] = a[mid];
			tmp_pos++;
            mid++;
        }
    }
 
	// Copy remainder of left
    while (left <= left_end) {
        b[tmp_pos] = a[left];
        left++;
        tmp_pos++;
    }

	// Copy remainder of right
    while (mid <= right) {
        b[tmp_pos] = a[mid];
        mid++;
        tmp_pos++;
    }
 
	// Copy temp array back to original
    for (i = 0; i < count; i++) {
    // for (i = 0; i <= count; i++) {
        a[right] = b[right];
        right--;
    }
}
