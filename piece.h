#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
using namespace std;

// Constants to represent color names.
const char WHITE = 'W';
const char BLACK = 'B';

// Constants to represent piece names.
const char KING = 'K';
const char QUEEN = 'Q';
const char ROOK = 'R';
const char BISHOP = 'B';
const char KNIGHT = 'N';
const char PAWN = 'P';

// Constants to represent potential movement outcomes.
const int BAD = -1;      // The piece cannot be moved to this square.
const int GOOD = 0;      // The piece can be moved to this square.
const int CHECK = 1;     // The enemy player's king is vulnerable and needs to be protected.
const int CHECKMATE = 2; // The enemy player's king is vulnerable and cannot be protected. You win.
const int STALEMATE = 3; // The enemy player's king isn't vulnerable, but cannot make a valid move. Nobody wins. Draw.

// Functions.
bool checkBounds(pair<int, int> location);

// It's important to remember the coords of a piece are dictated by [row][column], or [y][x].
class Piece
{
private:
    // Attributes
    char _color;              // The color of the piece. Can be 'W' or 'B'.
    char _name;               // The name of the piece. Can be 'K', 'Q', 'R', 'B', 'N', or 'P'
    pair<int, int> _location; // Current location of the piece on the chess board. Bottom left is {0,0}, top right is {7,7}.

public:
    // Constructors.
    Piece() : _color(0), _name(0), _location({-1, -1}) {}                                                      // Default constructor.
    Piece(char color, char name, pair<int, int> location) : _color(color), _name(name), _location(location) {} // Constructor for a specific piece.

    // Getters
    char color() const { return _color; }                         // Return the color char of the piece.
    char name() const { return _name; }                           // Return the name char of the piece.
    string fullName() const { return string(1, _color) + _name; } // Return the color+name of the piece, giving it a unique name for that player's side.
    pair<int, int> location() const { return _location; }         // Return the location pair of ints of the piece.

    // Setters
    void move(pair<int, int> location) { _location = location; } // Sets the location of the piece to the argument's value.

    virtual vector<pair<int, int>> moveCheck(pair<int, int> move_to) = 0; // Pure virtual function for returning the moves of a piece in a single direction.
    virtual vector<vector<pair<int, int>>> allMoveCheck() = 0;            // Pure virtual function for returning all the moves of a piece.
};

class King : public Piece
{
public:
    // Constructor.
    King(char color, pair<int, int> location) : Piece(color, KING, location) {}

    // Returns all squares between the king's current square and the square being moved to.
    vector<pair<int, int>> moveCheck(pair<int, int> move_to)
    {
        pair<int, int> to_add;
        vector<pair<int, int>> move_to_list;

        // Move up one space.
        to_add = {location().first + 1, location().second};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move diagonally top right one space.
        to_add = {location().first + 1, location().second + 1};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move right one space.
        to_add = {location().first, location().second + 1};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move diagonally bottom right one space.
        to_add = {location().first - 1, location().second + 1};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move down one space.
        to_add = {location().first - 1, location().second};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move diagonally bottom left one space.
        to_add = {location().first - 1, location().second - 1};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move left one space.
        to_add = {location().first, location().second - 1};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move diagonally top left one space.
        to_add = {location().first + 1, location().second - 1};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        return move_to_list;
    }

