# SE4HPCproject
The second section of the Software Engineering for HPC hands-on projects consists in the definition of a
continuous integration/deployment workflow to automate the build, test, and containerization steps.
Additionally, the introduction of the MPI-based matrix multiplication algoritthm equired the definition of a job script
to be run on the GALILEO Supercomputer as well as an extension of the previously defined action to target automatic 
execution on the cluster in the case of push to the repository.

## Results
In the root directory of the repository you will be able to find the [shell script](/job.sh) that was run on GALILEO. Workflows are defined 
in the usual directory [/.github/workflows](/.github/workflows), while the log files of the slurm job are present in the [/galileo](/galileo) directory, present
in the root.

## Two branches for two workflows
### The first workflow

### The refactored workflow

## Acknowledge
Project work carried out by 
- Edoardo Carrà 11015152
- Lorenzo Gentile 11001962
- Luca Guffanti 10720858
