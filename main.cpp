/*sf::RenderWindow window(sf::VideoMode(800, 600), "Matrix Visualizer");
while(window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
        
    window.clear(sf::Color::Black);

    window.display();
}*/

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "matrix_ops.h"

int main() {

    const int64_t rows_A = 3, cols_A = 3;
    const int64_t rows_B = 3, cols_B = 3;
    const int64_t rows_C = 3, cols_C = 3;
    std::vector<std::vector<int64_t>> A(rows_A, std::vector<int64_t>(cols_A));
    std::vector<std::vector<int64_t>> B(rows_B, std::vector<int64_t>(cols_B));
    std::vector<std::vector<int64_t>> C(rows_C, std::vector<int64_t>(cols_C));

    for (size_t i = 0; i < rows_A; i++) {
        for (size_t j = 0; j < cols_A; j++) {
            A[i][j] = std::rand() % 10;
        }
    }
    
    for (size_t i = 0; i < rows_B; i++) {
        for (size_t j = 0; j < cols_B; j++) {
            B[i][j] = std::rand() % 10;
        }
    }

    std::cout << "Matrix A:" << std::endl;
    for (const auto& row : A) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Matrix B:" << std::endl;
    for (const auto& row : B) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
        int64_t* A_ptr[rows_A];
        int64_t* B_ptr[rows_B];
        int64_t* C_ptr[rows_C];
        for (size_t i = 0; i < rows_A; i++) {
            A_ptr[i] = A[i].data();
        }
        for (size_t i = 0; i < rows_B; i++) {
            B_ptr[i] = B[i].data();
        }
        for (size_t i = 0; i < rows_C; i++) {
            C_ptr[i] = C[i].data();
        }
        
    if(cols_A == cols_B && cols_B == cols_C && rows_A == rows_B && rows_B == rows_C){
    
        matrix_add(A_ptr, B_ptr, C_ptr, rows_A, cols_A);
        
        std::cout << "Matrix C (A + B):" << std::endl;
        for (const auto& row : C) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    
    if(cols_A == cols_B && cols_B == cols_C && rows_A == rows_B && rows_B == rows_C){
    
        matrix_sub(A_ptr, B_ptr, C_ptr, rows_A, cols_A);
        
        std::cout << "Matrix C (A - B):" << std::endl;
        for (const auto& row : C) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    if(cols_A == rows_B && rows_A == rows_C && cols_B == cols_C){
    
        matrix_mul(A_ptr, B_ptr, C_ptr, rows_A, cols_A, cols_B);
        
        std::cout << "Matrix C (A * B):" << std::endl;
        for (const auto& row : C) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
