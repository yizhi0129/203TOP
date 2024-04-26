#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void sum(double* x, double c, int n){
	for (int i=0; i < n; i++){
		x[i] += c;
	}
}

int main(int argc, char** argv){

	if (argc < 3){
		printf("Usage: %s [vector size] [repetitions]\n", argv[0]);
		return 1;
	}

    int n = atoi(argv[1]);
    int rep = atoi(argv[2]);

    double t0, t1;
	int rank, p;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

    double* x = (double*)calloc(n/p, sizeof(double));
	double* y = (double*)calloc(n, sizeof(double));

	for (int t=0; t < rep; t++){

		if (rank == 0){

			t0 = MPI_Wtime();
			sum(x, 1, n/p);
			t1 = MPI_Wtime();
			printf("%d %g\n", p, t1 - t0);

		} else {

			sum(x, 1, n/p);
			
		}
	}

	MPI_Gather(x, n/p, MPI_DOUBLE, &(y[rank*n/p]), n/p, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// if(rank==0){
	// 	for(int i=0; i < n; i++){
	// 		printf("%f\n", y[i]);
	// 	}
	// }

	MPI_Finalize();

	return 0;
}
