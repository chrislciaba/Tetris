//
//  Piece.h
//  Project 3
//
//  Created by Christian Ciabattoni on 7/21/14.
//  Copyright (c) 2014 Christian Ciabattoni. All rights reserved.
//
#ifndef __Project_3__Piece__
#define __Project_3__Piece__
#include <queue>
//coordinates for each '#' component of a piece
struct Coord
{
public:
    Coord(int x, int y)
    :m_xCoord(x), m_yCoord(y){}
    int getX() const{return m_xCoord;}
    int getY() const{return m_yCoord;}
    void setX(int x){m_xCoord = x;}
    void setY(int y){m_yCoord = y;}
private:
    int m_xCoord;
    int m_yCoord;
};
class Screen;

class Piece
{
public:
    Piece(char type);
    Piece(Piece& p);
    //Adding different types of pieces to the queue
    void TPiece(int orientation, Coord c);
    void LPiece(int orientation, Coord c);
    void JPiece(int orientation, Coord c);
    void OPiece(int orientation, Coord c);
    void SPiece(int orientation, Coord c);
    void ZPiece(int orientation, Coord c);
    void IPiece(int orientation, Coord c);
    void VaporBomb(int orientation, Coord c);
    void FoamBomb(int orientation, Coord c);
    void CrazyShape(int orientation, Coord c);
    //////////////////////////////////////////////
    //////////GETTERS/////////////////////////////
    Coord get00() const{return m_00;}
    int getNumCoords() const{return m_numCoords;}
    int getOrientation() const{return m_or;};
    char getType() const{return m_type;}
    Coord getCoord();//CHANGES THE QUEUE, SO NOT CONST
    //////////////////////////////////////////////
    //////////SETTERS/////////////////////////////
    void set00(Coord setTo){m_00 = setTo;}
    void setOrientation(int orientation){m_or = orientation;}
    //////////////////////////////////////////////
    //////////MISC////////////////////////////////
    void display(Screen& screen, int x, int y);
    void typeOfPiece(char type); //figures out based on m_type and m_or what to put in m_queue
    
    //////////////////////////////////////////////
    //////////MOVE////////////////////////////////
    void rotateClockwise();
    void moveLeft();
    void moveRight();
    void moveDownOne();
private:
    Coord m_00; //upper left coordinate
    int m_numCoords;
    int m_or;
    char m_type;
    std::queue<Coord> m_queue;
};



#endif /* defined(__Project_3__Piece__) */
