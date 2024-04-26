#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char **argv) 
{
    int rank, size;
    char *buffer;
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
    buffer = (char *)malloc(size * sizeof(char));
    for (int i = 0; i < size; i ++)
    {
        buffer[i] = 'a' + (i % 26);
    }

    if (rank == 0) 
    {
        t0 = MPI_Wtime();
        MPI_Send(buffer, size, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        t1 = MPI_Wtime();
        printf("%d\t%g\n", size, t1 - t0);
    } 
    else if (rank == 1) 
    {
        //sleep(2);
        MPI_Recv(buffer, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
    }

    free(buffer);

    MPI_Finalize();

    return 0;
}
