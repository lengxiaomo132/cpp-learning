// practice14.cpp

#include <algorithm> // std::sort（借用，只提一句）
#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <typename T>
T max_of(T a, T b)
{
    return a > b ? a : b;
}

class Enemy
{
protected: // 自己和派生类能访问，外面不行
    std::string name;
    int hp;

public:
    Enemy(std::string n, int h) : name(n), hp(h) {}
    virtual ~Enemy() { std::cout << "~Enemy [" << name <<']'<< '\n'; }// 虚析构

    std::string get_name() const { return name; }
    int get_hp() const { return hp; }

    virtual int dmg_taken(int dmg) const { return dmg; }

    void take_hit(int dmg)
    {
        hp -= dmg_taken(dmg);
        if (hp < 0)
        {
            hp = 0;
        }
    }
};

class Boss : public Enemy
{
private:
    int armor;

public:
    Boss(std::string n, int h, int a) : Enemy(n, h), armor(a) {}
    ~Boss() override { std::cout << "~Boss [" << name <<']'<< '\n'; }
    int dmg_taken(int dmg) const override
    {
        int r = dmg - armor;
        return r < 0 ? 0 : r;
    }
};

std::ostream &operator<<(std::ostream &os, const Enemy &e) // const Enemy &e不可以调用一个可能改变e的函数，所有get_name和hp函数要加上const
{
    os << e.get_name() << "(hp=" << e.get_hp() << ')';
    return os;
}

int main()
{
    std::cout << "\n=== 1. 模板函数 ===\n";
    std::cout << "max_of(3, 7) = " << max_of(3, 7) << '\n';
    std::cout << "max_of(2.5, 1.5) = " << max_of(2.5, 1.5) << '\n';
    std::cout << "max_of(apple, pear) = "
              << max_of(std::string("apple"), std::string("pear")) << '\n';

    std::cout << "\n=== 2. lambda ===\n";
    auto square = [](int a) { return a * a; };
    auto add = [](int a, int b) { return a + b; };
    std::cout << "square(6) = " << square(6) << '\n';
    std::cout << "add(3, 4) = " << add(3, 4) << '\n';

    std::cout << "\n=== 3. 按 hp 排序 ===\n";
    std::vector<std::unique_ptr<Enemy>> enemies;
    enemies.push_back(std::make_unique<Enemy>("Orc", 30));
    enemies.push_back(std::make_unique<Boss>("Dragon", 200, 5));
    enemies.push_back(std::make_unique<Enemy>("Goblin", 15));

    std::cout << "排序前：\n";
    for (const auto &p : enemies) { std::cout << *p << '\n';}

    std::sort(enemies.begin(), enemies.end(),
              [](const std::unique_ptr<Enemy> &a, const std::unique_ptr<Enemy> &b)
              { return a->get_hp() < b->get_hp(); });

    std::cout << "排序后：\n";
    for (const auto &p : enemies) { std::cout << *p << '\n';}

    std::cout << '\n';
    return 0;
}