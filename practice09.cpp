// practice09.cpp

#include <iostream>
#include <string> // string

struct Player
{
    int hp;
};

struct Words
{
    std::string name;
};

void dmg_value(Player p, int dmg)
{
    p.hp = p.hp - dmg;
    std::cout << "函数内：p.hp = " << p.hp << '\n';
}

void dmg_refer(Player &p, int dmg)
{
    p.hp = p.hp - dmg;
    std::cout << "函数内：p.hp = " << p.hp << '\n';
}

void dmg_pointer(Player *p, int dmg)
{
    p->hp = p->hp - dmg;
    std::cout << "函数内：p->hp = " << p->hp << '\n';
}

int main()
{

    Player hero{30};

    std::cout << "=== 值传递 ===\n";
    std::cout << "传入前：hero.hp = " << hero.hp << '\n';
    dmg_value(hero, 10);
    std::cout << "返回后：hero.hp = " << hero.hp
              << "   ← 没变" << '\n';

    std::cout << "\n=== 引用传递 ===\n";
    std::cout << "传入前：hero.hp = " << hero.hp << '\n';
    dmg_refer(hero, 10);
    std::cout << "传入后：hero.hp = " << hero.hp
              << "   ← 变了" << '\n';

    std::cout << "\n=== 指针传递 ===\n";
    std::cout << "传入前：hero.hp = " << hero.hp << '\n';
    dmg_pointer(&hero, 15);
    std::cout << "传入后：hero.hp = " << hero.hp
              << "   ← 变了" << '\n';

    std::cout << "\n=== 指针改指向 ===\n";
    Words *p = nullptr;
    std::cout << "p 指向 nullptr 时，指针本身内存内容为 " << p << '\n';

    Words a{"A"};
    p = &a;
    std::cout << "p 指向 " << p->name << '\n';

    Words b{"B"};
    p = &b;
    std::cout << "p 指向 " << p->name << '\n';

    Words *nothing = nullptr;
    if (nothing == nullptr)
        std::cout << "nullptr 未使用\n";

    std::cout << "1.值传输：不带&，复制，新变量，不影响原变量\n\n"
              << "2.引用传输：带&，编译器认为代指原对象，无新\n"
              << "变量，影响原对象，r.name，改不了指向对象，需初始化，\n"
              << "引用不能是 nullptr\n\n"
              << "3.指针：*表示解引用，&a表示指向a，新变量存储\n"
              << "的是指向对象的内存地址，影响原对象，p->name or (*p).name,\n"
              << "可改指向对象，无需初始化";

    return 0;
}