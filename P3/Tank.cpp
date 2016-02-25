#include "Tank.h"
#include "UserInterface.h"
#include "randPieceType.h"
#include "Piece.h"

//////////////////////////////////////////////////////////////
//////////////CONSTRUCTOR & DESTRUCTOR////////////////////////
//////////////////////////////////////////////////////////////

Tank::Tank(int x, int y)
:m_rows(y), m_cols(x), m_isPieceAvailable(true), m_piece(NULL), m_next(NULL)//m_piece & m_next will be initialized at the start of the game.
{
    m_tankArr = new char*[m_rows + 2];// +2 because two rows containing '@' signs
    for(int i = 0; i < m_rows + 2; i++)
        m_tankArr[i] = new char[m_cols + 1];//+1 because one bottom column containg '@' signs
    
    clearTank();
    for(int i = 0; i < m_rows + 1; i++)
    {
        m_tankArr[i][0] = '@';
        m_tankArr[i][m_cols + 1] = '@';
    }
    for(int i = 1; i < m_cols + 1; i++)
        m_tankArr[m_rows][i] = '@';
}

Tank::~Tank()
{
    for(int i = 0; i < m_rows + 2; i++)
        delete [] m_tankArr[i];
    delete [] m_tankArr;
}

//////////////////////////////////////////////////////////////
//////////////DISPLAY WHAT IS IN THE TANK/////////////////////
//////////////////////////////////////////////////////////////


void Tank::display(Screen& screen, int x, int y)
{
    for(int i = 0; i < m_rows + 1; i++)
    {
        screen.gotoXY(0, i);
        std::string s = "";
        for(int j = 0; j < m_cols + 2; j++)
            s += m_tankArr[i][j];
        screen.printStringClearLine(s);
    }
}

//////////////////////////////////////////////////////////////
//////////////SELECT A RANDOM PIECE///////////////////////////
//////////////////////////////////////////////////////////////


void Tank::randPiece()
{
    switch (randPieceType())
	{
        case PIECE_I:
            m_next = Piece('I');
            break;
        case PIECE_Z:
            m_next = Piece('Z');
            break;
        case PIECE_L:
            m_next = Piece('L');
            break;
        case PIECE_T:
            m_next = Piece('T');
            break;
        case PIECE_J:
            m_next = Piece('J');
            break;
        case PIECE_O:
            m_next = Piece('O');
            break;
        case PIECE_S:
            m_next = Piece('S');
            break;
        case PIECE_VAPOR:
            m_next = Piece('V');
            break;
        case PIECE_FOAM:
            m_next = Piece('F');
            break;
        case PIECE_CRAZY:
            m_next = Piece('C');
            break;
    }
}

//////////////////////////////////////////////////////////////
////////////////CHECK IF MOVES LEGAL//////////////////////////
//////////////////////////////////////////////////////////////
bool Tank::isOccupied(int r, int c)
{
    int x, y, row, col;
    for(int i = 0; i < (m_piece.getNumCoords()); i++)
    {
        Coord temp = m_piece.getCoord();
        x = temp.getX();
        y = temp.getY();
        row = y + r;
        col = x + c;
        if(m_tankArr[row][col] == '@' || m_tankArr[row][col] == '$' || m_tankArr[row][col] == '*')
            return true;
    }
    return false;
}


bool Tank::moveRightPossible()
{
    if(isOccupied(0, 1))
        return false;
    return true;
}

bool Tank::moveLeftPossible()
{
    if(isOccupied(0, -1))
        return false;
    return true;
}

bool Tank::moveDownPossible()
{
    if(isOccupied(1, 0))
        return false;
    return true;
}

bool Tank::rotatePossible()
{
    int x, y;
    Piece* temp = new Piece(m_piece);
    temp->rotateClockwise();
    for(int i = 0; i < (temp->getNumCoords()); i++)
    {
        Coord c = temp->getCoord();
        x = c.getX();
        y = c.getY();
        if(m_tankArr[y][x] == '@' || m_tankArr[y][x] == '$' || m_tankArr[y][x] == '*')
            return false;
    }
    delete temp;
    return true;
}


//////////////////////////////////////////////////////////////
//////////////////////MOVE PIECES/////////////////////////////
//////////////////////////////////////////////////////////////

void Tank::movePieceRight()
{
    if(moveRightPossible())
    {
        Piece* temp = new Piece(m_piece);
        temp->moveRight();
        m_piece = *temp;
        delete temp;
    }
}

void Tank::movePieceLeft()
{
    if(moveLeftPossible())
    {
        Piece* temp = new Piece(m_piece);
        temp->moveLeft();
        m_piece = *temp;
        delete temp;
    }
}

