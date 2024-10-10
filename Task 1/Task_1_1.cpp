#include <cstdio>
#include "mpi.h">

int main(int argc, char *argv[])
{
	int numtasks, ranks;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &ranks);

	fprintf(stdout, "Process %d of %d \n", ranks, numtasks);

	MPI_Finalize();
	return 0;
}
