#include "mpi.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char** argv)
{
	char data[25];
	int myrank, count = 25;
	MPI_Status status;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	if (myrank == 0) {
		strcpy_s(data, "Hi, Parallel Programmer!");
		MPI_Bcast(data, count, MPI_CHAR, myrank, MPI_COMM_WORLD);
		printf("[%d] process send: %s\n", myrank, data);
	}
	else {
		MPI_Bcast(data, count, MPI_CHAR, 0, MPI_COMM_WORLD);
		printf("[%d] process received: %s\n", myrank, data);
	}

	MPI_Finalize();
	return 0;
}
