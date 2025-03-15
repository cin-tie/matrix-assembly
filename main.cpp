#include <iostream>
#include <SFML/Graphics.hpp>
#include "matrix_ops.h"

int main(){
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
    int64_t cols = 10, rows = 5;
    int64_t** A = new int64_t*[rows];
    int64_t** B = new int64_t*[rows];
    int64_t** C = new int64_t*[rows];
    for(size_t i = 0; i < rows; i++){
        A[i] = new int64_t[cols];
        B[i] = new int64_t[cols];
        C[i] = new int64_t[cols];
    }

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    matrix_add(A, B, C, rows, cols);
    
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            std::cout << B[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;


    for (int i = 0; i < rows; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
};