#include "board.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

// Default constructor for chess board.
//
// A chess board contains 8x8 squares.
// Also initializes the pieces and the squares containing those pieces to their default values.
Board::Board() : _rows(8), _cols(8), _squares(8, vector<Square>(8, Square()))
{
    init_pieces();
    init_board();
}

// Default destructor for chess board.
//
// Due to the board containing two vectors of pointers to white and black pieces, we need to delete
// them or Valgrind will be upset.
Board::~Board()
{
    // Travel through all white pieces and delete them all.
    for(auto it = _white.begin(); it != _white.end(); ++it)
    {
        delete *it;
    }

    // Travel through all black pieces and delete them all.
    for(auto it = _black.begin(); it != _black.end(); ++it)
    {
        delete *it;
    }
}

// Initializes the chess pieces by creating the amount that exists for each type in a standard game of chess.
void Board::init_pieces()
{
    int i = 0;

    _white.push_back(new Rook(WHITE, {0, i}));      _black.push_back(new Rook(BLACK, {7, i++}));
    _white.push_back(new Knight(WHITE, {0, i}));    _black.push_back(new Knight(BLACK, {7, i++}));
    _white.push_back(new Bishop(WHITE, {0, i}));    _black.push_back(new Bishop(BLACK, {7, i++}));
    _white.push_back(new Queen(WHITE, {0, i}));     _black.push_back(new Queen(BLACK, {7, i++}));
    _white.push_back(new King(WHITE, {0, i}));      _black.push_back(new King(BLACK, {7, i++}));
    _white.push_back(new Bishop(WHITE, {0, i}));    _black.push_back(new Bishop(BLACK, {7, i++}));
    _white.push_back(new Knight(WHITE, {0, i}));    _black.push_back(new Knight(BLACK, {7, i++}));
    _white.push_back(new Rook(WHITE, {0, i}));      _black.push_back(new Rook(BLACK, {7, i++}));

    for(i = 0; i < _cols; i++)
    {
        _white.push_back(new Pawn(WHITE, {1, i}));  _black.push_back(new Pawn(BLACK, {6, i}));
    }
}

// Initializes the board by placing the white and black pieces in their respective starting locations.
void Board::init_board()
{
    for(int c = 0; c < _cols; c++)
    {
        _squares[0][c].set_piece(_white[c], {0, c});
        _squares[1][c].set_piece(_white[c + _cols], {1, c});
        _squares[7][c].set_piece(_black[c], {7, c});
        _squares[6][c].set_piece(_black[c + _cols], {6, c});
    }
}

// Prints the contents of the board in its current state.
void Board::print_board(ostream& out) const
{
    /* This is how a new board should look when printed to the console.
    out << "  _______________________________________\n"
        << " |    |    |    |    |    |    |    |    |\n"
        << "8| BR | BN | BB | BQ | BK | BB | BN | BR |\n"
        << " |____|____|____|____|____|____|____|____|\n"
        << " |    |    |    |    |    |    |    |    |\n"
        << "7| BP | BP | BP | BP | BP | BP | BP | BP |\n"
        << " |____|____|____|____|____|____|____|____|\n"
        << " |    |    |    |    |    |    |    |    |\n"
        << "6|    |    |    |    |    |    |    |    |\n"
        << " |____|____|____|____|____|____|____|____|\n"
        << " |    |    |    |    |    |    |    |    |\n"
        << "5|    |    |    |    |    |    |    |    |\n"
        << " |____|____|____|____|____|____|____|____|\n"
        << " |    |    |    |    |    |    |    |    |\n"
        << "4|    |    |    |    |    |    |    |    |\n"
        << " |____|____|____|____|____|____|____|____|\n"
        << " |    |    |    |    |    |    |    |    |\n"
        << "3|    |    |    |    |    |    |    |    |\n"
        << " |____|____|____|____|____|____|____|____|\n"
        << " |    |    |    |    |    |    |    |    |\n"
        << "2| WP | WP | WP | WP | WP | WP | WP | WP |\n"
        << " |____|____|____|____|____|____|____|____|\n"
        << " |    |    |    |    |    |    |    |    |\n"
        << "1| WR | WN | WB | WQ | WK | WB | WN | WR |\n"
        << " |____|____|____|____|____|____|____|____|\n"
        << "   a    b    c    d    e    f    g    h" << endl;
    */

    // Print the top border.
    out << "  _______________________________________" << endl;

    // Print everything but the bottom letter coords.
    for(int r = _rows - 1; r >= 0; r--)
    {
        // Print the upper empty space of the squares and the number coordinate associated with that row.
        out << " |    |    |    |    |    |    |    |    |\n"
            << r + 1 << "|";

        // Print the names of the pieces in the squares of this row.
        for(int c = 0; c < _cols; c++)
        {
            out << " ";

            // If this square contains a piece, print its color and name.
            if(_squares[r][c].occupied())
            {
                out << _squares[r][c].piece()->fullName();
            }

            // If this square doesn't contain a piece, print two blank spaces.
            else
            {
                out << "  ";
            }

            out << " |";
        }

        // Print the bottom portion of each square.
        out << "\n"
            << " |____|____|____|____|____|____|____|____|" << endl;
    }

    // Print the bottom letter coordinates.
    out << "   a    b    c    d    e    f    g    h" << endl;
}

