/bin/bash
#SBATCH --job-name=singularity-container-run
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=1
#SBATCH --time=00:15:00
#SBATCH --partition=g100_all_serial
#SBATCH --account=tra23_hpbioinf
#SBATCH -o output/%x-%j.out # File to which STDOUT will be written
#SBATCH -e output/%x-%j.err # File to which STDERR will be written

module load singularity

singularity run mm.sif
