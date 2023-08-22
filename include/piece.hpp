#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

#include <vector>

#include "types.hpp"
#include "chess_ai.hpp"
#include "helper.hpp"
#include "move_handler.hpp"

class Piece {
public:
    Piece(Move_Handler& handler);
    ~Piece(){};

    Piece(char row, int col, Color team_color, const std::string& name, sf::Vector2f size, Move_Handler& handler);
    Piece(const Position& pos, Color team_color, const std::string& name, sf::Vector2f size,  Move_Handler& handler);

    Position get_pos() const;
    void draw(sf::RenderTarget& target) const;
    std::vector<Position> get_valid_moves() const;
    sf::RectangleShape* get_piece() const;
    Color get_team() const;

    std::vector<std::shared_ptr<Hitbox>> get_hitboxes() const;
    void clear_hitboxes();
    void add_hitbox(std::shared_ptr<Hitbox> hitbox);
    void add_valid_move(Position pos);

    virtual std::vector<Position> get_moves(const Position& pos, bool get_every_move = false) const = 0;

    bool operator==(const Piece& other) const;

    void set_piece_pos(Position pos);
    void set_position(sf::Vector2f pos);
    void clear_valid_moves();
    void set_valid_moves(std::vector<Position> incoming_valid_moves);
protected:
    std::unique_ptr<sf::RectangleShape> piece_rect_obj;
    std::vector<Position> valid_moves;
    Color team;
    Position piece_position;
    std::vector<std::shared_ptr<Hitbox>> hitboxes;
    std::string piece_name;

    Move_Handler& move_handler;

    virtual bool validate_move(char row, int col) const;
    virtual bool validate_move(const Position& pos) const;

    sf::Texture* load_sprite(const std::string& name, Color team_color) const;

};

#endif
