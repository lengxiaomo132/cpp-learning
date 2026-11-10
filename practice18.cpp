// practice18.cpp

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

bool safe_get(const std::vector<int> &v, int idx, int &out)
{
    if (idx < 0 || idx >= static_cast<int>(v.size()))
        return false;
    out = v[idx];
    return true;
}

int main()
{
    std::cout << "=== 1. 数组/容器越界（下标超出范围）===\n";
    {
        std::vector<int> v{10, 20, 30};
        std::cout << "  v.size() = " << v.size() << '\n';
        std::cout << "  v[2] = " << v[2] << "  <- 合法\n";
        std::cout << "  v[3] 危险：operator[] 不检查\n";
        std::cout << "  v.at(3) 会抛异常\n";
        int out = 0;
        std::cout << "  safe_get(v, 5, out) = " << std::boolalpha << safe_get(v, 5, out) << "  <- 安全拒绝\n";
        std::cout << "  safe_get(v, 1, out) = " << std::boolalpha << safe_get(v, 1, out) << "，out = " << out << '\n';
    }

    std::cout << "\n=== 2. 未初始化变量 ===\n";
    {
        int x;     // 没给初值
        int y = 0; // 给了初值
        std::cout << "  已初始化: y = " << y << '\n';
        std::cout << "  未初始化: x 的值不能依赖\n";
        std::cout << "  正确做法：int x = 0; 或 int x{};\n";
        (void)x;
    }

    std::cout << "\n=== 3. 悬垂指针（指向已销毁的对象）===\n";
    {
        int *p = nullptr;
        {
            int local = 42;
            p = &local;
            std::cout << "  *p = " << *p << "  <- local 活着时\n";
        }
        // local 已经销毁，p 变成悬垂指针
        std::cout << "  作用域结束后 p 悬垂，不解引用\n";
        std::cout << "  正确做法：不要返回局部变量地址；需要时用 unique_ptr\n";
        p = nullptr; // 用完后立即置空，避免误用
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
            std::cout << "  p 是空指针，跳过\n";
        }
        std::cout << "  正确做法：解引用前必须判空\n";
    }

    std::cout << "\n=== 5. 防御性编程：assert 和前置条件 ===\n";
    {
        int hp = 30;
        assert(hp >= 0); // 成立，继续
        std::cout << "  assert(hp >= 0) 通过，若不通过会立即停止运行并报错\n";
    }

    std::cout << "\n=== 6. 防线总结 ===\n";
    {
        std::cout << "  越界 -> 先检查或用 at()\n";
        std::cout << "  未初始化 -> 一律给初值\n";
        std::cout << "  悬垂 -> 不返回局部地址，用 unique_ptr\n";
        std::cout << "  空指针 -> 解引用前判空\n";
    }

    return 0;
}