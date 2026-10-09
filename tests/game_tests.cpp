#include "tto/game.hpp"

#include <cassert>
#include <stdexcept>

int main() {
    {
        tto::Game game;
        assert(game.current_player() == 'X');
        assert(game.make_move(0, 0));
        assert(game.current_player() == 'O');
        assert(!game.make_move(0, 0));
        assert(!game.make_move(3, 0));
    }

    {
        tto::Game game;
        assert(game.make_move(0, 0)); // X
        assert(game.make_move(1, 0)); // O
        assert(game.make_move(0, 1)); // X
        assert(game.make_move(1, 1)); // O
        assert(game.make_move(0, 2)); // X wins
        assert(game.winner() == 'X');
        assert(game.finished());
        assert(!game.make_move(2, 2));
    }

    {
        tto::Game game(2, 3);
        assert(game.make_move(0, 0)); // X
        assert(game.make_move(1, 0)); // O
        assert(game.make_move(0, 1)); // X
        assert(game.make_move(1, 1)); // O
        assert(game.make_move(0, 2)); // X wins row
        assert(game.winner() == 'X');
    }

    {
        tto::Game game;
        assert(game.make_move(0, 0)); // X
        assert(game.make_move(0, 1)); // O
        assert(game.make_move(1, 1)); // X
        assert(game.make_move(0, 2)); // O
        assert(game.make_move(2, 2)); // X wins diagonal
        assert(game.winner() == 'X');
    }

    {
        tto::Game game(2, 2);
        assert(game.make_move(0, 0)); // X
        assert(game.make_move(0, 1)); // O
        assert(game.make_move(1, 0)); // X wins column? no, this is diagonal? 
        assert(!game.is_draw());
    }

    {
        tto::Game game;
        assert(game.make_move(0, 0));
        game.reset();
        assert(game.current_player() == 'X');
        assert(game.at(0, 0) == ' ');
        assert(!game.finished());
    }

    {
        bool threw = false;
        try {
            tto::Game game(1, 3);
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        assert(threw);
    }

    return 0;
}
