#include <cstdio>  
#include "mpi.h"  
#include <iostream>  

int main(int argc, char** argv) {
    int myid, numprocs, * buf, source, i;
    int message[3] = { 0, 1, 2 };
    int myrank, data = 2002, count, TAG = 0;
    MPI_Status status;
    int k = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank == 0) {
        MPI_Send(&data, 1, MPI_INT, 2, TAG, MPI_COMM_WORLD);
        k++;
    }
    else if (myrank == 1) {
        MPI_Send(&message, 3, MPI_INT, 2, TAG, MPI_COMM_WORLD);
        k++;
    }
    else if (myrank == 2)
    {
        for (int i = 0; i < 2; i++) {

            MPI_Probe(i, TAG, MPI_COMM_WORLD, &status);
            source = status.MPI_SOURCE;
            MPI_Get_count(&status, MPI_INT, &count);

            buf = (int*)malloc(count * sizeof(int));
            MPI_Recv(buf, count, MPI_INT, source, TAG, MPI_COMM_WORLD,
                &status);

            printf("R_eceived from proccess %d, message: ", source);

            for (int i = 0; i < count; i++) {
                printf(" %d", buf[i]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
