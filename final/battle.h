// battel.h
#pragma once

#include <string>
#include <vector>
#include <memory> // unique_ptr, make_unique

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
    Player &player_; //引用玩家
    std::vector<std::unique_ptr<Enemy>> enemies_;//敌人列表
    int round_;//回合数

public:
    Battle(Player &p) : player_(p), round_(0) {}
    void add_enemy(std::unique_ptr<Enemy> e) { enemies_.push_back(std::move(e)); }//加入敌人到敌人列表
    bool all_dead() const; //
    bool run_round(std::istream &in, std::ostream &out);
    int round() const;
};