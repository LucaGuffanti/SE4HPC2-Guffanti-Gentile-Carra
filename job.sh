#!/bin/bash
#SBATCH --job-name=singularity-container-run
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=1
#SBATCH --time=00:15:00
#SBATCH --partition=g100_all_serial
#SBATCH --account=tra24_sepolimi
#SBATCH -o output/%x-%j.out.txt # File to which STDOUT will be written
#SBATCH -e output/%x-%j.err.txt # File to which STDERR will be written

# We employ the Hybrid Approach, where `mpirun` is invoked within the container
# launcher. This allows MPI processes outside the container to collaborate
# with MPI processes running within the container. When executed, the container
# runs an MPI application that performs matrix multiplications using two tasks.

# -C option contains not only file systems, but also PID, IPC, and environment
# doing so allows to execute the container without super user permissions
singularity run -C matrix.sif
