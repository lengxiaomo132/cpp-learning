// practice11.cpp

#include <iostream>
#include <string> // string
#include <vector>

struct RawPlayer
{
    std::string name;
    int hp;

    explicit RawPlayer(std::string n, int h) : name(n), hp(h) // 创建时打印结构信息
    {
        std::cout << "创建：" << name << "，初始 hp = " << hp << '\n';
    }
};

class Player
{
private:
    std::string name;
    int hp;
    int max_hp;

public:
    Player(std::string n, int h)
        : name(n), hp(h), max_hp(h)
    {
        std::cout << "创建：" << name << "，初始 hp = " << hp << '\n';
    }

    // setter:加限制
    void set_hp(int value)
    {
        if (value < 0)
            value = 0;
        if (value > max_hp)
            value = max_hp;
        hp = value;
    }

    // getter:只读
    auto get_hp() const { return hp; }
    auto get_max_hp() const { return max_hp; }
    auto get_name() const { return name; }
    bool is_alive() const { return hp > 0; }
};

int main()
{
    std::cout << "\n=== struct 的弱点 ===\n";
    RawPlayer raw{"Orc", 30}; // 创建
    raw.hp = -999;            // 改hp为-999
    std::cout << "Orc 的 hp 被改成" << raw.hp << "也没人管" << '\n';

    std::cout << "\n=== class 的封装 ===\n";
    Player player1{"Liam", 30}; // 创建
    player1.set_hp(-50);        // 改hp为-50
    std::cout << "set_hp(-50) 后：hp = " << player1.get_hp() << '\n';
    player1.set_hp(999); // 改hp为999
    std::cout << "set_hp(999) 后：hp = " << player1.get_hp() << '\n';
    std::cout << "is_alive() = " << (player1.is_alive() ? "true" : "false")
              << '\n'; // 通过输出0/1来判断输出T/F
    player1.set_hp(0);
    std::cout << "set_hp(0) 后: is_alive() = " << (player1.is_alive() ? "true" : "false")
              << '\n'; // hp为0时

    std::cout << "\n=== const 演示 ===\n";
    const int MAX_LEVEL = 100; // 声明一个const变量
    // MAX_LEVEL=200;  error: const 变量不能修改

    const Player boss{"boss", MAX_LEVEL};               // 声明一个const类
    std::cout << "boss.hp = " << boss.get_hp() << '\n'; // const 对象只能调 const 成员函数

    // 用 std::vector<Player> 装 2 个敌人
    std::vector<Player> party;
    party.push_back(Player{"Bad", 18});
    party.push_back(Player{"More_Bad", 99});

    for (const auto &p : party) // 用 range-for + const auto & 遍历打印
    {
        std::cout << p.get_name() << " hp = " << p.get_hp() << '\n';
    }

    return 0;
}