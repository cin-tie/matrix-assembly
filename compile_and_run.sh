#!/bin/bash

as matrix_add.s -o matrix_add.o
as matrix_sub.s -o matrix_sub.o
as matrix_mul.s -o matrix_mul.o

g++ -g -fsanitize=address -fno-omit-frame-pointer main.cpp matrix_add.o matrix_sub.o matrix_mul.o -o main -lsfml-graphics -lsfml-window -lsfml-system

./main