//
//  Piece.cpp
//  Project 3
//
//  Created by Christian Ciabattoni on 7/21/14.
//  Copyright (c) 2014 Christian Ciabattoni. All rights reserved.
//

#include "Piece.h"
#include "UserInterface.h"

Piece::Piece(char type)
:m_type(type), m_or(0), m_00(Coord(4, 0))
{
    typeOfPiece(type);
}

Piece::Piece(Piece &p)
:m_type(p.getType()), m_or(p.getOrientation()), m_00(Coord(p.get00().getX(), p.get00().getY())), m_numCoords(p.getNumCoords())
{
    for(int i = 0; i < m_numCoords; i++)
        m_queue.push(p.getCoord());
}

//////////////////////////////////////////////////////////////
//////////////FINISHES CREATING THE PIECE/////////////////////
//////////////////////////////////////////////////////////////


void Piece::typeOfPiece(char type)
{
    switch(type)
    {
        case 'T':
            TPiece(m_or, m_00);
            m_numCoords = 4;
            break;
        case 'L':
            LPiece(m_or, m_00);
            m_numCoords = 4;
            break;
        case 'J':
            JPiece(m_or, m_00);
            m_numCoords = 4;
            break;
        case 'S':
            SPiece(m_or, m_00);
            m_numCoords = 4;
            break;
        case 'Z':
            ZPiece(m_or, m_00);
            m_numCoords = 4;
            break;
        case 'O':
            OPiece(m_or, m_00);
            m_numCoords = 4;
            break;
        case 'I':
            IPiece(m_or, m_00);
            m_numCoords = 4;
            break;
        case 'V':
            VaporBomb(m_or, m_00);
            m_numCoords = 2;
            break;
        case 'F':
            FoamBomb(m_or, m_00);
            m_numCoords = 1;
            break;
        case 'C':
            CrazyShape(m_or, m_00);
            m_numCoords = 4;
            break;
        default:
            break;
    }
}

//////////////////////////////////////////////////////////////
//////////////ADD THE COORDINATES TO QUEUE////////////////////
//////////////////////////////////////////////////////////////

void Piece::TPiece(int orientation, Coord c)
{
    while(!m_queue.empty()) //clear out queue
        m_queue.pop();
    int x = c.getX();
    int y = c.getY();
    switch (orientation)
    {
        case 0:
            //LEFT-RIGHT, TOP BOTTOM
            m_queue.push(Coord(x + 1, y));
            m_queue.push(Coord(x, y + 1));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 2, y + 1));
            break;
        case 1:
            m_queue.push(Coord(x + 1, y));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x + 1, y + 2));
            break;
        case 2:
            m_queue.push(Coord(x, y + 1));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x + 1, y + 2));
            break;
        case 3:
            m_queue.push(Coord(x + 1, y));
            m_queue.push(Coord(x, y + 1));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 1, y + 2));
            break;
    }
}

void Piece::LPiece(int orientation, Coord c)
{
    while(!m_queue.empty()) //clear out queue
        m_queue.pop();
    int x = c.getX();
    int y = c.getY();
    switch (orientation)
    {
        case 0:
            //LEFT-RIGHT, TOP BOTTOM
            m_queue.push(Coord(x, y + 1));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x, y + 2));
            break;
        case 1:
            m_queue.push(Coord(x + 1, y));
            m_queue.push(Coord(x + 2, y));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x + 2, y + 2));
            break;
        case 2:
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x, y + 2));
            m_queue.push(Coord(x + 1, y + 2));
            m_queue.push(Coord(x + 2, y + 2));
            break;
        case 3:
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 1, y + 2));
            m_queue.push(Coord(x + 1, y + 3));
            m_queue.push(Coord(x + 2, y + 3));
            break;
    }
}

void Piece::JPiece(int orientation, Coord c)
{
    while(!m_queue.empty()) //clear out queue
        m_queue.pop();
    int x = c.getX();
    int y = c.getY();
    switch (orientation)
    {
        case 0:
            //LEFT-RIGHT, TOP BOTTOM
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x + 3, y + 1));
            m_queue.push(Coord(x + 3, y + 2));
            break;
        case 1:
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x + 2, y + 2));
            m_queue.push(Coord(x + 1, y + 3));
            m_queue.push(Coord(x + 2, y + 3));
            break;
        case 2:
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 1, y + 2));
            m_queue.push(Coord(x + 2, y + 2));
            m_queue.push(Coord(x + 3, y + 2));
            break;
        case 3:
            m_queue.push(Coord(x + 1, y));
            m_queue.push(Coord(x + 2, y));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 1, y + 2));
            break;
    }
}
void Piece::SPiece(int orientation, Coord c)
{
    while(!m_queue.empty()) //clear out queue
        m_queue.pop();
    int x = c.getX();
    int y = c.getY();
    switch(orientation)
    {
        case 0:
        case 2:
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x, y + 2));
            m_queue.push(Coord(x + 1, y + 2));
            break;
        case 1:
        case 3:
            m_queue.push(Coord(x + 1, y));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x + 2, y + 2));
            break;
    }
}

