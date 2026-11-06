# C++ 学习练习代码

Java/Python 背景转 C++ 的系统学习记录，包含每课的示例代码与课后练习。

## 目录

| 文件 | 内容 |
|---|---|
| `lesson01.cpp` ~ `lesson12.cpp` | 每课课堂示例 |
| `practice01.cpp` ~ `practice12.cpp` | 每课课后作业 |
| `lessonXXb.cpp` / `practiceXXb.cpp` | 补充内容与变体题 |
| `docs/` | 课程安排、作业要求、学习进度 |

## 课程进度

| 课次 | 主题 |
|---|---|
| 1 | 程序结构、编译流程 |
| 2 | 变量、类型、cin/cout |
| 3 | if/else、bool、输入有效性 |
| 4 | 循环（for / do-while / break / continue） |
| 5 | 函数、引用传递 |
| 6 | 数组 / 字符串处理 |
| 7 | std::string |
| 8 | struct |
| 9 | 引用 vs 指针（含 switch + enum 专题） |
| 10 | 栈 / 堆 / unique_ptr |
| 11 | 类：封装、const、初始化列表 |
| 12 | 析构、拷贝、运算符重载 |

## 如何编译运行

使用 g++（MinGW-w64）：

```bash
g++ -std=c++17 -Wall -Wextra lesson01.cpp -o lesson01.exe
./lesson01.exe
```

或使用 clang++/MSVC 均可。

## 说明

编译产物（`*.exe`、`*.o`、`*.pdb` 等）已被 `.gitignore` 排除，仓库中只保留源码与文档。
