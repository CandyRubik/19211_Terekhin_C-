#include "game.h"
#include "factory.h"


Game::Game()
{
    std::ifstream file2("info/MapS.txt");
    std::ifstream file1("info/MapF.txt");
    std::string str;
    for(int i = 0; i < 11; i++)
    {
        getline(file1, str);
    }
    file1.seekg(0);
    FirstGP.reset(Factory<GamerI, std::string, GamerI* (*)(std::ifstream &file)>::instance().makeBlock(str, file1));
    for(int i = 0; i < 11; i++)
    {
        getline(file2, str);
    }
    file2.seekg(0);
    SecondGP.reset(Factory<GamerI, std::string, GamerI* (*)(std::ifstream &file)>::instance().makeBlock(str, file2));
    if(FirstGP->getStatus())
        firstUserStatus = true;
    if(SecondGP->getStatus())
        secondUserStatus = true;
    file1.close();
    file2.close();
}

Game::~Game() {}

bool Game::getNextSecond() const
{
    return nextSecond;
}

GamerI* Game::getFirstGamer()
{
    return FirstGP.get();
}

GamerI* Game::getSecondGamer()
{
    return SecondGP.get();
}

void Game::switchNextSecond()
{
    nextSecond = !nextSecond;
}


void Game::move()
{
        if(nextSecond)
        {
            std::pair<int, int> shot = FirstGP->makeMove();
            std::vector<std::string>& enemyField = SecondGP->getField();
            if(enemyField[shot.first][shot.second] == '*')
            {
                enemyField[shot.first][shot.second] = 'X';
                FirstGP->getAffectedCells()++;
            }
            if(enemyField[shot.first][shot.second] == ' ')
            {
                enemyField[shot.first][shot.second] = '.';
            }
            if(FirstGP->getAffectedCells() == 22)
            {
                return;
            }
            switchNextSecond();
        }
        else
        {
            std::pair<int, int> shot = SecondGP->makeMove();
            std::vector<std::string>& enemyField = FirstGP->getField();
            if(enemyField[shot.first][shot.second] == '*')
            {
                enemyField[shot.first][shot.second] = 'X';
                SecondGP->getAffectedCells()++;
            }
            if(enemyField[shot.first][shot.second] == ' ')
            {
                enemyField[shot.first][shot.second] = '.';
            }
            if(SecondGP->getAffectedCells() == 22)
            {
                return;
            }
            switchNextSecond();
        }
        return;
}

void Game::setUserShot(std::pair<bool, std::pair<int, int>> p)
{
    userShot = p;
}

bool Game::getGamerUserStatus(int x) const
{
    if(x == 1)
        return firstUserStatus;
    else
        return secondUserStatus;
}
