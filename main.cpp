#include <iostream>
#include "lib/func.hpp"
using namespace std;

int main(void) {
    int mode;
    clearScreen();
    cout << "Welcome to chess++" << endl << endl;
    cout << "Game modes available: " << endl;
    cout << "\t1 : Standard mode" << endl;
    cout << "\t2 : Baby mode (5x5 board)" << endl;
    cout << "\t3 : Two kings mode" << endl;
    cout << "\t4 : Three players mode" << endl;
    cout << "\t5 : Kill queen mode (you lose when your queen is killed)" << endl;
    cout << "Choose game mode: ";
    cin >> mode;

    if(mode == 1){ // Standard move
        TwoDimShape my_std_board_shape = {8,8};
        TwoDimBoard my_std_board(my_std_board_shape);
        ChessGame my_game(CondToWin::KillKing);
        my_game.addBoard(my_std_board);
        my_game.addPlayer("Garry");
        my_game.addPlayer("Carlsen");
        my_game.setCondToWin(CondToWin::KillKing);
        my_game.startGame(PiecesOrderStyle::Standard);
    } else if(mode == 2){ // Baby mode
        TwoDimShape my_std_board_shape = {5,5};
        TwoDimBoard my_std_board(my_std_board_shape);
        ChessGame my_game(CondToWin::KillKing);
        my_game.addBoard(my_std_board);
        my_game.addPlayer("Garry");
        my_game.addPlayer("Carlsen");
        my_game.setCondToWin(CondToWin::KillKing);
        my_game.startGame(PiecesOrderStyle::Baby);
    } else if(mode == 3){ // Two kings mode
        TwoDimShape my_std_board_shape = {8,8};
        TwoDimBoard my_std_board(my_std_board_shape);
        ChessGame my_game(CondToWin::KillKing);
        my_game.addBoard(my_std_board);
        my_game.addPlayer("Garry");
        my_game.addPlayer("Carlsen");
        my_game.setCondToWin(CondToWin::KillKing);
        my_game.startGame(PiecesOrderStyle::TwoKings);
    } else if(mode == 4){ // Three players mode
        TwoDimShape my_std_board_shape = {10,10};
        TwoDimBoard my_std_board(my_std_board_shape);
        ChessGame my_game(CondToWin::KillKing);
        my_game.addBoard(my_std_board);
        my_game.addPlayer("Garry");
        my_game.addPlayer("Carlsen");
        my_game.addPlayer("Beth");
        my_game.setCondToWin(CondToWin::KillKing);
        my_game.startGame(PiecesOrderStyle::ThreePlayerVariation);
    } else if(mode == 5){ // Kill queen mode
        TwoDimShape my_std_board_shape = {8,8};
        TwoDimBoard my_std_board(my_std_board_shape);
        ChessGame my_game(CondToWin::KillKing);
        my_game.addBoard(my_std_board);
        my_game.addPlayer("Garry");
        my_game.addPlayer("Carlsen");
        my_game.setCondToWin(CondToWin::KillQueen);
        my_game.startGame(PiecesOrderStyle::Standard);
    } else {
        cout << "Invalid game mode" << endl;
    }
}

