// lesson18.cpp —— 第 18 课：未定义行为与防御性编程
// 本节工具：指针、vector、new/delete、std::string、class、range-for
// 本节新教：未定义行为（UB）、四种常见 UB、assert、不变量

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::cout << "=== 1. 数组/容器越界（下标超出范围）===\n";
    {
        std::vector<int> v{10, 20, 30};
        std::cout << "  v.size() = " << v.size() << '\n';
        std::cout << "  v[2] = " << v[2] << "  <- 合法的最后一个\n";
        // std::cout << v[3] << '\n';   // ❌ 越界！operator[] 不检查
        std::cout << "  v[3] 越界，但编译器不报错\n";
        std::cout << "  正确做法：if (i < v.size()) 或 v.at(3)（会抛异常）\n";
    }

    std::cout << "\n=== 2. 未初始化变量 ===\n";
    {
        int x;                     // 没给初值
        int y = 0;                 // 给了初值
        std::cout << "  int y = 0;  -> " << y << '\n';
        std::cout << "  int x;      -> 值未定义（可能是任何数），本例子不读取它\n";
        std::cout << "  正确做法：int x = 0; 或 int x{};\n";
        (void)x;
    }

    std::cout << "\n=== 3. 悬垂指针（指向已销毁的对象）===\n";
    {
        int *p = nullptr;
        {
            int local = 42;
            p = &local;
            std::cout << "  *p = " << *p << "  <- local 还活着\n";
        }
        // local 已经销毁，p 变成悬垂指针
        std::cout << "  local 已销毁，p 现在悬垂。这里不解引用它\n";
        std::cout << "  正确做法：不要返回局部变量地址；需要时用 unique_ptr\n";
        p = nullptr;               // 用完后立即置空，避免误用
    }

    std::cout << "\n=== 4. 解引用空指针 ===\n";
    {
        int *p = nullptr;
        if (p != nullptr)
        {
            std::cout << "  *p = " << *p << '\n';
        }
        else
        {
            std::cout << "  p 是空指针，跳过解引用\n";
        }
        std::cout << "  正确做法：解引用前必须判空\n";
    }

    std::cout << "\n=== 5. 防御性编程：assert 和前置条件 ===\n";
    {
        int hp = 30;
        assert(hp >= 0);           // 成立，继续
        std::cout << "  assert(hp >= 0) 通过\n";

        // 下面这行会失败（仅演示，已注释）
        // hp = -5;
        // assert(hp >= 0);
        std::cout << "  assert 失败会立即终止程序，并打印出错位置\n";
    }

    std::cout << "\n=== 6. 防御性写法对比 ===\n";
    {
        std::vector<int> v{10, 20, 30};
        int idx = 5;

        std::cout << "  v.at(3) 会抛 std::out_of_range\n";
        std::cout << "  检查: idx=" << idx << " size=" << v.size()
                  << " -> " << (idx < static_cast<int>(v.size()) ? "安全" : "越界，拒绝访问")
                  << '\n';
    }

    std::cout << "\n=== 完成：没有触发任何 UB ===\n";
    return 0;
}
