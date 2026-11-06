// lesson07.cpp —— std::string 基础
#include <iostream>
#include <string>

int main() {
    // ===== 1. 创建和输出 =====
    std::string name = "Liam";
    std::cout << "name = " << name << '\n';

    // ===== 2. 长度：size() 返回的是字符个数 =====
    std::cout << "name.size() = " << name.size() << '\n';

    // 注意：中文一个字可能占多个字节，size() 数的是字节
    std::string cn = "林";
    std::cout << "\"林\" 的 size() = " << cn.size() << "  <-- UTF-8 一个汉字 3 字节\n";

    // ===== 3. 取单个字符：像 vector 一样用下标，从 0 开始 =====
    std::cout << "name[0] = " << name[0] << '\n';
    std::cout << "name[1] = " << name[1] << '\n';

    // ===== 4. 拼接：直接用 + 号 =====
    std::string full = name + " the Brave";
    std::cout << "\n拼接结果: " << full << '\n';

    // string + 字符
    std::string ex = full + '!';
    std::cout << "加感叹号: " << ex << '\n';

    // ===== 5. 修改：下标赋值 =====
    std::string hero = "Lan";
    hero[0] = 'Y';
    std::cout << "\n修改后: " << hero << '\n';

    // ===== 6. 从键盘读 =====
    std::cout << "\n请输入一个单词: ";
    std::string word;
    std::cin >> word;
    std::cout << "你输入了: [" << word << "] 长度 " << word.size() << '\n';

    return 0;
}
