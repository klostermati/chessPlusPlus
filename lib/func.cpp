#include "func.hpp"
using namespace std;

map<char, string> Piece::whites_map = { { 'p', "\u265F"}, { 'r', "\u265C" }, { 'k', "\u265E" }, { 'b', "\u265D" }, { 'q', "\u265B" }, { 'K', "\u265A" } };
map<char, string> Piece::blacks_map = { { 'p', "\u2659"}, { 'r', "\u2656" }, { 'k', "\u2658" }, { 'b', "\u2657" }, { 'q', "\u2655" }, { 'K', "\u2654" } };
map<char, string> Piece::third_player_map = { { 'p', "\u2659"}, { 'r', "\u2656" }, { 'k', "\u2658" }, { 'b', "\u2657" }, { 'q', "\u2655" }, { 'K', "\u2654" } };

void clearScreen(){
    system("cls");      // windows
    system("clear");    // linux
}

Player::Player(string name_, int id_, char sign_)
    : id(id_)
    , name(move(name_))
    , status(PlayerStatus::Playing)
    , sign(sign_){
}

int Player::getId(){
    return id;
}

string Player::getName(){
    return name;
}

PlayerStatus Player::getStatus(){
    return status;
}

void Player::setStatus(PlayerStatus playerStatus){
    status = playerStatus;
}

char Player::getSign(){
    return sign;
}

Piece::Piece(Player *owner_, int value_, char id_)
    : owner(owner_)
    , value(value_)
    , id(id_) {
    if(owner->getId() == 0){ // white
        symbol = whites_map[id];
    } else if (owner->getId() == 1){ // black
        symbol = blacks_map[id];
    } else {
        symbol = third_player_map[id];
    }
}

Player* Piece::getOwner(){
    return owner;
}
int Piece::getValue(){
    return value;
}
char Piece::getId(){
    return id;
}
string Piece::getSymbol(){
    return symbol;
}

TwoDimBoard::TwoDimBoard(TwoDimShape shape_) : shape(move(shape_)) {
    board_pieces = new Piece**[shape.rows];
    for(int row = 0; row < shape.rows; row++){
        board_pieces[row] = new Piece*[shape.cols];
        for (int col = 0; col < shape.cols; col++){
            board_pieces[row][col] = nullptr;
        }
    }
}

TwoDimBoard::~TwoDimBoard(){
    // TODO: Delete news
}

