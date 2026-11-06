// lesson10.cpp —— 栈 / 堆 / unique_ptr
// 本节工具：int、函数、引用 &、指针 *、nullptr、struct、std::cout
// 新增：new/delete、std::unique_ptr、std::make_unique、#include <memory>

#include <iostream>
#include <memory> // unique_ptr, make_unique
#include <string>

struct Player
{
    std::string name;
    int hp;

    // 演示用：构造和析构时各打印一行，方便看"什么时候发生"
    explicit Player(int h) : name("hero"), hp(h)
    {
        std::cout << "  [创建] " << name << " hp=" << hp << '\n';
    }
    ~Player()
    {
        std::cout << "  [销毁] " << name << " hp=" << hp << '\n';
    }
};

// ===== 1. 栈：出作用域自动销毁 =====
void demo_stack()
{
    std::cout << "--- 栈：普通局部变量 ---\n";
    Player p{30};
    std::cout << "  函数体里，p 还活着\n";
} // p 在这里自动销毁

// ===== 2. 堆 + new/delete：必须手动释放 =====
void demo_heap_manual()
{
    std::cout << "\n--- 堆：new + 手动 delete ---\n";
    Player *p = new Player{20};
    std::cout << "  函数体里，p 指向的 Player 活着\n";
    delete p; // 不写这一行就是内存泄漏
    std::cout << "  已手动 delete\n";
}

// ===== 3. 堆 + unique_ptr：自动释放 =====
void demo_heap_unique()
{
    std::cout << "\n--- 堆：unique_ptr 自动释放 ---\n";
    std::unique_ptr<Player> p = std::make_unique<Player>(10);
    std::cout << "  函数体里，p 指向的 Player 活着\n";
    std::cout << "  用法和指针一样：p->hp = " << p->hp << '\n';
} // 这里自动 delete，不用你写

// ===== 4. 悬垂指针在下方"故意写错"里演示，这里不写 =====

int main()
{
    demo_stack();
    demo_heap_manual();
    demo_heap_unique();

    std::cout << "\n--- 对比总结 ---\n";
    std::cout << "栈对象：出 {} 自动消失\n";
    std::cout << "堆对象：new 出来，只有 delete 才会消失\n";
    std::cout << "unique_ptr：出 {} 自动 delete，等于替你写了 delete\n";

    return 0;
}
