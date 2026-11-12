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
    Character(std::string n, int h, int a);
    virtual ~Character() = default;

    std::string get_name() const;
    int get_hp() const;
    int get_max_hp() const;
    int get_atk() const;
    bool is_alive() const;
    void take_damage(int dmg);        // hp 不为负

    virtual int defense() const { return 0; }
    virtual std::string type_name() const { return "角色"; }
};

std::ostream &operator<<(std::ostream &os, const Character &c);