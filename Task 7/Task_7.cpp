#include <mpi.h>
#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
    int myid, np, n, i;
    double w, gsum, sum, v, time, time1, time2, mflops;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); 
    MPI_Comm_size(MPI_COMM_WORLD, &np);  

    if (myid == 0) {
        std::cout << "Enter the number of intervals: ";
        std::cin >> n;
        time1 = MPI_Wtime();  
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    w = 1.0 / static_cast<double>(n);
    sum = 0.0;

    for (i = myid + 1; i <= n; i += np) {
        v = (i - 0.5) * w;
        v = 4.0 / (1.0 + v * v);
        sum += v;
    }

    MPI_Reduce(&sum, &gsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myid == 0) {
        time2 = MPI_Wtime();
        time = time2 - time1; 
        mflops = 9.0 * n / (1000000.0 * time); 

        std::cout << "Approximated value of pi: " << gsum * w << std::endl;
        std::cout << "Execution time: " << time << " seconds" << std::endl;
        std::cout << "MFLOPS: " << mflops << " on " << np << " processors" << std::endl;
        std::cout << "MFLOPS per processor: " << mflops / np << std::endl;
    }

    MPI_Finalize();
    return 0;
}
