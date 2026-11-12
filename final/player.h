//player.h
#pragma once

#include <string>
#include "character.h"
#include <map>

class Player : public Character
{
private:
    std::map<std::string, int> bag_;
    bool defending_;

public:
    Player(std::string n, int h);
    void add_item(const std::string &item, int count);
    bool use_item(const std::string &item);
    int item_count(const std::string &item) const;
    void set_defending(bool d);
    int defense() const override;      // 防御时 5
    void print_bag() const;
};