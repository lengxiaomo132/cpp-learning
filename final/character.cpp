// character.cpp
#include "character.h"

Character::Character(std::string n, int h, int a)
    : name(n), hp(h), max_hp(h), atk(a) {}

void Character::healing(int heal) // 回血
{
    hp += heal;
    if (hp > max_hp)
        hp = max_hp;
}

void Character::take_damage(int dmg) // 打伤害
{
    hp -= dmg;
    if (hp < 0)
        hp = 0; // hp 不为负
}

std::ostream &operator<<(std::ostream &os, const Character &c) // 打印角色信息“.name(hp=.hp/.max_hp)”
{
    os << c.get_name() << "(hp=" << c.get_hp() << '/' << c.get_max_hp() << ')';
    return os;
};