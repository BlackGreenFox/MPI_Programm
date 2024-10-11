#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    MPI_Comm grid_comm;
    int ndims = 2, maxdims = 2;
    int coordinates[2];
    int my_grid_rank;
    int coords[2];

    coords[0] = 0;
    coords[1] = 1;

    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int dims[2] = { 0, 0 };
    MPI_Dims_create(size, 2, dims);
    int periods[2] = { true, true };
    int reorder = true;
    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &grid_comm);

    MPI_Comm_rank(grid_comm, &my_grid_rank);

    MPI_Cart_coords(grid_comm, my_grid_rank, maxdims, coordinates);
    printf("Process rank %d has coordinates %d %d\n", my_grid_rank, coordinates[0], coordinates[1]);

    MPI_Finalize();
    return 0;
}
