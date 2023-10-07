#pragma once

struct Position {
    char row;
    int col;
    bool has_piece;
    // Position(char r, int c) : row(r), col(c) {}

    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }

    bool operator<(const Position& other) const {
        if(row < other.row) return true;
        if(row > other.row) return false;
        return col < other.col;
    }
};

enum Color {
    WHITE = 1,
    BLACK = -1
};
