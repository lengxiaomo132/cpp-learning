// character.h
#pragma once

#include <string>
#include <ostream>

class Character
{
protected:
    std::string name;
    int hp;
    int max_hp;
    int atk;

public:
    Character(std::string n, int h, int a): name(n), hp(h), max_hp(h), atk(a){}
    virtual ~Character() = default;

    std::string get_name() const { return name; }
    int get_hp() const { return hp; }
    int get_max_hp() const { return max_hp; }
    int get_atk() const { return atk; }
    bool is_alive() const { return hp > 0; }
    void take_damage(int dmg)
    {
        hp -= dmg;
        if (hp < 0)
            hp = 0;
    } // hp 不为负

    virtual int defense() const { return 0; }
    virtual std::string type_name() const { return "Character"; }
};

std::ostream &operator<<(std::ostream &os, const Character &c)
{
    os << c.get_name() << "(hp=" << c.get_hp() <<'/'<<c.get_max_hp()<<')' << '\n';
    return os;
};