# ASCII-Chess
[![license](http://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Sundwalltanner/Ascii-Chess/blob/master/LICENSE)

I made this during my Junior year at Portland State University as a final project in a C++ course. It's a terminal-based chess game with support for everything you'd expect in a chess game except for AI, pawn promotions, castling, and en passant.

I didn't originally have a Github repository for this, so any commits made to this repository were done long after the project was finished and turned in for the course it was made for. I also wrote this README up long after finishing the project, so I could be wrong about some of the things written below.

## Why?
We were given the difficult task of making literally anything in C++. I tend to pick game-based projects, so I chose to make chess. I honestly didn't think it would be all that difficult when I submitted my original project proposal. I was wrong.

## Difficulty in making chess
I don't play chess all that often, so I forgot that the win-conditions for chess were a little more difficult than ```capture the enemy's king```. Instead, you end up with two basic game-ending conditions, a ```Checkmate``` and a ```Stalemate```.

* ```Checkmate``` means that a king is under direct threat from an opposing piece, and cannot make a move which will save their king. The player who has the other player's king in checkmate is declared the winner.
* ```Stalemate``` means that a king isn't under direct threat from an opposing piece, but cannot make a move which won't put their king under direct threat from an opposing piece. This ends in a draw, which is strange, but whatever. I didn't write the rules for chess.

This means that I had to write significantly more code than I'd originally planned, which means that the single weekend I'd given myself to work on this project was pretty rough, and I'll never be making that mistake again.

The basic logic for moving a piece goes like this:

1. Is that location even on the board?
2. Is there even a piece at that location?
3. Is it your piece?
4. Is this a legal move for this particular piece?
    * Can the piece be moved like this? Is it a pawn on its starting square trying to move forward two spaces? etc...
    * Is there a piece in between this piece and the location it wants to move to? It can't do that.
5. Does moving that piece put your king in check?
6. Does moving that piece put the opponent in check?

And then if somebody is in check, you have to go through the entire logic of checking to see whether they're just in check or if they're in checkmate. A whole lot of this logic relies on going through every single possible move that every single piece on the board can make, taking into account potential captures that can be made. All of this was very difficult to wrap my head around. I'm sure there's a better way to write a chess game. This is the type of game playable on incredibly hardware-restricted devices. I'll bet I just made the least optimized version of chess.

## How to run
1. Clone the repository: https://github.com/Sundwalltanner/Ascii-Chess
2. Open it up in your favorite terminal.
3. Type and enter ```make```.
4. Once the Makefile is done doing its thing and everything's compiled, execute it.
    * In Windows, this means type and enter ```./chess.exe```
    * If you're using another OS, you probably know what your version of an executable is.

## How to play
The actual directions for how to play chess in general are included in-game. I made the text-based commands based on how I wanted to play chess though, so they're not all that standard.

Basically, this is what the game should look like in your terminal:

![Chess tutorial image #1](https://i.imgur.com/GYG7nGS.png)

In the image above, I've entered ```a2 a4```. This means that I want to move the white's leftmost pawn forward two spaces.

![Chess tutorial image #2](https://i.imgur.com/wi67VVp.png)

Success! As you can see in the image above. The white's leftmost pawn was successfully moved forward two spaces, and it's now black's turn.

It's that easy to play. The game won't let you make incorrect moves based on the rules of chess, so you should probably know the basics of chess.

## What needs to be worked on?
* As I mentioned, it's missing some essential chess features like pawn promotions, castling, and en passant.
* AI. Currently, the game only supports local play between two humans. Even some rudimentary opponent that makes random valid moves would be better than this.