    // Returns all possible squares the king can move to.
    vector<vector<pair<int, int>>> allMoveCheck()
    {
        pair<int, int> to_add;
        vector<vector<pair<int, int>>> move_to_list;

        // Move up one space.
        to_add = {location().first + 1, location().second};
        if (checkBounds(to_add))
        {
            vector<pair<int, int>> up;
            up.push_back(to_add);
            move_to_list.push_back(up);
        }

        // Move diagonally top right one space.
        to_add = {location().first + 1, location().second + 1};
        if (checkBounds(to_add))
        {
            vector<pair<int, int>> diag_top_right;
            diag_top_right.push_back(to_add);
            move_to_list.push_back(diag_top_right);
        }

        // Move right one space.
        to_add = {location().first, location().second + 1};
        if (checkBounds(to_add))
        {
            vector<pair<int, int>> right;
            right.push_back(to_add);
            move_to_list.push_back(right);
        }

        // Move diagonally bottom right one space.
        to_add = {location().first - 1, location().second + 1};
        if (checkBounds(to_add))
        {
            vector<pair<int, int>> diag_bottom_right;
            diag_bottom_right.push_back(to_add);
            move_to_list.push_back(diag_bottom_right);
        }

        // Move down one space.
        to_add = {location().first - 1, location().second};
        if (checkBounds(to_add))
        {
            vector<pair<int, int>> down;
            down.push_back(to_add);
            move_to_list.push_back(down);
        }

        // Move diagonally bottom left one space.
        to_add = {location().first - 1, location().second - 1};
        if (checkBounds(to_add))
        {
            vector<pair<int, int>> diag_bottom_left;
            diag_bottom_left.push_back(to_add);
            move_to_list.push_back(diag_bottom_left);
        }

        // Move left one space.
        to_add = {location().first, location().second - 1};
        if (checkBounds(to_add))
        {
            vector<pair<int, int>> left;
            left.push_back(to_add);
            move_to_list.push_back(left);
        }

        // Move diagonally top left one space.
        to_add = {location().first + 1, location().second - 1};
        if (checkBounds(to_add))
        {
            vector<pair<int, int>> diag_top_left;
            diag_top_left.push_back(to_add);
            move_to_list.push_back(diag_top_left);
        }

        return move_to_list;
    }
};

class Queen : public Piece
{
public:
    // Constructor.
    Queen(char color, pair<int, int> location) : Piece(color, QUEEN, location) {}

    // Returns all squares between the queen's current square and the square being moved to.
    vector<pair<int, int>> moveCheck(pair<int, int> move_to)
    {
        pair<int, int> to_add;
        vector<pair<int, int>> move_to_list;

        // Move up many spaces.
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first + 1, to_add.second};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move diagonally top right many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first + 1, to_add.second + 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move right many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first, to_add.second + 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move diagonally bottom right many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first - 1, to_add.second + 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move down many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first - 1, to_add.second};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move diagonally bottom left many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first - 1, to_add.second - 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move left many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first, to_add.second - 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move diagonally top left many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first + 1, to_add.second - 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        return move_to_list;
    }

    // Returns all possible squares the queen can move to.
    vector<vector<pair<int, int>>> allMoveCheck()
    {
        pair<int, int> to_add;
        vector<vector<pair<int, int>>> move_to_list;

        // Move up many spaces.
        vector<pair<int, int>> up;
        to_add = {location().first + 1, location().second};
        while (checkBounds(to_add))
        {
            up.push_back(to_add);
            to_add = {to_add.first + 1, to_add.second};
        }
        move_to_list.push_back(up);

        // Move diagonally top right many spaces.
        vector<pair<int, int>> diag_top_right;
        to_add = {location().first + 1, location().second + 1};
        while (checkBounds(to_add))
        {
            diag_top_right.push_back(to_add);
            to_add = {to_add.first + 1, to_add.second + 1};
        }
        move_to_list.push_back(diag_top_right);

        // Move right many spaces.
        vector<pair<int, int>> right;
        to_add = {location().first, location().second + 1};
        while (checkBounds(to_add))
        {
            right.push_back(to_add);
            to_add = {to_add.first, to_add.second + 1};
        }
        move_to_list.push_back(right);

        // Move diagonally bottom right many spaces.
        vector<pair<int, int>> diag_bottom_right;
        to_add = {location().first - 1, location().second + 1};
        while (checkBounds(to_add))
        {
            diag_bottom_right.push_back(to_add);
            to_add = {to_add.first - 1, to_add.second + 1};
        }
        move_to_list.push_back(diag_bottom_right);

        // Move down many spaces.
        vector<pair<int, int>> down;
        to_add = {location().first - 1, location().second};
        while (checkBounds(to_add))
        {
            down.push_back(to_add);
            to_add = {to_add.first - 1, to_add.second};
        }
        move_to_list.push_back(down);

        // Move diagonally bottom left many spaces.
        vector<pair<int, int>> diag_bottom_left;
        to_add = {location().first - 1, location().second - 1};
        while (checkBounds(to_add))
        {
            diag_bottom_left.push_back(to_add);
            to_add = {to_add.first - 1, to_add.second - 1};
        }
        move_to_list.push_back(diag_bottom_left);

        // Move left many spaces.
        vector<pair<int, int>> left;
        to_add = {location().first, location().second - 1};
        while (checkBounds(to_add))
        {
            left.push_back(to_add);
            to_add = {to_add.first, to_add.second - 1};
        }
        move_to_list.push_back(left);

        // Move diagonally top left many spaces.
        vector<pair<int, int>> diag_top_left;
        to_add = {location().first + 1, location().second - 1};
        while (checkBounds(to_add))
        {
            diag_top_left.push_back(to_add);
            to_add = {to_add.first + 1, to_add.second - 1};
        }
        move_to_list.push_back(diag_top_left);

        return move_to_list;
    }
};

