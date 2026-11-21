// battel.h
#pragma once

#include <string>
#include <vector>
#include <memory> // unique_ptr, make_unique
#include <chrono>
#include <thread>

#include "player.h"
#include "enemy.h"

enum class Action
{
    Attack,
    Defend,
    Item,
    Flee,
    Unknown
};

class Battle
{
private:
    Player &player_;                              // 引用玩家
    std::vector<std::unique_ptr<Enemy>> enemies_; // 敌人列表
    int round_;                                   // 回合数

public:
    Battle(Player &p) : player_(p), round_(0) {} // 创建战斗类，初始回合数为1

    void add_enemy(std::unique_ptr<Enemy> e);

    bool all_dead() const; // 检查敌人存活

    int check_input(std::istream &in);

    void print_eneies(); // 打印敌人信息

    bool run_round(std::istream &in, std::ostream &out); // 战斗回合功能
    int get_round() const { return round_; };
};