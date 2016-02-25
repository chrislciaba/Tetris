#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Tank.h"
#include "UserInterface.h"
#include <string>
// [Add other #include directives as necessary.]
class Game
{
public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    void playLevel();
    void displayGame();
    void displayTankArr();
    void updateScore(int nRows);
    int getGameTimeMS();
    void displayPiece();
    void displayNextPiece();
    int getInput();
    std::string rightJustify(std::string str);
private:
    Tank    m_tank;
    Screen  m_screen;
    int     m_level;
    int     m_score;
    int     m_rowsGone;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
