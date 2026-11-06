// lesson09b.cpp —— switch + enum 小专题（第 9.5 课）
// 本节工具：int、std::string、if/else、std::cin/cout
// 新增：enum class、switch/case/break/default

#include <iostream>
#include <string>

// ===== 1. enum class 定义动作 =====
enum class Action
{
    Attack,
    Defend,
    Flee
};

// ===== 2. 用 enum 作参数（类型安全） =====
void do_action(Action a)
{
    switch (a)
    {
    case Action::Attack:
        std::cout << "你挥剑砍了下去\n";
        break; // 不写 break 会往下贯穿
    case Action::Defend:
        std::cout << "你举起盾牌\n";
        break;
    case Action::Flee:
        std::cout << "你转身逃跑\n";
        break;
    default:
        std::cout << "未知动作\n";
        break;
    }
}

// ===== 3. switch 也能接 int / char =====
std::string grade_of(int score)
{
    // 只演示 switch 的写法，真实判断区间要用 if
    switch (score / 60) // 0 = 不及格，1 = 及格
    {
    case 0:
        return "不及格";
    case 1:
        return "及格";
    default:
        return "超出范围";
    }
}

int main()
{
    std::cout << "=== 1. enum class 的基本用法 ===\n";
    Action a = Action::Attack;
    do_action(a);
    do_action(Action::Defend);
    do_action(Action::Flee);

    // ===== 4. 漏掉 break 的后果（见下方演示，这里正常写） =====
    std::cout << "\n=== 2. 每个 case 都要 break ===\n";
    std::cout << "漏掉 break 会贯穿到下一个 case，-Wextra 会给出警告\n";

    // ===== 5. 没有匹配项时走 default =====
    std::cout << "\n=== 3. default 的作用 ===\n";
    std::cout << "grade_of(75) = " << grade_of(75) << '\n';
    std::cout << "grade_of(45) = " << grade_of(45) << '\n';
    std::cout << "grade_of(150) = " << grade_of(150) << "  <- 走 default\n";

    // ===== 6. switch 不能接 string =====
    std::cout << "\n=== 4. switch 的适用范围 ===\n";
    std::cout << "switch 能接：int、char、enum class\n";
    std::cout << "switch 不能接：std::string（底层要跳转表，字符串无法直接索引）\n";

    return 0;
}
