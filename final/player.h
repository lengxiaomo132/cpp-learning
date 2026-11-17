// player.h
#pragma once

#include <iostream>
#include <map>
#include <string>

#include "character.h"

class Player : public Character // 玩家类
{
private:
    std::map<std::string, int> bag_; // 容器背包
    bool defending_;                 // 防御状态

public:
    Player(std::string n, int h) : Character(n, h, 15), defending_(false) // 创建玩家
    {                                                                     // 初始背包内容
        bag_["potion"] = 3;
        bag_["bomb"] = 1;
    }
    // 背包相关函数
    void add_item(const std::string &item, int count) // 加物品函数
    {
        bag_[item] += count;
        if (bag_[item] < 0)
            bag_[item] = 0;
    }
    bool use_item(const std::string &item) // 消耗物品函数
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
    int item_count(const std::string &item) const // 提物品数量，输入物品名，未定义物品按0算
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
    void print_bag() const // 打印背包所有物品，空时输出“(empty)”
    {
        bool empty = true;
        std::cout << "Bag: "; // 打印开头
        for (const auto &[k, v] : bag_)
        {
            if (v != 0)
            {
                std::cout << k << " x" << v << ' '; // 打印内容物
                if (empty == true)
                    empty = false; // 检测empty，避免重复赋值
            }
        }
        if (empty == true)
            std::cout << "(empty)";
        std::cout << '\n';
    }
    // 防御相关函数
    void set_defending(bool d) { defending_ = d; } // 修改防御状态
    int defense() const override                   // 提防御值
    {
        if (defending_ == true)
            return 5; // 防御时防御值为5
        else
            return 0;
    }
};