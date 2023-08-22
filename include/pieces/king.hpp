#ifndef KING_H
#define KING_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class King : public Piece {
public:
    King(char row, int col, Color team_color, sf::Vector2f size, Move_Handler& handler);
    King(const Position& pos, Color team_color, sf::Vector2f size, Move_Handler& handler);

    // bool is_in_check() const;

    bool validate_move(char row, int col) const override;
    bool validate_move(const Position &pos) const override;

    std::vector<Position> get_moves(const Position& pos, bool get_every_move = false) const override;

private:
    bool already_moved = false;
};

#endif
