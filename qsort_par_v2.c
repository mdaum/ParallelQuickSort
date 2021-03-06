#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

void printArray(double *d, int n){
	int i;
	printf("[");
	for(i=0;i<n;i++){
		printf(" %f ",d[i]);
	}
	printf("]\n");
}

void isSorted(double *d, int n){
	int i;
	for(i=0;i<n-1;i++){
		if(d[i]>d[i+1]){
			printf("Not sorted.\n");
			return;
		}
	}
	printf("Is sorted.\n");
}

int partition(double * data, int lo, int hi, int n){
	int l,r;
	double p_data;
	p_data=data[lo];
	l=lo;
	r=hi;
	while(l<r){
		while(l<n-1 && data[l]<=p_data)l++;
		while(r>0 && data[r]>p_data)r--;
		if(l<r){ //swap
			double temp;
			temp=data[l];
			data[l]=data[r];
			data[r]=temp;
		}
	}
	data[lo]=data[r];
	data[r]=p_data;
	return r;
}


void seq_qsort(double * data, int lo, int hi, int n){
	if(hi>lo){
		int pivot = partition(data,lo,hi,n);
		seq_qsort(data,lo,pivot-1,n);
		seq_qsort(data,pivot+1,hi,n);
	}
}

void quicksort(double * data, int lo, int hi, int n){
	if(hi>lo){
		if(hi-lo <n/omp_get_max_threads()){
			seq_qsort(data,lo,hi,n);
		}
		else{
			int pivot = partition(data,lo,hi,n);
			#pragma omp task firstprivate(data,lo,hi,pivot)
			quicksort(data,lo,pivot-1,n);
			#pragma omp task firstprivate(data,lo,hi,pivot)
			quicksort(data,pivot+1,hi,n);
		}
	}
}


int main(int argc,char *argv[]){
	int n; //size of array
	double t1,t2;//times
	n=atoi(argv[1]);
	omp_set_num_threads(atoi(argv[2]));//doesn't matter in sequential version
	//printf("n is %d\n",n);
	//printf("maxThreads= %d\n",omp_get_max_threads());
	double *data=(double*)malloc(n * sizeof(double));
	//puts("populating array");
	double toLoad;
	int i;
	#pragma omp parallel for shared(data) private (i)
	for(i=0;i<n;i++){
		double toLoad=(double)rand();
		if((rand()%2))toLoad*=-1;
		data[i]=toLoad;
	}
	//puts("start sort");
	t1=omp_get_wtime();
	#pragma omp parallel
	{
	#pragma omp single nowait
	quicksort(data,0,n-1,n);//do sort
	}
	t2=omp_get_wtime();
	//puts("done sorting...now checking array");
	//isSorted(data,n);
	//puts("final array:");
	//printArray(data,n);
	printf("%d,%d,%f\n",n,omp_get_max_threads(),t2-t1);
	//printf("\nEND\n\n\n");
	exit(0);
	
}