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

    int check_input(std::istream &in)
    {
        if (in.fail())
        {
            if (in.eof()) // Ctrl+D 式退出
            {
                std::cout << "\nInput finished, exiting。\n";
                return 0; // 结束战斗
            }
            in.clear();
            in.ignore(1000, '\n');
            std::cout << "Please enter number\n";
            return 1;
        }
        std::cout << "\033[2J\033[H"; // 清屏 + 光标移到左上角
        return 2;
    }

    void print_eneies() // 打印敌人信息
    {
        std::cout << "Enemies:\n";
        int order = 0;
        for (const auto &p : enemies_)
        {
            if (p->is_alive() == true)
            {
                order++;
                std::cout << order << '.' << *p;
            }
        }
    }

    bool run_round(std::istream &in, std::ostream &out) // 战斗回合功能
    {
        round_++;
        out << "\n=== Round " << round_ << " ===\n";

        out << player_; // 打印玩家信息
        print_eneies();
        // 选择动作
        out << "Action\n1.Attack 2.Defend 3.Item 4.Flee (Please enter number)\n>";
        int choice = 0;
        in >> choice;
        {
            int check = check_input(in);
            if (check == 0)
            {
                return false;
            }
            else if (check == 1)
            {
                return true;
            }
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
        {
            out << "Player choice: Attack\n";
            // 1. 先收集活着的敌人的下标
            std::vector<std::size_t> alive;
            for (std::size_t i = 0; i < enemies_.size(); ++i)
            {
                if (enemies_[i]->is_alive())
                    alive.push_back(i);
            }
            // 2. 打印（编号 = 收集顺序 + 1）
            out << "Enemy list:\n";
            for (std::size_t k = 0; k < alive.size(); ++k)
            {
                out << "  " << (k + 1) << ". " << *enemies_[alive[k]] << '\n';
            }
            // 3. 读入
            out << "Please choose a target:\n";
            int choice = 0;
            in >> choice;
            if (choice < 1 || choice > static_cast<int>(alive.size())) // 检测输入范围
            {
                out << "Invalid target\n";
                return true;
            }
            {
                int check = check_input(in);
                if (check == 0)
                {
                    return false;
                }
                else if (check == 1)
                {
                    return true;
                }
            }
            std::size_t idx = alive[static_cast<std::size_t>(choice - 1)];
            if (enemies_[idx]->is_alive())
            {
                int dmg = player_.get_atk() - enemies_[idx]->defense(); // 计算伤害值
                if (dmg < 1)                                            // 造成伤害至少为1
                    dmg = 1;
                enemies_[idx]->take_damage(dmg);
                out << player_.get_name() << " attack " << enemies_[idx]->get_name()
                    << ", cause " << dmg << " damage! \n";
                if (enemies_[idx]->is_alive())
                {
                    out << enemies_[idx]->get_name()
                        << " remain " << enemies_[idx]->get_hp() << " hp.\n";
                }
                else
                    out << enemies_[idx]->get_name()
                        << " Death.\n";
            }
            break;
        }
        case Action::Defend:
            out << "Player chooses: Defense\n";
            player_.set_defending(true);
            out << player_.get_name() << " Enter a defensive stance, reduce damage by 5 this turn.\n";
            break;
        case Action::Item:
            std::cout << "Player Choice: Items\n";
            if (player_.use_item("potion"))
            {
                player_.healing(30);
                out << player_.get_name() << "restore 30 hp, " << player_ << '\n';
            }
            else
            {
                out << "There's no more potion.\n";
            }
            break;
        case Action::Flee:
            std::cout << "Player choice: Flee\n"
                      << "Successfully escaped\n";
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));    // 停 1.5 秒
        // 检测敌人死完了吗
        if (all_dead())
        {
            out << "All enemies destroyed!";
            return false;
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
                out << p->get_name() << " counterattack " << player_.get_name()
                    << ", cause " << back_dmg << " damage!\n";
                if (!player_.is_alive()) // 检测玩家死亡
                {
                    out << player_.get_name() << " id defeated by " << p->get_name() << ".\n";
                    return false;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));    // 停 1.5 秒
        return true;
    }
    int get_round() const { return round_; };
};