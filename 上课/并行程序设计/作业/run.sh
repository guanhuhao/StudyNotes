#!/bin/bash
mpic++ -o fun test.cpp -fopenmp > compile.log
mpirun -n 9 -genv OMP_NUM_THREADS 1 ./fun > out.log