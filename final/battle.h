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
    Player &player_;                              // 引用玩家
    std::vector<std::unique_ptr<Enemy>> enemies_; // 敌人列表
    int round_;                                   // 回合数

public:
    Battle(Player &p) : player_(p), round_(0) {}                                   // 创建战斗类，初始回合数为1
    void add_enemy(std::unique_ptr<Enemy> e) { enemies_.push_back(std::move(e)); } // 加入敌人到敌人列表
    bool all_dead() const                                                          // 检查敌人存活
    {
        for (const auto &p : enemies_)
        {
            if (p->is_alive() == true)
                return false;
        }
        return true;
    }
    bool run_round(std::istream &in, std::ostream &out)
    {
        round_++;
        out << "\n=== 第 " << round_ << " 回合 ===\n";
        { // 打印敌人信息
            out << "Enemies:\n";
            int order = 0;
            for (const auto &p : enemies_)
            {

                if (p->is_alive() == true)
                    order++;
                out << order << '.' << *p;
            }
        }
        out << player_; // 打印玩家信息

        // 选择动作
        out << "Action\n1.Attack 2.Defend 3.Item 4.Flee(输入数字)\n>";
        int choice = 0;
        in >> choice;
        if (in.fail())
        {
            in.clear();
            in.ignore(1000, '\n');
            out << "请输入数字\n";
            return true;
        }
        Action a = Action::Attack;
        if (choice == 1)
            a = Action::Attack;
        else if (choice == 2)
            a = Action::Defend;
        else if (choice == 3)
            a = Action::Item;
        else if (choice == 4)
            a = Action::Flee;
        else
            a = Action::Unknown;
            
        //执行动作
        switch (a)
        {
        case Action::Attack:
            std::cout << "玩家选择：攻击\n"
                      << "攻击目标，造成10点伤害";
            break;
        case Action::Defend:
            std::cout << "玩家选择：防御\n"
                      << "你的防御力提升，本回合受到的伤害减少";
            break;
        case Action::Flee:
            std::cout << "玩家选择：逃跑\n"
                      << "成功逃跑了";
            break;
        case Action::Unknown:
            std::cout << "玩家选择：未知 (" << choice << ")\n"
                      << "输入无效，本回合无法行动。";
            break;
        default: // 兜底：以后加新枚举值时能发现
            std::cout << "内部错误：未处理的动作\n";
            break;
        }
    }
    int round() const;
};