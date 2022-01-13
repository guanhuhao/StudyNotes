import os
st = {1,2,4,8,16}
for i in st:
    for j in range(1,2):
        os.system("mpic++ -o fun test.cpp -fopenmp > compile.log")
        os.system("mpirun -n %d -genv OMP_NUM_THREADS 1 ./fun > out.log ")