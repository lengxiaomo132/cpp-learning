// enemy.h
#pragma once

#include <string>

#include "character.h"

class Enemy : public Character // 普通敌人类
{
public:
    Enemy(std::string n, int h, int a) : Character(n, h, a) {} // 创建敌人
    std::string type_name() const override { return "Enemy"; } // 类标注“敌人”
};

class Boss : public Enemy //  Boss类
{
private:
    int armor_; // Boss独有护甲
public:
    Boss(std::string n, int h, int a, int armor)
        : Enemy(n, h, a), armor_(armor) {}                    // 创建Boss，每个护甲不一样
    int defense() const override { return armor_; }           // 读取护甲值
    std::string type_name() const override { return "Boss"; } // 类标注“Boss”
};

std::ostream &operator<<(std::ostream &os, const Boss&c) // 打印Boss信息“[Boss].name(hp=.hp/.max_hp)”
{
    os << "[Boss]" << c.get_name() << "(hp=" << c.get_hp() << '/' << c.get_max_hp() << ')' << '\n';
    return os;
};

class Elite : public Enemy // 精英敌人类
{
    Elite(std::string n, int h, int a) : Enemy(n, h, a) {}     // 创建精英敌人
    std::string type_name() const override { return "Elite"; } // 类标注“精英”
};