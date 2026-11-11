//character.h
#pragma once

#include <string>

class Character
{
    protected:
    std::string name;
    int hp;
    int max_hp;
    int atk;

    public:
    Character(std::string n, int h) : name(n), hp(h) {}

    std::string get_name() const { return name; }
    int get_hp() const { return hp; }
    int get_atk() const { return atk; }

};