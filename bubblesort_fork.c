// Jiahao Luo jxl1305
// Jeremy Chan jsc126

// bubble sort fork
// http://www.geeksforgeeks.org/bubble-sort/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#define TEST 0 

void merge(int* a, int* b, int left, int mid, int right);
void swap(int *xp, int *yp);
void bubbleSort(int* a, int left, int right);
int* setup_memory(char *name, int size);
 
int main(int argc, char *argv[]) {
    
    int N = atoi(argv[1]); // Array size
    int P = atoi(argv[2]); // Number of threads
    char *nameA = "ArrayA";
    char *nameB = "ArrayB";

    const int SIZE = N * sizeof(int); // size for the array
    int *a = setup_memory(nameA, SIZE);
    int *b = setup_memory(nameB, SIZE);
    
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
 
    pid_t pid = 0;
    int iProc = 0;
    int nextProc;

    int subarrayLength = N / P;

	struct timeval start_time, stop_time, elapsed_time;  // timers
	gettimeofday(&start_time,NULL); // Unix timer

    for (nextProc = 1; nextProc < P & !pid; nextProc++) {
        pid = fork();
        if (!pid)
            iProc = nextProc;
    }

    int l;
    int r;
    l = subarrayLength * iProc;
    r = l + subarrayLength - 1;

        bubbleSort(a, l, r);

    for(i = (P-1); i > 0; i--){
        if(iProc == i){
            return 0;
        } else {
            wait(NULL);
        }
    }

    for (i = 1; i <= P - 2; i++) { // All but the last subarray
        int middle = i * subarrayLength;
        merge(a, b, 0, middle, middle + subarrayLength - 1);
    }

    merge(a, b, 0, (P - 1) * subarrayLength, N-1); // Last subarray

	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
	
    printf("%f\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
 
    if(TEST){
        printf("Sorted array: \n");
        for(i=0; i<N ; i++){
            printf("%d ", a[i]);
        }
        printf("\n");
    }

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
            tmp_pos = tmp_pos + 1;
            left++;
        } else {
            b[tmp_pos] = a[mid];
            tmp_pos = tmp_pos + 1;
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
    for (i = 0; i <= count; i++) {
        a[right] = b[right];
        right--;
    }
}

// Helper function to setup memory
int* setup_memory(char *name, int size) {
  int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, size);
  int *m = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (m == MAP_FAILED) {
    printf("Map failed\n");
    exit(-1);
  }
  return m;
}

