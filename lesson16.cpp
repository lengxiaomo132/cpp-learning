// lesson16.cpp —— 第 16 课：static 成员与静态函数
// 本节工具：class、private/public、getter、初始化列表、const 成员函数、构造/析构
// 本节新教：static 成员变量、static 成员函数、类外定义 static 成员

#include <iostream>
#include <string>

class Enemy
{
private:
    std::string name;   // 普通成员：每个对象各有一份
    int hp;

    static int total;   // 静态成员变量：整个类共用一份

public:
    Enemy(std::string n, int h) : name(n), hp(h)
    {
        ++total;        // 每创建一个对象，总数加 1
        std::cout << "  [创建] " << name << "，当前共 " << total << " 个敌人\n";
    }

    ~Enemy()
    {
        --total;        // 每销毁一个对象，总数减 1
        std::cout << "  [销毁] " << name << "，当前共 " << total << " 个敌人\n";
    }

    std::string get_name() const { return name; }
    int get_hp() const { return hp; }

    // 静态成员函数：不依赖任何具体对象
    static int count()
    {
        return total;
        // return name;   // 取消注释会报错：静态函数里没有 this，访问不到普通成员
    }
};

// 静态成员变量必须在类外定义一次（这是规则，不是可选项）
int Enemy::total = 0;

int main()
{
    std::cout << "=== 1. 一开始 ===\n";
    std::cout << "  Enemy::count() = " << Enemy::count() << '\n';

    std::cout << "\n=== 2. 创建两个对象 ===\n";
    {
        Enemy a{"Orc", 30};
        Enemy b{"Goblin", 15};

        std::cout << "  在作用域里：count() = " << Enemy::count() << '\n';
    }
    std::cout << "  离开作用域后：count() = " << Enemy::count() << '\n';

    std::cout << "\n=== 3. 静态函数用类名调用 ===\n";
    Enemy c{"Dragon", 200};
    std::cout << "  Enemy::count()  = " << Enemy::count() << '\n';
    std::cout << "  c.count()       = " << c.count()
              << "  <- 也能用对象调，但没必要\n";

    std::cout << "\n=== 4. 普通成员 vs 静态成员 ===\n";
    Enemy d{"Slime", 5};
    std::cout << "  c.get_name() = " << c.get_name()
              << "  <- 每个对象自己的\n";
    std::cout << "  Enemy::count() = " << Enemy::count()
              << "  <- 所有对象共享的\n";

    return 0;
}
