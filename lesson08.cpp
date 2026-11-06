// lesson08.cpp —— struct 组织数据
// 本节工具：std::string、.size()、[0]、std::cin >>、std::getline、std::cin.ignore
//           int / double / bool、if/else、cin.fail()、函数、void、引用 &、std::vector

#include <iostream>
#include <string>
#include <vector>

// ===== 0. 先用两个独立变量写一个玩家 =====
// 问题：数据是散的，换个函数就要传一堆参数

// ===== 1. 定义一个新的类型：struct =====
// 大括号后面必须写分号 —— 这是定义语句，不是函数
struct Player
{
    std::string name; // 成员变量，叫「字段」
    int hp;
    int atk;
}; // <-- 分号不能少

// 在函数签名里表示「只会读」，后面会专门讲
void print_player(const Player &p)
{
    std::cout << "[" << p.name << "] HP " << p.hp << " / ATK " << p.atk << '\n';
}

int main()
{
    // ===== 2. 创建对象：用花括号初始化（推荐） =====
    Player hero{"Liam", 30, 12};
    print_player(hero);

    // 用点号访问成员
    std::cout << "hero.name   = " << hero.name << '\n';
    std::cout << "hero.hp     = " << hero.hp << '\n';
    std::cout << "hero.name.size() = " << hero.name.size() << '\n';
    std::cout << "hero.name[0]     = " << hero.name[0] << '\n';

    // ===== 3. 成员可以像普通变量一样改 =====
    hero.hp = hero.hp - 5;
    print_player(hero);

    // ===== 4. 整个对象可以拷贝（值语义） =====
    Player backup = hero; // 复制一份
    backup.name = "Copy"; // 改副本
    std::cout << "\n改副本之后：\n";
    print_player(hero);   // 原对象没变
    print_player(backup);

    // ===== 5. struct 放进 vector =====
    std::vector<Player> party;
    party.push_back(hero);
    party.push_back(Player{"Mia", 18, 9}); // 临时对象直接塞进去

    std::cout << "\n队伍里 " << party.size() << " 人：\n";
    for (std::size_t i = 0; i < party.size(); ++i)
    {
        print_player(party[i]);
    }

    // ===== 6. 故意写错，看真实报错（把下面三行前面的 // 去掉试一次） =====
    // hero.level = 3;              // 成员不存在
    // Player p2{"Bob", 20};        // 成员少了
    // Player p3{"Bob", "20", 5};   // 类型对不上

    return 0;
}
