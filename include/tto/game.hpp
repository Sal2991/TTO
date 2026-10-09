#pragma once

#include <cstddef>
#include <vector>

namespace tto {

class Game {
public:
    Game(std::size_t rows = 3, std::size_t cols = 3);

    bool make_move(std::size_t row, std::size_t col);
    void reset();

    std::size_t rows() const noexcept;
    std::size_t cols() const noexcept;
    char at(std::size_t row, std::size_t col) const;
    char current_player() const noexcept;
    char winner() const noexcept;
    bool is_draw() const noexcept;
    bool finished() const noexcept;

private:
    bool has_won(char player) const;
    bool board_is_full() const;
    bool row_is_full(std::size_t row, char player) const;
    bool column_is_full(std::size_t col, char player) const;

    std::vector<std::vector<char>> board_;
    char current_player_ = 'X';
    char winner_ = ' ';
    bool draw_ = false;
};

} // namespace tto
