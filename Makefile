all: qsort_seq partition_seq qsort_par_v1 qsort_par_v2

CFLAGS = -o3 -fopenmp
qsort_seq: qsort_seq.c
	gcc $(CFLAGS) -o qsort_seq qsort_seq.c

partition_seq: partition_seq.c
	gcc $(CFLAGS) -o partition_seq partition_seq.c

qsort_par_v1: qsort_par_v1.c
	gcc $(CFLAGS) -o qsort_par_v1 qsort_par_v1.c

qsort_par_v2: qsort_par_v2.c
	gcc $(CFLAGS) -o qsort_par_v2 qsort_par_v2.c

clean:
	rm -f core.* qsort_seq partition_seq qsort_par_v1 qsort_par_v2
