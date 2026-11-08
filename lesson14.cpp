// lesson14.cpp —— 第 14 课：模板 + lambda
// 本节工具：函数、引用 &、const、auto、range-for、vector、unique_ptr、继承、virtual、operator<<
// 本节新教：template<typename T>（函数模板）、lambda [](参数){ }
// 借用：std::sort（<algorithm>，只提一句）

#include <algorithm> // std::sort（借用，只提一句）
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ===== 1. 没有模板：每种类型都要写一遍 =====
int max_int(int a, int b)
{
    return a > b ? a : b;
}
double max_double(double a, double b)
{
    return a > b ? a : b;
}

// ===== 2. 有模板：写一次，所有类型通用 =====
template <typename T>
T max_of(T a, T b)
{
    return a > b ? a : b;
}

// ===== 3. 复用第 13 课的 Enemy / Boss =====
class Enemy
{
protected:
    std::string name;
    int hp;

public:
    Enemy(std::string n, int h) : name(n), hp(h) {}
    virtual ~Enemy() = default;

    std::string get_name() const { return name; }
    int get_hp() const { return hp; }
};

class Boss : public Enemy
{
public:
    Boss(std::string n, int h) : Enemy(n, h) {}
};

std::ostream &operator<<(std::ostream &os, const Enemy &e)
{
    os << e.get_name() << "(hp=" << e.get_hp() << ")";
    return os;
}

int main()
{
    std::cout << "=== 1. 模板：一次定义，多种类型 ===\n";
    std::cout << "  max_of(3, 7)       = " << max_of(3, 7) << '\n';
    std::cout << "  max_of(2.5, 1.5)   = " << max_of(2.5, 1.5) << '\n';
    std::cout << "  max_of(\"apple\", \"pear\") = " << max_of<std::string>("apple", "pear") << '\n';
    std::cout << "  max_of('a', 'z')   = " << max_of('a', 'z') << '\n';

    std::cout << "\n=== 2. lambda：写在表达式里的小函数 ===\n";
    auto square = [](int x)
    {
        return x * x;
    };
    std::cout << "  square(5) = " << square(5) << '\n';

    auto add = [](int a, int b)
    {
        return a + b;
    };
    std::cout << "  add(3, 4) = " << add(3, 4) << '\n';

    std::cout << "\n=== 3. 用 lambda 按 hp 排序 ===\n";
    std::vector<std::unique_ptr<Enemy>> enemies;
    enemies.push_back(std::make_unique<Enemy>("Orc", 30));
    enemies.push_back(std::make_unique<Boss>("Dragon", 200));
    enemies.push_back(std::make_unique<Enemy>("Goblin", 15));

    std::cout << "  排序前：\n";
    for (const auto &e : enemies)
    {
        std::cout << "    " << *e << '\n';
    }

    std::sort(enemies.begin(), enemies.end(),
              [](const std::unique_ptr<Enemy> &a, const std::unique_ptr<Enemy> &b)
              {
                  return a->get_hp() < b->get_hp();
              });

    std::cout << "  排序后（hp 从小到大）：\n";
    for (const auto &e : enemies)
    {
        std::cout << "    " << *e << '\n';
    }

    std::cout << "\n=== 4. 用模板函数处理自定义类型 ===\n";
    std::cout << "  max_of(10, 99) = " << max_of(10, 99) << '\n';
    std::cout << "  max_of(std::string) 也能用，因为 string 支持 >\n";

    return 0;
}
