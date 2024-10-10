#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    int ranks, size, message;
    int TAG = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ranks);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    message = ranks;

    if ((ranks % 2) == 0) {
        if ((ranks + 1) != size) {
            MPI_Send(&message, 1, MPI_INT, ranks + 1, TAG, MPI_COMM_WORLD);
        }
    }
    else {
        if (ranks != 0) {
            MPI_Recv(&message, 1, MPI_INT, ranks - 1, TAG, MPI_COMM_WORLD, &status);
            printf("received : %i\n", message);
        }
    }

    MPI_Finalize();
    return 0;
}
