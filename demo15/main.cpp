// main.cpp —— 使用
#include "player.h"
#include <iostream>

int main()
{
    Player p{"Liam", 30};
    std::cout << "名字：" << p.get_name() << '\n';
    std::cout << "血量：" << p.get_hp() << '\n';

    p.take_damage(10);
    std::cout << "受 10 伤后：" << p.get_hp() << '\n';

    p.take_damage(100);
    std::cout << "受 100 伤后：" << p.get_hp() << "  <- 不会为负\n";
    return 0;
}