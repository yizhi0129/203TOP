#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char **argv) 
{
    int rank, size;
    char *buffer1, *buffer2;
    MPI_Status status;

    double t0, t1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc != 2) 
    {
        if (rank == 0)
            printf("Usage: %s <message_size>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    size = atoi(argv[1]);
    buffer1 = (char *)malloc(size * sizeof(char));
    buffer2 = (char *)malloc(size * sizeof(char));

    if (rank == 0) 
    {
        t0 = MPI_Wtime();
        MPI_Send(buffer1, size, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(buffer2, size, MPI_CHAR, 1, 10, MPI_COMM_WORLD, &status);
        t1 = MPI_Wtime();
        printf("%d\t%g\n", size, t1 - t0);
    } 
    else if (rank == 1) 
    {
        MPI_Recv(buffer1, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Send(buffer2, size, MPI_CHAR, 0, 10, MPI_COMM_WORLD);
    }

    free(buffer1);
    free(buffer2);

    MPI_Finalize();

    return 0;
}
