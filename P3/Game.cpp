#include "Game.h"
#include "UserInterface.h"
#include <string>
#include <cmath>

///////////////////////////////////////////////////
////////////////////CONST VARS/////////////////////
///////////////////////////////////////////////////

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int TANK_X = 0;
const int TANK_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

///////////////////////////////////////////////////
////////////////////CONSTRUCTOR////////////////////
///////////////////////////////////////////////////

Game::Game(int width, int height)
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_score(0),
m_tank(width, height), m_rowsGone(0)
{}
///////////////////////////////////////////////////
//////////////////PLAY FUNCTIONS///////////////////
///////////////////////////////////////////////////
void Game::play()
{
    //  score, rows left, level
    displayTankArr();
    displayStatus();
    displayPrompt("Press the Enter key to begin playing Imitris!");
    m_screen.refresh();
    waitForEnter();  // [in UserInterface.h]
    
    for(;;)
    {
        if ( ! playOneLevel())
            break;
        m_level++;
        m_rowsGone = 0;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_tank.clearTank();
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

bool Game::playOneLevel()
{
    int time = getGameTimeMS();
    int endTime = 0, b = 0, numRowsGone = 0;
    bool oneMore;
    m_tank.randPiece();
    m_tank.setNextToCurrentPiece();
    while(5 * m_level > m_rowsGone)//if the level is currently being played
    {
        m_tank.setNextToCurrentPiece();
        if(m_tank.isOccupied(0,0))//if the first spot is occupied, return true
        {
            displayGame();
            return false;
        }
        
        displayGame();
        oneMore = true;
        while(m_tank.moveDownPossible() || oneMore)
        {
            endTime = getMsecSinceStart() + time;
            if(!m_tank.moveDownPossible())
                oneMore = false;
            
            // Repeat as long as current time has not yet reached the end time
            while (getMsecSinceStart() < endTime)
            {
                b = getInput();
                if(b == 1)
                    break;
                if(b == 2)
                    break;
                if(b == -1)
                    return false;
            }
            if(b == 2)
                break;
            if(m_tank.moveDownPossible())
                m_tank.movePieceDownOne();
            //after time to move piece is up
            displayGame();
        }
        m_tank.placePiece();
        numRowsGone = m_tank.deleteFullRows();
        displayGame();
        updateScore(numRowsGone);
    }
    m_screen.refresh();
    displayTankArr();
    displayStatus();
    displayNextPiece();
    return true;
}

///////////////////////////////////////////////////
///////////////DISPLAY FUNCTIONS///////////////////
///////////////////////////////////////////////////

void Game::displayGame()
{
    displayTankArr();
    displayPiece();
    displayNextPiece();
    displayStatus();
    m_screen.refresh();
}

void Game::displayTankArr()
{
    m_tank.display(m_screen, TANK_X, TANK_Y);
}

void Game::displayPiece()
{
    m_tank.getPiece().display(m_screen, TANK_X, TANK_Y);
}

void Game::displayNextPiece()
{
    m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
    m_screen.printString("Next piece:");
    m_tank.getNextPiece().display(m_screen, (NEXT_PIECE_X - 4), NEXT_PIECE_Y);//subtract 4 because the piece starts at (4,0)
}

void Game::displayPrompt(std::string s)
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
    //displays the score
    m_screen.gotoXY(SCORE_X, SCORE_Y);
    m_screen.printString("Score:     ");
    std::string s = rightJustify(std::to_string(m_score));
    m_screen.printString(s);
    //displays the rows left
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    m_screen.printString("Rows left: ");
    int x = (5 * m_level) - m_rowsGone;
    if(x < 0)
        x = 0;
    std::string rowsLeft = rightJustify(std::to_string(x));//looked to_string up. couldn't find a better way to do this
    m_screen.printString(rowsLeft);
    //prints the current level
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    m_screen.printString("Level:     ");
    std::string level = rightJustify(std::to_string(m_level));
    m_screen.printString(level);
    m_screen.refresh();
}

///////////////////////////////////////////////////
//////////////////MISC FUNCTIONS///////////////////
///////////////////////////////////////////////////

void Game::updateScore(int nRows)
{
    m_rowsGone += nRows;
    if(nRows > 0)
        m_score += (pow((double)2, double((nRows - 1))))*100;
}

int Game::getGameTimeMS()
{
    int t = 1000-(100*(m_level-1));
    if(t > 100)
        return t;
    else
        return 100;
}

int Game::getInput()
{
    char ch;
    if (getCharIfAny(ch))
    {
        switch(ch)
        {
            case ARROW_DOWN: //move down one row
            case 's':
                m_tank.movePieceDownOne();
                if(!m_tank.moveDownPossible())
                    return 1;   //return 1 to break out of one loop
                displayGame();
                break;
            case 'Q':
            case 'q':
                return -1;  //return -1 to end game
                break;
            case ' ':
                while(m_tank.moveDownPossible())
                {
                    m_tank.movePieceDownOne();
                }
                return 2; //return 2 to break out of two loops
                break;
            default:
                break;
        }
        if(m_tank.getPiece().getType() == 'C')
        {
            switch (ch)
            {
                case ARROW_LEFT: //move left
                case 'a':
                    m_tank.movePieceRight();
                    displayGame();
                    break;
                case ARROW_RIGHT: //move right
                case 'd':
                    m_tank.movePieceLeft();
                    displayGame();
                    break;
                case ARROW_UP: //rotate clockwise
                case 'w':
                    m_tank.rotatePiece();
                    displayGame();
                    break;
                default:
                    break;
            }
        }
        
        else
        {
            switch (ch)
            {
                case ARROW_LEFT: //move left
                case 'a':
                    //case '4': same as ARROW_LEFT
                    m_tank.movePieceLeft();
                    displayGame();
                    break;
                case ARROW_RIGHT: //move right
                case 'd':
                    //case '6':
                    m_tank.movePieceRight();
                    displayGame();
                    break;
                case ARROW_UP: //rotate clockwise
                case 'w':
                    
                    m_tank.rotatePiece();
                    displayGame();
                    break;
                default:
                    break;
            }
        }
        displayGame();
    }
    return 0;
}

std::string Game::rightJustify(std::string str)
{
    std::string s = "";
    for(int i = 0; i < 7 - str.length(); i++)
        s+=" ";
    s += str;
    return s;
}



