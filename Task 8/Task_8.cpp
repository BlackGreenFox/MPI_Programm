#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <windows.h>

void fillMatrix(int** matrix, int m, int n) {
    srand((unsigned int)time(0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (rand() % 201) - 100; 
        }
    }
}

void printMatrix(int** matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int findMaxInRow(int* row, int n) {
    int max = row[0];
    for (int i = 1; i < n; i++) {
        if (row[i] > max) {
            max = row[i];
        }
    }
    return max;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int m = 4; 
    int n = 6; 

    int** A = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        A[i] = (int*)malloc(n * sizeof(int));
    }

    int* B = (int*)malloc(m * sizeof(int));
    int* C = (int*)malloc(m * sizeof(int));

    fillMatrix(A, m, n);

#pragma omp parallel
    {
#pragma omp single
        {
            printf("Lab work No. 8\n");
            printf("Title: Introduction to technology Parallel Programming OpenMP\n");
            printf("Group: CP-437\n");
            printf("Full name: Kostiuchenko Anton \n");
            printf("Variant: 2\n");
            printf("Task: Find the maximum value in each row of the matrix\n");
        }
    }

    printf("\nMatrix A:\n");
    printMatrix(A, m, n);

    double startParallel = omp_get_wtime(); 
#pragma omp parallel for num_threads(m)
    for (int i = 0; i < m; i++) {
        B[i] = findMaxInRow(A[i], n);
        printf("Thread %d is processing row %d, max value: %d\n",
            omp_get_thread_num(), i, B[i]);
    }
    double endParallel = omp_get_wtime(); 
    double timeParallel = endParallel - startParallel;

    printf("\nResult of parallel processing (array B):\n");
    for (int i = 0; i < m; i++) {
        printf("B[%d] = %d\n", i, B[i]);
    }


    double startSequential = omp_get_wtime(); 
    for (int i = 0; i < m; i++) {
        C[i] = findMaxInRow(A[i], n);
    }
    double endSequential = omp_get_wtime(); 
    double timeSequential = endSequential - startSequential;


    printf("\nResult of sequential processing (array C):\n");
    for (int i = 0; i < m; i++) {
        printf("C[%d] = %d\n", i, C[i]);
    }

    int identical = 1;
    for (int i = 0; i < m; i++) {
        if (B[i] != C[i]) {
            identical = 0;
            break;
        }
    }

    printf("\nParallel processing time: %.8f seconds\n", timeParallel);
    printf("Sequential processing time: %.8f seconds\n", timeSequential);
    if (identical) {
        printf("The results of parallel and sequential processing are identical.\n");
    }
    else {
        printf("The results of parallel and sequential processing do not match.\n");
    }

    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
