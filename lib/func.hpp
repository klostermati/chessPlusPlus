#ifndef FUNC_HPP
#define FUNC_HPP

#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<map>
using namespace std;

enum class PlayerStatus {Playing, Lost}; // Last player in Playing condition is the winner
enum class PiecesOrderStyle {Standard, Baby, TwoKings, ThreePlayerVariation};
enum class CondToWin {KillKing, KillQueen};

void clearScreen();

class Player{
    public:
        Player(string name_, int id_, char sign_);
        ~Player();
        int getId();
        string getName();
        PlayerStatus getStatus();
        void setStatus(PlayerStatus playerStatus);
        char getSign();
    private:
        int id;
        string name;
        PlayerStatus status;
        char sign;
};

class Piece;

class Board{
    public:
        virtual ~Board();
        virtual void orderPieces(const vector<Player*> &playerList, PiecesOrderStyle order_style = PiecesOrderStyle::Standard) = 0;
        virtual void showBoard() = 0;
        virtual bool movePiece(int i_row, int i_col, int f_row, int f_col, CondToWin condToWin) = 0;
        virtual Piece* getPiece(int row, int col) = 0;
        virtual bool isPieceOfPlayerMissing(char piece, int playerId) = 0;
        virtual void deletePlayer(int playerId) = 0;
};

class TwoDimBoard;

class Piece{
    public:
        static map<char, string> whites_map;
        static map<char, string> blacks_map;
        static map<char, string> third_player_map;
        Piece(Player *owner_, int value_, char id_);
        virtual ~Piece();
        virtual bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard* board) = 0;
        Player* getOwner();
        int getValue();
        char getId();
        string getSymbol();
    private:
        Player *owner;
        int value;
        char id;
        string symbol;
};

struct TwoDimShape{
    int rows, cols;
};

class TwoDimBoard : public Board{
    public:
        TwoDimBoard(TwoDimShape shape_);
        ~TwoDimBoard();
        TwoDimShape getShape(){
            return shape;
        }
        Piece* getPiece(int row, int col);
        bool isFree(int row, int col);
        void orderPieces(const vector<Player*>&, PiecesOrderStyle);
        void showBoard();
        bool movePiece(int i_row, int i_col, int f_row, int f_col, CondToWin condToWin);
        bool isPieceOfPlayerMissing(char piece, int playerId);
        void deletePlayer(int playerId);
    private:
        TwoDimShape shape;
        Piece ***board_pieces; // Each element of the 2d array is a pointer to a object of class Piece
        void putPiece(int row, int col, Piece *piece);
};

class TwoDimPiece : public Piece {
    public:
        TwoDimPiece(Player *owner_, int value_, char id_);
        virtual ~TwoDimPiece();
        bool isOutBoard(int f_row, int f_col, int rows, int cols);
        virtual bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard* board) = 0;
        bool isInFreeLine(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board, Player *player);
        enum class DiagDir {UpRowUpCol, UpRowDownCol, DownRowUpCol, DownRowDownCol};
        bool isInFreeDiag(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board, Player *player);
        bool isInSamePos(int i_row, int i_col, int f_row, int f_col);
    private:
        void op(int &row, int &col, DiagDir diagDir);
};

class TwoDimStdPawn : public TwoDimPiece {
    public:
        TwoDimStdPawn(Player *owner_);
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board);
};

class TwoDimStdKnight : public TwoDimPiece {
    public:
        TwoDimStdKnight(Player *owner_);
        ~TwoDimStdKnight();
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board);
};

class TwoDimStdKing : public TwoDimPiece{
    public:
        TwoDimStdKing(Player *owner_);
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board);
};

class TwoDimStdBishop : public TwoDimPiece{
    public:
        TwoDimStdBishop(Player *owner_);
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board);
};

class TwoDimStdRook : public TwoDimPiece{
    public:
        TwoDimStdRook(Player *owner_);
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board);
};

class TwoDimStdQueen : public TwoDimPiece{
    public:
        TwoDimStdQueen(Player *owner_);
        bool allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board);
};

class ChessGame {
    public:
        ChessGame(CondToWin condToWin);
        void addBoard(Board &board_);
        Player* addPlayer(const string &name);
        void setCondToWin(CondToWin condToWin_);
        void startGame(PiecesOrderStyle orderStyle);
        int updatePlayersStatus();
        void showPlayers(int curPlayer);
    private:
        Board *board;
        vector<Player*> players;
        CondToWin condToWin;
        void deletePlayers();
};

#endif