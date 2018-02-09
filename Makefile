all:
	gcc mergesort_fork.c -lrt -o mergesort_fork
	gcc bubblesort_fork.c -lrt -o bubblesort_fork
	gcc mergesort_omp.c -o mergesort_omp -fopenmp
	gcc bubblesort_omp.c -o bubblesort_omp -fopenmp
	gcc mergesort_pthread.c -o mergesort_pthread -lpthread
	gcc bubblesort_pthread.c -o bubblesort_pthread -lpthread
