// lesson03.cpp —— bool、逻辑运算符、输入有效性判断
#include <iostream>

int main() {
    // ===== 1. bool 只有两个值 =====
    bool alive = true;
    bool dead  = false;
    std::cout << "true 打印出来是: " << alive << '\n';   // 1
    std::cout << "false 打印出来是: " << dead  << '\n';  // 0
    std::cout << "std::boolalpha 打开后: " << std::boolalpha << alive << '\n';

    // ===== 2. 比较运算返回 bool =====
    std::cout << "\n=== 比较结果 ===\n";
    int a = 7, b = 4;
    std::cout << (a > b)  << "  (a > b)\n";
    std::cout << (a == b) << "  (a == b)\n";

    // ===== 3. 逻辑运算符 && || ! =====
    std::cout << "\n=== 逻辑运算符 ===\n";
    int hp = 25;
    int max_hp = 100;
    // 血量低于 30% 且大于 0 -> 濒死
    bool low_hp = (hp < max_hp * 0.3) && (hp > 0);
    std::cout << "hp=" << hp << " 濒死状态: " << low_hp << '\n';

    // ===== 4. 关键：cin 失败检测 =====
    std::cout << "\n=== 输入有效性 ===\n";
    int n = 0;                    // 先给个安全初始值！
    std::cout << "请输入一个整数: ";
    std::cin >> n;

    if (std::cin.fail()) {        // cin 读失败时为 true
        std::cout << "输入无效！你输入的不是整数。\n";
    } else {
        std::cout << "你输入了: " << n << '\n';
    }
    return 0;
}
