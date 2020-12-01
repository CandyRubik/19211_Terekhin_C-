#include "game.h"
#include "factory.h"

GamerI* createGamerUser(std::ifstream &file) {
    return new GamerUser(file);
}

static bool add_creatorGamerUser()
{
    Factory<GamerI, std::string, GamerI* (*)(std::ifstream &file)>::instance().addCreator("User", createGamerUser);
    return true;
}
static bool a = add_creatorGamerUser();

GamerUser::GamerUser(std::ifstream &file) : GamerI()
{
    std::string str;
    for(int i = 0; i < 10; i++)
    {
        getline(file, str);
        field.push_back(str + '\n');
    }
}
std::pair<int, int> GamerUser::makeMove()
{
    return Game::instance().userShot.second;
}

GamerUser::~GamerUser() {}

std::vector<std::string>& GamerUser::getField()
{
    return field;
}


int& GamerUser::getAffectedCells()
{
    return affectedCells;
}

bool GamerUser::getStatus() const
{
    return true;
}
