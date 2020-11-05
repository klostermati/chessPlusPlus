#ifndef FUNC_HPP
#define FUNC_HPP

#include<iostream>
#include<vector>
#include<list>
#include<string>
using namespace std;

//enum class GameStatus {InPrep, Playing, Finished};
enum class PlayerStatus {Playing, Lost, Won};
enum class PiecesOrderStyle {Standard};
enum class GameRules {Standard};

class Player{
    public:
        Player(string name_, int id_)
            : id(id_)
            , name(move(name_))
            , status(PlayerStatus::Playing) {
        }
        int getId(){
            return id;
        }
        string getName(){
            return name;
        }
        PlayerStatus getStatus(){
            return status;
        }
        void setStatus(PlayerStatus playerStatus){
            status = playerStatus;
        }
    private:
        int id;
        string name;
        PlayerStatus status;
};

class Piece;

class Board{
    public:
        virtual void orderPieces(const vector<Player*> &playerList, PiecesOrderStyle order_style = PiecesOrderStyle::Standard) = 0;
        virtual void showBoard() = 0;
        virtual bool movePiece(int i_row, int i_col, int f_row, int f_col, GameRules gameRules) = 0;
        virtual Piece* getPiece(int row, int col) = 0;
        virtual bool isKingOfPlayerMissing(int playerId) = 0;
};

class TwoDimBoard;

class Piece{
    public:
        Piece(Player *owner_, int value_, char c_) 
            : owner(owner_)
            , value(value_)
            , c(c_){
        }
        virtual bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard* board) = 0;
        Player* getOwner(){
            return owner;
        }
        int getValue(){
            return value;
        }
        char getChar(){
            return c;
        }
    private:
        Player *owner;
        int value;
        char c;
};

struct TwoDimShape{
    int rows, cols;
};

class TwoDimBoard : public Board{
    public:
        TwoDimBoard(TwoDimShape shape_, PiecesOrderStyle order_style = PiecesOrderStyle::Standard, uint n_players = 2)
            : shape(move(shape_))
        {
            board_pieces = new Piece**[shape.rows];
            for(int row = 0; row < shape.rows; row++){
                board_pieces[row] = new Piece*[shape.cols];
                for (int col = 0; col < shape.cols; col++){
                    board_pieces[row][col] = nullptr;
                }
            }
        }
        ~TwoDimBoard(){
            // TODO: Delete news
        }
        TwoDimShape getShape(){
            return shape;
        }
        Piece* getPiece(int row, int col){
            return board_pieces[row][col];
        }
        bool isFree(int row, int col){
            if(board_pieces[row][col] == nullptr)
                return true;
            return false;
        }
        void orderPieces(const vector<Player*>&, PiecesOrderStyle);
        void showBoard();
        bool movePiece(int i_row, int i_col, int f_row, int f_col, GameRules gameRules);
        bool isKingOfPlayerMissing(int playerId);
    private:
        TwoDimShape shape;
        Piece ***board_pieces; // Each element of the 2d array is a pointer to a object of class Piece
        void putPiece(int row, int col, Piece *piece){
            board_pieces[row][col] = piece;
        }
};

