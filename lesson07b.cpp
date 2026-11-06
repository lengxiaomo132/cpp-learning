// lesson07b.cpp —— getline 与 cin 的配合
#include <iostream>
#include <string>

int main() {
    // 先读一个数字
    int age = 0;
    std::cout << "请输入年龄: ";
    std::cin >> age;

    // 关键：cin >> 读完数字后，回车符 '\n' 还留在缓冲区
    // 直接 getline 会读到空行！所以要先清掉
    std::cin.ignore(1000, '\n');

    // 再读一整行（可以含空格）
    std::string full_name;
    std::cout << "请输入全名: ";
    std::getline(std::cin, full_name);

    std::cout << "\n年龄 = " << age << '\n';
    std::cout << "全名 = [" << full_name << "] 长度 " << full_name.size() << '\n';

    // 演示：如果不清 ignore，会读到什么
    return 0;
}