void Tank::rotatePiece()
{
    if(rotatePossible())
    {
        Piece* temp = new Piece(m_piece);
        temp->rotateClockwise();
        m_piece = *temp;
        delete temp;
    }
}

void Tank::movePieceDownOne()
{
    if(moveDownPossible())
    {
        Piece* temp = new Piece(m_piece);
        temp->moveDownOne();
        m_piece = *temp;
        delete temp;
    }
}


//////////////////////////////////////////////////////////////
////////////////DELETE PIECES ONCE DROPPED////////////////////
//////////////////////////////////////////////////////////////


//Clear out any of the full rows and return the number cleared out
int Tank::deleteFullRows()
{
    int numRowsEliminated = 0;
    bool rowFound;
    for(int i = 0; i < m_rows; i++)
    {
        rowFound = true;
        for(int j = 1; j < m_cols +1; j++)
        {
            if(m_tankArr[i][j] == ' ')
            {
                rowFound = false;
                break;
            }
        }
        if(rowFound)
        {
            numRowsEliminated++;
            moveRowRecursive(i);
            
            i--;
        }
    }
    return numRowsEliminated;
}
//overwrites the row to be deleted with the row above it and then
//does that until it replaces the top row with all whitespaces
void Tank::moveRowRecursive(int row)
{
    if(row == 0)
        for(int i = 1; i < m_cols + 1; i++)
            m_tankArr[0][i] = ' ';
    else
    {
        for(int i = 1; i < m_cols + 1; i++)
            m_tankArr[row][i] = m_tankArr[row - 1][i];
        moveRowRecursive(row - 1);
    }
}


//////////////////////////////////////////////////////////////
///////////TRANSLATE PIECE INTO TANK ARRAY////////////////////
//////////////////////////////////////////////////////////////

//translates a piece's coordinates to '$'s in the tankArr
void Tank::placePiece()
{
    if(m_piece.getType() == 'V')
        vaporBombExplode();
    else if(m_piece.getType() == 'F')
    {
        foamBombExplode(m_piece.getCoord());
    }
    else
    {
        for(int i = 0; i < m_piece.getNumCoords(); i++)
        {
            Coord c = m_piece.getCoord();
            m_tankArr[c.getY()][c.getX()] = '$';
        }
    }
}

//////////////////////////////////////////////////////////////
////SETS CURRENTLY DISPLAYED PIECE TO PIECE BEING PLAYED//////
//////////////////////////////////////////////////////////////


void Tank::setNextToCurrentPiece()
{
    m_piece = m_next;
    randPiece();
}

//////////////////////////////////////////////////////////////
////////////CLEARS TANK AFTER LEVEL HAS ENDED/////////////////
//////////////////////////////////////////////////////////////


void Tank::clearTank()
{
    for(int i = 0; i < m_rows; i++)
        for(int j = 1; j < m_cols + 1; j++)
            m_tankArr[i][j] = ' ';
}

//////////////////////////////////////////////////////////////
/////////////////////EXPLODES VAPORBOMB//////////////////////
//////////////////////////////////////////////////////////////

void Tank::vaporBombExplode()
{
    int x, y;
    for(int i = 0; i < m_piece.getNumCoords(); i++)
    {
        Coord c = m_piece.getCoord();
        x = c.getX();
        y = c.getY();
        for(int i = y - 2; i <= y + 2; i++)
        {
            if(i >= 0 && i < m_rows)
               if( m_tankArr[i][x] != '@')
                   m_tankArr[i][x] = ' ';
        }
    }
}

//////////////////////////////////////////////////////////////
/////////////////////EXPLODES FOAMBOMB////////////////////////
//////////////////////////////////////////////////////////////

void Tank::foamBombExplode(Coord explodeAt)
{
    int x = explodeAt.getX();
    int y = explodeAt.getY();
    if(!( x<= m_cols + 1 && x >= 1 && y >= 0 && y<= m_rows))
        return;
    char check = m_tankArr[y][x];
    int distanceFromX = x - m_piece.getCoord().getX();
    int distanceFromY = y - m_piece.getCoord().getY();
    if(distanceFromX <= 2 && distanceFromY <= 2 && distanceFromX >= -2 && distanceFromY >= -2 && x<= m_cols + 1 && x >= 1 && y >= 0 && y<= m_rows)
    {
        if(check == ' ' || check == '#')
        {
            m_tankArr[y][x] = '*';
            foamBombExplode(Coord(x, y + 1));
            foamBombExplode(Coord(x, y - 1));
            foamBombExplode(Coord(x + 1, y));
            foamBombExplode(Coord(x - 1, y));
        }
    }
}

