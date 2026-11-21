// main.cpp
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "battle.h"
#include <iostream>

int main()
{
    std::cout << "\033[2J\033[H"; // 清屏 + 光标移到左上角
    std::cout << "==============================\n";
    std::cout << "       RPG Battle Demo\n";
    std::cout << "==============================\n";

    // 读玩家名字
    std::string name;
    std::cout << "Tap in your name:";
    std::cin >> name;

    // 读血量
    int hp = 0;
    std::cout << "Tap in hp(1-200):";
    std::cin >> hp;
    if (std::cin.fail() || hp < 1 || hp > 200)
    {
        std::cout << "Please use valid number.";
        return 1;
    }

    std::cout << "\033[2J\033[H"; // 清屏 + 光标移到左上角
    // 创建 Player
    Player hero{name, hp};
    hero.add_item("potion", 3);
    hero.add_item("bomb", 1);
    std::cout << hero << " ATK:" << hero.get_atk() << '\n';
    ;
    hero.print_bag();

    Battle battle{hero};
    battle.add_enemy(std::make_unique<Enemy>("Orc", 40, 8));
    battle.add_enemy(std::make_unique<Elite>("EliteGoblin", 30, 10));
    battle.add_enemy(std::make_unique<Boss>("Dragon", 200, 20, 5));

    while (battle.run_round(std::cin, std::cout))
    {
    }

    std::cout << "Finish.";
}