// Prints a list of the pieces that are still on the board for both white and black.
void Board::print_active(ostream& out) const
{
    out << "\nWhite Active: " << endl;
    for(auto it = _white.begin(); it != _white.end(); ++it)
    {
        out << (*it)->name() << " ";
    }

    out << "\n";

    out << "\nBlack Active: " << endl;
    for(auto it = _black.begin(); it != _black.end(); ++it)
    {
        out << (*it)->name() << " ";
    }

    out << "\n";
}

// Prints a list of the pieces captured by both white and black.
void Board::print_captured(ostream& out) const
{
    out << "\nCaptured by White: " << endl;
    for(auto it = _black_captured.begin(); it != _black_captured.end(); ++it)
    {
        out << *it << " ";
    }

    out << "\n";

    out << "\nCaptured by Black: " << endl;
    for(auto it = _white_captured.begin(); it != _white_captured.end(); ++it)
    {
        out << *it << " ";
    }

    out << "\n";
}

// Play a game of chess between two human players locally.
void Board::play_human()
{
    string command;                 // Entire line inputted by user as a command. Parsed for max of two potential separate strings later.
    string turn_color = "White";    // Color whose turn it currently is.
    string off_color = "Black";     // Color whose turn is next.
    bool draw_agree = false;        // True if one player attempts to declare a draw.

    // Main game loop.
    //
    // This will loop forever unless one player quits, both players draw, or one player is put in checkmate and loses.
    for(;;)
    {
        print_board(cout);

        cout << "\nIt is " << turn_color << "'s turn.\n"
             << "Please input a command: ";
        getline(cin, command);
        transform(command.begin(), command.end(), command.begin(), ::tolower);
        istringstream iss(command);
        vector<string> commands{istream_iterator<string>{iss}, istream_iterator<string>{}};

        string first = commands[0];

        // Check if player whose turn it last was has attempted to declare a draw.
        if(draw_agree)
        {
            // Second player has agreed to a draw, and both players forfeit the game.
            if(first == "draw" || first == "stalemate" || first == "agree" || first == "yes" || first == "y")
            {
                cout << "\nBoth sides have agreed to a draw.\n"
                     << "Nobody wins." << endl;
                pressEnterToContinue();

                return;
            }

            // Second player has disagreed to a draw, and the first player proceeds their turn as if nothing happened.
            else
            {
                cout << "\n" << turn_color << " disagreed to a draw.\n"
                     << off_color << " will proceed their turn as normal." << endl;
                pressEnterToContinue();

                draw_agree = false;
                string temp = turn_color;
                turn_color = off_color;
                off_color = temp;

                continue;
            }
        }

        // Exit chess program
        if(first == "exit" || first == "quit" || first == "surrender" || first == "forfeit")
        {
            cout << "\n" << turn_color << " has given up.\n"
                 << off_color << " wins!" << endl;
            pressEnterToContinue();

            return;
        }

        // Print list of potential commands the user can input.
        else if(first == "?" || first == "help" || first == "instructions" || first == "guide" || first == "commands" || first == "info")
        {
            cout << "\nCommands List:\n"
                 << "  [letter][number] [letter][number]\n"
                 << "    -  Moves a piece from the first location to the second location.\n"
                 << "    -  Ex: If white has a pawn located at a2, they may input: a2 a4\n"
                 << "  ? / help / instructions / guide / commands / info\n"
                 << "    -  How'd you get here?\n"
                 << "  exit / quit / surrender / forfeit\n"
                 << "    -  Quit the game. Whoever's turn it is forfeits the match.\n"
                 << "  active / alive\n"
                 << "    -  Prints a list of the pieces that are still on the board for both white and black.\n"
                 << "  captured / dead\n"
                 << "    -  Prints a list of the pieces that have been captured by white and black.\n"
                 << "  draw / stalemate\n"
                 << "    -  Both players will need to enter this command on their turn in order to call a draw." << endl;
             pressEnterToContinue();
             continue;
        }

        // Print list of names of pieces currently on the board.
        else if(first == "active" || first == "alive")
        {
            print_active(cout);
            pressEnterToContinue();
            continue;
        }

        // Print list of names of pieces that have been captured.
        else if(first == "captured" || first == "dead")
        {
            print_captured(cout);
            pressEnterToContinue();
            continue;
        }

        // Declare a draw. If the other player draws during their next turn, the match ends and nobody wins.
        else if(first == "draw" || first == "stalemate")
        {
            draw_agree = true;

            cout << "\n" << turn_color << " has declared a draw.\n"
                 << "If " << off_color << " also declares a draw, the game will end in a draw." << endl;
            pressEnterToContinue();
        }

        // If the command is two sets of coordinates.
        else if(commands.size() > 1)
        {
            string second = commands[1];
            int move_result = move(toupper(turn_color[0]), first, second);

            // The piece was not moved for some reason.
            if(move_result == BAD)
            {
                continue;
            }

            // The enemy is in check and needs to secure their king.
            else if(move_result == CHECK)
            {
                print_board(cout);

                cout << "\n" << off_color << " is in check.\n"
                     << "Save your king!" << endl;
                pressEnterToContinue();
            }

            // The enemy is in checkmate and has lost the game.
            else if(move_result == CHECKMATE)
            {
                print_board(cout);

                cout << "\n" << off_color << " is in checkmate.\n"
                     << turn_color << " wins!" << endl;
                pressEnterToContinue();

                return;
            }

            // The enemy is in stalemate and nobody wins the game.
            else if(move_result == STALEMATE)
            {
                print_board(cout);

                cout << "\n" << off_color << " is in stalemate.\n"
                     << "Nobody wins." << endl;
                pressEnterToContinue();

                return;
            }
        }

        // Invalid command.
        else
        {
            cout << "\nInvalid command. Please input [?] without the brackets if you need help." << endl;
            pressEnterToContinue();

            continue;
        }

        // Necessary steps to take in order to change the turn order.
        string temp = turn_color;
        turn_color = off_color;
        off_color = temp;
    }
}

