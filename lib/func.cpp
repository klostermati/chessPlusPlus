#include "func.hpp"
using namespace std;

map<char, string> Piece::whites_map = { { 'p', "\u265F"}, { 'r', "\u265C" }, { 'k', "\u265E" }, { 'b', "\u265D" }, { 'q', "\u265B" }, { 'K', "\u265A" } };
map<char, string> Piece::blacks_map = { { 'p', "\u2659"}, { 'r', "\u2656" }, { 'k', "\u2658" }, { 'b', "\u2657" }, { 'q', "\u2655" }, { 'K', "\u2654" } };
map<char, string> Piece::third_player_map = { { 'p', "\u2659"}, { 'r', "\u2656" }, { 'k', "\u2658" }, { 'b', "\u2657" }, { 'q', "\u2655" }, { 'K', "\u2654" } };

void clearScreen(){
    system("cls");      // windows
    system("clear");    // linux
}

void TwoDimBoard::orderPieces(const vector<Player*> &playerList, PiecesOrderStyle order_style = PiecesOrderStyle::Standard){
    if(order_style == PiecesOrderStyle::Standard){
        if(shape.rows != 8 || shape.cols != 8){
            cout << "Standard order style must have a 8x8 board" << endl;
            return;
        }
        if(playerList.size() != 2){
            cout << "Standard order style must have 2 players" << endl;
            return;
        }
        for(auto const& player : playerList){
            int backRow, pawnsRow;
            if(player->getId() == 0)
                backRow = 0, pawnsRow = 1;
            else
                backRow = 7, pawnsRow = 6;
            putPiece(backRow,0, new TwoDimStdRook(player));
            putPiece(backRow,7, new TwoDimStdRook(player));
            putPiece(backRow,1, new TwoDimStdKnight(player));
            putPiece(backRow,6, new TwoDimStdKnight(player));
            putPiece(backRow,2, new TwoDimStdBishop(player));
            putPiece(backRow,5, new TwoDimStdBishop(player));
            putPiece(backRow,3, new TwoDimStdQueen(player));
            putPiece(backRow,4, new TwoDimStdKing(player));
            for(int col = 0; col < shape.cols; col ++)
                putPiece(pawnsRow, col, new TwoDimStdPawn(player));
        }
    } else if(order_style == PiecesOrderStyle::Baby) {
        if(shape.rows != 5 || shape.cols != 5){
            cout << "Baby order style must have a 5x5 board" << endl;
            return;
        }
        if(playerList.size() != 2){
            cout << "Baby order style must have 2 players" << endl;
            return;
        }
        for(auto const& player : playerList){
            int backRow, pawnsRow;
            if(player->getId() == 0)
                backRow = 0, pawnsRow = 1;
            else
                backRow = 4, pawnsRow = 3;
            putPiece(backRow,0, new TwoDimStdRook(player));
            putPiece(backRow,1, new TwoDimStdKnight(player));
            putPiece(backRow,2, new TwoDimStdBishop(player));
            putPiece(backRow,3, new TwoDimStdQueen(player));
            putPiece(backRow,4, new TwoDimStdKing(player));
            for(int col = 0; col < shape.cols; col ++)
                putPiece(pawnsRow, col, new TwoDimStdPawn(player));
        }
    } else if(order_style == PiecesOrderStyle::TwoKings) {
        if(shape.rows != 8 || shape.cols != 8){
            cout << "TwoKings order style must have a 8x8 board" << endl;
            return;
        }
        if(playerList.size() != 2){
            cout << "TwoKings order style must have 2 players" << endl;
            return;
        }
        for(auto const& player : playerList){
            int backRow, pawnsRow;
            if(player->getId() == 0)
                backRow = 0, pawnsRow = 1;
            else
                backRow = 7, pawnsRow = 6;
            putPiece(backRow,0, new TwoDimStdRook(player));
            putPiece(backRow,7, new TwoDimStdRook(player));
            putPiece(backRow,1, new TwoDimStdKnight(player));
            putPiece(backRow,6, new TwoDimStdKnight(player));
            putPiece(backRow,2, new TwoDimStdQueen(player));
            putPiece(backRow,5, new TwoDimStdBishop(player));
            putPiece(backRow,3, new TwoDimStdKing(player));
            putPiece(backRow,4, new TwoDimStdKing(player));
            for(int col = 0; col < shape.cols; col ++)
                putPiece(pawnsRow, col, new TwoDimStdPawn(player));
        }
    } else if(order_style == PiecesOrderStyle::ThreePlayerVariation) {
        if(shape.rows != 9 || shape.cols != 10){
            cout << "ThreePlayerVariation order style must have a 9x10 board" << endl;
            return;
        }
        if(playerList.size() != 3){
            cout << playerList.size() << "ThreePlayerVariation order style must have 3 players" << endl;
            return;
        }
        for(auto const& player : playerList){
            if(player->getId() != 2){
                int backRow, pawnsRow;
                if(player->getId() == 0)
                    backRow = 0, pawnsRow = 1;
                else
                    backRow = 8, pawnsRow = 7;
                putPiece(backRow,1, new TwoDimStdRook(player));
                putPiece(backRow,8, new TwoDimStdRook(player));
                putPiece(backRow,2, new TwoDimStdKnight(player));
                putPiece(backRow,7, new TwoDimStdKnight(player));
                putPiece(backRow,3, new TwoDimStdBishop(player));
                putPiece(backRow,6, new TwoDimStdBishop(player));
                putPiece(backRow,4, new TwoDimStdQueen(player));
                putPiece(backRow,5, new TwoDimStdKing(player));
                for(int col = 0; col < shape.cols; col ++)
                    putPiece(pawnsRow, col, new TwoDimStdPawn(player));
            } else {
                putPiece(4,4, new TwoDimStdKing(player));
                putPiece(4,3, new TwoDimStdQueen(player));
                putPiece(4,5, new TwoDimStdQueen(player));
                putPiece(3,4, new TwoDimStdRook(player));
                putPiece(5,4, new TwoDimStdRook(player));
                putPiece(3,3, new TwoDimStdKnight(player));
                putPiece(5,5, new TwoDimStdKnight(player));
                putPiece(3,5, new TwoDimStdKnight(player));
                putPiece(5,3, new TwoDimStdKnight(player));
            }
        }
    }
}

