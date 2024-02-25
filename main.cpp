#include <iostream>
#include <cstdlib>
#include "field.h"

void Winner(int16_t);
bool playAgain = true;

int main() {

    while (playAgain) {
        Field field;
        field.Initialize();

        std::cout << "Enter 1 for " << GREEN << 0
            << RESET << " / 2 for " << GREEN << 'X'
            << RESET << " [1 / 2]: ";
        uint16_t choice;
        std::cin >> choice;
        field.PlayerChoice(choice);

        field.Print();

        while (!field.isGameOver()) {
            uint16_t playerMove;
            std::cout << "Enter the cell number (1-9) to make your move: ";
            std::cin >> playerMove;

            field.PlayerMove(playerMove);
            field.Print();

            field.Delay();

            field.AIMove();
            field.Print();

            field.chekIfWin();

            if (field.isGameOver()) {
                int16_t score = field.getScore();
                Winner(score);
                break;
            }
        }

        std::cout << "Do you want to play again? [y/n]: ";
        char playAgain;
        std::cin >> playAgain;
        if (playAgain == 'y') {
            playAgain = true;
        }
        else if (playAgain == 'n')
            break;
    }

    return 0;
}

void Winner(int16_t score) {
    if (score == 10)
        std::cout << "You win! ";
    else if (score == 0)
        std::cout << "Tie! ";
    else
        std::cout << "You lose! ";
}