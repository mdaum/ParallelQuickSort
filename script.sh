
n=50000000
echo "problem size,num_proc,runtime\n"
runs=0
until [$runs -eq 10]
do
	echo $n
	echo ",1,"
	./qsort_seq $n
	echo "\n"
	n=`expr $runs + 1`
done


