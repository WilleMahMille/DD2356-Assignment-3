
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    printf("Started calculating\n");
    int rank, size, i, provided;

    // number of cells (global)
    int nxc = 128;         // make sure nxc is divisible by size
    double L = 2 * 3.1415; // Length of the domain

    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // number of nodes (local to the process): 0 and nxn_loc-1 are ghost cells
    int nxn_loc = nxc / size + 3; // number of nodes is number cells + 1; we add also 2 ghost cells
    double L_loc = L / ((double)size);
    double dx = L / ((double)nxc);

    // define out function
    double *f = calloc(nxn_loc, sizeof(double));    // allocate and fill with z
    double *dfdx = calloc(nxn_loc, sizeof(double)); // allocate and fill with z

    for (i = 1; i < (nxn_loc - 1); i++)
        f[i] = sin(L_loc * rank + (i - 1) * dx);

    // need to communicate and fill ghost cells f[0] and f[nxn_loc-1]
    // communicate ghost cells

    /**
        FIRST:  Send forwards
        SECOND:  Send backwards
    */
    if (rank % 2)
    {
        // odd numbered
        int left_node = rank - 1;
        int right_node = (rank + 1) % size;
        // int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
        // [1,2,3,4,5,6,8,8,9,10]
        MPI_Request reqs[4];
        MPI_Isend(&f[1], 1, MPI_DOUBLE, left_node, 0, MPI_COMM_WORLD, &reqs[0]);
        MPI_Irecv(&f[0], 1, MPI_DOUBLE, left_node, 0, MPI_COMM_WORLD, &reqs[1]);
        MPI_Isend(&f[nxn_loc - 2], 1, MPI_DOUBLE, right_node, 0, MPI_COMM_WORLD, &reqs[2]);
        MPI_Irecv(&f[nxn_loc - 1], 1, MPI_DOUBLE, right_node, 0, MPI_COMM_WORLD, &reqs[3]);
    }
    else
    {
        // even numbered
        int left_node = (rank - 1 + size) % size;
        int right_node = (rank + 1) % size;
        MPI_Request reqs[4];
        MPI_Irecv(&f[nxn_loc - 1], 1, MPI_DOUBLE, right_node, 0, MPI_COMM_WORLD, &reqs[0]);
        MPI_Isend(&f[nxn_loc - 2], 1, MPI_DOUBLE, right_node, 0, MPI_COMM_WORLD, &reqs[1]);
        MPI_Irecv(&f[0], 1, MPI_DOUBLE, left_node, 0, MPI_COMM_WORLD, &reqs[2]);
        MPI_Isend(&f[1], 1, MPI_DOUBLE, left_node, 0, MPI_COMM_WORLD, &reqs[3]);
    }

    // here we finish the calculations

    // calculate first order derivative using central difference
    // here we need to correct value of the ghost cells!
    for (i = 1; i < (nxn_loc - 1); i++)
        dfdx[i] = (f[i + 1] - f[i - 1]) / (2 * dx);

    // Print f values
    if (rank == 0)
    { // print only rank 0 for convenience
        printf("My rank %d of %d\n", rank, size);
        printf("Here are my values for f including ghost cells and the corresponding errors (ignore first and last 2)\n");
        for (i = 0; i < nxn_loc; i++)
            printf("%f, err:%f\n", f[i], dfdx[i] - cos(L_loc * rank + (i - 1) * dx));
        printf("\n");
    }

    MPI_Finalize();
}
