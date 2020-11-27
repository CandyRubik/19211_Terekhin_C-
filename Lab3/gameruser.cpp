#include "gameruser.h"
#include "gameri.h"
#include "game.h"

GamerUser::GamerUser(std::ifstream &file) : GamerI()
{
    std::string str;
    for(int i = 0; i < 10; i++)
    {
        getline(file, str);
        field.push_back(str + '\n');
    }
}
std::pair<int, int> GamerUser::makeMove(Game& game)
{
    return game.userShot.second;
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
