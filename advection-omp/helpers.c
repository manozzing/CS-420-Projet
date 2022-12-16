#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

int NX, NY, nstep, nthreads;

void setup_env(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "usage is: %s <nx> <ny> <nstep><nthread>\n", argv[0]);
        exit(1);
    }
  // Parse the arguments
    NX = atoi(argv[1]);
    NY = atoi(argv[2]);
    nstep = atoi(argv[3]);
    nthreads = atoi(argv[4]);
}

