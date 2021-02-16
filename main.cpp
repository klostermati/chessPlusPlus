// Useless comment added
#include <iostream>
#include "lib/func.hpp"
using namespace std;

int main(void) {
    int mode;
    clearScreen();
    cout << "Welcome to chess++" << endl << endl;
    cout << "Example of chess notation used to indicate the position of a piece:" << endl;
    cout << "b3 means the position of the second column and third row" << endl << endl;
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
        my_game.addPlayer("Garry Kasparov");
        my_game.addPlayer("Magnus Carlsen");
        my_game.setCondToWin(CondToWin::KillKing);
        try{
            my_game.startGame(PiecesOrderStyle::Standard);
        } catch (runtime_error &e) {
            cout << e.what() << endl;
        }
    } else if(mode == 2){ // Baby mode
        TwoDimShape my_std_board_shape = {5,5};
        TwoDimBoard my_std_board(my_std_board_shape);
        ChessGame my_game(CondToWin::KillKing);
        my_game.addBoard(my_std_board);
        my_game.addPlayer("Garry Kasparov");
        my_game.addPlayer("Magnus Carlsen");
        my_game.setCondToWin(CondToWin::KillKing);
        try{
            my_game.startGame(PiecesOrderStyle::Baby);
        } catch (runtime_error &e) {
            cout << e.what() << endl;
        }
    } else if(mode == 3){ // Two kings mode
        TwoDimShape my_std_board_shape = {8,8};
        TwoDimBoard my_std_board(my_std_board_shape);
        ChessGame my_game(CondToWin::KillKing);
        my_game.addBoard(my_std_board);
        my_game.addPlayer("Garry Kasparov");
        my_game.addPlayer("Magnus Carlsen");
        my_game.setCondToWin(CondToWin::KillKing);
        try{
            my_game.startGame(PiecesOrderStyle::TwoKings);
        } catch (runtime_error &e) {
            cout << e.what() << endl;
        }
    } else if(mode == 4){ // Three players mode
        TwoDimShape my_std_board_shape = {9,10};
        TwoDimBoard my_std_board(my_std_board_shape);
        ChessGame my_game(CondToWin::KillKing);
        my_game.addBoard(my_std_board);
        my_game.addPlayer("Garry Kasparov");
        my_game.addPlayer("Magnus Carlsen");
        my_game.addPlayer("Beth Harmon");
        my_game.setCondToWin(CondToWin::KillKing);
        try{
            my_game.startGame(PiecesOrderStyle::ThreePlayerVariation);
        } catch (runtime_error &e) {
            cout << e.what() << endl;
        }
    } else if(mode == 5){ // Kill queen mode
        TwoDimShape my_std_board_shape = {8,8};
        TwoDimBoard my_std_board(my_std_board_shape);
        ChessGame my_game(CondToWin::KillKing);
        my_game.addBoard(my_std_board);
        my_game.addPlayer("Garry Kasparov");
        my_game.addPlayer("Magnus Carlsen");
        my_game.setCondToWin(CondToWin::KillQueen);
        try{
            my_game.startGame(PiecesOrderStyle::Standard);
        } catch (runtime_error &e) {
            cout << e.what() << endl;
        }
    } else {
        cout << "Invalid game mode" << endl;
    }
}
