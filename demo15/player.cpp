// player.cpp —— 实现：具体怎么工作
#include "player.h"

Player::Player(std::string n, int h) : name(n), hp(h) {}

std::string Player::get_name() const { return name; }
int Player::get_hp() const { return hp; }

void Player::take_damage(int dmg)
{
    hp -= dmg;
    if (hp < 0) hp = 0;
}