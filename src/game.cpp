#include "tto/game.hpp"

#include <stdexcept>

namespace tto {

Game::Game(std::size_t rows, std::size_t cols)
    : board_(rows, std::vector<char>(cols, ' ')) {
    if (rows < 2 || rows > 10 || cols < 2 || cols > 10) {
        throw std::invalid_argument("board dimensions must be between 2 and 10");
    }
}

bool Game::make_move(std::size_t row, std::size_t col) {
    if (finished() || row >= rows() || col >= cols() || board_[row][col] != ' ') {
        return false;
    }

    board_[row][col] = current_player_;

    if (has_won(current_player_)) {
        winner_ = current_player_;
    } else if (is_draw()) {
        draw_ = true;
    } else {
        current_player_ = current_player_ == 'X' ? 'O' : 'X';
    }

    return true;
}

void Game::reset() {
    for (auto& row : board_) {
        for (char& cell : row) {
            cell = ' ';
        }
    }

    current_player_ = 'X';
    winner_ = ' ';
    draw_ = false;
}

std::size_t Game::rows() const noexcept {
    return board_.size();
}

std::size_t Game::cols() const noexcept {
    return board_.empty() ? 0 : board_.front().size();
}

char Game::at(std::size_t row, std::size_t col) const {
    if (row >= rows() || col >= cols()) {
        throw std::out_of_range("board position is out of range");
    }

    return board_[row][col];
}

char Game::current_player() const noexcept {
    return current_player_;
}

char Game::winner() const noexcept {
    return winner_;
}

bool Game::is_draw() const noexcept {
    return draw_;
}

bool Game::finished() const noexcept {
    return winner_ != ' ' || draw_;
}

bool Game::row_is_full(std::size_t row, char player) const {
    for (char cell : board_[row]) {
        if (cell != player) {
            return false;
        }
    }

    return true;
}

bool Game::column_is_full(std::size_t col, char player) const {
    for (const auto& row : board_) {
        if (row[col] != player) {
            return false;
        }
    }

    return true;
}

bool Game::has_won(char player) const {
    for (std::size_t row = 0; row < rows(); ++row) {
        if (row_is_full(row, player)) {
            return true;
        }
    }

    for (std::size_t col = 0; col < cols(); ++col) {
        if (column_is_full(col, player)) {
            return true;
        }
    }

    if (rows() == cols()) {
        bool main_diagonal = true;
        bool other_diagonal = true;

        for (std::size_t i = 0; i < rows(); ++i) {
            if (board_[i][i] != player) {
                main_diagonal = false;
            }

            if (board_[i][cols() - i - 1] != player) {
                other_diagonal = false;
            }
        }

        return main_diagonal || other_diagonal;
    }

    return false;
}

} // namespace tto
