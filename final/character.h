// character.h
#pragma once

#include <string>
#include <ostream>

class Character // 角色类
{
protected:
    std::string name; // 名字
    int hp;           // 血量
    int max_hp;       // 最大血量
    int atk;          // 攻击

public:
    Character(std::string n, int h, int a); // 创建角色
    virtual ~Character() = default;         // 虚析构

    // getter函数
    std::string get_name() const { return name; }
    int get_hp() const { return hp; }
    int get_max_hp() const { return max_hp; }
    int get_atk() const { return atk; }
    bool is_alive() const { return hp > 0; }
    virtual int defense() const { return 0; } // 提防御值，角色固定类为0

    void healing(int heal);    // 回血
    void take_damage(int dmg); // 打伤害

    virtual std::string type_name() const { return "Character"; } // 类标签“角色”
};

std::ostream &operator<<(std::ostream &os, const Character &c); // 打印角色信息“.name(hp=.hp/.max_hp)”