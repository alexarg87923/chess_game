#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "string.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include "unistd.h"
#include "types.hpp"

class Board;
class King;

class Piece {
public:
    Piece(){};
    ~Piece(){};
    Piece(char row, int col, char team_color);
    Piece(Position pos, char team_color);

    virtual void draw(sf::RenderTarget& target) const;
    virtual void update_position(Position pos);
    virtual std::vector<Position> get_valid_moves();
    virtual sf::RectangleShape* get_ppiece();
    virtual void calc_valid_moves();

protected:
    sf::RectangleShape* piece;
    std::vector<Position> valid_moves;
    char team;
    Position position;
    std::string name;

    virtual void save_piece(sf::RectangleShape *tmp);

    virtual Position get_pos();

    virtual bool validate_move(char row, int col);
    virtual bool validate_move(Position pos);
    virtual std::string get_working_dir();
    virtual sf::Texture* load_sprite(const std::string& name, char team_color);
    virtual void save_moves_globally(std::string piece_name);

    void save_piece_to_map(char team, std::string name, Piece* piece);
    bool is_king_in_check();
private:
    void set_position(Position &pos);
};

#endif
