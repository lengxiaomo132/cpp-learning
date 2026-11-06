// practice08.cpp

#include <iostream>
#include <string> // string
#include <vector>

// 建立角色结构
struct Player
{
    std::string name;
    int hp;
    int atk;
}; // <-- 分号不能少

// 定义对战函数
void run_battle(Player &p, const std::vector<int> &dmg)
{

    int i = 0;
    while (i < 3)
    {
        int hp_last_turn = p.hp;
        p.hp = p.hp - dmg[i]; // 攻击扣血
        if (p.hp < 0)
            p.hp = 0; // 防止血量剩余显示为负数
        std::cout << "第 " << i + 1 << " 回合："
                  << p.name << " 受到 "
                  << dmg[i] << " 伤害，HP "
                  << hp_last_turn << " -> "
                  << p.hp << '\n';
        if (p.hp < 1)
            break;
        ++i;
    }
}

// 程序开始
int main()
{
    Player hero_1;
    // 输入玩家名
    std::cout << "请输入玩家名（可含空格）：";
    std::getline(std::cin, hero_1.name);
    if (hero_1.name.empty())
    {
        std::cout << "角色名不能为空\n";
        return 1;
    }

    // 输入血量
    std::cout << "请输入血量：";
    std::cin >> hero_1.hp;
    if (std::cin.fail())
    {
        std::cout << "血量只能为整数\n";
        return 1;
    }
    std::cin.ignore(1000, '\n');

    // 输入攻击力
    std::cout << "请输入攻击力：";
    std::cin >> hero_1.atk;
    if (std::cin.fail())
    {
        std::cout << "攻击力只能为整数\n";
        return 1;
    }

    // 玩家资料出现
    std::cout << "\n=== 战斗开始 ===\n"
              << hero_1.name << " 血量 " << hero_1.hp << "，攻击力 " << hero_1.atk << '\n';

    // 战斗开始
    std::vector<int> dmg;
    dmg = {15, 10, 10}; // 创建攻击伤害

    // 玩家受伤
    if (hero_1.hp == 0)
        std::cout << "血量不足，别打了。\n";
    else
        run_battle(hero_1, dmg);

    // 关卡结算
    std::cout << "=== 战斗结束 ===\n";
    if (hero_1.hp > 0)
        std::cout << hero_1.name << " 胜利了。";
    else
        std::cout << hero_1.name << " 倒下了。";
    return 0;
}