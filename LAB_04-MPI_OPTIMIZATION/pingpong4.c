#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define LOOP_COUNT 20
#define WARM_COUNT 5
#define BYTE_NUMBER 32
#define BYTE_MAX_VALUE 3200

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);

  int size_world;
  MPI_Comm_size(MPI_COMM_WORLD, &size_world);
  if (size_world != 2)
  {
    fprintf(stderr, "Code should be used with 2 process exactly!\n");
    MPI_Finalize();
    return 1;
  }

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int tag1 = 0;
  int tag2 = 42;

  for (size_t size = BYTE_NUMBER; size <= BYTE_MAX_VALUE; size += BYTE_NUMBER)
  {
    char* buffer = malloc(size * sizeof(char));

    // Warm-up
    for (size_t i = 0; i < WARM_COUNT; ++i)
    {
      if (rank == 0)
      {
        MPI_Send(buffer, size, MPI_CHAR, 1, tag1, MPI_COMM_WORLD);
        MPI_Recv(buffer, size, MPI_CHAR, 1, tag2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
      else if (rank == 1)
      {
        MPI_Recv(buffer, size, MPI_CHAR, 0, tag1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(buffer, size, MPI_CHAR, 0, tag2, MPI_COMM_WORLD);
      }
    }

    
    
    double t0 = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD);
    for (size_t i = 0; i < LOOP_COUNT; ++i)
    {
      if (rank == 0)
      {       
        MPI_Send(buffer, size, MPI_CHAR, 1, tag1, MPI_COMM_WORLD);
        MPI_Recv(buffer, size, MPI_CHAR, 1, tag2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);    
      }
      else if (rank == 1)
      {
        MPI_Recv(buffer, size, MPI_CHAR, 0, tag1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(buffer, size, MPI_CHAR, 0, tag2, MPI_COMM_WORLD);
      }
    }
    free(buffer);
    double t1 = MPI_Wtime();
    
    if (rank == 0)
    {
      double tel = t1 - t0;
      double avg = tel / LOOP_COUNT;
      printf("%ld\t%g\n", size, avg);
    }
  }

  MPI_Finalize();
  return 0;
}