class Rook : public Piece
{
public:
    // Constructor.
    Rook(char color, pair<int, int> location) : Piece(color, ROOK, location) {}

    // Returns all squares between the rook's current square and the square being moved to.
    vector<pair<int, int>> moveCheck(pair<int, int> move_to)
    {
        pair<int, int> to_add;
        vector<pair<int, int>> move_to_list;

        // Move up many spaces.
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first + 1, to_add.second};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move right many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first, to_add.second + 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move down many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first - 1, to_add.second};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move left many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first, to_add.second - 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        return move_to_list;
    }

    // Returns all possible squares the rook can move to.
    vector<vector<pair<int, int>>> allMoveCheck()
    {
        pair<int, int> to_add;
        vector<vector<pair<int, int>>> move_to_list;

        // Move up many spaces.
        vector<pair<int, int>> up;
        to_add = {location().first + 1, location().second};
        while (checkBounds(to_add))
        {
            up.push_back(to_add);
            to_add = {to_add.first + 1, to_add.second};
        }
        move_to_list.push_back(up);

        // Move right many spaces.
        vector<pair<int, int>> right;
        to_add = {location().first, location().second + 1};
        while (checkBounds(to_add))
        {
            right.push_back(to_add);
            to_add = {to_add.first, to_add.second + 1};
        }
        move_to_list.push_back(right);

        // Move down many spaces.
        vector<pair<int, int>> down;
        to_add = {location().first - 1, location().second};
        while (checkBounds(to_add))
        {
            down.push_back(to_add);
            to_add = {to_add.first - 1, to_add.second};
        }
        move_to_list.push_back(down);

        // Move left many spaces.
        vector<pair<int, int>> left;
        to_add = {location().first, location().second - 1};
        while (checkBounds(to_add))
        {
            left.push_back(to_add);
            to_add = {to_add.first, to_add.second - 1};
        }
        move_to_list.push_back(left);

        return move_to_list;
    }
};

class Bishop : public Piece
{
public:
    // Constructor.
    Bishop(char color, pair<int, int> location) : Piece(color, BISHOP, location) {}

    // Returns all squares between the bishop's current square and the square being moved to.
    vector<pair<int, int>> moveCheck(pair<int, int> move_to)
    {
        pair<int, int> to_add;
        vector<pair<int, int>> move_to_list;

        // Move diagonally top right many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first + 1, to_add.second + 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move diagonally bottom right many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first - 1, to_add.second + 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move diagonally bottom left many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first - 1, to_add.second - 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        // Move diagonally top left many spaces.
        move_to_list.clear();
        to_add = {location().first, location().second};
        while (checkBounds(to_add))
        {
            to_add = {to_add.first + 1, to_add.second - 1};
            move_to_list.push_back(to_add);

            if (to_add == move_to)
            {
                return move_to_list;
            }
        }

        return move_to_list;
    }