// Play a game of chess between a human player and AI locally.
void Board::play_ai()
{
    cout << "\nThis chess game is still in early access.\n"
                 << "This feature isn't yet available." << endl;
    pressEnterToContinue();
}

// Move a chess piece from one location to another.
int Board::move(char color, string first, string second)
{
    // Check that the coordinates given are within the boundaries of the 8x8 chess board.
    if(!checkMoveCoords(first[0], first[1]) || !checkMoveCoords(second[0], second[1]))
    {
        cout << "\nInvalid command. Please input [?] without the brackets if you need help." << endl;
        pressEnterToContinue();
        return BAD;
    }

    // Ascii math necessary to obtain the square at the [letter][number] coordinates given.
    Square *move_from = &_squares[first[1] - 49][first[0] - 97];

    // If the coordinates lead to a square that has no piece on it.
    if(!move_from->occupied())
    {
        cout << "\nThere is no piece on that square." << endl;
        pressEnterToContinue();
        return BAD;
    }

    // If the coordinates lead to a square that has an enemy piece on it.
    if(move_from->piece()->color() != color)
    {
        cout << "\nThat's not your piece." << endl;
        pressEnterToContinue();
        return BAD;
    }

    //
    // Anything past this assumes that the square given has one of the player's pieces on it.
    //

    pair<int, int> move_from_loc = {first[1] - 49, first[0] - 97};
    pair<int, int> move_to_loc = {second[1] - 49, second[0] - 97};
    vector<pair<int, int>> move_to_list = move_from->piece()->moveCheck(move_to_loc);

    // The last square in the list will be the square the player is attempting to move their piece to.
    // This checks to confirm that the player has made a valid choice based on the way in which that
    // particular piece can move according to the rules of chess.
    if(move_to_list.empty() || move_to_list.back() != move_to_loc)
    {
        cout << "\nThat piece's movement doesn't allow it to reach that square." << endl;
        pressEnterToContinue();
        return BAD;
    }

    // Checks the entire list of squares in the direction the piece is being moved to ensure that it
    // isn't being blocked by any other piece. Only the knight may move through other pieces. Although
    // pieces like the queen, rook, bishop, and pawn (at initial location) may move multiple spaces
    // in a direction, they may not pass through another piece. They'll have to choose the location of that
    // piece, and assuming it's an opponent's piece, capture it.
    for(auto it = move_to_list.begin(); it != move_to_list.end() - 1; ++it)
    {
        if(_squares[(*it).first][(*it).second].occupied())
        {
            cout << "\nThat piece is blocked from reaching that square." << endl;
            pressEnterToContinue();
            return BAD;
        }
    }

    Square *move_to = &_squares[move_to_loc.first][move_to_loc.second];

    // If the square the piece is trying to move to is occupied by another piece.
    if(move_to->occupied())
    {
        // If a pawn is being moved forward, that means it's not going to capture another piece.
        if(move_from->piece()->name() == PAWN && move_from->piece()->location().second == move_to_loc.second)
        {
            // If the pawn is trying to move to a square occupied by a friendly piece.
            if(move_to->piece()->color() == color)
            {
                cout << "\nThat piece is blocked from reaching that square." << endl;
                pressEnterToContinue();
                return BAD;
            }

            // If the pawn is trying to capture an enemy piece in front of it.
            // A pawn can only capture enemy pieces one space diagonal in front of them.
            cout << "\nA pawn can only capture another piece by moving forward diagonally one space." << endl;
            pressEnterToContinue();
            return BAD;
        }

        // If a piece is trying to capture a friendly piece.
        if(move_to->piece()->color() == color)
        {
            cout << "\nYou cannot capture your own piece." << endl;
            pressEnterToContinue();
            return BAD;
        }
        // If a piece is trying to capture an enemy piece.
        else
        {
            // This is an invalid move, because moving here would allow the enemy to capture
            // the player's king on their next turn.
            if(is_suicide(move_from->piece(), move_to->piece(), move_to_loc))
            {
                cout << "\nTrying to capture that piece would render your king vulnerable to capture." << endl;
                pressEnterToContinue();
                return BAD;
            }

            Piece move_to_piece = *move_to->piece();

            cout << "\n" << move_from->piece()->fullName() << " captured " << move_to->piece()->fullName() << endl;
            move_to->remove_piece();

            // If piece being captured is white.
            if(move_to->piece()->color() == WHITE)
            {
                // Because we're removing the piece from the list of pieces we have a destructor for, we need
                // to manually scrape it from the vector and delete it so Valgrind won't get mad.
                // We also push its name to a list of the names of pieces that have been captured.
                //
                _white_captured.push_back(move_to->piece()->name());
                auto to_remove = find(_white.begin(), _white.end(), move_to_piece);
                delete *to_remove;
                _white.erase(to_remove);
            }

            // If piece being captured is black.
            else
            {
                // Because we're removing the piece from the list of pieces we have a destructor for, we need
                // to manually scrape it from the vector and delete it so Valgrind won't get mad.
                // We also push its name to a list of the names of pieces that have been captured.
                //
                _black_captured.push_back(move_to->piece()->name());
                auto to_remove = find(_black.begin(), _black.end(), move_to_piece);
                delete *to_remove;
                _black.erase(to_remove);
            }
        }
    }

    // If the square the piece is trying to move to isn't occupied by another piece.
    else
    {
        // If a pawn is being moved to an empty square, it has to be in front of it.
        // A pawn can only be moved diagonally one space if the space is occupied by an enemy piece.
        if(move_from->piece()->name() == PAWN && move_from->piece()->location().second != move_to_loc.second)
        {
            cout << "\nA pawn can only capture another piece by moving forward diagonally one space." << endl;
            pressEnterToContinue();
            return BAD;
        }

        // This is an invalid move, because moving here would allow the enemy to capture
        // the player's king on their next turn.
        if(is_suicide(move_from->piece(), move_to->piece(), move_to_loc))
        {
            cout << "\nMoving that piece there would render your king vulnerable to capture." << endl;
            pressEnterToContinue();
            return BAD;
        }
    }

    // Set the new square to contain this piece.
    move_to->set_piece(move_from->piece(), move_to_loc);
    move_from->remove_piece();

    return is_check(move_to->piece());
}

