#!/bin/bash
# Use 5 minutes
#SBATCH --time=00:05:00
# Name of the job and account
#SBATCH -A edu24.DD2356
# Number of nodes
#SBATCH -p shared
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8
#SBATCH -e error.txt
srun -n 8 -o ./output3.txt ./e3.out