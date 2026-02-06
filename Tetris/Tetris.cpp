#include <iostream>
#include <thread>
#include <chrono>

#include "Map.h"
#include "ConsoleInput.h"
#include "Piece.h"
#include "PiecesStack.h"
#include "PiecesOrder.h"

#define ROWS 14
#define COLS 14

bool printMatrixDebug(Matrix& matrix_test) {
    for (size_t i = 0; i < COLS; i++)
    {
        for (size_t j = 0; j < ROWS; j++)
        {
            std::cout << matrix_test[i][j];
        }
        std::cout << '\n';
    }
    return true;

}

void processInput(char& ch, std::unique_ptr<BasePiece>& piece, Map& map, bool& gameIsRunning) {
    
    ConsoleUtils::getInput(ch);

    switch(ch) {
       
    case 'a': 
        piece->moveSides(Directions::Left, map.getMatrix()); 
        break;
    
    case 'd': 
        piece->moveSides(Directions::Right, map.getMatrix()); 
        break;
    
    case 's': 
        piece->moveDown(map.getMatrix()); 
        break; 

    case 'w':
    case 'z':
        piece->rotate(Rotations::Right);
        break;

    case 'q':
        std::cout << "Saliendo... [DEBUG]" << std::endl;
        gameIsRunning = false;
        break;

    default: 
        //std::cout << "Tecla no reconocida!" << '\n';
        break;
    }
}

auto previousTime = std::chrono::steady_clock::now();
float timer{0.0f};
float delay{ 0.3f };
PiecesStack piecesStack{};

void update(std::unique_ptr<BasePiece>& currentPiece, Map& map) {

    // Hay que tratar al update como una maquina de estados

    // Me traigo la siguiente pieza antes de hacer el update
    if (currentPiece == nullptr) {
        currentPiece = piecesStack.getNextPiece(COLS/2, 0);
        if (currentPiece->checkCollision(map.getMatrix())) {
            // GAME OVER
            std::cout << "GAME OVER" << std::endl;
            exit(0);
        }
    }

    auto currentTime = std::chrono::steady_clock::now();

    std::chrono::duration<float> elapsed = currentTime - previousTime;

    previousTime = currentTime;
    timer += elapsed.count();

    if (timer > delay) {
        // GRAVEDAD
        const size_t originalY = currentPiece->getPieceData().y;

        currentPiece->moveDown(map.getMatrix());

        if (currentPiece->piece.solid == true)
        {
            map.writePiece(currentPiece->piece);
            map.checkLine();

        }

        if (currentPiece->getPieceData().y == originalY)
        {
            currentPiece = nullptr;
        }
        
        timer = 0;

    }

}

void render(Map& map, std::unique_ptr<BasePiece>& piece) {
    map.renderMap(piece);
    // TODO: Desharcodear esto...
    std::this_thread::sleep_for(std::chrono::milliseconds(140));
    ConsoleUtils::clear();
}


int main()
{
    // consola a UTF-8:
    // SetConsoleOutputCP(65001);

    // Generacion de mapa:
    Map map = Map(ROWS, COLS);

    // GAME LOOP:
    bool gameIsRunning{ true };

    // Buffer para la tecla que presione el usuario.
    char ch{};
    std::unique_ptr<BasePiece> currentPiece = nullptr;


    while (gameIsRunning) {

        update(currentPiece, map);

        if (currentPiece != nullptr) {
            processInput(ch, currentPiece, map, gameIsRunning);
        }

        render(map, currentPiece);
        
    }

    printMatrixDebug(map.getMatrix());

    return 0;
}

