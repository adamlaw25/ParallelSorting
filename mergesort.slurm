#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=16
#SBATCH --output=mergesort_sorted.txt 

cp mergesort_fork $PFSDIR/.
cp mergesort_pthread $PFSDIR/.
cp mergesort_omp $PFSDIR/.
cd $PFSDIR
echo fork
echo fork 50000
for N in 1 2 4 
do
	echo $N
	./mergesort_fork 50000 $N
done
echo fork 100000
for N in 1 2 4 
do
	echo $N
	./mergesort_fork 100000 $N
done
echo fork 150000
for N in 1 2 4 
do
	echo $N
	./mergesort_fork 150000 $N
done
echo fork 200000
for N in 1 2 4 
do
	echo $N
	./mergesort_fork 200000 $N
done
echo pthread
echo pthread 50000
for N in 1 2 4
do
	echo $N
	./mergesort_pthread 50000 $N
done
echo pthread 100000
for N in 1 2 4
do
	echo $N
	./mergesort_pthread 100000 $N
done
echo pthread 150000
for N in 1 2 4
do
	echo $N
	./mergesort_pthread 150000 $N
done
echo pthread 200000
for N in 1 2 4
do
	echo $N
	./mergesort_pthread 200000 $N
done
echo omp
echo omp 50000
for N in 1 2 4
do
	echo $N
	./mergesort_omp 50000 $N
done
echo omp 100000
for N in 1 2 4
do
	echo $N
	./mergesort_omp 100000 $N
done
echo omp 150000
for N in 1 2 4
do
	echo $N
	./mergesort_omp 150000 $N
done
echo omp 200000
for N in 1 2 4
do
	echo $N
	./mergesort_omp 200000 $N
done
