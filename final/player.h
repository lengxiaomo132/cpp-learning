// player.h
#pragma once

#include <iostream>
#include <map>
#include <string>

#include "character.h"

class Player : public Character
{
private:
    std::map<std::string, int> bag_;
    bool defending_;

public:
    Player(std::string n, int h) : Character(n, h, 15), defending_(false)
    {
        bag_["potion"] = 3;
        bag_["bomb"] = 1;
    }
    void add_item(const std::string &item, int count)
    {
        bag_[item] += count;
        if (bag_[item] < 0)
            bag_[item] = 0;
    }
    bool use_item(const std::string &item)
    {
        auto it = bag_.find(item);
        if (it == bag_.end() || (*it).second == 0)
        {
            return false;
        }
        else
        {
            it->second -= 1;
            return true;
        }
    }
    int item_count(const std::string &item) const
    {
        auto it = bag_.find(item);
        if (it == bag_.end())
        {
            return 0;
        }
        else
        {
            return it->second;
        }
    }
    void set_defending(bool d) { defending_ = d; }
    int defense() const override
    {
        if (defending_ == true)
            return 5;
        else
            return 0;
    } // 防御时 5
    void print_bag() const
    {
        bool empty = false;
        std::cout << "Bag: ";
        for (const auto &[k, v] : bag_)
        {
            if (v != 0)
            {
                std::cout << k << " x" << v << ' ';
                empty = true;
            }
        }
        if (empty == false)
            std::cout << "(empty)";
        std::cout << '\n';
    }
};