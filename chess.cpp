// Tanner Sundwall, 2/22/19, CS410P, HW4: Chess
//
// chess.cpp
//
// The goal of this project is to create a program that utilizes what I've learned
// from this course.
//
// My project in particular is a functional chess game playable from within
// the command console.
//
// Features that made it:
//      * All unique movesets of all 6 types of pieces.
//      * Actual win condition of chess: not capturing the king, but checkmate.
//      * Notify player of check.
//      * Allow players to forfeit or draw.
//      * Stalemate condition.
//      * Prevent player from moving king into a position to be captured.
//      * Tracker for captured and uncaptured pieces.
//      * Navigatable command-based menus.
//      * Other stuff.
//
// Features that didn't make it:
//      * Special moves: castling, pawn promotion, or en passant.
//      * Draw conditions: threefold repetition, fifty-move rule.
//      * AI
//      * Non-broken input parser. The current method in which input is parsed is very easy to segfault.

#include "board.h"
#include <iostream>
using namespace std;

bool checkOptionSelected(int option, int optionCount);
void printInstructions();
void printPieceInfo();

int main(int argc, char** argv)
{
    // This is the entire chess game's loop. It can only be stopped by inputting
    // the option for "Exit" from the main menu.
    //
    // Due to everything in here using cin >> ..., it's rather easy to break. Sorry about that.
    for(;;)
    {
        int option = 0;         // Option selected by the user.
        int optionCount = 0;    // Number of options available for user to select.

        // Main menu loop.
        do
        {
            optionCount = 0;

            cout << "\nWelcome to Tanner's console-based chess game!\n"
                 << "Please input a number to select an option below:\n"
                 << "  " << ++optionCount << ". Play against human\n"
                 << "  " << ++optionCount << ". Play against AI\n"
                 << "  " << ++optionCount << ". Instructions\n"
                 << "  " << ++optionCount << ". Exit\n"
                 << "  : ";
            cin >> option;
            cin.ignore();

            // Exit chess program.
            if(option == optionCount)
            {
                return 0;
            }

        } while(!checkOptionSelected(option, optionCount));

        // Play chess against a human.
        if(option == 1)
        {
            Board board;
            board.play_human();
        }

        // Play chess against AI.
        else if(option == 2)
        {
            Board board;
            board.play_ai();
        }

        // Print chess instructions.
        else if(option == 3)
        {
            printInstructions();
        }

    }
}

// Ensures that the user inputs an option within the range of options available.
bool checkOptionSelected(int option, int optionCount)
{
    if(option > 0 && option < optionCount)
    {
        return true;
    }

    cout << "\nInvalid user input. Please input a number between 1 and " << optionCount << " next time." << endl;
    pressEnterToContinue();
    return false;
}

// Print chess instructions.
void printInstructions()
{
    int option = 0;
    int optionCount = 0;

    // Main loop for instructions menu.
    // Will loop forever until user inputs command for "Exit".
    for(;;)
    {
        do
        {
            optionCount = 0;

            cout << "\nWhat would you like to know about this chess game?\n"
                 << "Please input a number to select an option below:\n"
                 << "  " << ++optionCount << ". The Pieces\n"
                 << "  " << ++optionCount << ". How to Play\n"
                 << "  " << ++optionCount << ". Exit\n"
                 << "  : ";
            cin >> option;
            cin.ignore();

            // Exit printInstructions function
            if(option == optionCount)
            {
                return;
            }
        } while(!checkOptionSelected(option, optionCount));

        // Bring us to menu for displaying info about each chess piece.
        if(option == 1)
        {
            printPieceInfo();

        }

        // Print directions regarding how to actually play this chess game.
        else if(option == 2)
        {
            cout << "\nTwo players will take turns moving their pieces.\n"
                 << "The game will indicate whose turn (white or black) it is.\n"
                 << "The player whose turn it is will need to input the location\n"
                 << "of the piece they want to move, and then the location they\n"
                 << "want to move it to.\n"
                 << "For example:\n"
                 << "  It's white's turn to move.\n"
                 << "  White wants to move a pawn located at d2 to d4.\n"
                 << "  White needs to input: d2 d4\n"
                 << "  If the move is valid, the board will be printed again\n"
                 << "  with that pawn now located at d4 rather than d2.\n";
            pressEnterToContinue();
        }
    }
}

// Print piece info.
void printPieceInfo()
{
    int option = 0;
    int optionCount = 0;

    // Main loop for piece info menu.
    // Will loop forever like the other menus until the user inputs command for "Exit".
    for(;;)
    {
        do
        {
            optionCount = 0;

            cout << "\nWhich chess piece would you like to know more about?\n"
                 << "Please input a number to select an option below:\n"
                 << "  " << ++optionCount << ". The King\n"
                 << "  " << ++optionCount << ". The Queen\n"
                 << "  " << ++optionCount << ". The Rooks\n"
                 << "  " << ++optionCount << ". The Bishops\n"
                 << "  " << ++optionCount << ". The Knights\n"
                 << "  " << ++optionCount << ". The Pawns\n"
                 << "  " << ++optionCount << ". Exit\n"
                 << "  : ";
            cin >> option;
            cin.ignore();

            // Exit printPieceInfo function
            if(option == optionCount)
            {
                return;
            }
            
        } while(!checkOptionSelected(option, optionCount));

        // Print info about King.
        if(option == 1)
        {
            cout << "\nThe King\n"
                 << "The most important piece in the game of chess.\n"
                 << "If this piece is put in checkmate (put in a situation\n"
                 << "where capture is unavoidable), the owner loses the game.\n"
                 << "Moves exactly one vacant square in any direction." << endl;
            pressEnterToContinue();
        }

        // Print info about Queen.
        else if(option == 2)
        {
            cout << "\nThe Queen\n"
                 << "Moves any number of vacant squares in any direction." << endl;
            pressEnterToContinue();
        }

        // Print info about Rook.
        else if(option == 3)
        {
            cout << "\nThe Rooks\n"
                 << "Move any number of vacant squares forwards, backwards,\n"
                 << "left, or right in a straight line." << endl;
            pressEnterToContinue();
        }

        // Print info about Bishop.
        else if(option == 4)
        {
            cout << "\nThe Bishops\n"
                 << "Move any number of vacant squares diagonally in a straight line." << endl;
            pressEnterToContinue();
        }

        // Print info about Knight.
        else if(option == 5)
        {
            cout << "\nThe Knights\n"
                 << "Move on an extended diagonal from one corner of any 2x3 rectangle\n"
                 << "of squares to the furthest opposite corner." << endl;
            pressEnterToContinue();
        }

        // Print info about Pawn.
        else if(option == 6)
        {
            cout << "\nThe Pawns\n"
                 << "Move forward exactly one space, or two spaces when on their starting\n"
                 << "square. Can only capture the opponent's pieces one space forward to the\n"
                 << "left or right diagonally." << endl;
            pressEnterToContinue();
        }
    }
}