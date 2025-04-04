#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "matrix_ops.h"


bool loadSystemFont(sf::Font& font) {
    // Try common Linux font paths first
    const std::vector<std::string> fontPaths = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",  // Common on many Linux distros
        "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf",    // Ubuntu
        "/usr/share/fonts/truetype/freefont/FreeSans.ttf",  // Free font
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", // Red Hat/Fedora
        "arial.ttf"  // Last try local directory
    };

    for (const auto& path : fontPaths) {
        if (font.loadFromFile(path)) {
            return true;
        }
    }
    return false;
}

void drawMatrix(sf::RenderWindow& window, const std::vector<std::vector<int64_t>>& matrix, 
                float startX, float startY, const sf::Color& color, sf::Font& font) {
    const float cellSize = 50.f;
    const float padding = 10.f;
    
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            // Draw cell background
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(startX + j * (cellSize + padding), 
                            startY + i * (cellSize + padding));
            cell.setFillColor(sf::Color::Transparent);
            cell.setOutlineThickness(2.f);
            cell.setOutlineColor(color);
            window.draw(cell);
            
            // Draw cell value
            sf::Text text(std::to_string(matrix[i][j]), font, 20);
            text.setFillColor(color);
            text.setPosition(
                startX + j * (cellSize + padding) + cellSize/2 - text.getLocalBounds().width/2,
                startY + i * (cellSize + padding) + cellSize/2 - text.getLocalBounds().height/2
            );
            window.draw(text);
        }
    }
}
int main() {
    const int64_t rows_A = 3, cols_A = 3;
    const int64_t rows_B = 3, cols_B = 3;
    const int64_t rows_C = 3, cols_C = 3;
    std::vector<std::vector<int64_t>> A(rows_A, std::vector<int64_t>(cols_A));
    std::vector<std::vector<int64_t>> B(rows_B, std::vector<int64_t>(cols_B));
    std::vector<std::vector<int64_t>> C(rows_C, std::vector<int64_t>(cols_C));

    // Initialize matrices with random values
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

    // Console output
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
    
    // Create pointer arrays for assembly functions
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
    
    // Perform initial matrix operation
    std::string operation = "Original Matrices";
    if(cols_A == cols_B && cols_B == cols_C && rows_A == rows_B && rows_B == rows_C) {
        matrix_add(A_ptr, B_ptr, C_ptr, rows_A, cols_A);
        operation = "Matrix Addition (A + B)";
        
        std::cout << "Matrix C (A + B):" << std::endl;
        for (const auto& row : C) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    
    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Matrix Visualizer");
    window.setFramerateLimit(60);
    
    // Load font - trying multiple options
    sf::Font font;
    if (!font.loadFromFile("arial.ttf") && 
        !font.loadFromFile("/usr/share/fonts/truetype/arial.ttf") && 
        !font.loadFromFile("C:/Windows/Fonts/arial.ttf") && 
        !font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        // If no font found, create a default one
        std::cerr << "Warning: Could not load font. Using default." << std::endl;
    }
    
    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Handle keyboard input to switch between operations
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    operation = "Original Matrices";
                }
                else if (event.key.code == sf::Keyboard::Num2 && 
                         cols_A == cols_B && cols_B == cols_C && 
                         rows_A == rows_B && rows_B == rows_C) {
                    matrix_add(A_ptr, B_ptr, C_ptr, rows_A, cols_A);
                    operation = "Matrix Addition (A + B)";
                }
                else if (event.key.code == sf::Keyboard::Num3 && 
                         cols_A == cols_B && cols_B == cols_C && 
                         rows_A == rows_B && rows_B == rows_C) {
                    matrix_sub(A_ptr, B_ptr, C_ptr, rows_A, cols_A);
                    operation = "Matrix Subtraction (A - B)";
                }
                else if (event.key.code == sf::Keyboard::Num4 && 
                         cols_A == rows_B && rows_A == rows_C && cols_B == cols_C) {
                    matrix_mul(A_ptr, B_ptr, C_ptr, rows_A, cols_A, cols_B);
                    operation = "Matrix Multiplication (A * B)";
                }
            }
        }
        
        // Clear window
        window.clear(sf::Color(240, 240, 240));
        
        // Draw title
        sf::Text title(operation, font, 24);
        title.setFillColor(sf::Color::Black);
        title.setPosition(300, 20);
        window.draw(title);
        
        // Draw instructions
        sf::Text instructions("Press: 1-Original 2-Add 3-Sub 4-Mul", font, 18);
        instructions.setFillColor(sf::Color::Black);
        instructions.setPosition(250, 550);
        window.draw(instructions);
        
        // Draw matrices
        drawMatrix(window, A, 50, 100, sf::Color::Blue, font);
        drawMatrix(window, B, 300, 100, sf::Color::Red, font);
        drawMatrix(window, C, 550, 100, sf::Color::Green, font);
        
        // Draw operator symbols
        if (operation == "Original Matrices") {
            sf::Text op1("A", font, 24);
            op1.setPosition(120, 70);
            op1.setFillColor(sf::Color::Blue);
            window.draw(op1);
            
            sf::Text op2("B", font, 24);
            op2.setPosition(370, 70);
            op2.setFillColor(sf::Color::Red);
            window.draw(op2);
        }
        else {
            sf::Text op1("A", font, 24);
            op1.setPosition(120, 70);
            op1.setFillColor(sf::Color::Blue);
            window.draw(op1);
            
            sf::Text opSym(operation.substr(7, 1), font, 24);
            opSym.setPosition(270, 180);
            opSym.setFillColor(sf::Color::Black);
            window.draw(opSym);
            
            sf::Text op2("B", font, 24);
            op2.setPosition(370, 70);
            op2.setFillColor(sf::Color::Red);
            window.draw(op2);
            
            sf::Text eqSym("=", font, 24);
            eqSym.setPosition(500, 180);
            eqSym.setFillColor(sf::Color::Black);
            window.draw(eqSym);
            
            sf::Text res("C", font, 24);
            res.setPosition(620, 70);
            res.setFillColor(sf::Color::Green);
            window.draw(res);
        }
        
        // Display everything
        window.display();
    }
    
    return 0;
}