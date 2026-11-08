// main.cpp
#include "enemy.h"
#include <iostream>

int main()
{
    Enemy a("Orc", 40);
    std::cout << "名字：" << a.get_name() << '\n';
    std::cout << "血量：" << a.get_hp() << '\n';
    a.take_damage(15);
    std::cout << "受到 15 伤害后：" << a.get_hp() << '\n';
    a.take_damage(100);
    std::cout << "受到 100 伤害后：" << a.get_hp() << '\n';
    std::cout << "状态：" << (a.is_alive() ? "存活" : "已倒下") << '\n';
    return 0;
}