// Check if the player's king is vulnerable. Return true if vulnerable.
bool Board::is_suicide(Piece * move_from_piece, Piece * move_to_piece, pair<int, int> move_to_loc)
{
    // Piece being moved is white.
    if(move_from_piece->color() == WHITE)
    {
        // Iterate through every black piece on the board.
        for(auto it = _black.begin(); it != _black.end(); ++it)
        {
            // If move_to_piece isn't NULL.
            //
            // It will be NULL when is_suicide() is called and there is no piece on the square being moved to.
            if(move_to_piece)
            {
                // Ensure that the piece being moved to isn't the one being captured, as a captured piece cannot move.
                if(*it == move_to_piece)
                {
                    continue;
                }
            }

            vector<vector<pair<int, int>>> all_move_to_list = (*it)->allMoveCheck(); // All possible squares the piece can move to.

            // Iterate through the coordinates of every square the piece can potentially move to.
            for(auto ita = all_move_to_list.begin(); ita != all_move_to_list.end(); ++ita)
            {
                for(auto itb = (*ita).begin(); itb != (*ita).end(); ++itb)
                {
                    pair<int, int> location = {(*itb).first, (*itb).second};        // Coordinates of the square being moved to.
                    Square *move_to = &_squares[location.first][location.second];   // Square being moved to.

                    // If square being moved to is the same square the original piece moved to.
                    // This needs to be checked for because this function can run before the board is updated, meaning
                    // the movement of isn't reflected by our data structures yet.
                    //
                    // This means this piece is capable of capturing the piece we just moved.
                    if(location == move_to_loc)
                    {
                        // If the piece is a pawn and it hasn't changed columns, it's trying to capture a piece
                        // without moving diagonally. Don't let it do that.
                        if((*it)->name() == PAWN && (*it)->location().second == location.second)
                        {
                            break;
                        }

                        // If the piece the player moved is a king, and this new piece is capable of capturing it.
                        if(move_from_piece->name() == KING)
                        {
                            return true;
                        }

                        break;
                    }

                    // As mentioned, because this function is called before a piece's movement is shown in our data structures,
                    // we need to check to make sure no piece is stopped by the location this piece won't be located at after the movement.
                    //
                    // If the location of our new piece is the same as the original location of the piece that might be moved, proceed. We can move through it.
                    if(location == move_from_piece->location())
                    {
                        continue;
                    }

                    // If the square being moved to is occupied.
                    if(move_to->occupied())
                    {
                        // Once again, we can't use a pawn to capture another piece unless we move diagonally.
                        if((*it)->name() == PAWN && (*it)->location().second == location.second)
                        {
                            break;
                        }

                        // If the piece that occupies this space is the enemy player's king.
                        if(move_to->piece()->fullName() == "WK")
                        {
                            return true;
                        }

                        break;
                    }
                }
            }
        }
    }

    // Piece being moved is black.
    else
    {
        // Iterate through every white piece on the board.
        for(auto it = _white.begin(); it != _white.end(); ++it)
        {
            // If move_to_piece isn't NULL.
            //
            // It will be NULL when is_suicide() is called and there is no piece on the square being moved to.
            if(move_to_piece)
            {
                // Ensure that the piece being moved to isn't the one being captured, as a captured piece cannot move.
                if(*it == move_to_piece)
                {
                    continue;
                }
            }

            vector<vector<pair<int, int>>> all_move_to_list = (*it)->allMoveCheck(); // All possible squares that piece can move to.

            // Iterate through the coordinates of every square the piece can potentially move to.
            for(auto ita = all_move_to_list.begin(); ita != all_move_to_list.end(); ++ita)
            {
                for(auto itb = (*ita).begin(); itb != (*ita).end(); ++itb)
                {
                    pair<int, int> location = {(*itb).first, (*itb).second};        // Coordinates of the square being moved to.
                    Square *move_to = &_squares[location.first][location.second];   // Square being moved to.

                    // If square being moved to is the same square the original piece moved to.
                    // This needs to be checked for because this function can run before the board is updated, meaning
                    // the movement of isn't reflected by our data structures yet.
                    if(location == move_to_loc)
                    {
                        // If the piece is a pawn and it hasn't changed columns, it's trying to capture a piece
                        // without moving diagonally. Don't let it do that.
                        if((*it)->name() == PAWN && (*it)->location().second == location.second)
                        {
                            break;
                        }

                        // If the piece the player moved is a king, and this new piece is capable of capturing it.
                        if(move_from_piece->name() == KING)
                        {
                            return true;
                        }

                        break;
                    }

                    // As mentioned, because this function is called before a piece's movement is shown in our data structures,
                    // we need to check to make sure no piece is stopped by the location this piece won't be located at after the movement.
                    //
                    // If the location of our new piece is the same as the original location of the piece that might be moved, proceed. We can move through it.
                    if(location == move_from_piece->location())
                    {
                        continue;
                    }

                    // If the square being moved to is occupied.
                    if(move_to->occupied())
                    {
                        // Once again, we can't use a pawn to capture another piece unless we move diagonally.
                        if((*it)->name() == PAWN && (*it)->location().second == location.second)
                        {
                            break;
                        }

                        // If the piece that occupies this space is the enemy player's king.
                        if(move_to->piece()->fullName() == "BK")
                        {
                            return true;
                        }

                        break;
                    }
                }
            }
        }
    }

    return false;
}

