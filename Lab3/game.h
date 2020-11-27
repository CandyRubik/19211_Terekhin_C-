#ifndef GAME_H
#define GAME_H
#include "gameri.h"
#include <memory>

class GamerI;

class Game
{
    std::unique_ptr<GamerI> FirstGP;
    std::unique_ptr<GamerI> SecondGP;
    bool nextSecond = true;
    bool firstUserStatus = false;
    bool secondUserStatus = false;
    std::pair<bool, std::pair<int, int>> userShot = {false, {0, 0}};
public:
    Game();

    ~Game();

    Game(Game &&rr);

    void switchNextSecond();

    bool getNextSecond();

    GamerI* getFirstGamer();

    GamerI* getSecondGamer();

    void setUserShot(std::pair<bool, std::pair<int, int>> p);

    bool move();

    bool getGamerUserStatus(int x);

    friend class GamerUser;
};

#endif // GAME_H
