#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

#include <vector>
#include <string.h>
#include <unistd.h>

#include "types.hpp"
#include "chess_ai.hpp"

class King;

class Piece {
public:
    Piece(){};
    ~Piece(){};
    Piece(char row, int col, char team_color);
    Piece(Position pos, char team_color);

    Position get_pos();
    void draw(sf::RenderTarget& target) const;
    std::vector<Position> get_valid_moves();
    sf::RectangleShape* get_piece();
    char get_team();
    std::vector<Hitbox*> get_hitboxes();
    void clear_hitboxes();
    void add_hitbox(Hitbox *hitbox);

    virtual void update_position(Position pos);
    virtual void calc_valid_moves();
    virtual std::vector<Position> get_moves(Position pos, bool get_every_move) = 0;

protected:
    sf::RectangleShape* piece;
    std::vector<Position> valid_moves;
    char team;
    Position piece_position;
    std::string name;
    std::vector<Hitbox*> hitboxes;

    virtual void save_piece(sf::RectangleShape *tmp);
    virtual bool validate_move(char row, int col);
    virtual bool validate_move(Position pos);

    sf::Texture* load_sprite(const std::string& name, char team_color);

    bool is_king_in_check();

    void save_piece_to_map(char team, std::string name, Piece* piece);

    bool is_this_move_going_to_stop_check(Position pos);
private:
    void set_position(Position &pos);
    std::string get_working_dir();
    void refresh_affected_pieces(Position pos);

};

#endif
