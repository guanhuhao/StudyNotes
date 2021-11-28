#!/bin/bash
mpic++ -o fun test.cpp -fopenmp > compile.log
mpirun -n 1 -genv OMP_NUM_THREADS 8 ./fun > out.log