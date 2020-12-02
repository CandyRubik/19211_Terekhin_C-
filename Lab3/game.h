#ifndef GAME_H
#define GAME_H
#include "gameri.h"
#include "gameruser.h"
#include "gameroptimal.h"
#include "gamerrandom.h"
#include <memory>


class Game
{
    std::unique_ptr<GamerI> FirstGP;
    std::unique_ptr<GamerI> SecondGP;
    bool nextSecond = true;
    bool firstUserStatus = false;
    bool secondUserStatus = false;
    std::pair<bool, std::pair<int, int>> userShot = {false, {0, 0}};
public:

    static Game& instance()
    {
        static Game game;
        return game;
    }

    ~Game();

    void switchNextSecond();

    bool getNextSecond() const;

    GamerI* getFirstGamer();

    GamerI* getSecondGamer();

    void setUserShot(std::pair<bool, std::pair<int, int>> p);

    void move();

    bool getGamerUserStatus(int x) const;

    friend std::pair<int, int> GamerUser::makeMove();
    friend std::pair<int, int> GamerOptimal::makeMove();
    friend std::pair<int, int> GamerRandom::makeMove();
private:
    explicit Game();

    Game(Game const&);

    Game& operator=(Game const&);
};

#endif // GAME_H
