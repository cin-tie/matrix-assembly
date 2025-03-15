#pragma once

#include <cstdint>

extern "C" {
    void matrix_add(int64_t** A, int64_t** B, int64_t** C, int64_t rows, int64_t cols);
    void matrix_sub(int64_t** A, int64_t** B, int64_t** C, int64_t rows, int64_t cols);
    void matrix_mul(int64_t** A, int64_t** B, int64_t** C, int64_t rows1, int64_t cols1, int64_t cols2);
}