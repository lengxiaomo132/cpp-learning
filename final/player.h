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
    Player(std::string n, int h); // 创建玩家
    // 背包相关函数
    void add_item(const std::string &item, int count); // 加物品函数
    bool use_item(const std::string &item);            // 消耗物品函数
    int item_count(const std::string &item) const;     // 提物品数量，输入物品名，未定义物品按0算
    void print_bag() const;                            // 打印背包所有物品，空时输出“(empty)”
    // 防御相关函数
    void set_defending(bool d) { defending_ = d; } // 修改防御状态
    int defense() const override;                  // 提防御值
};