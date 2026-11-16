// main.cpp
#include "character.h"
#include <iostream>

int main()
{
    std::cout << "==============================\n";
    std::cout << "        RPG 战斗演示\n";
    std::cout << "==============================\n";

    //std::string n;
    //int hp = 0;
    //std::cout << "请输入你的名字：";
    //std::cin >> n;
    //std::cout << "请输入血量（1-200）：";
    //std::cin >> hp;
    
    //std::cout << "\n=== 你的角色 ===\n";
    Character a{"12", 100, 10};  
    std::cout << a;
    a.take_damage(1000);
       
    std::cout<< a.get_hp()<<'\n';
    std::cout<< a.is_alive()<<'\n';













}