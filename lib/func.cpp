#include "func.hpp"
using namespace std;

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
    }
}

void TwoDimBoard::showBoard(){
    TwoDimShape shape = getShape();
    Piece *ptrPiece;
    char pieceChar, playerChar;
    cout << "-------------------------------------------------" << endl;
    for(int row = shape.rows - 1; 0 <= row; row--){
        for(int col = 0; col < shape.cols; col++){
            ptrPiece = getPiece(row, col);
            ptrPiece == nullptr ? pieceChar = ' ' : pieceChar = ptrPiece->getChar();
            playerChar = ' ';
            if(ptrPiece != nullptr){
                if(ptrPiece->getOwner()->getId() == 0)
                    playerChar = '*';
                else if(ptrPiece->getOwner()->getId() == 1)
                    playerChar = '^';
            }
            cout << "| "<< playerChar << pieceChar << playerChar <<" ";
        }
        cout << "|" << endl << "-------------------------------------------------" << endl;
    }
}

bool TwoDimBoard::movePiece(int i_row, int i_col, int f_row, int f_col, GameRules gameRules){
    bool ret = board_pieces[i_row][i_col]->allowedMove(i_row, i_col, f_row, f_col, this);
    if(ret){
        if(!this->isFree(f_row, f_col))
            delete board_pieces[f_row][f_col];
        board_pieces[f_row][f_col] = board_pieces[i_row][i_col];
        board_pieces[i_row][i_col] = nullptr;

        if(gameRules == GameRules::Standard){
            Player* cur_player = board_pieces[f_row][f_col]->getOwner();
            if( (cur_player->getId() == 0 && f_row == this->getShape().rows - 1) || (cur_player->getId() == 1 && f_row == 0) ){
                delete board_pieces[f_row][f_col];
                putPiece(f_row, f_col, new TwoDimStdQueen(cur_player));
            }
        }
    }
    return ret;
}

bool TwoDimBoard::isKingOfPlayerMissing(int playerId){
    int curPiecePlayerId;
    for(int row = 0; row < shape.rows; row++){
        for(int col = 0; col < shape.cols; col++){
            if(board_pieces[row][col] == nullptr)
                continue;
            curPiecePlayerId = this->board_pieces[row][col]->getOwner()->getId();
            if(curPiecePlayerId == playerId && board_pieces[row][col]->getChar() == 'K')
                return false;
        }
    }
    return true;
}