// practice14b.cpp

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    std::vector<std::string> words{"sword", "shield", "sword",
                                   "potion", "sword", "shield",
                                   "bow"};

    std::cout << "\n=== 1. map 统计 ===\n";
    std::map<std::string, int> count_words;
    for (const auto &w : words)
    {
        ++count_words[w];
    }
    for (const auto &[k, v] : count_words)
    {
        std::cout << "  " << k << " : " << v << '\n';
    }

    std::cout << "\n=== 2. 查找 ===\n";
    auto it = count_words.find("sword");
    if (it != count_words.end())
    {
        std::cout << "  sword 出现了 " << it->second << " 次\n";
    }
    else
    {
        std::cout << "  未找到sword" << '\n';
    }

    auto it2 = count_words.find("axe");
    if (it2 != count_words.end())
    {
        std::cout << "  axe 出现了 " << it2->second << " 次\n";
    }
    else
    {
        std::cout << "  未找到axe" << '\n';
    }

    std::cout << "\n=== 3. operator[] 的陷阱 ===\n";
    std::cout << "  查 axe 之前 size = " << count_words.size() << '\n';
    std::cout << "  查到的值 = " << count_words["axe"] << '\n'; // 显式说明"我故意不用它"
    std::cout << "  查 axe 之后 size = " << count_words.size() << "   <- 被插入了" << '\n';
    count_words.erase("axe");
    std::cout << "  erase 之后 size = " << count_words.size() << '\n';

    std::cout << "\n=== 4. unordered_map 验证 ===\n";
    std::unordered_map<std::string, int> u;
    for (const auto &w : words)
    {
        ++u[w];
    }
    std::cout << "  u[\"sword\"] = " << u["sword"] << '\n';
    std::cout << "  u.count(\"sword\") = " << u.count("sword") << '\n';
    return 0;
}