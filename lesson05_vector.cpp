// lesson05_vector.cpp —— vector 基础：先全部读进来，再统一处理
#include <iostream>
#include <vector>

int main() {
    // ===== 1. 造一个空列表 =====
    std::vector<int> hps;
    std::cout << "初始大小: " << hps.size() << '\n';

    // ===== 2. 往里加 =====
    hps.push_back(30);
    hps.push_back(50);
    hps.push_back(10);
    std::cout << "加完 3 个后大小: " << hps.size() << '\n';

    // ===== 3. 按下标取 =====
    std::cout << "hps[0]=" << hps[0]
              << " hps[1]=" << hps[1]
              << " hps[2]=" << hps[2] << '\n';

    // ===== 4. 最常用：for + size + [] 遍历 =====
    std::cout << "\n遍历: ";
    for (std::size_t i = 0; i < hps.size(); ++i) {
        std::cout << hps[i] << ' ';
    }
    std::cout << '\n';

    // ===== 5. 先全部读入，再统一处理（你要的模式）=====
    std::cout << "\n=== 先读入 N 个，再统一处理 ===\n";
    int n = 0;
    std::cin >> n;

    std::vector<int> enemy_hps;
    for (int i = 0; i < n; ++i) {
        int hp = 0;
        std::cin >> hp;
        enemy_hps.push_back(hp);      // 读一个就存一个，不会覆盖
    }

    // 此时全部血量都在 enemy_hps 里了
    std::cout << "共读入 " << enemy_hps.size() << " 个敌人\n";
    for (std::size_t i = 0; i < enemy_hps.size(); ++i) {
        std::cout << "  第 " << i + 1 << " 个: " << enemy_hps[i] << '\n';
    }

    // 现在可以"先打完再算"了：比如统计总血量
    int total = 0;
    for (std::size_t i = 0; i < enemy_hps.size(); ++i) {
        total += enemy_hps[i];
    }
    std::cout << "总血量 = " << total << '\n';
    return 0;
}