// Check if the color passed in is in checkmate by running through every single possible move that its
// available pieces can make to see if even a single one will ensure that their king cannot be captured
// by the enemy next turn.
bool Board::is_checkmate(char color)
{
    // Piece potentially in checkmate is white.
    if(color == BLACK)
    {
        // Iterate through every white piece on the board.
        for(auto it = _white.begin(); it != _white.end(); ++it)
        {
            vector<vector<pair<int, int>>> all_move_to_list = (*it)->allMoveCheck(); // A list of the potential squares a piece can move to.

            // Iterate through the coordinates of every potential square this piece can move to.
            for(auto ita = all_move_to_list.begin(); ita != all_move_to_list.end(); ++ita)
            {
                for(auto itb = (*ita).begin(); itb != (*ita).end(); ++itb)
                {
                    pair<int, int> location = {(*itb).first, (*itb).second};        // Location of square being moved to.
                    Square *move_to = &_squares[location.first][location.second];   // Square being moved to.

                    // If piece hits a square with another piece in it.
                    if(move_to->occupied())
                    {
                        // If piece hits a friendly piece, it can't move to that square or beyond it.
                        // Also checks if piece is a pawn and attempting to capture an enemy piece in front of it.
                        if(move_to->piece()->color() == WHITE || ((*it)->name() == PAWN && (*it)->location().second == location.second))
                        {
                            break;
                        }

                        // If piece hits an enemy piece, check for checkmate based on new piece's location, and the fact that particular
                        // enemy piece will be captured.
                        if(!is_suicide(*it, move_to->piece(), location))
                        {
                            return false;
                        }
                    }

                    // If piece hits an empty square.
                    else
                    {
                        // If piece is a pawn and attempting to move diagonally without capturing an enemy piece.
                        if((*it)->name() == PAWN && (*it)->location().second != location.second)
                        {
                            break;
                        }

                        // Check for checkmate based on new piece's location.
                        if(!is_suicide(*it, NULL, location))
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    // Piece potentially in checkmate is black.
    else
    {
        // Iterate through every black piece on the board.
        for(auto it = _black.begin(); it != _black.end(); ++it)
        {
            vector<vector<pair<int, int>>> all_move_to_list = (*it)->allMoveCheck(); // A list of the potential squares a piece can move to.

            // Iterate through the coordinates of every potential square this piece can move to.
            for(auto ita = all_move_to_list.begin(); ita != all_move_to_list.end(); ++ita)
            {
                for(auto itb = (*ita).begin(); itb != (*ita).end(); ++itb)
                {
                    pair<int, int> location = {(*itb).first, (*itb).second};        // Location of square being moved to.
                    Square *move_to = &_squares[location.first][location.second];   // Square being moved to.

                    // If piece hits a square with another piece in it.
                    if(move_to->occupied())
                    {
                        // If piece hits a friendly piece, it can't move to that square or beyond it.
                        // Also checks if piece is a pawn and attempting to capture an enemy piece in front of it.
                        if(move_to->piece()->color() == BLACK || ((*it)->name() == PAWN && (*it)->location().second == location.second))
                        {
                            break;
                        }

                        // If piece hits an enemy piece, check for checkmate based on new piece's location, and the fact that particular
                        // enemy piece will be captured.
                        if(!is_suicide(*it, move_to->piece(), location))
                        {
                            return false;
                        }
                    }
                    else
                    {
                        // If piece is a pawn and attempting to move diagonally without capturing an enemy piece.
                        if((*it)->name() == PAWN && (*it)->location().second != location.second)
                        {
                            break;
                        }

                        // Check for checkmate based on new piece's location.
                        if(!is_suicide(*it, NULL, location))
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

// Checks if the enemy is in check, checkmate, stalemate, or good.
//
// Returns 0 if good, 1 if check, 2 if checkmate, and 3 if stalemate.
int Board::is_check(Piece * move_from_piece)
{
    vector<vector<pair<int, int>>> check_list = move_from_piece->allMoveCheck();

    // If piece that was moved was white.
    if(move_from_piece->color() == WHITE)
    {
        for(auto it = check_list.begin(); it != check_list.end(); ++it)
        {
            for(auto ita = (*it).begin(); ita != (*it).end(); ++ita)
            {
                pair<int, int> location = {(*ita).first, (*ita).second};
                Square *move_to_square = &_squares[location.first][location.second];

                if(move_to_square->occupied())
                {
                    if(move_from_piece->name() == PAWN && move_from_piece->location().second == location.second)
                    {
                        break;
                    }

                    if(move_to_square->piece()->fullName() == "BK")
                    {
                        if(is_checkmate(WHITE))
                        {
                            return CHECKMATE;
                        }

                        return CHECK;
                    }

                    break;
                }
            }
        }
    }

    // If piece that was moved was black.
    else
    {
        for(auto it = check_list.begin(); it != check_list.end(); ++it)
        {
            for(auto ita = (*it).begin(); ita != (*it).end(); ++ita)
            {
                pair<int, int> location = {(*ita).first, (*ita).second};
                Square *move_to_square = &_squares[location.first][location.second];

                if(move_to_square->occupied())
                {
                    if(move_from_piece->name() == PAWN && move_from_piece->location().second == location.second)
                    {
                        break;
                    }

                    if(move_to_square->piece()->fullName() == "WK")
                    {
                        if(is_checkmate(BLACK))
                        {
                            return CHECKMATE;
                        }

                        return CHECK;
                    }

                    break;
                }
            }
        }
    }

    // If the enemy player isn't in check, but cannot make any valid moves, they are in stalemate,
    // and the game ends in a draw.
    if(is_checkmate(move_from_piece->color()))
    {
        return STALEMATE;
    }

    // The enemy player isn't in check, checkmate, or stalemate.
    return GOOD;
}

// Prompts the user to press ENTER to proceed.
// Usually happens because the user has been given some text to read, but no other input option to proceed, therefore
// we don't want to overwhelm the user with both the text from this message and the proceeding message.
void pressEnterToContinue()
{
    cout << "\nPress ENTER to continue";
    cin.get();
    cin.clear();
}

// Checks to see if the location we want to move a piece to is within the bounds of the chess board's 8x8 grid.
bool checkMoveCoords(char first, char second)
{
    if(first >= 'a' && first <= 'h' && second >= '1' && second <= '8')
    {
        return true;
    }

    return false;
}
