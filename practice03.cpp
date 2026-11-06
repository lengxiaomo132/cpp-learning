// practice03.cpp

#include <iostream>

int main()
{ // 程序开始

    // 血量输入
    int hp = 0;
    std::cout << "请输入角色剩余血量：";
    std::cin >> hp;

    // 检查输入是否有效
    if (std::cin.fail())
    {
        std::cout << "输入无效！你输入的不是整数。\n";
        return 1;
    }
    std::cout << "角色剩余血量: " << hp << '\n';

    // 做出血量分级判断

    bool need_health = (hp > 0) && (hp < 30);
    if (hp <= 0)
    {
        std::cout << "已阵亡\n";
    }
    else if (need_health)
    {
        std::cout << "濒死\n";
    }
    else if (hp < 80)
    {
        std::cout << "负伤\n";
    }
    else
    {
        std::cout << "健康\n";
    }

    // 确认是否需要治疗
    std::cout << "需要治疗: " << std::boolalpha << need_health << '\n';

    // 程序结束
    return 0;
}