// Jiahao Luo jxl1305
// Jeremy Chan jsc126

// merge sort pthread

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>
#define TEST 0

int* a;
int* b;
int subarrayLength ;

void merge(int* a, int* b, int left, int mid, int right);
void sort(int* a, int* b, int left, int right);
void *child(void *left); /* start child thread */

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]); // Array size
    int P = atoi(argv[2]); // Number of threads

    const int SIZE = N * sizeof(int); // size for the array
	a = malloc(SIZE);
	b = malloc(SIZE);

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

    subarrayLength =  N / P;

    pthread_t tid[P]; // thread IDs
    int l[P];
	printf("%d \n", P);

	struct timeval start_time, stop_time, elapsed_time;  // timers
	gettimeofday(&start_time,NULL); // Unix timer

	int j; // Loop iterator

    //create
    for (j = 0; j < P; j++) {
        l[j] = subarrayLength * j;
        pthread_create(&tid[j], NULL, child, &l[j]);
	}
    
    // Join
    for (j = 0; j < P; j++)
        pthread_join(tid[j], NULL);

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

void *child(void *left) {
    int *l = left;
    int r =  *l + subarrayLength - 1;
    sort(a, b, *l, r);
    pthread_exit(0);
}

// Recursive sort
void sort(int* a, int* b, int left, int right) {
    int mid;
    if (right > left) {
        mid = (right + left) / 2;
        sort(a, b, left, mid);
        sort(a, b, mid + 1, right);
        merge(a, b, left, mid + 1, right);
    }
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