    // Returns all possible squares the bishop can move to.
    vector<vector<pair<int, int>>> allMoveCheck()
    {
        pair<int, int> to_add;
        vector<vector<pair<int, int>>> move_to_list;

        // Move diagonally top right many spaces.
        vector<pair<int, int>> diag_top_right;
        to_add = {location().first + 1, location().second + 1};
        while (checkBounds(to_add))
        {
            diag_top_right.push_back(to_add);
            to_add = {to_add.first + 1, to_add.second + 1};
        }
        move_to_list.push_back(diag_top_right);

        // Move diagonally bottom right many spaces.
        vector<pair<int, int>> diag_bottom_right;
        to_add = {location().first - 1, location().second + 1};
        while (checkBounds(to_add))
        {
            diag_bottom_right.push_back(to_add);
            to_add = {to_add.first - 1, to_add.second + 1};
        }
        move_to_list.push_back(diag_bottom_right);

        // Move diagonally bottom left many spaces.
        vector<pair<int, int>> diag_bottom_left;
        to_add = {location().first - 1, location().second - 1};
        while (checkBounds(to_add))
        {
            diag_bottom_left.push_back(to_add);
            to_add = {to_add.first - 1, to_add.second - 1};
        }
        move_to_list.push_back(diag_bottom_left);

        // Move diagonally top left many spaces.
        vector<pair<int, int>> diag_top_left;
        to_add = {location().first + 1, location().second - 1};
        while (checkBounds(to_add))
        {
            diag_top_left.push_back(to_add);
            to_add = {to_add.first + 1, to_add.second - 1};
        }
        move_to_list.push_back(diag_top_left);

        return move_to_list;
    }
};

class Knight : public Piece
{
public:
    // Constructor.
    Knight(char color, pair<int, int> location) : Piece(color, KNIGHT, location) {}

    // Returns all squares between the knight's current square and the square being moved to.
    vector<pair<int, int>> moveCheck(pair<int, int> move_to)
    {
        pair<int, int> to_add;
        vector<pair<int, int>> move_to_list;

        // Move up two, right one.
        to_add = {location().first + 2, location().second + 1};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move right two, up one.
        to_add = {location().first + 1, location().second + 2};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move right two, down one.
        to_add = {location().first - 1, location().second + 2};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move down two, right one.
        to_add = {location().first - 2, location().second + 1};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move down two, left one.
        to_add = {location().first - 2, location().second - 1};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move left two, down one.
        to_add = {location().first - 1, location().second - 2};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move left two, up one.
        to_add = {location().first + 1, location().second - 2};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        // Move up two, left one.
        to_add = {location().first + 2, location().second - 1};
        if (to_add == move_to)
        {
            move_to_list.push_back(to_add);
            return move_to_list;
        }

        return move_to_list;
    }

    // Returns all possible squares the knight can move to.
    vector<vector<pair<int, int>>> allMoveCheck()
    {
        pair<int, int> to_add;
        vector<pair<int, int>> move;
        vector<vector<pair<int, int>>> move_to_list;

        // Move up two, right one.
        to_add = {location().first + 2, location().second + 1};
        if (checkBounds(to_add))
        {
            move.push_back(to_add);
        }

        // Move right two, up one.
        to_add = {location().first + 1, location().second + 2};
        if (checkBounds(to_add))
        {
            move.push_back(to_add);
        }

        // Move right two, down one.
        to_add = {location().first - 1, location().second + 2};
        if (checkBounds(to_add))
        {
            move.push_back(to_add);
        }

        // Move down two, right one.
        to_add = {location().first - 2, location().second + 1};
        if (checkBounds(to_add))
        {
            move.push_back(to_add);
        }

        // Move down two, left one.
        to_add = {location().first - 2, location().second - 1};
        if (checkBounds(to_add))
        {
            move.push_back(to_add);
        }

        // Move left two, down one.
        to_add = {location().first - 1, location().second - 2};
        if (checkBounds(to_add))
        {
            move.push_back(to_add);
        }

        // Move left two, up one.
        to_add = {location().first + 1, location().second - 2};
        if (checkBounds(to_add))
        {
            move.push_back(to_add);
        }

        // Move up two, left one.
        to_add = {location().first + 2, location().second - 1};
        if (checkBounds(to_add))
        {
            move.push_back(to_add);
        }

        move_to_list.push_back(move);

        return move_to_list;
    }
};

class Pawn : public Piece
{
public:
    // Constructor.
    Pawn(char color, pair<int, int> location) : Piece(color, PAWN, location) {}

