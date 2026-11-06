// practice10.cpp

#include <iostream>
#include <string> // string
#include <memory> // unique_ptr, make_unique

struct Enemy
{
    std::string name;
    int hp;

    Enemy(std::string n, int h) : name(n), hp(h)
    {
        std::cout << "创建：" << name << " hp=" << hp << '\n';
    }

    // 析构函数：名字前面加 ~，没有参数
    ~Enemy()
    {
        std::cout << "[销毁] " << name << " hp=" << hp << '\n'
                  << '\n';
    }
};

void demo_stack()
{
    std::cout << "=== 栈对象 ===\n";
    Enemy p{"hero", 30}; // 创建方式
    std::cout << "销毁时机：函数结束时自动\n";
}

void demo_heap_manual()
{
    std::cout << "=== new / delete ===\n";
    Enemy *p = new Enemy{"enemy", 50};
    std::cout << "销毁时机：手动 delete\n";
    delete p;
}

void demo_heap_unique()
{
    std::cout << "=== unique_ptr ===\n";
    std::unique_ptr<Enemy> p;
    if (p == nullptr)
        std::cout << "p==nullptr 指针为空，不能访问\n";
    if (p)
        std::cout << "有对象，p->hp = " << p->hp << '\n';

    p = std::make_unique<Enemy>("boss", 100);
    if (p == nullptr)
        std::cout << "p==nullptr 指针为空，不能访问\n";
    if (p)
        std::cout << "有对象，p->hp = " << p->hp << '\n';

    std::cout << "销毁时机：函数结束自动\n";
}

int main()
{
    demo_stack();
    demo_heap_manual();
    demo_heap_unique();

    std::cout << "\n=== 结论 ===\n";
    std::cout << "栈：自动，快，容量小\n";
    std::cout << "new：手动 delete，忘了就泄漏\n";
    std::cout << "unique_ptr：自动 delete，不可能泄漏\n";
    return 0;
}
