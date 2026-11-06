// lesson06b.cpp —— 多余输入在哪里
#include <iostream>

int main() {
    int count = 0;
    std::cout << "输入 count: ";
    std::cin >> count;

    // 模拟：读 count 个血量
    int hp = 0;
    for (int i = 0; i < count; ++i) {
        std::cin >> hp;
        std::cout << "  读到 hp[" << i << "] = " << hp << '\n';
    }

    // 关键：下一个读的是什么？
    char c = '?';
    std::cin >> c;
    std::cout << "下一个字符 c = [" << c << "]\n";

    char c2 = '?';
    std::cin >> c2;
    std::cout << "再下一个   c2 = [" << c2 << "]\n";
    return 0;
}
