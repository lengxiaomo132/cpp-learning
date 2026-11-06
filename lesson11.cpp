// lesson11.cpp —— 第 11 课：类：封装、const、初始化列表（顺带 auto 与 range-for）
// 本节工具：struct、函数、引用、vector、string、cout、构造/析构
// 本节新教：class、private/public、getter、const 成员函数、初始化列表、const 变量、auto、range-for

#include <iostream>
#include <string>
#include <vector>

// ===== 1. struct：默认 public，谁都能改 =====
struct RawPlayer
{
    std::string name;
    int hp;
};

// ===== 2. class：默认 private，改必须经过函数 =====
class Player
{
private:
    std::string name;
    int hp;
    int max_hp;

public:
    // 构造函数：和类同名，没有返回类型
    Player(std::string n, int h)
        : name(n), hp(h), max_hp(h) // 初始化列表
    {
        std::cout << "  [构造] " << name << " hp=" << hp << '\n';
    }

    // getter：只读，必须加 const
    std::string get_name() const { return name; }
    int get_hp() const { return hp; }
    int get_max_hp() const { return max_hp; }

    // setter：所有修改都走这里，检查也在这里
    void set_hp(int value)
    {
        if (value < 0)
            value = 0;
        if (value > max_hp)
            value = max_hp; // 上限保护
        hp = value;
    }

    bool is_alive() const { return hp > 0; }
};

int main()
{
    // ===== 3. struct 没有保护 =====
    std::cout << "=== struct：可以乱改 ===\n";
    RawPlayer raw{"Orc", 30};
    raw.hp = -999; // 没人拦你
    std::cout << "  raw.hp = " << raw.hp << "  <- 负数也放行\n";

    // ===== 4. class 有保护 =====
    std::cout << "\n=== class：必须经过 set_hp ===\n";
    Player hero{"Liam", 30};
    // hero.hp = -999;   // ❌ 编译错误：hp 是 private
    hero.set_hp(-999); // 走 setter，被钳到 0
    std::cout << "  set_hp(-999) 后 hp = " << hero.get_hp() << '\n';

    hero.set_hp(999); // 超上限，被钳到 max_hp
    std::cout << "  set_hp(999) 后 hp = " << hero.get_hp()
              << "  <- 上限 " << hero.get_max_hp() << '\n';

    std::cout << "  is_alive() = " << (hero.is_alive() ? "true" : "false") << '\n';

    // ===== 5. const 变量：值定了不能改 =====
    std::cout << "\n=== const 变量 ===\n";
    const int MAX_LEVEL = 100;
    std::cout << "  const int MAX_LEVEL = " << MAX_LEVEL << '\n';
    // MAX_LEVEL = 200;   // 取消注释：error: assignment of read-only variable

    // ===== 6. const 对象：只能调 const 成员函数 =====
    std::cout << "\n=== const 对象 ===\n";
    const Player boss{"Boss", 200};
    std::cout << "  boss.get_hp() = " << boss.get_hp()
              << "  <- get_hp 有 const，可以调\n";
    // boss.set_hp(10);   // 取消注释：error: discards qualifiers

    // ===== 7. auto =====
    std::cout << "\n=== auto ===\n";
    auto n = hero.get_hp();                  // int
    auto s = hero.get_name();                // std::string
    auto size = std::string("hello").size(); // std::size_t
    std::cout << "  auto n = " << n << '\n';
    std::cout << "  auto s = " << s << '\n';
    std::cout << "  auto size = " << size << '\n';

    // ===== 8. range-for =====
    std::cout << "\n=== range-for ===\n";
    std::vector<Player> party;
    party.push_back(Player{"Mia", 18});
    party.push_back(Player{"Ken", 25});

    std::cout << "  只读遍历 const auto &：\n";
    for (const auto &p : party)
    {
        std::cout << "    " << p.get_name() << " hp=" << p.get_hp() << '\n';
    }

    std::cout << "  可写遍历 auto &（先扣到 1，再全部回满）：\n";
    for (auto &p : party) // 去掉 const 和 &：改不到容器里的真对象
    {
        p.set_hp(1); // 扣到 1 血
    }
    for (const auto &p : party)
    {
        std::cout << "    扣血后 " << p.get_name() << " hp=" << p.get_hp() << '\n';
    }

    for (auto &p : party) // 加 & ：改的是容器里真正的元素
    {
        p.set_hp(p.get_max_hp()); // 回满
    }
    for (const auto &p : party)
    {
        std::cout << "    回满后 " << p.get_name() << " hp=" << p.get_hp() << '\n';
    }

    return 0;
}
