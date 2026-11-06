// practice04.cpp

#include <iostream>

int main()
{ // 程序开始

    // 输入血量
    int hp_player = 0;
    int hp_enemy = 0;

    std::cout << "请输入玩家血量：";//输入玩家血量
    std::cin >> hp_player;
    if (std::cin.fail()) // 输入无效值时退出程序
    {
        std::cout << "输入无效！你输入的不是整数。\n";
        return 1;
    }

    std::cout << "请输入敌人血量：";//输入敌人血量
    std::cin >> hp_enemy;
    if (std::cin.fail()) // 输入无效值时退出程序
    {
        std::cout << "输入无效！你输入的不是整数。\n";
        return 1;
    }

    // 攻击敌人
    int round = 0;
    while (hp_enemy > 0)
    {
        hp_enemy = hp_enemy - 10; // 玩家攻击
        ++round;
        if (hp_enemy < 0)
            hp_enemy = 0; // 防止血量剩余显示为负数
        std::cout << "第 " << round << " 回合：敌人剩余 " << hp_enemy << " 点 HP\n";
    }

    // 战斗结算显示
    if (round == 0)
        std::cout << "敌人本来大抵已经是死了的。";
    else
        std::cout << "敌人被击败！共用 " << round << " 回合\n";

    // 程序结束
    return 0;
}