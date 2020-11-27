#ifndef GAMERRANDOM_H
#define GAMERRANDOM_H

#include "gameri.h"
#include <string>
#include <vector>
#include <fstream>

class GamerRandom : public GamerI
{
    std::vector<std::string> field;
    std::vector<std::string> enemyField;
    int affectedCells = 0;
    bool generated = false;
    std::pair<int, int> shotPos;
public:
    GamerRandom(std::ifstream &file);

    virtual std::pair<int, int> makeMove(Game& game) override;

    virtual ~GamerRandom();

    int& getAffectedCells() override;

    std::vector<std::string>& getField() override;
};

#endif // GAMERRANDOM_H