class TwoDimPiece : public Piece {
    public:
        TwoDimPiece(Player *owner_, int value_, char c_) : Piece(owner_, value_, c_){}
        bool isOutBoard(int f_row, int f_col, int rows, int cols){
            if(f_row < 0 || f_row >= rows || f_col < 0 || f_col >= cols)
                return true;
            return false;
        }
        virtual bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard* board) = 0;
        bool isInFreeLine(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board, Player *player){ // like the rook move
            if((i_row == f_row) && (i_col != f_col)){
                if(i_col < f_col)
                    for(int col = i_col + 1; col <= f_col; col++){
                        if(col != f_col && !board->isFree(i_row, col))
                            return false;
                        if(col == f_col){
                            if(!(board->isFree(i_row, col)) && (board->getPiece(i_row, col)->getOwner()->getId() == player->getId()) )
                                return false;
                            else 
                                return true;
                        }
                    }
                if(f_col < i_col)
                    for(int col = i_col - 1; col >= f_col; col--){
                        if(col != f_col && !board->isFree(i_row, col))
                            return false;
                        if(col == f_col){
                            if(!(board->isFree(i_row, col)) && (board->getPiece(i_row, col)->getOwner()->getId() == player->getId()) )
                                return false;
                            else 
                                return true;
                        }
                    }
            }
            if((i_row != f_row) && (i_col == f_col)){
                if(i_row < f_row)
                    for(int row = i_row + 1; row <= f_row; row++){
                        if(row != f_row && !board->isFree(row, i_col))
                            return false;
                        if(row == f_row){
                            if(!(board->isFree(row, i_col)) && (board->getPiece(row, i_col)->getOwner()->getId() == player->getId()) )
                                return false;
                            else 
                                return true;
                        }
                    }
                if(f_row < i_row)
                    for(int row = i_row - 1; row >= f_row; row--){
                        if(row != f_row && !board->isFree(row, i_col))
                            return false;
                        if(row == f_row){
                            if(!(board->isFree(row, i_col)) && (board->getPiece(row, i_col)->getOwner()->getId() == player->getId()) )
                                return false;
                            else 
                                return true;
                        }
                    }
            }
            return false;
        }
        enum class DiagDir {UpRowUpCol, UpRowDownCol, DownRowUpCol, DownRowDownCol};
        bool isInFreeDiag(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board, Player *player){ // like the bishop move
            if( abs(f_row - i_row) != abs(f_col - i_col) )
                return false;
            DiagDir diagDir;
            if(i_row < f_row && i_col < f_col)
                diagDir = DiagDir::UpRowUpCol;
            else if(i_row < f_row && f_col < i_col)
                diagDir = DiagDir::UpRowDownCol;
            else if(f_row < i_row && i_col < f_col)
                diagDir = DiagDir::DownRowUpCol;
            else if(f_row < i_row && f_col < i_col)
                diagDir = DiagDir::DownRowDownCol;
            
            int row = i_row;
            int col = i_col;
            for(int i = 0; i < abs(f_row - i_row); i++){
                op(row, col, diagDir); // updates row and col
                if(row != f_row && !board->isFree(row, col))
                    return false;
                if(row == f_row){
                    if(!(board->isFree(row, col)) && (board->getPiece(row, col)->getOwner()->getId() == player->getId()) )
                        return false;
                    else 
                        return true;
                }
            }
        }
        bool isInSamePos(int i_row, int i_col, int f_row, int f_col){
            if(i_row == f_row && i_col == f_col)
                return true;
            return false;
        }
    private:
        void op(int &row, int &col, DiagDir diagDir){
            if(diagDir == DiagDir::UpRowUpCol){
                row++;
                col++;
            } else if(diagDir == DiagDir::UpRowDownCol){
                row++;
                col--;
            } else if(diagDir == DiagDir::DownRowUpCol){
                row--;
                col++;
            } else if(diagDir == DiagDir::DownRowDownCol){
                row--;
                col--;
            }
            return;
        }
};

class TwoDimStdPawn : public TwoDimPiece {
    public:
        TwoDimStdPawn(Player *owner_):TwoDimPiece(owner_, 1, 'p'){}
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
            int rows = board->getShape().rows;
            int cols = board->getShape().cols;
            int ownerId = this->getOwner()->getId();
            if(isOutBoard(f_row, f_col, rows, cols))
                return false;
            if(isInSamePos(i_row, i_col, f_row, f_col))
                return false;
            if(ownerId == 0){
                if(i_col == f_col){
                    int pawn_max = 1;
                    if (i_row == 1)
                        pawn_max = 2;
                    if( pawn_max < f_row - i_row || f_row < i_row)
                        return false;
                } else {
                    if(abs(f_col - i_col) != 1 || f_row - i_row != 1)
                        return false;
                    if(board->getPiece(f_row, f_col) == nullptr)
                        return false;
                    else if(board->getPiece(f_row, f_col)->getOwner()->getId() == this->getOwner()->getId() )
                        return false;
                }
            } else if (ownerId == 1){
                if(i_col == f_col){
                    int pawn_max = 1;
                    if (i_row == 6)
                        pawn_max = 2;
                    if( pawn_max < i_row - f_row || i_row < f_row)
                        return false;
                } else {
                    if(abs(f_col - i_col) != 1 || i_row - f_row != 1)
                        return false;
                    if(board->getPiece(f_row, f_col) == nullptr)
                        return false;
                    else if(board->getPiece(f_row, f_col)->getOwner()->getId() == this->getOwner()->getId() )
                        return false;
                }
            }
            return true;
        }
};

class TwoDimStdKnight : public TwoDimPiece {
    public:
        TwoDimStdKnight(Player *owner_):TwoDimPiece(owner_, 3, 'k'){}
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
            int rows = board->getShape().rows;
            int cols = board->getShape().cols;
            if(isOutBoard(f_row, f_col, rows, cols))
                return false;
            if( ((abs(i_row - f_row) != 1) || (abs(i_col - f_col) != 2)) && ((abs(i_row - f_row) != 2) || (abs(i_col - f_col) != 1)) )
                return false;
            return true;
        }
};

class TwoDimStdKing : public TwoDimPiece{
    public:
        TwoDimStdKing(Player *owner_):TwoDimPiece(owner_, 0, 'K'){}
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
            int rows = board->getShape().rows;
            int cols = board->getShape().cols;
            if(isOutBoard(f_row, f_col, rows, cols))
                return false;
            if(isInSamePos(i_row, i_col, f_row, f_col))
                return false;
            if(abs(i_row - f_row) > 1 || abs(i_col - f_col) > 1)
                return false;
            return true;
        }
};

