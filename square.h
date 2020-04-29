#ifndef SQUARE_H
#define SQUARE_H

// An individual square on the chess board.
//
// Is either occupied or not occupied by a piece.
class Square
{
private:
    // Attributes.
    bool _occupied; // True if the square if occupied.
    Piece *_piece;  // Pointer to a piece occupying the square.

public:
    // Constructors.
    Square() : _occupied(false), _piece(NULL) {} // Default constructor.
    Square(const Square &s) : _occupied(s._occupied), _piece(s._piece) {}

    // Getters.
    bool occupied() const { return _occupied; } // Return occupied bool of square.
    Piece *piece() const { return _piece; }     // Return piece pointer occupying square.

    // Remove a piece from the square.
    //
    // Doesn't go through the effort of actually making it point to an empty piece or something.
    // We don't need to do anything beyong indicate that it's not occupied.
    void remove_piece()
    {
        _occupied = false;
    }

    // Sets the location of a piece to the location of this square on the board, renders it
    // occupied, and points to the piece.
    void set_piece(Piece *piece, pair<int, int> location)
    {
        _occupied = true;
        _piece = piece;
        _piece->move(location);
    }
};

#endif // SQUARE_H