# SINGULARITY CONTAINER
This folder contains the Singularity container used to run the application. The singularity *definition* file is `matrix_multiplication.def`. To build the container, run the following command:

```bash
sudo singularity build mm.sif matrix_multiplication.def
``` 

The container is built starting from the base image `ubuntu:22.04` and moves the project into the container. The former command creates a compressed read-only Singularity Image File (SIF) named `mm.sif`. In order to build the container with writable root directory, you can specify the option `--sandbox` for interactive development.

To run the container, use the following command:

```bash
singularity run mm.sif
```

To execute the tests, run the following command:

```bash
singularity test mm.sif
```