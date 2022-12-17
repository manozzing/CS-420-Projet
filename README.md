To compile the code, please use

$make advect

To run the simulation, please use

$./advect <nx><ny><nstep>  # for serial version
$./advect <nx><ny><nstep><numthreads>  # for omp version
$mpirun -n <numPes> ./advect <nx><ny><nstep>  # for mpi version

where 

nx, ny defines the dimensions
nstep defines the number of time steps
numthreads defines the number of threads to use
numPes defines the number of nodes to use
