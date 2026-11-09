// practice16.cpp

#include <iostream>
#include <string>

class Enemy
{
private:
    std::string name;
    int hp;
    static int total;

public:
    Enemy(std::string n, int h) : name(n), hp(h)
    {
        total++;
        std::cout << "创建 [" << name << "], 当前共 " << total << "个\n";
    }
    ~Enemy()
    {
        total--;
        std::cout << "析构 [" << name << "], 当前共 " << total << "个\n";
    }

    std::string get_name() const { return name; }
    static int count() { return total; }
    static void reset_total() { total = 0; }
};

int Enemy::total = 0;

int main()
{
    std::cout << "\n=== 1. 初始状态 ===\n";
    std::cout << "当前敌人数 = " << Enemy::count() << '\n';

    std::cout << "\n=== 2. 创建三个 ===\n";
    {
        Enemy a{"Orc", 100};
        Enemy b{"Goblin", 50};
        {
            Enemy c{"Dragon", 200};
            std::cout << "此时 count() = " << Enemy::count() << '\n';
        }

        std::cout << "\n=== 3. 销毁一个 ===\n";
    }

    std::cout << "\n=== 4. 再创建一个 ===\n";
    {
        Enemy d{"Slime", 5};
        std::cout << "Slime 的名字是 " << d.get_name() << '\n';
        std::cout << "Enemy::count() = " << Enemy::count() << "   <- 所有对象共享" << '\n';
    }
    std::cout << "\n=== 5. static void reset_total() ===\n";
    {
        Enemy a{"Orc", 100};
        Enemy b{"Goblin", 50};
        std::cout << "此时 count() = " << Enemy::count() << '\n';
        Enemy::reset_total();
        std::cout << "Enemy::reset_total()后 count() = " << Enemy::count() << '\n';
    }

    return 0;
}