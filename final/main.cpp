// main.cpp
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "battle.h"
#include <iostream>


int main()
{
    std::cout << "==============================\n";
    std::cout << "       RPG Battle Demo\n";
    std::cout << "==============================\n";

    Player hero{"mortis", 100};
    hero.add_item("potion", 0);
    hero.add_item("bomb", 0);
    std::cout << hero;
    hero.print_bag();

    Battle battle{hero};
    battle.add_enemy(std::make_unique<Enemy>("Orc", 40, 8));
    battle.add_enemy(std::make_unique<Elite>("EliteGoblin", 30, 10));
    
    while (battle.run_round(std::cin, std::cout)){}

    std::cout << "Finish.";

}