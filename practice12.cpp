// practice12.cpp

#include <iostream>
#include <string> // string
#include <vector>

class Enemy
{
private:
    std::string name;
    int hp;

public:
    Enemy(std::string n, int h) : name(n), hp(h)
    {
        std::cout << "[构造] " << name << " hp=" << hp << '\n';
    }

    ~Enemy()
    {
        std::cout << "[析构] " << name << '\n';
    }

    Enemy(const Enemy &other) : name(other.name), hp(other.hp)
    {
        std::cout << "[拷贝构造] " << name << "(来自 " << other.name << ')' << '\n';
    }

    std::string get_name() const { return name; }
    int get_hp() const { return hp; }

    void set_hp(int value)
    {
        if (value < 0)
            value = 0;
        hp = value;
    }
};

std::ostream &operator<<(std::ostream &os, const Enemy &e) // const Enemy &e不可以调用一个可能改变e的函数，所有get_name和hp函数要加上const
{
    os << e.get_name() << "(hp=" << e.get_hp() << ')';
    return os;
}

int main()
{

    std::cout << "\n=== 1. 构造与析构 ===\n";
    {
        Enemy a{"Orc", 30}; // 试了一下不带变量名，创建临时变量，在这个完整语句结束的瞬间就析构了，再无它存在过的证明。临时变量的作用域是其所在的完整语句结束时。
        std::cout << "  进入作用域\n";
    }
    std::cout << "  离开作用域\n";

    std::cout << "\n=== 2. 拷贝构造 ===\n";
    Enemy b{"Goblin", 15};
    auto c = b;
    std::cout << "&c = " << &c << '\n';
    std::cout << "&b = " << &b << '\n';
    if (&b != &c)
        std::cout << "  b 地址与 c 地址不同\n";

    std::cout << "\n=== 3. 重载 << ===\n";
    c.set_hp(30);
    std::cout << b << '\n';
    std::cout << b << "和" << c << '\n';

    std::cout << "\n=== 4. 结束 ===\n";
    return 0;
}