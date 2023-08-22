#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

#include <vector>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include "types.hpp"
#include "chess_ai.hpp"

class King;

class Piece {
public:
    Piece(){};
    ~Piece(){};
    Piece(char row, int col, Color team_color, const std::string& name, sf::Vector2f size);
    Piece(const Position& pos, Color team_color, const std::string& name, sf::Vector2f size);

    Position get_pos() const;
    void draw(sf::RenderTarget& target) const;
    std::vector<Position> get_valid_moves() const;
    sf::RectangleShape* get_piece() const;
    Color get_team() const;
    std::vector<Hitbox*> get_hitboxes() const;

    void clear_hitboxes();
    void add_hitbox(Hitbox *hitbox);

    virtual void update_position(const Position& pos);
    virtual void calc_valid_moves();
    virtual std::vector<Position> get_moves(const Position& pos) const = 0;

protected:
    sf::RectangleShape* piece;
    std::vector<Position> valid_moves;
    Color team;
    Position piece_position;
    std::vector<Hitbox*> hitboxes;

    virtual void save_piece(sf::RectangleShape *tmp);
    virtual bool validate_move(char row, int col) const;
    virtual bool validate_move(const Position& pos) const;

    sf::Texture* load_sprite(const std::string& name, Color team_color) const;

    bool is_king_in_check() const;

    bool is_this_move_going_to_stop_check(const Position& pos) const;

private:
    void set_position(const Position &pos);
    std::string get_working_dir() const;
    void refresh_affected_pieces(const std::vector<Hitbox*>& pos);

};

#endif
