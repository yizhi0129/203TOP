#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void fem_iter(int n, double *x_1, double *x_2)
{
    x_2[0] = (x_1[0] + x_1[1]) / 2;
    for (int i = 1; i < n - 1; i++)
    {
        x_2[i] = (x_1[i - 1] + 2 * x_1[i] + x_1[i + 1]) / 4;
    }
    x_2[n - 1] = (x_1[n - 2] + x_1[n - 1]) / 2;
}

int main(int argc, char **argv)
{
    int rank, p;
    int n = atoi(argv[1]); // Size of the array
    double *x_1, *x_2;
    double *local_x_1, *local_x_2;
    MPI_Status status;
    double start_fem, end_fem, start_total, end_total;
    double avg_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    int local_n = n / p; // Number of elements per process

    // Allocate memory for local arrays
    local_x_1 = (double *)malloc(local_n * sizeof(double));
    local_x_2 = (double *)malloc(local_n * sizeof(double));

    // Allocate memory for global arrays on root process
    if (rank == 0)
    {
        x_1 = (double *)malloc(n * sizeof(double));
        x_2 = (double *)malloc(n * sizeof(double));
        // Initialize x_1 array
        for (int i = 0; i < n; i++)
        {
            x_1[i] = i;
        }
    }

    // Distribute x_1 array among processes
    MPI_Scatter(x_1, local_n, MPI_DOUBLE, local_x_1, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Start total timer
    start_total = MPI_Wtime();

    for(int i = 0; i < 5; i++)
    {
        fem_iter(local_n, local_x_1, local_x_2);
    }

    // Perform FEM iteration and measure its execution time
    start_fem = MPI_Wtime();
    for (int i = 0; i < 20; i++)
    {
        fem_iter(local_n, local_x_1, local_x_2);
    }   
    end_fem = MPI_Wtime();

    avg_time = (end_fem - start_fem) / 20.0;

    // Exchange boundary values between neighboring processes
    if (rank != 0)
    {
        MPI_Send(&local_x_2[0], 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&local_x_2[-1], 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &status);
    }
    if (rank != p - 1)
    {
        MPI_Send(&local_x_2[local_n - 1], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&local_x_2[local_n], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &status);
    }

    // Gather results back to the root process
    MPI_Gather(local_x_2, local_n, MPI_DOUBLE, x_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // End total timer
    end_total = MPI_Wtime();

    // Output timing information on root process
    if (rank == 0)
    {
        printf("%d\t%g\n", p, avg_time);
        //printf("FEM Iteration Time: %lf seconds\n", end_fem - start_fem);
        //printf("Total Execution Time: %lf seconds\n", end_total - start_total);
    }

    // Clean up
    free(local_x_1);
    free(local_x_2);
    if (rank == 0)
    {
        free(x_1);
        free(x_2);
    }

    MPI_Finalize();

    return 0;
}
