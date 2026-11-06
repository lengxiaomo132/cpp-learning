// lesson09.cpp —— 引用 vs 指针
// 本节工具：struct、引用 &、const &、std::cout、if
// 新增：指针 *、取地址 &、解引用 *、nullptr、->

#include <iostream>
#include <string>

struct Player
{
    std::string name;
    int hp;
};

// 1. 值传递：改的是副本
void damage_value(Player p, int dmg)
{
    p.hp = p.hp - dmg;
}

// 2. 引用传递：改的是原对象
void damage_ref(Player &p, int dmg)
{
    p.hp = p.hp - dmg;
    if (p.hp < 0)
        p.hp = 0;
}

// 3. 指针传递：同样能改原对象，但调用处要传地址
void damage_ptr(Player *p, int dmg)
{
    p->hp = p->hp - dmg; // p->hp 等价于 (*p).hp
    if (p->hp < 0)
        p->hp = 0;
}

int main()
{
    Player hero{"Bob", 30};

    // ===== 1. 值传递 vs 引用传递 =====
    damage_value(hero, 10);
    std::cout << "值传递后 hp = " << hero.hp << "   <- 还是 30\n";

    damage_ref(hero, 10);
    std::cout << "引用传递后 hp = " << hero.hp << "  <- 变成 20\n";

    // ===== 2. 指针：取地址 & 和解引用 * =====
    int x = 42;
    int *px = &x; // &x 是「取 x 的地址」
    std::cout << "\nx = " << x << '\n';
    std::cout << "px = " << px << "   <- 一串地址\n";
    std::cout << "*px = " << *px << "  <- 解引用，拿到 42\n";

    *px = 100; // 通过指针改 x
    std::cout << "改完 *px = 100，x = " << x << '\n';

    // ===== 3. 指针也能改 struct =====
    damage_ptr(&hero, 5); // 注意调用处要写 &
    std::cout << "\n指针传递后 hp = " << hero.hp << "  <- 20 - 5 = 15\n";

    // ===== 4. 指针可以为空，引用不能 =====
    Player *nothing = nullptr;
    if (nothing == nullptr)
    {
        std::cout << "\nnothing 是空指针，不能 *nothing\n";
    }

    // ===== 5. 指针可以改指向，引用不能改绑 =====
    Player a{"A", 1};
    Player b{"B", 2};

    Player &r = a;
    r = b; // 这是把 b 的值【整体复制】给 a，不是让 r 改指 b！
    std::cout << "\nr = b 之后：a.name = " << a.name << "，a.hp = " << a.hp
              << "  <- a 的 name 和 hp 都被覆盖成 b 的\n";

    // 用一份干净的 a2 来看指针改指向
    Player a2{"A2", 1};
    Player *p1 = &a2;
    std::cout << "p1 原本指向 " << p1->name << '\n';
    p1 = &b; // 指针可以改指向
    std::cout << "p1 = &b 之后指向 " << p1->name << "  <- a2 本身没变："
              << a2.name << '\n';

    return 0;
}
