#include "mpi.h"
#include <stdio.h>
#include <malloc.h>

int main(int argc, char** argv) {
	int* buffer;
	int myrank, buf;
	MPI_Status status;
	int buffsize = 1, TAG = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank == 0) {
		int buffer_attached_size = buffsize + MPI_BSEND_OVERHEAD;
		buffer = (int*)malloc(buffsize + MPI_BSEND_OVERHEAD);
		MPI_Buffer_attach(buffer, buffer_attached_size);
		buffer = (int*)10;
		MPI_Bsend(&buffer, buffsize, MPI_INT, 1, TAG, MPI_COMM_WORLD);
		MPI_Buffer_detach(&buffer, &buffer_attached_size);
		free(buffer);
	}
	else if (myrank == 1) {
		MPI_Recv(&buffer, buffsize, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status);
		printf("received: %i\n", buffer);
	}

	MPI_Finalize();
	return 0;
}
