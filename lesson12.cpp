// lesson12.cpp —— 第 12 课：析构、拷贝、运算符重载
// 本节工具：struct、class、private/public、getter、初始化列表、const、auto、range-for、cout
// 本节新教：析构函数、拷贝构造函数、operator<<（输出运算符重载）

#include <iostream>
#include <string>
#include <vector>

class Player
{
private:
    std::string name;
    int hp;

public:
    // ===== 1. 构造函数 =====
    Player(std::string n, int h)
        : name(n), hp(h)
    {
        std::cout << "  [构造] " << name << '\n';
    }

    // ===== 2. 析构函数：对象死的时候自动调用 =====
    ~Player()
    {
        std::cout << "  [析构] " << name << '\n';
    }

    // ===== 3. 拷贝构造函数：用已有的对象造新对象 =====
    Player(const Player &other)
        : name(other.name), hp(other.hp)
    {
        std::cout << "  [拷贝构造] " << name << "（从 " << other.name << " 复制）\n";
    }

    std::string get_name() const { return name; }
    int get_hp() const { return hp; }
};

// ===== 4. 运算符重载：让 cout << player 能打印 =====
std::ostream &operator<<(std::ostream &os, const Player &p)
{
    os << "Player(" << p.get_name() << ", hp=" << p.get_hp() << ")";
    return os;
}

// ===== 5. 值传递会触发拷贝构造 =====
void show_by_value(Player p)
{
    std::cout << "    函数收到：" << p << '\n';
}

int main()
{
    std::cout << "=== 1. 构造与析构的顺序 ===\n";
    {
        Player a{"Liam", 30};
        std::cout << "  大括号内结束前\n";
    }
    std::cout << "  大括号结束了\n";

    std::cout << "\n=== 2. 拷贝构造 ===\n";
    Player b{"Mia", 18};
    Player c = b; // 拷贝构造：用 b 造 c
    std::cout << "  b 的地址 = " << &b << '\n';
    std::cout << "  c 的地址 = " << &c << '\n';
    std::cout << "  地址不同 = 两个独立对象\n";

    std::cout << "\n=== 3. 运算符重载 ===\n";
    std::cout << "  直接打印：" << b << '\n';
    std::cout << "  也能串起来：" << b << " 和 " << c << '\n';

    std::cout << "\n=== 4. 值传递触发拷贝 ===\n";
    Player d{"Ken", 25};
    std::cout << "  调用 show_by_value(d) 前\n";
    show_by_value(d);
    std::cout << "  返回了\n";

    std::cout << "\n=== 5. vector 里存对象 ===\n";
    {
        std::vector<Player> party;
        party.push_back(Player{"Bad", 18});
        std::cout << "  push_back 完成\n";
        for (const auto &p : party)
        {
            std::cout << "    " << p << '\n';
        }
    }
    std::cout << "  队伍大括号结束\n";

    std::cout << "\n=== 6. 全部结束 ===\n";
    return 0;
}
