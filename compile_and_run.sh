#!/bin/bash

as matrix_add.s -o matrix_add.o
as matrix_sub.s -o matrix_sub.o
as matrix_mul.s -o matrix_mul.o
as matrix_det.s -o matrix_det.o

g++ -g main.cpp matrix_add.o matrix_sub.o matrix_mul.o matrix_det.o -o main -lsfml-graphics -lsfml-window -lsfml-system

./main