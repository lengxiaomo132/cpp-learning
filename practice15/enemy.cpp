// enemy.cpp
#include "enemy.h"

Enemy::Enemy(std::string n, int h) : name(n), hp(h) {}

std::string Enemy::get_name() const { return name; }
int Enemy::get_hp() const { return hp; }
void Enemy::take_damage(int dmg)
{
    hp -= dmg;
    if (hp < 0)
    {
        hp = 0;
    }
}
bool Enemy::is_alive() const { return hp > 0; }