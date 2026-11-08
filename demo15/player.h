// player.h —— 声明：告诉别人"有这些东西"
#pragma once

#include <string>

class Player
{
private:
    std::string name;
    int hp;

public:
    Player(std::string n, int h);
    std::string get_name() const;
    int get_hp() const;
    void take_damage(int dmg);
};