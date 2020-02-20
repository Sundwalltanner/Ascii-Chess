
all:
	g++ board.cpp chess.cpp -std=c++1z -o chess

debug:
	g++ board.cpp chess.cpp -std=c++1z -o chess -g