void TwoDimBoard::showBoard(){
    TwoDimShape shape = getShape();
    Piece *ptrPiece;
    string pieceSymbol;
    char playerSign;
    
    cout << "   "; for(int i = 0; i < shape.cols; i++){ cout << "------"; } cout << "-" << endl;
    for(int row = shape.rows - 1; 0 <= row; row--){
        cout << row + 1 << "  " ;
        for(int col = 0; col < shape.cols; col++){
            ptrPiece = getPiece(row, col);
            ptrPiece == nullptr ? pieceSymbol = ' ' : pieceSymbol = ptrPiece->getSymbol();
            ptrPiece == nullptr ? playerSign = ' ' : playerSign = ptrPiece->getOwner()->getSign();
            cout << "| "<< playerSign << pieceSymbol << playerSign <<" ";
        }
        cout << "|" << endl << "   ";
        for(int i = 0; i < shape.cols; i++){ cout << "------"; } cout << "-" << endl;
    }
    cout << "   "; for(int i = 0; i < shape.cols; i++){ cout << "   " << char(i+97) << "  "; } cout << " " << endl << endl;
}

bool TwoDimBoard::movePiece(int i_row, int i_col, int f_row, int f_col, CondToWin condToWin){
    bool ret = board_pieces[i_row][i_col]->allowedMove(i_row, i_col, f_row, f_col, this);
    if(ret){
        if(!this->isFree(f_row, f_col)){
            delete board_pieces[f_row][f_col];
            board_pieces[f_row][f_col] = nullptr;
        }
        board_pieces[f_row][f_col] = board_pieces[i_row][i_col];
        board_pieces[i_row][i_col] = nullptr;

        Player* cur_player = board_pieces[f_row][f_col]->getOwner();
        if(board_pieces[f_row][f_col]->getId() == 'p')
            if( (cur_player->getId() == 0 && f_row == this->getShape().rows - 1) || (cur_player->getId() == 1 && f_row == 0) ){
                delete board_pieces[f_row][f_col];
                putPiece(f_row, f_col, new TwoDimStdQueen(cur_player));
            }
    }
    return ret;
}

bool TwoDimBoard::isPieceOfPlayerMissing(char piece, int playerId){
    int curPiecePlayerId;
    for(int row = 0; row < shape.rows; row++){
        for(int col = 0; col < shape.cols; col++){
            if(board_pieces[row][col] == nullptr)
                continue;
            curPiecePlayerId = this->board_pieces[row][col]->getOwner()->getId();
            if(curPiecePlayerId == playerId && board_pieces[row][col]->getId() == piece)
                return false;
        }
    }
    return true;
}

void TwoDimBoard::deletePlayer(int playerId){
    int curPiecePlayerId;
    for(int row = 0; row < shape.rows; row++){
        for(int col = 0; col < shape.cols; col++){
            if(board_pieces[row][col] == nullptr)
                continue;
            curPiecePlayerId = this->board_pieces[row][col]->getOwner()->getId();
            if(curPiecePlayerId == playerId){
                delete board_pieces[row][col];
                board_pieces[row][col] = nullptr;
            }
        }
    }
}