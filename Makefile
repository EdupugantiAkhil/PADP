1a:
	g++ 1a.cpp -o pi_montecarlo -fopenmp
	./pi_montecarlo 

1b:
	mpic++ 1b.cpp -o pi_montecarlo_mpi
	mpirun -np 4 pi_montecarlo_mpi
2:
	g++ 2.cpp -o pi_montecarlo -fopenmp
	./pi_montecarlo
3:
	g++ 3.cpp -o sieve -fopenmp 
	./sieve
4:
	g++ 4.cpp -o grayImage -fopenmp -lgd 
	./grayImage
5:
	mpicc 5.cpp -o mpi_hello -lstdc++
	mpirun -np 4 mpi_hello
6:
	g++ 6.cpp -o wordSearch -fopenmp
	./wordSearch
7:
	g++ 7.cpp -o saxpy -lOpenCL
	./saxpy

clean:
	rm -f pi_montecarlo pi_montecarlo_mpi sieve grayImage mpi_hello wordSearch saxpy