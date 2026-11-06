// practice07.cpp

#include <iostream>
#include <cctype> // toupper
#include <string> // string

int main()
{ // 程序开始
    std::string name;
    std::cout << "请输入角色名（可含空格）：";
    std::getline(std::cin, name);
    if (name.empty())
    {
        std::cout << "角色名不能为空\n";
        return 1;
    }

    std::string job;
    std::cout << "请输入职业：";
    std::cin >> job;
    if (job.empty())
    {
        std::cout << "职业不能为空\n";
        return 1;
    }

    int level = 0;
    std::cout << "请输入等级：";
    std::cin >> level;

    std::cout << "=== 角色卡 ===\n"
              << "名字: " << name << " (" << name.size() << " 个字符)\n"
              << "职业: " << job << '\n'
              << "等级: " << level << '\n'
              << "首字母: " << name[0] << '\n'
              << "职业代号: " << '[' << (char)std::toupper(job[0]) << ']' << job.substr(1) << '\n';

    return 0;
}