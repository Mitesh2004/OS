#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000

int main(int argc, char *argv[]) {
    int rank, size, data[N], part[N], local_sum = 0, total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk = N / size;
    if (rank == 0) for (int i = 0; i < N; i++) data[i] = rand() % 100;

    MPI_Scatter(data, chunk, MPI_INT, part, chunk, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++)
        if (part[i] % 2 != 0) local_sum += part[i];

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) printf("Sum of all odd numbers = %d\n", total_sum);

    MPI_Finalize();
}

