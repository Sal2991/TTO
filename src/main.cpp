#include "tto/game.hpp"

#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

namespace {

void print_board(const tto::Game& game) {
    for (std::size_t row = 0; row < game.rows(); ++row) {
        for (std::size_t col = 0; col < game.cols(); ++col) {
            std::cout << ' ' << game.at(row, col) << ' ';
            if (col + 1 < game.cols()) {
                std::cout << '|';
            }
        }
        std::cout << '\n';

        if (row + 1 < game.rows()) {
            for (std::size_t col = 0; col < game.cols(); ++col) {
                std::cout << "---";
                if (col + 1 < game.cols()) {
                    std::cout << '+';
                }
            }
            std::cout << '\n';
        }
    }
}

bool read_number(const std::string& prompt, int& value) {
    std::string line;
    std::cout << prompt;

    if (!std::getline(std::cin, line)) {
        return false;
    }

    std::istringstream input(line);
    char extra = '\0';
    return (input >> value) && !(input >> extra);
}

bool play_again() {
    std::string answer;
    while (true) {
        std::cout << "Play again? (y/n): ";
        if (!std::getline(std::cin, answer)) {
            return false;
        }

        if (answer == "y" || answer == "Y") {
            return true;
        }
        if (answer == "n" || answer == "N") {
            return false;
        }

        std::cout << "Enter y or n.\n";
    }
}

void play_game(std::size_t rows, std::size_t cols) {
    tto::Game game(rows, cols);

    while (!game.finished()) {
        print_board(game);
        int row = 0;
        int col = 0;

        if (!read_number("Player " + std::string(1, game.current_player()) +
                             ", enter row and column: ",
                         row)) {
            return;
        }

        std::string line;
        if (!std::getline(std::cin, line)) {
            return;
        }
        std::istringstream input(line);
        if (!(input >> col) || (input >> std::ws && !input.eof())) {
            std::cout << "Enter two numbers, such as: 2 3\n";
            continue;
        }

        if (row < 1 || col < 1 ||
            !game.make_move(static_cast<std::size_t>(row - 1),
                            static_cast<std::size_t>(col - 1))) {
            std::cout << "That move isn't valid. Try again.\n";
        }
    }

    print_board(game);
    if (game.winner() != ' ') {
        std::cout << "Player " << game.winner() << " wins!\n";
    } else {
        std::cout << "It's a draw.\n";
    }
}

} // namespace

int main() {
    int rows = 3;
    int cols = 3;

    while (true) {
        if (!read_number("Rows (2-10): ", rows) ||
            rows < 2 || rows > 10) {
            std::cout << "Please enter a whole number from 2 to 10.\n";
            continue;
        }
        break;
    }

    while (true) {
        if (!read_number("Columns (2-10): ", cols) ||
            cols < 2 || cols > 10) {
            std::cout << "Please enter a whole number from 2 to 10.\n";
            continue;
        }
        break;
    }

    do {
        play_game(static_cast<std::size_t>(rows), static_cast<std::size_t>(cols));
    } while (play_again());

    std::cout << "Goodbye!\n";
    return 0;
}
