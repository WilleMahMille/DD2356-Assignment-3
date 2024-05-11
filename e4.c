
#define SEED 921
// #define NUM_ITER 1000000000
#define NUM_ITER 1000000000
#define PARA 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#if PARA == 1
#include <mpi.h>
#endif

int calculate_hits(int max_iter, int rank)
{
    // Calculate PI following a Monte Carlo method

    int count = 0;
    double x, y, z, pi;
    for (int iter = 0; iter < max_iter; iter++)
    {
        // Generate random (X,Y) points
        x = (double)random() / (double)RAND_MAX;
        y = (double)random() / (double)RAND_MAX;
        z = (x * x) + (y * y);

        // Check if point is in unit circle
        if (z <= 1.0)
        {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    int count = 0;
    int tot_count = 0;
    double x, y, z, pi;
    int size = 1, rank = 0, provided;
    double start_time = 0.0, end_time = 0.0, elapsed = 0.0;

#if PARA == 1
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    start_time = MPI_Wtime();
#endif

    srand(SEED * rank); // Important: Multiply SEED by "rank" when you introduce MPI!

    int max_iter = NUM_ITER;
#if PARA == 1
    max_iter = (int)(NUM_ITER / size);
#endif
    count = calculate_hits(max_iter, rank);

#if PARA == 1
    MPI_Reduce(&count, &tot_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
#endif

    if (rank == 0)
    {
        // Estimate Pi and display the result
        pi = ((double)tot_count / (double)(max_iter * size)) * 4.0;
    }

#if PARA == 1
    end_time = MPI_Wtime();
    elapsed = end_time - start_time;
#endif

    if (rank == 0 || size == 1)
    {
        printf("The result is %f\n", pi);
        printf("Time: %f seconds\n", elapsed);
    }
#if PARA == 1
    MPI_Finalize();
#endif

    return 0;
}
