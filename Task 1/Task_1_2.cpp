#include <cstdio>
#include "mpi.h">
#include <string.h>

int main(int argc, char* argv[])
{
    int numtasks, ranks;
    char message[25];
    int myrank;
    MPI_Status status;
    int TAG = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ranks);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (ranks == 0)
    {
        strcpy_s(message, sizeof(message), "Hi, Second Processor!");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 1, TAG, MPI_COMM_WORLD);
    }
    else if (ranks == 1)
    {
        MPI_Recv(message, 25, MPI_CHAR, 0, TAG, MPI_COMM_WORLD, &status);
        printf("received: %s\n", message);
    }

    MPI_Finalize();
    return 0;
}
