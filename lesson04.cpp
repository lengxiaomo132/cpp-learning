// lesson04.cpp —— 循环的四种基本形态 + 常见坑
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

int main() {
    // ===== 1. for：知道次数 =====
    std::cout << "=== for: 打印 1~5 ===\n";
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    // ===== 2. while：不知道次数，靠条件 =====
    std::cout << "\n=== while: 每次减半，直到 <= 1 ===\n";
    int hp = 100;
    int round = 0;
    while (hp > 1) {
        hp = hp / 2;
        ++round;
        std::cout << "第 " << round << " 回合: hp=" << hp << '\n';
    }

    // ===== 3. break：中途跳出 =====
    std::cout << "\n=== break: 找到 7 的倍数就停 ===\n";
    for (int i = 1; i <= 100; ++i) {
        if (i % 7 == 0) {
            std::cout << "第一个 7 的倍数是 " << i << '\n';
            break;                       // 跳出整个循环
        }
    }

    // ===== 4. continue：跳过本次 =====
    std::cout << "\n=== continue: 只打印奇数 ===\n";
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) {
            continue;                    // 跳过本轮剩余部分
        }
        std::cout << i << ' ';
    }
    std::cout << '\n';

    // ===== 5. 经典坑：size() 是无符号 =====
    std::cout << "\n=== 坑 1: 空 vector 倒序 ===\n";
    std::vector<int> empty;
    std::cout << "empty.size() = " << empty.size() << '\n';
    std::cout << "empty.size() - 1 = " << empty.size() - 1 << "  <-- 天文数字\n";

    // 正确写法：用 std::size_t 并注意条件
    std::vector<int> v = {10, 20, 30};
    std::cout << "正确倒序: ";
    for (std::size_t i = v.size(); i > 0; --i) {
        std::cout << v[i - 1] << ' ';
    }
    std::cout << '\n';

    // ===== 6. 经典坑：分号 =====
    std::cout << "\n=== 坑 2: for 后面多写分号 ===\n";
    int count = 0;
    for (int i = 0; i < 3; ++i);      // <-- 这个分号让循环体变成空语句
    {
        ++count;                       // 只执行一次
    }
    std::cout << "count = " << count << "  <-- 期望 3，实际 1\n";
    return 0;
}
