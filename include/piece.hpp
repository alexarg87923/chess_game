#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

#include <queue>
#include <map>
#include <vector>

enum MoveAttributes {
    OBSTRUCT_ON_OCCUPY,  // Move is obstructed if the square is occupied.
    VALID_ON_ENEMY_ONLY,     // Move is valid if the square has an enemy piece
    SEARCH    // Move is valid if the square is empty.
};


#include "types.hpp"
#include "helper.hpp"

class Hitbox;

class Piece {
public:
    Piece();
    ~Piece();
    
    Piece(char row, int col, Color team_color, const std::string& name, sf::Vector2f size);
    Piece(const Position& pos, Color team_color, const std::string& name, sf::Vector2f size);

    Position get_pos() const;
    void draw(sf::RenderTarget& target) const;
    sf::RectangleShape* get_piece() const;
    Color get_team() const;

    std::vector<std::shared_ptr<Hitbox>> get_hitboxes() const;
    void clear_hitboxes();
    void add_hitbox(std::shared_ptr<Hitbox> hitbox);

    void set_piece_pos(Position pos);
    void set_position(sf::Vector2f pos);

    virtual std::map<MoveAttributes, std::vector<std::queue<Position>>> calc_moves(const Position& pos) const = 0;

    bool operator==(const Piece& other) const;

    bool moves_are_valid() const;
    void cache_moves(const std::map<MoveAttributes, std::vector<std::queue<Position>>>& moves);
    std::map<MoveAttributes, std::vector<std::queue<Position>>>& get_moves_mutable();
    const std::map<MoveAttributes, std::vector<std::queue<Position>>>& get_moves() const;
    void invalidate_moves();
protected:
    std::unique_ptr<sf::RectangleShape> piece_rect_obj;
    Color team;
    Position piece_position;
    std::vector<std::shared_ptr<Hitbox>> hitboxes;
    std::string piece_name;

    std::map<MoveAttributes, std::vector<std::queue<Position>>> cached_moves;

    bool are_moves_valid = false;
    
    virtual bool validate_in_bounds(char row, int col) const;
    virtual bool validate_in_bounds(const Position& pos) const;

    sf::Texture* load_sprite(const std::string& name, Color team_color) const;
};

#endif
