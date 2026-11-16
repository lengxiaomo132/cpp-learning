// main.cpp
#include "character.h"
#include "player.h"
#include "enemy.h"
#include <iostream>

int main()
{
    std::cout << "==============================\n";
    std::cout << "        RPG 战斗演示\n";
    std::cout << "==============================\n";

    Character a{"liam", 100, 10};  
    std::cout << a;
    a.take_damage(1000);
       
    std::cout<< a.get_hp()<<'\n';
    std::cout<< a.is_alive()<<'\n';

    Player b{"mortis", 50};
    std::cout << b;
    b.add_item("potion",-3);
    b.add_item("bomb",-3);
    b.print_bag();















}