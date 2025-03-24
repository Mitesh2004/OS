#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000
//#define M_C N  // Adjust if needed

int main(int argc, char *argv[]) {
    int rank, size, data[N], part[N], lmin, lmax, gmin, gmax;
   // static int data[N], part[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk = N / size;
  //  int part[chunk];
    if (rank == 0) for (int i = 0; i < N; i++) data[i] = rand() % 1000;

    MPI_Scatter(data, chunk, MPI_INT, part, chunk, MPI_INT, 0, MPI_COMM_WORLD);

    lmin = lmax = part[0];
    for (int i = 1; i < chunk; i++) {
        if (part[i] < lmin) lmin = part[i];
        if (part[i] > lmax) lmax = part[i];
    }

    MPI_Reduce(&lmin, &gmin, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&lmax, &gmax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) printf("Min: %d\nMax: %d\n", gmin, gmax);

    MPI_Finalize();
    return 0;
}

