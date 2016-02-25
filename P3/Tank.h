#ifndef TANK_INCLUDED
#define TANK_INCLUDED
#include "Piece.h"

class Screen;

class Tank
{
public:
    Tank(int x, int y);
    ~Tank();
    ///////////GETTERS/SETTERS////////////
    bool getIsPieceAvailable() const{return m_isPieceAvailable;}
    void setIsPieceAvailable(bool setTo){m_isPieceAvailable = setTo;}
    Piece& getPiece(){return m_piece;}
    Piece& getNextPiece(){return m_next;};
    ///////////RANDOM FUNCTIONS NEEDED FOR GAME IMPLEMENTATION///////////
    void display(Screen& screen, int x, int y);
    void randPiece();
    int deleteFullRows();
    void moveRowRecursive(int row);
    void setNextToCurrentPiece();
    void placePiece();
    void clearTank();
    /////////////CHECK MOVE LEGALITY////////////
    bool isOccupied(int r, int c);
    bool moveDownPossible();
    bool moveRightPossible();
    bool moveLeftPossible();
    bool rotatePossible();
    ///////////MOVE PIECE////////////
    void movePieceRight();
    void movePieceLeft();
    void rotatePiece();
    void movePieceDownOne();
    ///////////SPECIAL PIECE ACTIONS/////
    void vaporBombExplode();
    void foamBombExplode(Coord explodeAt);
private:
    char** m_tankArr;
    int m_rows;
    int m_cols;
    Piece m_piece;
    Piece m_next;
    bool m_isPieceAvailable;
};

#endif // TANK_INCLUDED
