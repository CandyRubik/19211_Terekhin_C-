#ifndef GAMERI_H
#define GAMERI_H

#include <vector>
#include <string>


class GamerI
{
public:
    virtual std::pair<int, int> makeMove() = 0;

    virtual std::vector<std::string>& getField() = 0;

    virtual int& getAffectedCells() = 0;

    virtual bool getStatus() const = 0;

    virtual ~GamerI() {}
};

#endif // GAMER_H
