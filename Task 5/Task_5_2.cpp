#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv)
{

	MPI_Init(&argc, &argv);
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (size != 4)
		printf("This application is meant to be run with 4 processes, not %d.\n", size);

	int dims[2] = { 0, 0 };
	MPI_Dims_create(size, 2, dims);
	int periods[2] = { false, false };
	int reorder = true;

	MPI_Comm new_communicator;
	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &new_communicator);

	enum DIRECTIONS { DOWN, UP, LEFT, RIGHT };
	const  char* neighbours_names[4] = { "down", "up", "left", "right" };
	int neighbours_ranks[4];

	MPI_Cart_shift(new_communicator, 0, 1, &neighbours_ranks[LEFT], &neighbours_ranks[RIGHT]);
	MPI_Cart_shift(new_communicator, 1, 1, &neighbours_ranks[DOWN], &neighbours_ranks[UP]);

	int my_rank;
	MPI_Comm_rank(new_communicator, &my_rank);
	int coordinates[2];
	int maxdims = 2;
	MPI_Cart_coords(new_communicator, my_rank, maxdims, coordinates);

	printf("Process %d has coordinates %d,%d\n",
		my_rank, coordinates[0], coordinates[1]);

	for (int i = 0; i < 4; i++) {
		if (neighbours_ranks[i] == MPI_PROC_NULL)
			printf("Process %d don't have a %s neighbour.\n",
				my_rank, neighbours_names[i]);
		else
			printf("Process %d have a %s neighbour: process %d.\n",
				my_rank, neighbours_names[i], neighbours_ranks[i]);
	}

	MPI_Finalize();
	return 1;
}
