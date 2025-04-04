#pragma once

#include <cstdint>

extern "C" void matrix_add(int64_t** A, int64_t** B, int64_t** C, int64_t rows, int64_t cols);
extern "C" void matrix_sub(int64_t** A, int64_t** B, int64_t** C, int64_t rows, int64_t cols);
extern "C" void matrix_mul(int64_t* const* A, int64_t* const* B, int64_t* const* C, int64_t rows_A, int64_t cols_A, int64_t cols_B);
extern "C" int64_t matrix_det(int64_t** A, int64_t rows_cols);