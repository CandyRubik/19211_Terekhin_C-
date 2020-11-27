#include "gameruser.h"
#include "game.h"
#include "gameroptimal.h"
#include "gamerrandom.h"
#include <QDir>


inline constexpr std::uint32_t fnv1a(const char* str, std::uint32_t hash = 2166136261UL) {
    return *str ? fnv1a(str + 1, (hash ^ *str) * 16777619ULL) : hash;
}

Game::Game()
{
    //std::ifstream file2("D:/LabsC++/Lab3/info/MapS.txt");
    std::ifstream file2("info/MapS.txt");
    //std::ifstream file1("D:/LabsC++/Lab3/info/MapF.txt");
    std::ifstream file1("info/MapF.txt");
    std::string str;
    for(int i = 0; i < 11; i++)
    {
        getline(file1, str);
    }
    file1.seekg(0);
    switch (fnv1a(str.c_str())) {
    case fnv1a("User"):
        FirstGP = std::make_unique<GamerUser>(file1);
        firstUserStatus = true;
        break;
    case fnv1a("Random strategy"):
        FirstGP = std::make_unique<GamerRandom>(file1);
        break;
    case fnv1a("Optimal strategy"):
        FirstGP = std::make_unique<GamerOptimal>(file1);
        break;
    }
    for(int i = 0; i < 11; i++)
    {
        getline(file2, str);
    }
    file2.seekg(0);
    switch (fnv1a(str.c_str())) {
    case fnv1a("User"):
       SecondGP = std::make_unique<GamerUser>(file2);
       secondUserStatus = true;
        break;
    case fnv1a("Random strategy"):
        SecondGP = std::make_unique<GamerRandom>(file2);
        break;
    case fnv1a("Optimal strategy"):
        SecondGP = std::make_unique<GamerOptimal>(file2);
        break;
    }
}

Game::~Game() {}

bool Game::getNextSecond()
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

Game::Game(Game &&rr) : FirstGP(std::move(rr.FirstGP)), SecondGP(std::move(rr.SecondGP)), nextSecond(rr.nextSecond)
{
    rr.FirstGP = nullptr;
    rr.SecondGP = nullptr;
}

bool Game::move()
{
        if(nextSecond)
        {
            std::pair<int, int> shot = FirstGP->makeMove(*this);
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
                return true;
            }
            switchNextSecond();
        }
        else
        {
            std::pair<int, int> shot = SecondGP->makeMove(*this);
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
                return true;
            }
            switchNextSecond();
        }
        return false;
}

void Game::setUserShot(std::pair<bool, std::pair<int, int>> p)
{
    userShot = p;
}

bool Game::getGamerUserStatus(int x)
{
    if(x == 1)
        return firstUserStatus;
    else
        return secondUserStatus;
}
