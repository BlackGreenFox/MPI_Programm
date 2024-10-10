#define _CRT_SECURE_NO_WARNINGS
#include "mpi.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char** argv)
{
	int myrank, n;
	int root = 0;
	int count = 1;
	float a, b;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 0) {
		scanf("%f %f %i", &a, &b, &n);
		MPI_Bcast(&a, 1, MPI_FLOAT, myrank, MPI_COMM_WORLD);
		MPI_Bcast(&b, 1, MPI_FLOAT, myrank, MPI_COMM_WORLD);
		MPI_Bcast(&n, 1, MPI_INT, myrank, MPI_COMM_WORLD);
	}
	else {
		MPI_Bcast(&a, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&b, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		printf("%i Process got %f %f %i\n", myrank, a, b, n);
	}

	MPI_Finalize();
	return 0;
}
