#ifndef KING_H
#define KING_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <piece.hpp>

#include "board.hpp"


class King : public Piece {
public:
    King();
    ~King();

    King(char row, int col, char team_color);
    King(Position pos, char team_color);

    bool is_in_check();

    void calc_valid_moves() override;
    bool validate_move(char row, int col) override;
    bool validate_move(Position pos) override;

    std::vector<Position> get_moves(Position pos, bool get_every_move) override;

    void update_position(Position pos) override;
private:
    bool already_moved = false;
    std::string name = "king"; 
};

#endif
