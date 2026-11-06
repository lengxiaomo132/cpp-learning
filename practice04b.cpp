// practice04b.cpp
// programe name:三关战斗

#include <iostream>
#include <vector>
#include <limits>


// 读敌人数量
bool read_enemy_count(int &enemy_count)
{
    enemy_count = 0;
    while (!(enemy_count > 0))
    {
        std::cout << "请输入敌人总数：";
        std::cin >> enemy_count;
        if (std::cin.fail()) // 输入无效值时退出程序
        {
            std::cout << "输入无效！你输入的不是整数。\n";
            return false;
        }
        // 输入0时重新输入
        if (enemy_count == 0)
            std::cout << "你来打架怎么能没人呢？\n\n";
    }
    return true;
}

// 读敌人血量（vector)
bool read_enemy_hps(std::vector<int> &enemy_hps, int enemy_count)
{
    int hp = 0;
    std::cout << "请输入" << enemy_count << " 个敌人的血量（空格分隔）：";
    for (int i = 0; i < enemy_count; ++i)
    {

        // 循环读hp
        std::cin >> hp;
        if (std::cin.fail()) // 输入无效值时退出程序
        {
            std::cout << "输入无效！你输入的不是整数。\n";
            return false;
        }
        enemy_hps.push_back(hp); //   读一个存一个
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n";
    return true;
}

// 询问是否开始战斗
bool ask_confirm()
{
    char confirm = 'n';
    do
    {
        std::cout << "是否开始战斗？(y/n):";
        std::cin >> confirm;
    } while (confirm != 'y' && confirm != 'n');

    return confirm == 'y'; // 用户输入 y 就返回 true，否则 false
}

// 开始战斗
void run_battle(std::vector<int> &enemy_hps, int &defeated, int enemy_count)
{
    for (int i = 1; i <= enemy_count; ++i)
    {

        // 用 continue 跳过无效敌人
        if (enemy_hps[i - 1] <= 0)
        {
            std::cout << "第 " << i << " 关："
                      << "敌人大抵是早已死了的\n";
            std::cout << "第 " << i << " 关通过\n\n";
            continue;
        }

        // 敌人生成
        std::cout << "第 " << i << " 关：敌人生成，血量 "
                  << enemy_hps[i - 1] << '\n';

        // 用 break 处理过强敌人
        if (enemy_hps[i - 1] > 100)
        {
            std::cout << "敌人过于强大，撤退\n";
            break;
        }

        // 玩家攻击
        while (enemy_hps[i - 1] > 0)
        {
            enemy_hps[i - 1] = enemy_hps[i - 1] - 10; // 攻击扣血

            // 防止血量剩余显示为负数
            if (enemy_hps[i - 1] < 0)
                enemy_hps[i - 1] = 0;

            std::cout <<"敌人剩余血量 "
                      << enemy_hps[i - 1] << '\n';
        }

        // 关卡结算
        std::cout << "第 " << i << " 关通过\n\n";
        ++defeated; // 击败敌人计数
    }
}

// 程序开始
int main()
{

    int enemy_count = 0; // 1. 输入敌人数量
    if (!read_enemy_count(enemy_count))
        return 1;

    std::vector<int> enemy_hps; // 2. 记录每个敌人血量
    if (!read_enemy_hps(enemy_hps, enemy_count))
        return 1;

    if (!ask_confirm()) // 3. 询问是否开始战斗
    {
        std::cout << "不尝试一下嘛，好吧拜拜\n";
        return 0;
    }
    std::cout << "\n";

    int defeated = 0; // 4. 战斗开始
    run_battle(enemy_hps, defeated, enemy_count);

    std::cout << "战斗结束，共击败 " << defeated << " 个敌人\n"; // 5. 战斗结算
    return 0;
}