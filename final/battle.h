//battel.h
#pragma once

#include <string>
#include "player.h"
#include "enemy.h"
#include <vector>
#include <memory> // unique_ptr, make_unique

enum class Action { Attack, Defend, Item, Flee, Unknown };

class Battle
{
private:
    Player &player_;
    std::vector<std::unique_ptr<Enemy>> enemies_;
    int round_;

public:
    Battle(Player &p):player_(p), round_(0) {}
    void add_enemy(std::unique_ptr<Enemy> e){enemies_.push_back(std::move(e));}
    bool all_dead() const;
    bool run_round(std::istream &in, std::ostream &out);
    int round() const;
};