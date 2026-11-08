// enemy.h
#pragma once

#include <string>

class Enemy
{
private:
    std::string name;
    int hp;

public:
    Enemy(std::string n, int h);
    std::string get_name() const;
    int get_hp() const;
    void take_damage(int dmg);
    bool is_alive() const;
};
