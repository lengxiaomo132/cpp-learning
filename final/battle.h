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
    Battle(Player &p) : player_(p), round_(0) {} // 创建战斗类，初始回合数为1
    void add_enemy(std::unique_ptr<Enemy> e)
    {
        enemies_.push_back(std::move(e)); // 加入敌人到敌人列表
    }
    bool all_dead() const // 检查敌人存活
    {
        for (const auto &p : enemies_)
        {
            if (p->is_alive() == true)
                return false;
        }
        return true;
    }
    void print_eneies() // 打印敌人信息
    {
        std::cout << "Enemies:\n";
        int order = 0;
        for (const auto &p : enemies_)
        {

            if (p->is_alive() == true)
                order++;
            std::cout << order << '.' << *p;
        }
    }

    bool run_round(std::istream &in, std::ostream &out) // 战斗回合功能
    {
        round_++;
        out << "\n=== 第 " << round_ << " 回合 ===\n";

        out << player_; // 打印玩家信息
        print_eneies();
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

        // 执行动作
        switch (a)
        {
        case Action::Attack:
            out << "玩家选择：攻击\n";
            print_eneies();
            out << "选择你要攻击的敌人:";
            in >> choice;
            if (in.fail())
            {
                in.clear();
                in.ignore(1000, '\n');
                out << "请输入数字\n";
                return true;
            }
            if (enemies_[choice - 1]->is_alive())
            {
                int dmg = player_.get_atk() - enemies_[choice - 1]->defense(); // 计算伤害值
                if (dmg < 1) // 造成伤害至少为1
                    dmg = 1;
                enemies_[choice - 1]->take_damage(dmg);
                out << player_.get_name() << " 攻击 " << enemies_[choice - 1]->get_name()
                    << ", 造成 " << dmg << " 伤害! \n"
                    << enemies_[choice - 1]->get_name()
                    << " 剩余 " << enemies_[choice - 1]->get_hp() << " 血.\n";
            }
            break;
        case Action::Defend:
            out << "玩家选择：防御\n";
            player_.set_defending(true);
            out << player_.get_name() << " 进入防御姿态，本回合减伤 " << 5 << ".\n";
            break;
        case Action::Item:
            std::cout << "玩家选择：道具\n";
            if (player_.use_item("potion"))
            {
                player_.healing(30);
                out << player_.get_name() << "回复 30 hp, " << player_ << '\n';
            }
            else
            {
                out << "没有药水了\n";
            }
            break;
        case Action::Flee:
            std::cout << "玩家选择：逃跑\n"
                      << "成功逃跑了\n";
            return false;
            break;
        case Action::Unknown:
            std::cout << "玩家选择：未知 (" << choice << ")\n"
                      << "输入无效，本回合无法行动。\n";
            break;
        default: // 兜底：以后加新枚举值时能发现
            std::cout << "内部错误：未处理的动作\n";
            break;
        }
        // if (!player_.is_alive()) return false; //检查玩家死亡
        // 敌人反击
        for (const auto &p : enemies_)
        {
            if (p->is_alive() == true)
            {
                int back_dmg = p->get_atk() - player_.defense(); // 计算反击值
                if (back_dmg < 1)                                // 反击数值至少为1
                    back_dmg = 1;
                player_.take_damage(back_dmg); // 对玩家造成伤害
                out << p->get_name() << " 反击 " << player_.get_name()
                    << ", 造成 " << back_dmg << " 伤害!\n";
                if (!player_.is_alive()) // 检测玩家死亡
                {
                    out << player_.get_name() << " 被 " << p->get_name() << " 击败.\n";
                    return false;
                }
            }
        }
        return true;
    }
    int get_round() const { return round_; };
};