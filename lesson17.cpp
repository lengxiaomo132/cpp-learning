// lesson17.cpp —— 第 17 课：移动语义、拷贝控制
// 本节工具：拷贝构造、析构、std::string、std::cout、左值/右值
// 本节新教：右值引用 &&、std::move、移动构造函数、Rule of Three

#include <iostream>
#include <string>
#include <utility> // std::move
#include <vector>

class Enemy
{
private:
    std::string name;
    int hp;

public:
    Enemy(std::string n, int h) : name(n), hp(h) {}

    // 拷贝构造：复制（左值走这里）
    Enemy(const Enemy &other) : name(other.name), hp(other.hp)
    {
        std::cout << "  [拷贝构造] " << name << '\n';
    }

    // 移动构造：搬走（右值走这里）
    Enemy(Enemy &&other) : name(std::move(other.name)), hp(other.hp)
    {
        std::cout << "  [移动构造] " << name << '\n';
    }

    Enemy &operator=(const Enemy &other)
    {
        name = other.name;
        hp = other.hp;
        std::cout << "  [拷贝赋值] " << name << '\n';
        return *this;
    }

    Enemy &operator=(Enemy &&other)
    {
        name = std::move(other.name);
        hp = other.hp;
        std::cout << "  [移动赋值] " << name << '\n';
        return *this;
    }

    const std::string &get_name() const { return name; }
    int get_hp() const { return hp; }
};

int main()
{
    std::cout << "=== 1. 左值 → 拷贝 ===\n";
    Enemy a{"Orc", 30};
    Enemy b = a;
    std::cout << "  a=\"" << a.get_name() << "\" b=\"" << b.get_name() << "\"\n";

    std::cout << "\n=== 2. 右值 → 移动 ===\n";
    Enemy c = Enemy{"Goblin", 15};
    std::cout << "  c=\"" << c.get_name() << "\"\n";

    std::cout << "\n=== 3. std::move 前后 ===\n";
    Enemy d{"Dragon", 200};
    std::cout << "  move 前 d.name=\"" << d.get_name() << "\"\n";
    Enemy e = std::move(d);
    std::cout << "  e.name=\"" << e.get_name() << "\"\n";
    std::cout << "  d.name=\"" << d.get_name() << "\"  <- 被搬空\n";
    std::cout << "  d.hp=" << d.get_hp() << "  <- int 是复制的\n";

    std::cout << "\n=== 4. push_back 时有什么区别 ===\n";
    std::vector<Enemy> v;
    Enemy f{"Slime", 5};
    std::cout << "  push_back(左值 f)：\n";
    v.push_back(f);
    std::cout << "  push_back(临时对象)：\n";
    v.push_back(Enemy{"Bat", 3});

    std::cout << "\n=== 5. 赋值 vs 初始化 ===\n";
    Enemy g{"Knight", 50};
    Enemy h{"Mage", 40};
    std::cout << "  h = g;（拷贝赋值）\n";
    h = g;
    std::cout << "  h = Enemy{...};（移动赋值）\n";
    h = Enemy{"Thief", 20};

    return 0;
}
