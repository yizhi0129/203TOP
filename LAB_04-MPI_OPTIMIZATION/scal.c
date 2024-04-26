#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

void sum_iter(int n, int k, int rank, double c, double *x_1, double *x_2)
{
    for (int i = rank; i < n; i += k)
    {
        x_1[i] = 1.0;
        x_2[i] = x_1[i] + c;
    }
}

int main(int argc, char **argv)
{
    int rank, size, p;
    double t0, t1, d;
    double c = 1.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (argc != 2)
    {
        if (rank == 0)
            printf("Usage: %s <message_size>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    size = atoi(argv[1]);
    double *x_1 = (double *)malloc(size * sizeof(double));
    double *x_2 = (double *)malloc(size * sizeof(double));

    for (int i = 0; i < 5; i++)
    {
        sum_iter(size, p, rank, c, x_1, x_2);
    }

    t0 = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD);
    for (int i = 0; i < 20; i++)
    {
        sum_iter(size, p, rank, c, x_1, x_2);
    }        
    t1 = MPI_Wtime();
    d = (t1 - t0) / 20.0;
    
    if (rank == 0)
    {
        printf("%d\t%g\n", p, d);
    }

    free(x_1);
    free(x_2);
    MPI_Finalize();
    
    return 0;
}