    // Returns all squares between the pawn's current square and the square being moved to.
    vector<pair<int, int>> moveCheck(pair<int, int> move_to)
    {
        pair<int, int> to_add;
        vector<pair<int, int>> move_to_list;

        // Piece is white
        if (color() == WHITE)
        {
            // Move up one space.
            to_add = {location().first + 1, location().second};
            move_to_list.push_back(to_add);
            if (to_add == move_to)
            {
                return move_to_list;
            }

            // Move up two spaces if at initial location.
            if (location().first == 1)
            {
                to_add = {location().first + 2, location().second};
                if (to_add == move_to)
                {
                    move_to_list.push_back(to_add);
                    return move_to_list;
                }
            }

            move_to_list.clear();

            // Move diagonally top right if capturing a piece.
            to_add = {location().first + 1, location().second + 1};
            if (to_add == move_to)
            {
                move_to_list.push_back(to_add);
                return move_to_list;
            }

            // Move diagonally top left if capturing a piece.
            to_add = {location().first + 1, location().second - 1};
            if (to_add == move_to)
            {
                move_to_list.push_back(to_add);
                return move_to_list;
            }
        }

        // Piece is black
        else
        {
            // Move down one space.
            to_add = {location().first - 1, location().second};
            move_to_list.push_back(to_add);
            if (to_add == move_to)
            {
                return move_to_list;
            }

            // Move down two spaces if at initial location.
            if (location().first == 6)
            {
                to_add = {location().first - 2, location().second};
                if (to_add == move_to)
                {
                    move_to_list.push_back(to_add);
                    return move_to_list;
                }
            }

            move_to_list.clear();

            // Move diagonally bottom right if capturing a piece.
            to_add = {location().first - 1, location().second + 1};
            if (to_add == move_to)
            {
                move_to_list.push_back(to_add);
                return move_to_list;
            }

            // Move diagonally bottom left if capturing a piece.
            to_add = {location().first - 1, location().second - 1};
            if (to_add == move_to)
            {
                move_to_list.push_back(to_add);
                return move_to_list;
            }
        }

        return move_to_list;
    }

    // Returns all possible squares the pawn can move to.
    vector<vector<pair<int, int>>> allMoveCheck()
    {
        pair<int, int> to_add;
        vector<vector<pair<int, int>>> move_to_list;

        // Piece is white.
        if (color() == WHITE)
        {
            // Move up one space.
            to_add = {location().first + 1, location().second};
            vector<pair<int, int>> up;
            if (checkBounds(to_add))
            {
                up.push_back(to_add);
            }

            // Move up two spaces if at initial location.
            if (location().first == 1)
            {
                to_add = {location().first + 2, location().second};
                up.push_back(to_add);
            }

            move_to_list.push_back(up);

            // Move diagonally top right if capturing a piece.
            to_add = {location().first + 1, location().second + 1};
            if (checkBounds(to_add))
            {
                vector<pair<int, int>> diag_top_right;
                diag_top_right.push_back(to_add);
                move_to_list.push_back(diag_top_right);
            }

            // Move diagonally top left if capturing a piece.
            to_add = {location().first + 1, location().second - 1};
            if (checkBounds(to_add))
            {
                vector<pair<int, int>> diag_top_left;
                diag_top_left.push_back(to_add);
                move_to_list.push_back(diag_top_left);
            }
        }

        // Piece is black.
        else
        {
            // Move down one space.
            to_add = {location().first - 1, location().second};
            vector<pair<int, int>> down;
            if (checkBounds(to_add))
            {
                down.push_back(to_add);
            }

            // Move down two spaces if at initial location.
            if (location().first == 6)
            {
                to_add = {location().first - 2, location().second};
                down.push_back(to_add);
            }

            move_to_list.push_back(down);

            // Move diagonally bottom right if capturing a piece.
            to_add = {location().first - 1, location().second + 1};
            if (checkBounds(to_add))
            {
                vector<pair<int, int>> diag_top_right;
                diag_top_right.push_back(to_add);
                move_to_list.push_back(diag_top_right);
            }

            // Move diagonally bottom left if capturing a piece.
            to_add = {location().first - 1, location().second - 1};
            if (checkBounds(to_add))
            {
                vector<pair<int, int>> diag_top_left;
                diag_top_left.push_back(to_add);
                move_to_list.push_back(diag_top_left);
            }
        }

        return move_to_list;
    }
};

// Operator overload for comparing two pieces.
inline bool operator==(const Piece *lhs, const Piece &rhs)
{
    return lhs->fullName() == rhs.fullName() && lhs->location() == rhs.location();
}

// Return true if location is within 8x8 grid of chess board.
inline bool checkBounds(pair<int, int> location)
{
    return location.first >= 0 && location.second >= 0 && location.first <= 7 && location.second <= 7;
}

#endif // PIECE_H