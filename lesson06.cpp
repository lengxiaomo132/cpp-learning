// lesson06.cpp —— 函数基础：返回值、void、引用传递
#include <iostream>

// ① 有返回值：给两个数，返回和
int add(int a, int b) {
    return a + b;
}

// ② void：什么都不返回，只做事
void say_hello() {
    std::cout << "你好，冒险者！\n";
}

// ③ 值传递：改的是副本，外面不受影响
void attack_by_value(int hp) {
    hp = hp - 10;
    std::cout << "  [值传递] 函数内 hp = " << hp << '\n';
}

// ④ 引用传递：加 &，改的是本体
void attack_by_ref(int& hp) {
    hp = hp - 10;
    std::cout << "  [引用传递] 函数内 hp = " << hp << '\n';
}

int main() {
    // ===== 1. 有返回值的函数 =====
    int x = add(3, 4);
    std::cout << "add(3, 4) = " << x << '\n';
    std::cout << "add(10, 20) = " << add(10, 20) << '\n';

    // ===== 2. void 函数 =====
    say_hello();

    // ===== 3. 关键对比：值传递 vs 引用传递 =====
    std::cout << "\n=== 值传递 ===\n";
    int player_hp = 100;
    std::cout << "调用前: " << player_hp << '\n';
    attack_by_value(player_hp);
    std::cout << "调用后: " << player_hp << "   <-- 没变！\n";

    std::cout << "\n=== 引用传递 ===\n";
    std::cout << "调用前: " << player_hp << '\n';
    attack_by_ref(player_hp);
    std::cout << "调用后: " << player_hp << "   <-- 变了！\n";
    return 0;
}
