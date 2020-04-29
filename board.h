#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "square.h"

// The actual chess board.
//
// A board contains 8 rows and 8 columns of squares.
// A square can either be occupied or not occupied by a piece.
// A board also keeps track of all the uncaptured white pieces,
// uncaptured black pieces, captured white pieces, and captured black pieces.
class Board
{
private:
    // Attributes.
    int _rows;                       // There are 8 rows on a chess board.
    int _cols;                       // There are 8 columns on a chess board.
    vector<vector<Square>> _squares; // An individual square on the board.
    vector<Piece *> _white;          // All white pieces currently on the board.
    vector<Piece *> _black;          // All black pieces currently on the board.
    vector<char> _white_captured;    // Names of all white pieces that have been captured by black.
    vector<char> _black_captured;    // Names of all black pieces that have been captured by white.

public:
    // Constructor and destructor.
    Board();  // Default constructor.
    ~Board(); // Default destructor.

    // These initializers are called by the board's default constructor.
    void init_pieces(); // Initialize the pieces by creating all the initial chess pieces and adding them to _white and _black.
    void init_board();  // Initialize the board by linking each initial square to its matching piece.

    // Print functions.
    void print_board(ostream &out) const;    // Print the board and its contents in a readable format.
    void print_active(ostream &out) const;   // Print a list of the active pieces for both white and black.
    void print_captured(ostream &out) const; // Print a list of the captured pieces for both white and black.

    // Getter functions..
    int rows() const { return _rows; }    // Retrieve the integer value for rows that this board holds.
    int columns() const { return _cols; } // Retrieve the integer value for columns that this board holds.

    // Play functions.
    void play_human(); // Play a game of chess between two human players locally.
    void play_ai();    // Play a game of chess between a human player and AI locally.

    // Other functions.
    int move(char color, string first, string second);                                         // Attempt to move a chess piece from one location to another. Return -1 if fail, 0 if good, 1 if check, 2 if checkmate, 3 if stalemate.
    bool is_suicide(Piece *move_from_piece, Piece *move_to_piece, pair<int, int> move_to_loc); // Check if the player's king is vulnerable. Return true if vulnerable.
    bool is_checkmate(char color);                                                             // Check if the player is in checkmate. Return true if in checkmate.
    int is_check(Piece *move_from_piece);                                                      // Check if the player is in check. Return 0 if good, 1 if check, 2 if checkmate, 3 if stalemate.
};

void pressEnterToContinue();                   // Pauses the game until the player presses the ENTER key on their keyboard.
bool checkMoveCoords(char first, char second); // Checks to see if the coordinates given are within the boundaries of the 8x8 chess board.

#endif // BOARD_H