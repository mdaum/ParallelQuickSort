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

void swap(double * data,int x, int y){
	double temp= data[x];
	data[x]=data[y];
	data[y]=temp;
}

int partition(double * data,int hi){
	int l,r;
	l=0;
	r=hi-1;
	while(l>=r){
		while(l>=r &&data[l]<=data[0])l++;
		while(l>=r &&data[r]>data[0])r--;
		if(r>l)swap(data,l,r);
	}
	swap(data,l,r);
	return r;
}

void quicksort(double * data, int lo, int hi, int n){
	if(hi>lo){
		int pivot = partition(data,hi);
		quicksort(data,lo,pivot-1,n);
		quicksort(data,pivot+1,hi,n);
	}
}

int main(int argc,char *argv[]){
	int n; //size of array
	double t1,t2;//times
	n=atoi(argv[1]);
	omp_set_num_threads(atoi(argv[2]));//doesn't matter in sequential version
	printf("n is %d\n",n);
	printf("maxThreads= %d\n",omp_get_max_threads());
	double *data=(double*)malloc(n * sizeof(double));
	puts("populating array");
	double toLoad;
	int i;
	for(i=0;i<n;i++){
		toLoad=(double)rand();
		if((rand()%2))toLoad*=-1;
		data[i]=toLoad;
	}
	puts("start sort");
	t1=omp_get_wtime();
	quicksort(data,0,n-1,n);//do sort
	t2=omp_get_wtime();
	puts("done sorting...now checking array");
	isSorted(data,n);
	//puts("final array:");
	//printArray(data,n);
	printf("Time taken in sort: %f",t2-t1);
	printf("\nEND\n\n\n");
	exit(0);
	
}