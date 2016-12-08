all: qsort_seq qsort_par_v1

CFLAGS = -o3 -fopenmp
qsort_seq: qsort_seq.c
	gcc $(CFLAGS) -o qsort_seq qsort_seq.c

qsort_par_v1: qsort_par_v1.c
	gcc $(CFLAGS) -o qsort_par_v1 qsort_par_v1.c

clean:
	rm -f core.* qsort_seq qsort_par_v1
