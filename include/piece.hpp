#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

#include <queue>
#include <map>
#include <vector>

enum class PIECE {
    Pawn,
    King,
    Knight,
    Rook,
    Queen,
    Bishop
};

enum MovementType {
    STRAIGHT,
    DIAGONAL
};

#include "constants.hpp"
#include "helper.hpp"
#include "hitbox.hpp"
// class Hitbox;

class Piece {
public:
    Piece();
    ~Piece();
    
    Piece(char row, int col, Color team_color, const PIECE& piece, sf::Vector2f size, const std::string& name);
    Piece(const Position& pos, Color team_color, const PIECE& piece, sf::Vector2f size,  const std::string& name);

    Position get_pos() const;
    void draw(sf::RenderTarget& target) const;
    sf::RectangleShape* get_piece() const;
    Color get_team() const;

    std::vector<std::shared_ptr<Hitbox>> get_hitboxes() const;
    void clear_hitboxes();
    void add_hitbox(std::shared_ptr<Hitbox> hitbox);

    void set_piece_pos(Position pos);
    void set_position(sf::Vector2f pos);

    PIECE get_piece_type();
    virtual std::vector<std::queue<std::shared_ptr<Hitbox>>> calc_moves(const Position& pos) = 0;

    bool operator==(const Piece& other) const;

    bool moves_are_valid() const;
    void cache_moves(const std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves);
    std::vector<std::queue<std::shared_ptr<Hitbox>>>& get_moves_mutable();
    const std::vector<std::queue<std::shared_ptr<Hitbox>>>& get_moves() const;
    void invalidate_moves();

    bool is_king() const;
protected:
    std::unique_ptr<sf::RectangleShape> piece_rect_obj;
    Color team;
    Position piece_position;
    PIECE piece_type;

    std::vector<std::shared_ptr<Hitbox>> hitboxes;
    std::vector<std::queue<std::shared_ptr<Hitbox>>> cached_moves;

    bool are_moves_valid = false;
    
    virtual bool validate_in_bounds(char row, int col) const;
    virtual bool validate_in_bounds(const Position& pos) const;

    sf::Texture* load_sprite(const std::string& name, Color team_color) const;
};

