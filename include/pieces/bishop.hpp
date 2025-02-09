#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "piece.hpp"
#include "constants.hpp"

#include <map>

class Bishop : virtual public Piece {
public:
    Bishop();
    ~Bishop();

    Bishop(char row, int col, Color team_color, sf::Vector2f size);
    Bishop(const Position& pos, Color team_color, sf::Vector2f size);

    virtual std::map<MoveAttributes, std::vector<std::queue<Position>>> calc_moves(const Position& pos) const override;
};

