// lesson01.cpp
// 第 1 课：一个完整程序由什么组成
#include <iostream>   // 1. 引入"输入输出"工具，才有 std::cout

int main() {          // 2. 程序入口：main 是唯一起点，返回 int
    int age = 18;     // 3. 声明一个整数变量并初始化
    std::cout << "年龄 = " << age << '\n';   // 4. 把内容输出到屏幕
    return 0;         // 5. 返回 0 表示"程序正常结束"
}