void Piece::ZPiece(int orientation, Coord c)
{
    while(!m_queue.empty()) //clear out queue
        m_queue.pop();
    int x = c.getX();
    int y = c.getY();
    switch(orientation)
    {
        case 0:
        case 2:
            m_queue.push(Coord(x, y + 1));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 1, y + 2));
            m_queue.push(Coord(x + 2, y + 2));
            break;
        case 1:
        case 3:
            m_queue.push(Coord(x + 2, y));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x + 1, y + 2));
            break;
    }
}

void Piece::OPiece(int orientation, Coord c)
{
    while(!m_queue.empty()) //clear out queue
        m_queue.pop();
    int x = c.getX();
    int y = c.getY();
    switch (orientation)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            //LEFT-RIGHT, TOP BOTTOM
            m_queue.push(Coord(x, y));
            m_queue.push(Coord(x + 1, y));
            m_queue.push(Coord(x, y + 1));
            m_queue.push(Coord(x + 1, y + 1));
            break;
    }
}

void Piece::IPiece(int orientation, Coord c)
{
    while(!m_queue.empty()) //clear out queue
        m_queue.pop();
    int x = c.getX();
    int y = c.getY();
    switch (orientation)
    {
        case 0:
        case 2:
            //LEFT-RIGHT, TOP BOTTOM
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x + 3, y + 1));
            m_queue.push(Coord(x + 4, y + 1));
            break;
        case 1:
        case 3:
            m_queue.push(Coord(x + 1, y));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 1, y + 2));
            m_queue.push(Coord(x + 1, y + 3));
            break;
    }
}

void Piece::VaporBomb(int orientation, Coord c)
{
    while(!m_queue.empty()) //clear out queue
        m_queue.pop();
    int x = c.getX();
    int y = c.getY();
    switch (orientation)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            //LEFT-RIGHT, TOP BOTTOM
            m_queue.push(Coord(x + 1, y));
            m_queue.push(Coord(x + 2, y));
            break;
    }
}

void Piece::FoamBomb(int orientation, Coord c)
{
    while(!m_queue.empty()) //clear out queue
        m_queue.pop();
    int x = c.getX();
    int y = c.getY();
    switch (orientation)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            //LEFT-RIGHT, TOP BOTTOM
            m_queue.push(Coord(x + 1, y + 1));
            break;
    }
}

void Piece::CrazyShape(int orientation, Coord c)
{
    while(!m_queue.empty()) //clear out queue
        m_queue.pop();
    int x = c.getX();
    int y = c.getY();
    switch (orientation)
    {
        case 0:
            //LEFT-RIGHT, TOP BOTTOM
            m_queue.push(Coord(x, y));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x + 3, y));
            break;
        case 1:
            m_queue.push(Coord(x + 3, y));
            m_queue.push(Coord(x + 2, y + 1));
            m_queue.push(Coord(x + 2, y + 2));
            m_queue.push(Coord(x + 3, y + 3));
            break;
        case 2:
            m_queue.push(Coord(x + 1, y + 2));
            m_queue.push(Coord(x + 2, y + 2));
            m_queue.push(Coord(x, y + 3));
            m_queue.push(Coord(x + 3, y + 3));
            break;
        case 3:
            m_queue.push(Coord(x , y));
            m_queue.push(Coord(x + 1, y + 1));
            m_queue.push(Coord(x + 1, y + 2));
            m_queue.push(Coord(x, y + 3));
            break;
    }
}

void Piece::display(Screen& screen, int x, int y)
{
    for(int i = 0; i < m_numCoords; i++)
    {
        Coord dis = m_queue.front();
        m_queue.pop();
        screen.gotoXY(dis.getX() + x, dis.getY() + y);
        screen.printChar('#');
        m_queue.push(dis);
    }
}

///POPS A COORDINATE OFF THE TOP, PLACES IT AT THE BACK, AND CONTINUES SO YOU CAN CYCLE THROUGH ALL OF THE COORDINATES IN THE QUEUE
Coord Piece::getCoord()
{
    Coord cur = m_queue.front();
    m_queue.pop();
    m_queue.push(cur);
    return cur;
}
//all of these call typeofpiece because orientation or position change and the queue needs to be modified
void Piece::rotateClockwise()
{
    m_or = (m_or + 1) % 4;
    typeOfPiece(m_type);
}
void Piece::moveLeft()
{
    int xNew = m_00.getX() - 1;
    m_00.setX(xNew);
    typeOfPiece(m_type);
}
void Piece::moveRight()
{
    int xNew = m_00.getX() + 1;
    m_00.setX(xNew);
    typeOfPiece(m_type);
}
void Piece::moveDownOne()
{
    int yNew = m_00.getY() + 1;
    m_00.setY(yNew);
    typeOfPiece(m_type);
}
