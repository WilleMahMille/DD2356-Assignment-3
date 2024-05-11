#!/bin/bash
# Use 5 minutes
#SBATCH --time=00:00:30
# Name of the job and account
#SBATCH -A edu24.DD2356
# Number of nodes
#SBATCH -p shared
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=128
#SBATCH -e error.txt
srun -n 256 -o ./output4.txt ./e4.out