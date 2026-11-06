// lesson03b.cpp —— cin 的内部状态
#include <iostream>
#include <string>

static void show_state(const char* tag) {
    std::cout << tag
              << " | fail=" << std::cin.fail()
              << " eof="  << std::cin.eof()
              << " bad="  << std::cin.bad()
              << " good=" << std::cin.good() << '\n';
}

int main() {
    int n = 0;

    show_state("开始前      ");
    std::cout << "请输入整数: ";
    std::cin >> n;
    show_state("读取之后    ");
    std::cout << "n = " << n << '\n';

    // 尝试再读一次，看失败状态会不会持续
    int m = 0;
    std::cin >> m;
    std::cout << "第二次读取后 m = " << m << '\n';
    show_state("第二次之后  ");

    // 清除错误状态，再试
    std::cin.clear();                 // 只清状态标志
    std::string rest;
    std::cin >> rest;                 // 读走卡住的垃圾
    std::cout << "清掉后读到的残留内容: [" << rest << "]\n";

    int k = 0;
    std::cin >> k;
    std::cout << "清除后第三次 k = " << k << '\n';
    show_state("清除+跳过后");
    return 0;
}
