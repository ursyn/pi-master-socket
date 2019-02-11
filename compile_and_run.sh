#!/bin/bash
#Compiles and runs the program
./configure --without-pvm --without-file --without-mpi && make && ./master_pi_indp <in_master.indp