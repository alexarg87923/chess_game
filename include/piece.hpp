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
    virtual ~Piece() = default;
    
    Piece(char row, int col, Color team_color, const PIECE& piece, sf::Vector2f size, const std::string& name);
    Piece(const Position& pos, Color team_color, const PIECE& piece, sf::Vector2f size,  const std::string& name);

    Position get_pos() const;
    void draw(sf::RenderTarget& target) const;
    sf::RectangleShape* get_piece() const;
    Color get_team() const;


    void set_piece_pos(Position pos);
    void set_position(sf::Vector2f pos);

    PIECE get_piece_type();
    virtual std::vector<std::queue<std::shared_ptr<Hitbox>>> calc_moves(const Position& pos) = 0;

    bool operator==(const Piece& other) const;

    void clear_hitboxes();
    void add_hitbox(std::shared_ptr<Hitbox> hitbox);
    bool hitboxes_are_valid() const;
    const std::vector<std::shared_ptr<Hitbox>>& get_hitboxes() const;
    std::vector<std::shared_ptr<Hitbox>>& get_hitboxes_mutable();
    
    void cache_moves(const std::vector<std::queue<std::shared_ptr<Hitbox>>>& moves);
    std::vector<std::queue<std::shared_ptr<Hitbox>>>& get_cache_mutable();
    const std::vector<std::queue<std::shared_ptr<Hitbox>>>& get_cache() const;
    void invalidate_moves();

    void process();
    bool is_being_processed();
    bool is_king() const;
protected:
    std::unique_ptr<sf::RectangleShape> piece_rect_obj;
    Color team;
    Position piece_position;
    PIECE piece_type;

    std::vector<std::shared_ptr<Hitbox>> hitboxes;
    std::vector<std::queue<std::shared_ptr<Hitbox>>> cached_moves;

    bool being_processed = false;
    bool are_moves_valid = false;

    virtual bool validate_in_bounds(char row, int col) const;
    virtual bool validate_in_bounds(const Position& pos) const;

    sf::Texture* load_sprite(const std::string& name, Color team_color) const;
};

