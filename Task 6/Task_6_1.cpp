#include <mpi.h>
#include <stdio.h>
#include <math.h>

double Function(double x);
double Trapezoidal(double local_a, double local_b, int local_n, double h);

int main(int argc, char** argv)
{
    int rank, size;
    double a = 0.0, b = 1.0;
    double local_a, local_b;
    int local_n;
    double local_integral, total_integral;
    double start_time, end_time;
    int n_values[] = { 100, 1000, 10000, 100000 };

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < 4; i++) {
        int n = n_values[i];
        double h = (b - a) / n;

        start_time = MPI_Wtime();

        local_n = n / size;
        local_a = a + rank * local_n * h;
        local_b = local_a + local_n * h;
        local_integral = Trapezoidal(local_a, local_b, local_n, h);


        MPI_Reduce(&local_integral, &total_integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        end_time = MPI_Wtime();

        if (rank == 0)
            printf("N = %d trapezoids | Processes = %d , Integral is: %.15f | Execution time: %f seconds\n", n, size, total_integral, end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}


double Function(double x)
{
    return (2 * pow(x, 2) - 15) * cos(3 * x);
}

double Trapezoidal(double local_a, double local_b, int local_n, double h)
{
    double integral;
    double x;
    int i;

    integral = (Function(local_a) + Function(local_b)) / 2.0;
    for (i = 1; i <= local_n - 1; i++) {
        x = local_a + i * h;
        integral += Function(x);
    }
    integral = integral * h;
    return integral;
}