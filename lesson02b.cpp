// lesson02b.cpp —— 字节到底代表什么 + 输入提示怎么写
#include <iostream>
#include <limits>     // std::numeric_limits 在这个头文件里
#include <string>

int main() {
    // ===== 第一部分：字节 = 容量上限 =====
    std::cout << "=== 字节代表容量 ===\n";
    std::cout << "char       占 " << sizeof(char)      << " 字节, 最大值 = " << (int)std::numeric_limits<char>::max() << '\n';
    std::cout << "short      占 " << sizeof(short)     << " 字节, 最大值 = " << std::numeric_limits<short>::max() << '\n';
    std::cout << "int        占 " << sizeof(int)       << " 字节, 最大值 = " << std::numeric_limits<int>::max() << '\n';
    std::cout << "long long  占 " << sizeof(long long) << " 字节, 最大值 = " << std::numeric_limits<long long>::max() << '\n';

    // ===== 第二部分：同一块内存，换个类型看，结果完全不同 =====
    std::cout << "\n=== 字节代表什么？同一块内存两种解读 ===\n";
    int number = 65;

    char as_char = static_cast<char>(number);   // 按 char 解读：65 是字母 'A'
    std::cout << "存进去的整数: " << number << '\n';
    std::cout << "按 char 解读 : " << as_char << '\n';

    int code = 'A';                             // 反方向：字母在内存里其实是数字
    std::cout << "'A' 的编码  : " << code << '\n';

    // ===== 第三部分：字符串占多大（注意：不等于字符个数）=====
    std::cout << "\n=== std::string 占多大 ===\n";
    std::string empty = "";
    std::string name  = "Liam";
    std::cout << "空字符串 sizeof = " << sizeof(empty) << '\n';
    std::cout << "\"Liam\" sizeof    = " << sizeof(name)  << '\n';
    std::cout << "\"Liam\" 字符数     = " << name.size()  << '\n';
    return 0;
}
