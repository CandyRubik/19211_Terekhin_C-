#include "gameroptimal.h"

GamerOptimal::GamerOptimal(std::ifstream &file) : GamerI()
{
    std::string str;
    for(int i = 0; i < 10; i++)
    {
        getline(file, str);
        field.push_back(str + '\n');
        enemyField.push_back("          ");
    }
}

GamerOptimal::~GamerOptimal() {}

std::pair<int, int> GamerOptimal::makeMove(Game &game)
{
    if(!generated)
    {
        if(game.getNextSecond())
        {
            enemyField = game.getSecondGamer()->getField();
        }
        else
        {
            enemyField = game.getFirstGamer()->getField();
        }
        if(!battleshipKillingStatus && !battleshipKillConfirmation(enemyField)) // if the battleship is not killed
        {
            for(auto it = battleshipTactic.begin(); it != battleshipTactic.end(); ++it)
            {
                if(enemyField[it->first][it->second] == 'X' && finish(it, enemyField, 4))
                {
                    return shotPos;
                }
                if(enemyField[it->first][it->second] == '.')
                {
                    continue;
                }
                if(enemyField[it->first][it->second] == ' ' || enemyField[it->first][it->second] == '*')
                {
                    generated = true;
                    shotPos = {it->first, it->second};
                    return shotPos;
                }
            }
        }
        if(!cruiserKillingStatus && !cruiserKillConfirmation(enemyField)) // if the cruisers is not killed
        {
            for(auto it = cruiserTactic.begin(); it != cruiserTactic.end(); ++it)
            {
                if(enemyField[it->first][it->second] == 'X' && finish(it, enemyField, 3))
                {
                    return shotPos;
                }
                if(enemyField[it->first][it->second] == '.')
                {
                    continue;
                }
                if(enemyField[it->first][it->second] == ' ' || enemyField[it->first][it->second] == '*')
                {
                    generated = true;
                    shotPos = {it->first, it->second};
                    return shotPos;
                }
            }
        }
        else
        {
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
    }
    else
    {
        generated = false;
        return shotPos;
    }
}

int& GamerOptimal::getAffectedCells()
{
    return affectedCells;
}

std::vector<std::string>& GamerOptimal::getField()
{
    return field;
}

bool GamerOptimal::battleshipKillConfirmation(std::vector<std::string> field)
{
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 7; j++)
        {
            if(field[i][j] == 'X' && field[i][j + 1] == 'X' && field[i][j + 2] == 'X' && field[i][j + 3] == 'X')
            {
               battleshipKillingStatus = true;
               return true;
            }
            if(field[j][i] == 'X' && field[j + 1][i] == 'X' && field[j + 2][i] == 'X' && field[j + 3][i] == 'X')
            {
               battleshipKillingStatus = true;
               return true;
            }
        }
    return false;
}

bool GamerOptimal::cruiserKillConfirmation(std::vector<std::string> field)
{
    int count = 0;
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 8; j++)
        {
            if(field[i][j] == 'X' && field[i][j + 1] == 'X' && field[i][j + 2] == 'X')
            {
               count++;
            }
            if(field[j][i] == 'X' && field[j + 1][i] == 'X' && field[j + 2][i] == 'X')
            {
               count++;
            }
        }
    if(count == 3)
    {
        cruiserKillingStatus = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool GamerOptimal::finish(std::vector<std::pair<int, int>>::iterator it, std::vector<std::string> enemyField, int numberOfDecs)
{
    if((it->first - 1 >= 0) && enemyField[it->first - 1][it->second] == '*')
    {
        generated = true;
        shotPos = {it->first - 1, it->second};
        return generated;
    }
    if((it->first + 1 <= 9) && enemyField[it->first + 1][it->second] == '*')
    {
        generated = true;
        shotPos = {it->first + 1, it->second};
        return generated;
    }
    if((it->second + 1 <= 9) && enemyField[it->first][it->second + 1] == '*')
    {
        generated = true;
        shotPos = {it->first, it->second + 1};
        return generated;
    }
    if((it->second - 1 >= 0) && enemyField[it->first][it->second - 1] == '*')
    {
        generated = true;
        shotPos = {it->first, it->second - 1};
        return generated;
    }
    if((it->first - 2 >= 0) && enemyField[it->first - 2][it->second] == '*')
    {
        generated = true;
        shotPos = {it->first - 2, it->second};
        return generated;
    }
    if((it->first + 2 <= 9) && enemyField[it->first + 2][it->second] == '*')
    {
        generated = true;
        shotPos = {it->first + 2, it->second};
        return generated;
    }
    if((it->second + 2 <= 9) && enemyField[it->first][it->second + 2] == '*')
    {
        generated = true;
        shotPos = {it->first, it->second + 2};
        return generated;
    }
    if((it->second - 2 >= 0) && enemyField[it->first][it->second - 2] == '*')
    {
        generated = true;
        shotPos = {it->first, it->second - 2};
        return generated;
    }
    if(numberOfDecs == 4)
    {
        if((it->first - 3 >= 0) && enemyField[it->first - 3][it->second] == '*')
        {
            generated = true;
            shotPos = {it->first - 3, it->second};
            return generated;
        }
        if((it->first + 3 <= 9) && enemyField[it->first + 3][it->second] == '*')
        {
            generated = true;
            shotPos = {it->first + 3, it->second};
            return generated;
        }
        if((it->second + 3 <= 9) && enemyField[it->first][it->second + 3] == '*')
        {
            generated = true;
            shotPos = {it->first, it->second + 3};
            return generated;
        }
        if((it->second - 3 >= 0) && enemyField[it->first][it->second - 3] == '*')
        {
            generated = true;
            shotPos = {it->first, it->second - 3};
            return generated;
        }
    }
    return generated;
}
