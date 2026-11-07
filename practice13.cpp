// practice13.cpp

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Enemy
{
protected: // 自己和派生类能访问，外面不行
    std::string name;
    int hp;

public:
    Enemy(std::string n, int h) : name(n), hp(h) {}
    virtual ~Enemy() { std::cout << "  ~Enemy"<< name<< '\n'; }; // 虚析构

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
    ~Boss() override { std::cout << "  ~Boss"<< name<< '\n'; }
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
    std::cout << "\n=== 1. 继承 ===\n";
    Boss d{"Dragon", 200, 5};
    std::cout << d.get_name() << " 的 hp = " << d.get_hp() << '\n'; // Boss class继承了Enemy的protected里的变量,和public里面的函数.

    {
        std::cout << "\n=== 2. 虚函数 ===\n";
        Enemy a{"普通敌人", 50};
        std::cout << "普通敌人受 10 伤：" << a.dmg_taken(10) << '\n'; // virtual是定义虚函数,override可以把原class里面的虚函数改写成只有继承class可以运行的同名函数,功能可以不同
        std::cout << "Boss 受 10 伤：" << d.dmg_taken(10) << '\n';
    }

    {
        std::cout << "\n=== 3. 一次性打全体 ===\n";
        std::vector<std::unique_ptr<Enemy>> enemies;
        enemies.push_back(std::make_unique<Enemy>("Orc", 30));
        enemies.push_back(std::make_unique<Boss>("Dragon", 200, 5));
        for (const auto &p : enemies) // p是在栈上的unique_ptr的引用,*p就得到在堆上的Enemy
        {
            std::cout << "敌人出现" << *p << '\n'; // 用 range-for + const auto & 遍历打印
        }
        std::cout << "一次性攻击全体20点hp\n";
        hit_all(enemies, 20);
    }

    std::cout << "\n=== 4. 通过基类引用 ===\n";
    Enemy &ref = d;
    std::cout << "通过 Enemy& 看 Boss：" << ref << '\n';
    std::cout << "ref.dmg_taken(10) = " << ref.dmg_taken(10) << '\n';
}