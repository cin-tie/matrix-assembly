#!/bin/bash

as matrix_ops.s -o matrix_ops.o

g++ main.cpp matrix_ops.o -o main

./main