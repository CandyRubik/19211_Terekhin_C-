#ifndef GAMERUSER_H
#define GAMERUSER_H

#include "gameri.h"
#include <string>
#include <vector>
#include <fstream>


class GamerUser : public GamerI
{
    std::vector<std::string> field;
    int affectedCells = 0;
public:
    GamerUser(std::ifstream &file);

    virtual std::pair<int, int> makeMove() override;

    virtual ~GamerUser();

    int& getAffectedCells() override;

    std::vector<std::string>& getField() override;
};

#endif // GAMERUSER_H
