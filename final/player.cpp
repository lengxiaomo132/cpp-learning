// player.cpp
#include "player.h"

Player::Player(std::string n, int h)
    : Character(n, h, 15), defending_(false) // 创建玩家
{                                            // 初始背包内容
    bag_["potion"] = 0;
    bag_["bomb"] = 0;
}
void Player::add_item(const std::string &item, int count) // 加物品函数
{
    bag_[item] += count;
    if (bag_[item] < 0)
        bag_[item] = 0;
}

bool Player::use_item(const std::string &item) // 消耗物品函数
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

int Player::item_count(const std::string &item) const // 提物品数量，输入物品名，未定义物品按0算
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

void Player::print_bag() const // 打印背包所有物品，空时输出“(empty)”
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

int Player::defense() const // 提防御值
{
    if (defending_ == true)
        return 5; // 防御时防御值为5
    else
        return 0;
}
