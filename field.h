#pragma once

#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <ctime>

#define RESET   "\033[0m"
#define GREY    "\033[90m"
#define GREEN   "\033[32m" 

class Field {
public:
    Field()
        : rows(3), cols(3)
        , field(new char* [rows])
        , playerInput(' ')
        , aiInput(' ')
        , score(0)
        , gameOver(false)
    {
        for (int i = 0; i < rows; ++i) {
            field[i] = new char[cols];
        }
    }

    void Initialize() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                field[i][j] = ' ';
            }
        }
    }

    void PlayerChoice(uint16_t ch) {
        for (; !isValidChoose(ch);) {
            std::cout << "Invalid choice. Try Again";
            std::cin >> ch;
        }
        if (ch == 1) {
            playerInput = '0';
            std::cout << "You picked: " << GREEN << 0 << RESET << std::endl;
        }
        else {
            playerInput = 'X';
            std::cout << "You picked: " << GREEN << 'X' << RESET << std::endl;
        }
    }

    void PlayerMove(uint16_t playerMove) {
        std::pair<int, int> indices = ConvertToIndices(playerMove);
        int row = indices.first;
        int col = indices.second;

        if (field[row][col] == ' ') {
            field[row][col] = playerInput;
        }
        else {
            std::cout << "This cell is already taken. Try again." << std::endl;
            int newChoice;
            std::cout << "Enter new cell number (1-9): ";
            std::cin >> newChoice;
            PlayerMove(newChoice);
        }
    }

    void AIMove() {
        srand(time(nullptr));

        bool moved = false;
        while (!moved) {
            uint16_t aiNumber = rand() % 9 + 1;

            std::pair<int, int> indices = ConvertToIndices(aiNumber);
            int row = indices.first;
            int col = indices.second;

            aiInput = (playerInput == '0') ? 'X' : '0';

            if (field[row][col] == ' ') {
                field[row][col] = aiInput;
                moved = true;
            }
        }
    }

    void Delay() {
        std::cout << "AI thinking..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    void chekIfWin() {
        char winner = ' ';

        for (int i = 0; i < rows; ++i) {
            if (field[i][0] == field[i][1] && field[i][1] == field[i][2] && field[i][0] != ' ') {
                winner = field[i][0];
                break;
            }
        }

        for (int j = 0; j < cols; ++j) {
            if (field[0][j] == field[1][j] && field[1][j] == field[2][j] && field[0][j] != ' ') {
                winner = field[0][j];
                break;
            }
        }

        if ((field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[0][0] != ' ') ||
            (field[0][2] == field[1][1] && field[1][1] == field[2][0] && field[0][2] != ' ')) {
            winner = field[1][1];
        }

        if (winner == playerInput) {
            gameOver = true;
            score = 10;
        }
        else if (winner == aiInput) {
            gameOver = true;
            score = -10;
        }
        else {
            bool hasEmptyCell = false;
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (field[i][j] == ' ') {
                        hasEmptyCell = true;
                        break;
                    }
                }
                if (hasEmptyCell) {
                    break;
                }
            }
            if (!hasEmptyCell) {
                gameOver = true;
                score = 0;
            }
        }
    }

    void Print() {
        std::cout << "=========" << std::endl;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (field[i][j] == ' ') {
                    std::cout << '[' << GREY << (i * cols + j + 1) << RESET << ']';
                }
                else {
                    std::cout << '[' << GREEN << field[i][j] << RESET << ']';
                }
            }
            std::cout << std::endl;
        }
        std::cout << "=========" << std::endl;
    }

    ~Field() {
        for (int i = 0; i < rows; ++i) {
            delete field[i];
        }
        delete[] field;
    }

    bool isGameOver() const {
        return gameOver;
    }

    int16_t getScore() {
        return score;
    }


private:
    const size_t rows;
    const size_t cols;
    char** field;
    char playerInput;
    char aiInput;
    int16_t score;
    bool gameOver;

    bool isValidChoose(uint16_t choice) {
        return (choice == 1 || choice == 2);
    }

    std::pair<int, int> ConvertToIndices(uint16_t playerMove) {
        int row = (playerMove - 1) / 3;
        int col = (playerMove - 1) % 3;
        return std::make_pair(row, col);
    }
};