class TwoDimStdBishop : public TwoDimPiece{
    public:
        TwoDimStdBishop(Player *owner_):TwoDimPiece(owner_, 3, 'b'){}
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
            int rows = board->getShape().rows;
            int cols = board->getShape().cols;
            if(isOutBoard(f_row, f_col, rows, cols))
                return false;
            if(isInSamePos(i_row, i_col, f_row, f_col))
                return false;
            if(!isInFreeDiag(i_row, i_col, f_row, f_col, board, this->getOwner() ))
                return false;
            return true;
        }
};

class TwoDimStdRook : public TwoDimPiece{
    public:
        TwoDimStdRook(Player *owner_):TwoDimPiece(owner_, 5, 'r'){}
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
            int rows = board->getShape().rows;
            int cols = board->getShape().cols;
            if(isOutBoard(f_row, f_col, rows, cols))
                return false;
            if(!isInFreeLine(i_row, i_col, f_row, f_col, board, this->getOwner()))
                return false;
            return true;
        }
};

class TwoDimStdQueen : public TwoDimPiece{
    public:
        TwoDimStdQueen(Player *owner_):TwoDimPiece(owner_, 9, 'q'){}
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
            int rows = board->getShape().rows;
            int cols = board->getShape().cols;
            if(isOutBoard(f_row, f_col, rows, cols))
                return false;
            if(isInSamePos(i_row, i_col, f_row, f_col))
                return false;
            if(!isInFreeLine(i_row, i_col, f_row, f_col, board, this->getOwner()) && !isInFreeDiag(i_row, i_col, f_row, f_col, board, this->getOwner()))
                return false;
            return true;
        }
};

class ChessGame {
    public:
        ChessGame(int num_players_)
            : board(nullptr)
            , num_players(num_players_) 
            , game_rules(GameRules::Standard){
        }
        void addBoard(Board &board_){
            board = &board_;
        }
        Player* addPlayer(const string &name) {
            if(players.size() == 2 ){
                cout << "Mssg: max number of players is 2" << endl;
                return nullptr;
            }
            Player *player_to_add = new Player(name, players.size());
            players.push_back(player_to_add);
            return player_to_add;
        }
        void setGameRules(GameRules game_rules_){
            game_rules = game_rules_;
        }
        void startGame(PiecesOrderStyle orderStyle = PiecesOrderStyle::Standard){
            // Check if combination of status, board, num_players, list players.size(), game_rules is compatible
            // or return

            // Order pieces
            board->orderPieces(players, orderStyle);

            int winnerId = -1;
            int num_players = players.size();
            int cur_player = -1;
            while(1) {
                cur_player++;
                system("cls");      // windows
                system("clear");    // linux
                if(winnerId == -1)
                    cout << "cur player: " << players[cur_player]->getName() << endl;
                // TODO: check if player is in playing state
                board->showBoard();
                if(winnerId != -1)
                    break;
                bool played = false;
                int input, i_row, i_col, f_row, f_col;
                do {
                    cout << "Initial row and column of piece to move: ";
                    cin >> input;
                    i_row = input / 10 - 1;
                    i_col = input % 10 - 1;
                    if( board->getPiece(i_row, i_col) == nullptr ){
                        cout << "Empty place" << endl;
                        continue;
                    }
                    if( cur_player != board->getPiece(i_row, i_col)->getOwner()->getId() ){
                        cout << "This is not one of your pieces" << endl;
                        continue;
                    }

                    cout << "Final row and column of piece to move: ";
                    cin >> input;
                    f_row = input / 10 - 1;
                    f_col = input % 10 - 1;
                    if(board->movePiece(i_row, i_col, f_row, f_col, game_rules))
                        played = true;
                    
                } while (played == false);

                winnerId = updatePlayersStatus();

                if( (cur_player+1) == players.size())
                        cur_player = -1;
            }
            cout << players[winnerId]->getName() << " is the winner" << endl;
        }
        int updatePlayersStatus(){ // Returns id of winner or -1 in case there's no winner yet
            int winnerId = -1;

            if(game_rules == GameRules::Standard){
                int nPlaying = 0;

                for(const auto& p: players){
                    if(p->getStatus() == PlayerStatus::Lost)
                        continue;
                    if(board->isKingOfPlayerMissing(p->getId())) {
                        p->setStatus(PlayerStatus::Lost);
                    } else {
                        nPlaying++;
                        if(nPlaying == 1)
                            winnerId = p->getId();
                        else
                            winnerId = -1;
                    }
                }
            } else {
                cout << "GameRules not fully implemented" << endl;
            }
            return winnerId;
        }
    private:
        Board *board;
        int num_players;
        vector<Player*> players;
        GameRules game_rules;
};

#endif