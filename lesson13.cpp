// lesson13.cpp —— 第 13 课：继承 + 虚函数
// 本节工具：class、private/public、getter、初始化列表、const、operator<<、指针、vector、range-for
// 本节新教：继承（public 派生）、protected、虚函数 virtual、override、多态

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ===== 1. 基类：所有敌人都有的东西 =====
class Enemy
{
protected: // 自己和派生类能访问，外面不行
    std::string name;
    int hp;

public:
    Enemy(std::string n, int h) : name(n), hp(h) {}
    virtual ~Enemy() = default; // 多态基类必须有虚析构

    std::string get_name() const { return name; }
    int get_hp() const { return hp; }

    // virtual：允许派生类改写它
    virtual int damage_taken(int dmg) const
    {
        return dmg; // 普通敌人全额受伤
    }

    void take_hit(int dmg)
    {
        hp = hp - damage_taken(dmg); // 这里会"看实际是谁"来决定扣多少
        if (hp < 0)
            hp = 0;
    }
};

// ===== 2. 派生类：Boss 继承 Enemy，改写受伤规则 =====
class Boss : public Enemy
{
private:
    int armor;

public:
    Boss(std::string n, int h, int a) : Enemy(n, h), armor(a) {}

    // override：我是在改写基类的虚函数（写错名字编译器会报）
    int damage_taken(int dmg) const override
    {
        int result = dmg - armor;
        if (result < 0)
            result = 0;
        return result;
    }
};

// ===== 3. 输出运算符 =====
std::ostream &operator<<(std::ostream &os, const Enemy &e)
{
    os << e.get_name() << "(hp=" << e.get_hp() << ")";
    return os;
}

// ===== 4. 关键：参数是基类的指针，实际可能是任何派生类 =====
void hit_all(const std::vector<std::unique_ptr<Enemy>> &enemies, int dmg)
{
    for (const auto &e : enemies)
    {
        e->take_hit(dmg);
        std::cout << "  " << *e << '\n';
    }
}

int main()
{
    std::cout << "=== 1. 继承：Boss 拥有 Enemy 的一切 ===\n";
    Boss b{"Dragon", 200, 5};
    std::cout << "  name = " << b.get_name() << '\n';
    std::cout << "  hp   = " << b.get_hp() << '\n';

    std::cout << "\n=== 2. 虚函数：同一个指针，不同行为 ===\n";
    Enemy normal{"Orc", 30};

    std::cout << "  普通敌人受 10 伤：" << normal.damage_taken(10) << '\n';
    std::cout << "  Boss 受 10 伤：   " << b.damage_taken(10)
              << "  <- 减了 armor\n";

    std::cout << "\n=== 3. 多态：放进同一个容器 ===\n";
    std::vector<std::unique_ptr<Enemy>> enemies;
    enemies.push_back(std::make_unique<Enemy>("Orc", 30));
    enemies.push_back(std::make_unique<Boss>("Dragon", 200, 5));

    std::cout << "  对全体造成 20 点伤害：\n";
    hit_all(enemies, 20);

    std::cout << "  再来一次：\n";
    hit_all(enemies, 20);

    std::cout << "\n=== 4. 用基类引用只能看到基类部分 ===\n";
    const Enemy &ref = b;
    std::cout << "  通过 Enemy& 看 Boss：" << ref << '\n';
    std::cout << "  ref.damage_taken(10) = " << ref.damage_taken(10)
              << "  <- 仍然是 Boss 的算法\n";

    return 0;
}
