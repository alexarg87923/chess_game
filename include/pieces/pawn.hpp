#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"

class Pawn : public Piece {
public:
    Pawn();
    ~Pawn();
    Pawn(char row, int col, Color team_color, sf::Vector2f size);
    Pawn(const Position& pos, Color team_color, sf::Vector2f size);

    std::vector<Position> get_moves(const Position& pos) const override;

    void update_position(const Position& pos) override;

private:
    bool first_move = true;
};

#endif
