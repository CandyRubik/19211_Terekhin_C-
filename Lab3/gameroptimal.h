#ifndef GAMEROPTIMAL_H
#define GAMEROPTIMAL_H

#include "gameri.h"
#include <string>
#include <vector>
#include <fstream>

class Game;

class GamerOptimal : public GamerI
{
    std::vector<std::string> field;
    std::vector<std::string> enemyField;
    std::vector<std::pair<int, int>> battleshipTactic = { {0, 3}, {1, 2}, {2, 1}, {3, 0}, {0, 7}, {1, 6}, {2, 5}, {3, 4}, {4, 3}, {5, 2}, {6, 1}, {7,0}, {2, 9}, {3, 8}, {4, 7}, {5, 6}, {6, 5}, {7, 4}, {8, 3}, {9, 2}, {6, 9}, {7, 8}, {8, 7}, {9, 6} };
    std::vector<std::pair<int, int>> cruiserTactic = { {0, 1}, {1, 0}, {0, 5}, {1, 4}, {2, 3}, {3, 2}, {4, 1}, {5, 0}, {0, 9}, {1, 8}, {2, 7}, {3, 6}, {4, 5}, {5, 4}, {6, 3}, {7, 2}, {8, 1}, {9, 0}, {4, 9}, {5, 8}, {6, 7}, {7, 6}, {8, 5}, {9, 4}, {8, 9}, {9, 8}};
    int affectedCells = 0;
    bool battleshipKillingStatus = false;
    bool cruiserKillingStatus = false;
    bool generated = false;
    std::pair<int, int> shotPos;
public:
    GamerOptimal(std::ifstream &file);

    virtual std::pair<int, int> makeMove() override;

    virtual ~GamerOptimal();

    int& getAffectedCells() override;

    std::vector<std::string>& getField() override;

    bool battleshipKillConfirmation(std::vector<std::string> field);

    bool cruiserKillConfirmation(std::vector<std::string> field);

    bool finish(std::vector<std::pair<int, int>>::iterator it, std::vector<std::string> enemyField, int numberOfDecs);
};

#endif // GAMEROPTIMAL_H
