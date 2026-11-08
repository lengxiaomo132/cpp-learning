// lesson14b.cpp —— 第 14.5 课：map 与 unordered_map
// 本节工具：vector、string、range-for、auto、const auto &、lambda、模板
// 本节新教：std::map、std::unordered_map、operator[]、find、count、erase

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    // ===== 1. 问题：统计每个词出现几次 =====
    std::vector<std::string> words{
        "sword", "shield", "sword", "potion",
        "sword", "shield", "bow"};

    // ===== 2. map：键值对，会自动按键排序 =====
    std::cout << "=== 1. std::map 统计词频 ===\n";
    std::map<std::string, int> count_map;

    for (const auto &w : words)
    {
        count_map[w] = count_map[w] + 1; // 不存在时自动创建为 0
    }

    for (const auto &pair : count_map)
    {
        std::cout << "  " << pair.first << " : " << pair.second << '\n';
    }

    // ===== 3. unordered_map：同样统计，但顺序不保证 =====
    std::cout << "\n=== 2. std::unordered_map 同样统计 ===\n";
    std::unordered_map<std::string, int> count_umap;

    for (const auto &w : words)
    {
        ++count_umap[w]; // 等价写法
    }

    for (const auto &pair : count_umap)
    {
        std::cout << "  " << pair.first << " : " << pair.second << '\n';
    }

    // ===== 4. 查找：find 和 count =====
    std::cout << "\n=== 3. 查找 ===\n";

    auto it = count_map.find("sword");
    if (it != count_map.end())
    {
        std::cout << "  find(\"sword\") 成功，次数 = " << it->second << '\n';
    }
    else
    {
        std::cout << "  没找到 sword\n";
    }

    auto it2 = count_map.find("axe");
    if (it2 == count_map.end())
    {
        std::cout << "  find(\"axe\") 没找到（返回 end()）\n";
    }

    std::cout << "  count(\"bow\") = " << count_map.count("bow") << '\n';
    std::cout << "  count(\"axe\") = " << count_map.count("axe") << '\n';

    // ===== 5. 危险：operator[] 会偷偷插入 =====
    std::cout << "\n=== 4. operator[] 的陷阱 ===\n";
    std::cout << "  查 count_map[\"axe\"]（原本没有）："
              << count_map["axe"] << '\n';
    std::cout << "  现在 count_map.size() = " << count_map.size()
              << "  <- 多了一个！\n";
    std::cout << "  count(\"axe\") = " << count_map.count("axe")
              << "  <- 它被插进去了\n";

    // ===== 6. 删掉它 =====
    count_map.erase("axe");
    std::cout << "  erase 之后 size() = " << count_map.size() << '\n';

    // ===== 7. 遍历时用 first / second =====
    std::cout << "\n=== 5. 遍历的两种写法 ===\n";
    for (const auto &[key, value] : count_map) // 结构化绑定（C++17，借用）
    {
        std::cout << "  " << key << " -> " << value << '\n';
    }

    return 0;
}