Piece* TwoDimBoard::getPiece(int row, int col){
    if(row < 0 || shape.rows <= row || col < 0 || shape.cols <= col)
        return nullptr;
    return board_pieces[row][col];
}
bool TwoDimBoard::isFree(int row, int col){
    if(board_pieces[row][col] == nullptr)
        return true;
    return false;
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

void TwoDimBoard::putPiece(int row, int col, Piece *piece){
    board_pieces[row][col] = piece;
}

TwoDimPiece::TwoDimPiece(Player *owner_, int value_, char id_) : Piece(owner_, value_, id_){
}

bool TwoDimPiece::isOutBoard(int f_row, int f_col, int rows, int cols){
    if(f_row < 0 || f_row >= rows || f_col < 0 || f_col >= cols)
        return true;
    return false;
}

bool TwoDimPiece::isInFreeLine(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board, Player *player){ // like the rook move
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

bool TwoDimPiece::isInFreeDiag(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board, Player *player){ // like the bishop move
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

bool TwoDimPiece::isInSamePos(int i_row, int i_col, int f_row, int f_col){
    if(i_row == f_row && i_col == f_col)
        return true;
    return false;
}

void TwoDimPiece::op(int &row, int &col, DiagDir diagDir){
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

TwoDimStdPawn::TwoDimStdPawn(Player *owner_) : TwoDimPiece(owner_, 1, 'p'){
}

bool TwoDimStdPawn::allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
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

TwoDimStdKnight::TwoDimStdKnight(Player *owner_):TwoDimPiece(owner_, 3, 'k'){
}

bool TwoDimStdKnight::allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
    int rows = board->getShape().rows;
    int cols = board->getShape().cols;
    if(isOutBoard(f_row, f_col, rows, cols))
        return false;
    if( ((abs(i_row - f_row) != 1) || (abs(i_col - f_col) != 2)) && ((abs(i_row - f_row) != 2) || (abs(i_col - f_col) != 1)) )
        return false;
    if(board->getPiece(f_row,f_col) != nullptr)
        if(board->getPiece(f_row, f_col)->getOwner()->getId() == this->getOwner()->getId() )
            return false;
    return true;
}

TwoDimStdKing::TwoDimStdKing(Player *owner_):TwoDimPiece(owner_, 0, 'K'){
}

bool TwoDimStdKing::allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
    int rows = board->getShape().rows;
    int cols = board->getShape().cols;
    if(isOutBoard(f_row, f_col, rows, cols))
        return false;
    if(isInSamePos(i_row, i_col, f_row, f_col))
        return false;
    if(abs(i_row - f_row) > 1 || abs(i_col - f_col) > 1)
        return false;
    if(board->getPiece(f_row,f_col) != nullptr)
        if(board->getPiece(f_row, f_col)->getOwner()->getId() == this->getOwner()->getId() )
            return false;
    return true;
}

TwoDimStdBishop::TwoDimStdBishop(Player *owner_):TwoDimPiece(owner_, 3, 'b'){
}

bool TwoDimStdBishop::allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
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

TwoDimStdRook::TwoDimStdRook(Player *owner_):TwoDimPiece(owner_, 5, 'r'){
}

bool TwoDimStdRook::allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
    int rows = board->getShape().rows;
    int cols = board->getShape().cols;
    if(isOutBoard(f_row, f_col, rows, cols))
        return false;
    if(!isInFreeLine(i_row, i_col, f_row, f_col, board, this->getOwner()))
        return false;
    return true;
}

TwoDimStdQueen::TwoDimStdQueen(Player *owner_):TwoDimPiece(owner_, 9, 'q'){
}

bool TwoDimStdQueen::allowedMove(int i_row, int i_col, int f_row, int f_col, TwoDimBoard *board){
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

ChessGame::ChessGame(CondToWin condToWin = CondToWin::KillKing) : board(nullptr) {}

void ChessGame::addBoard(Board &board_){
    board = &board_;
}
Player* ChessGame::addPlayer(const string &name) {
    map<int, char> signs_map = { {0,'*'}, {1,'^'}, {2,'@'} };
    Player *player_to_add = new Player(name, players.size(), signs_map[players.size()]);
    players.push_back(player_to_add);
    return player_to_add;
}
void ChessGame::setCondToWin(CondToWin condToWin_){
    condToWin = condToWin_;
}
void ChessGame::startGame(PiecesOrderStyle orderStyle = PiecesOrderStyle::Standard){
    // Order pieces
    board->orderPieces(players, orderStyle);

    int winnerId = -1;
    int num_players = players.size();
    int cur_player = -1;
    while(1) {
        if( (cur_player+1) == players.size())
                cur_player = -1;
        cur_player++;
        if(players[cur_player]->getStatus() == PlayerStatus::Lost)
            continue;
        
        clearScreen();
        board->showBoard();
        if(winnerId != -1)
            break;
        showPlayers(cur_player);
        bool played = false;
        string input, str_i_row, str_i_col, str_f_row, str_f_col;
        int i_row, f_row, i_col, f_col;
        do {
            cout << "Initial position of piece to move: ";
            cin >> input;
            i_row = char(input[1] - 49);
            i_col = char(input[0]) - 97;
            if( board->getPiece(i_row, i_col) == nullptr ){
                cout << "Try again" << endl;
                continue;
            }
            if( cur_player != board->getPiece(i_row, i_col)->getOwner()->getId() ){
                cout << "This is not one of your pieces" << endl;
                continue;
            }

            cout << "Final position of piece to move: ";
            cin >> input;
            f_row = char(input[1] - 49);
            f_col = char(input[0]) - 97;
            if(board->movePiece(i_row, i_col, f_row, f_col, condToWin))
                played = true;
            else
                cout << "Try again" << endl;
            
        } while (played == false);

        winnerId = updatePlayersStatus();
    }
    cout << players[winnerId]->getName() << " is the winner" << endl;
}

int ChessGame::updatePlayersStatus(){ // Returns id of winner or -1 in case there's no winner yet
    int winnerId = -1;
    int nPlaying = 0;
    char piece;
    if(condToWin == CondToWin::KillKing)
        piece = 'K';
    else if(condToWin == CondToWin::KillQueen)
        piece = 'q';

    for(const auto& p: players){
        if(p->getStatus() == PlayerStatus::Lost)
            continue;
        if(board->isPieceOfPlayerMissing(piece ,p->getId())) {
            p->setStatus(PlayerStatus::Lost);
            board->deletePlayer(p->getId());
        } else {
            nPlaying++;
            if(nPlaying == 1)
                winnerId = p->getId();
            else
                winnerId = -1;
        }
    }
    return winnerId;
}

void ChessGame::showPlayers(int curPlayer){
    cout << "Players:" << endl;
    for(const auto& p: players){
        if(p->getStatus() == PlayerStatus::Lost)
            continue;
        cout << "\t" << p->getName() << "\t (" << p->getSign() << ")";
        if (p->getId() == curPlayer)
            cout << "\t <---";
        cout << endl;
    }
    cout << endl;
}