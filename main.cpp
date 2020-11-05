#include <iostream>
#include "lib/func.hpp"
using namespace std;

int main(void) {
    TwoDimShape my_std_board_shape = {8,8};
    TwoDimBoard my_std_board(my_std_board_shape);
    ChessGame my_game(2); // two players
    my_game.addBoard(my_std_board);
    Player *mati = my_game.addPlayer("Mati");
    Player *mai = my_game.addPlayer("Maia");

    my_game.startGame();
}

