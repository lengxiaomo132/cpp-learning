// lesson02.cpp —— 类型大小 & 整数溢出的现实
#include <iostream>
#include <limits>

int main() {
    // sizeof 会告诉你每种类型占几个字节（1 字节 = 8 位）
    std::cout << "int   = " << sizeof(int)        << " 字节\n";
    std::cout << "long  = " << sizeof(long)       << " 字节\n";
    std::cout << "long long = " << sizeof(long long) << " 字节\n";
    std::cout << "float = " << sizeof(float)      << " 字节\n";
    std::cout << "double= " << sizeof(double)     << " 字节\n";
    std::cout << "char  = " << sizeof(char)       << " 字节\n\n";

    // int 的最大值到底是多少
    std::cout << "int 最大值 = " << std::numeric_limits<int>::max() << '\n';

    // 游戏里最常见的溢出场景：金币反作弊 / 伤害累加
    int gold = 2000000000;      // 20 亿
    std::cout << "gold = " << gold << '\n';
    gold = gold + gold;         // 40 亿 -> 装不下
    std::cout << "gold + gold = " << gold << "  <-- 注意这个负数\n";
    return 0;
}
