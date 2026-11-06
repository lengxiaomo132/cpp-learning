// lesson07c.cpp —— char 参与算术、大小写转换、substr
#include <cctype>
#include <iostream>
#include <string>

int main() {
    std::cout << "=== 1. char 是数字 ===\n";
    char ch = 'w';
    std::cout << "ch = " << ch << '\n';
    std::cout << "(int)ch = " << (int)ch << "  <- 本质是 119\n";
    std::cout << "'a' - 'A' = " << ('a' - 'A') << '\n';

    std::cout << "\n=== 2. 手算大小写转换 ===\n";
    char upper = ch - 'a' + 'A';   // 119 - 97 + 65 = 87 = 'W'
    std::cout << ch << " -> " << upper << '\n';

    std::cout << "\n=== 3. 用 std::toupper（推荐）===\n";
    std::cout << "std::toupper('w') = " << (char)std::toupper('w') << '\n';
    std::cout << "std::toupper('W') = " << (char)std::toupper('W') << "  <- 本来大写也不变\n";
    std::cout << "std::toupper('5') = " << (char)std::toupper('5') << "  <- 非字母不动\n";

    std::cout << "\n=== 4. 手算的问题：非小写会出错 ===\n";
    char bad = 'W' - 'a' + 'A';    // 87 - 97 + 65 = 55 = '7'
    std::cout << "'W' 手算结果 = '" << bad << "'  <- 变成了 7！\n";

    std::cout << "\n=== 5. substr：截取一段 ===\n";
    std::string job = "warrior";
    std::cout << "job = " << job << '\n';
    std::cout << "job.substr(1) = " << job.substr(1) << "  <- 从下标 1 开始\n";
    std::cout << "job.substr(0, 3) = " << job.substr(0, 3) << "  <- 从 0 开始取 3 个\n";

    std::cout << "\n=== 6. 拼出 [W]arrior ===\n";
    char first_upper = (char)std::toupper(job[0]);
    std::string code = "[" + std::string(1, first_upper) + "]" + job.substr(1);
    std::cout << code << '\n';

    std::cout << "\n=== 7. 用 cout 直接拼，不用 std::string(1,c) ===\n";
    std::cout << "[" << first_upper << "]" << job.substr(1) << '\n';
    return 0;
}
