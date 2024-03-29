#include "game.h"
#include "factory.h"

GamerI* createGamerRandom(std::ifstream &file) {
    return new GamerRandom(file);
}

static bool add_creatorGamerRandom()
{
    Factory<GamerI, std::string, GamerI* (*)(std::ifstream &file)>::instance().addCreator("Random strategy", createGamerRandom);
    return true;
}
static bool b = add_creatorGamerRandom();

GamerRandom::GamerRandom(std::ifstream &file)
{
    std::string str;
    for(size_t i = 0; i < 10; i++)
    {
        getline(file, str);
        field.push_back(str + '\n');
        enemyField.push_back("          ");
    }
}

GamerRandom::~GamerRandom() {}

std::pair<int, int> GamerRandom::makeMove()
{
    if(!generated)
    {
        if(Game::instance().getNextSecond())
        {
            enemyField = Game::instance().getSecondGamer()->getField();
        }
        else
        {
            enemyField = Game::instance().getFirstGamer()->getField();
        }
        while(true)
        {
            int x = rand() % 10;
            int y = rand() % 10;
            if(enemyField[x][y] == ' ' || enemyField[x][y] == '*')
            {
                generated = true;
                shotPos = {x, y};
                return shotPos;
            }
        }
    }
    else
    {
        generated = false;
        return shotPos;
    }
}

int& GamerRandom::getAffectedCells()
{
    return affectedCells;
}

std::vector<std::string>& GamerRandom::getField()
{
    return field;
}

bool GamerRandom::getStatus() const
{
    return false;
}
