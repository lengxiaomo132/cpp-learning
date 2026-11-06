// practice09b.cpp

#include <iostream>
#include <string> // string

enum class Action
{
    Attack,
    Defend,
    Flee,
    Unknown
};

void do_action(Action a, int choice)
{
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

int main()
{
    int choice = 0;
    std::cout << "请选择动作（1=攻击 2=防御 3=逃跑）：";
    std::cin >> choice;
    if (std::cin.fail()) // 输入无效值时退出程序
    {
        std::cout << "输入无效！你输入的不是整数。\n";
        return 1;
    }

    Action a = Action::Attack;
    if (choice == 1)
        a = Action::Attack;
    else if (choice == 2)
        a = Action::Defend;
    else if (choice == 3)
        a = Action::Flee;
    else
        a = Action::Unknown;

    std::cout << "\n=== 回合结算 ===\n";
    do_action(a, choice);
    std::cout << '\n'
              << '\n';
    return 0;
}