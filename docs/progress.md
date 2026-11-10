# 学习进度

> **最后更新**：2026-11-10

- 学什么 → [cpp-schedule.md](cpp-schedule.md)｜怎么教 → [teaching-notes.md](teaching-notes.md)｜作业要求 → [assignments.md](assignments.md)｜启动指令 → [START-HERE.md](START-HERE.md)

---

## 当前位置

| 项 | 值 |
|---|---|
| 已完成 | 第 17 课（移动语义、拷贝控制），practice17.cpp ✅ 实测通过 |
| 下一课 | 第 18 课：未定义行为与防御性编程 |
| 学生水平 | 有 Python/Java 概念，C++ 从零起步 |

---

## 完成记录

| 课次 | 主题 | 作业文件 | 结果 |
|---|---|---|---|
| 1 | 程序结构、编译流程 | practice01.cpp | ✅ |
| 2 | 变量、类型、cin/cout | practice02.cpp | ✅ |
| 3 | if/else、bool、输入有效性 | practice03.cpp | ✅ |
| 4 | 循环 | practice04.cpp | ✅ |
| 补充 | for/do-while/break/continue | practice04b.cpp | ✅ |
| 5 | 函数、引用传递 | practice04b.cpp（重构版） | ✅ |
| 6 | std::vector | lesson05_vector.cpp（预习） | ✅ |
| 7 | std::string | practice07.cpp | ✅ |
| 8 | struct | practice08.cpp | ✅ |
| 9 | 引用 vs 指针 | practice09.cpp | ✅ |
| 9.5 | switch + enum 专题 | practice09b.cpp | ✅ |
| 10 | 栈 / 堆 / unique_ptr | practice10.cpp | ✅ |
| 11 | 类：封装、const、初始化列表 | practice11.cpp | ✅ |
| 12 | 析构、拷贝、运算符重载 | practice12.cpp | ✅ |
| 13 | 继承 + 虚函数 | practice13.cpp | ✅ |
| 14 | 模板 + lambda | practice14.cpp | ✅ |
| 14.5 | map 与 unordered_map | practice14b.cpp | ✅ |
| 15 | 多文件工程 | practice15/（enemy.h + enemy.cpp + main.cpp） | ✅ |
| 16 | static 成员与静态函数 | practice16.cpp | ✅ |
| 17 | 移动语义、拷贝控制 | practice17.cpp | ✅ |

> practice04b.cpp 兼作循环补充与函数重构成果，没有单独的 practice05。

---

## 已掌握

| 课次 | 内容 |
|---|---|
| 1 | `#include`、`main`、`int`、`std::cout`、`<<`、`'\n'`、`return`、退出码 |
| 2 | `std::cin`、`>>`、`int/double/bool`、整数除法陷阱、`static_cast` |
| 3 | `if/else if/else`、比较运算符、`bool`、`boolalpha`、`&&/\|\|/!`、短路求值、`cin.fail()`、`cin.clear()`、`cin.ignore()`、卫语句 |
| 4 | `for`、`while`、`do-while`、`break`、`continue`、边界钳制 |
| 5 | 函数定义/调用、`void`、参数、**引用 `&`**、值传递 vs 引用传递、用 `bool` 返回错误 |
| 预习 | `std::vector<int>`：`push_back`、`size()`、`[i]`、`std::size_t` |
| 7 | `std::string`：`#include <string>`、`.size()`、`[0]`、`std::getline`、`.empty()`、`.substr(1)`、`std::toupper`、`(char)` 强转 |
| 8 | `struct`：定义、字段、`.` 访问、`{}` 初始化、值语义拷贝、`const Player &`、`const std::vector<int> &`、`run_battle` 拆函数 |
| 9 | **引用 vs 指针**：值传递/引用传递/指针传递对比、取地址 `&`、解引用 `*`、`->`、`nullptr`、指针改指向、引用不能改绑/不能为空 |
| 9.5 | **`enum class`** 定义动作、**`switch`/`case`/`break`/`default`**、贯穿（fallthrough）陷阱、枚举作参数 |
| 10 | **栈 vs 堆**、`new`/`delete`、`std::make_unique`/`unique_ptr`、构造/析构打印时机、`p`（栈上的管家）vs `*p`（堆上的对象）、判空、`reset()`/`release()` 区别 |
| 11 | **`class` 与 `private`/`public`**、getter/setter、**初始化列表**、**`const` 三种用法**（const 变量 / const 成员函数 / const 对象）、**`auto`**、**range-for 与 `const auto &`**、`explicit`（学生自用） |
| 12 | **析构函数**（时机、逆序）、**拷贝构造函数** `const 类名 &`（为什么必须 `&` 和 `const`）、副本在不同地址、**`operator<<` 重载**（`std::ostream &` 返回值、用 `os` 不用 `std::cout`、`return os`）、`void` vs `std::ostream &`、临时对象在完整语句结束时析构 |
| 13 | **继承**（`class Boss : public Enemy`）、**`protected`**、**`virtual` 与多态**、**`override`**、**虚析构**、派生类两段析构（`~Boss`→`~Enemy`）、`vector` 元素正序析构 vs 局部变量逆序 |
| 14 | **函数模板** `template <typename T>`、类型推导与限制（同类型、需支持操作）、**lambda** `[](){}`、**捕获列表** `[x]`/`[&x]`/`[=]`/`[&]`、`std::sort` + lambda 比较器、**比较器必须严格弱序（用 `<` 不用 `<=`）** |
| 14.5 | **`std::map` / `std::unordered_map`**、`operator[]` 自动插入、`find`+`end()`、`count`（数键不数值）、`erase`、结构化绑定 `[k, v]`、有序 vs 查找速度的取舍 |
| 15 | **多文件工程**：`.h` 声明 vs `.cpp` 实现、`#pragma once`、`类名::` 作用域、多文件编译命令、`undefined reference`（链接错误） |
| 16 | **`static` 成员变量**（类里声明、类外定义、全类共享一份）、**`static` 成员函数**（无 `this`、不能碰普通成员）、`this` 指针（指向当前对象、`const` 函数里是 `const 类名*`） |
| 17 | **左值与右值**、**右值引用 `T&&`**、**`std::move`**（只标记不移动）、**移动构造 / 移动赋值**、moved-from 状态、**Rule of Five**（声明移动会删除拷贝 → move-only） |

**已讲解未练习**：无

**尚未接触**：未定义行为（第 18 课）

**待补练**：

- [ ] `.size()` 数的是字节（`"林小雨".size() == 9`）
- [ ] `cin >>` 读数字后接 `getline` 必须 `ignore`（practice08 先 getline 后读数，未撞上）
- [ ] `cin >>` **不校验整行**：`30abc` 读到 30、`fail()` 为 false（practice08 实测发现）
- [ ] `char` 算术 `'w'-'a'+'A'`（可选）

**概念易混（第 9 课发现）**：

- [ ] 「语言允许」≠「应该这么做」：指针可以不初始化，但**不应**这么做
- [ ] 引用指向**对象**（变量），不是「函数」——曾把「原对象」写成了「原函数」

**概念易混（第 10 课发现）**：

- [ ] 「对象是栈上的」指 `unique_ptr` 变量本身，被管的 `Enemy` 在堆上
- [ ] `if (p)` 的「空」= 内部指针为 `nullptr`（没管任何对象），不是 `Enemy` 为空

**概念易混（第 13 课发现）**：

- [ ] **析构顺序分三种情况**：局部变量**逆序**（后建先拆）；`vector` 元素**正序**（从前往后）；派生类对象**先派生后基类**
- [ ] 基类引用限制了「你能写什么」（编译期），虚函数决定「实际调用谁」（运行期），两件事分开看

**概念易混（第 14 课发现）**：

- [ ] **`"apple"` 是 `const char*`，不是 `std::string`**：`>` 比的是指针地址不是内容。要内容比较必须 `std::string("apple")`
- [ ] lambda 捕获：值捕获 `[x]` 抓副本（外部改了不跟），引用捕获 `[&x]` 用原件（lambda 活得比变量久就悬垂）
- [ ] `std::sort` 比较器必须严格弱序：用 `<`，用 `<=` 在数据量大时崩溃（实测 2000 个元素 `0xC0000374`）

**概念易混（第 16 课发现）**：

- [ ] `static` 成员**类里只写声明**，必须在类外定义一次（`int Enemy::total = 0;`），否则 `undefined reference`
- [ ] **静态成员变量只能由构造/析构维护**：`reset_total()` 强行清零会让计数与真实对象数脱钩，后续析构把 `total` 减成负数（practice16 实测到 -2）

**概念易混（第 17 课发现）**：

- [ ] **`const T&` 也能接右值**：所以「不写 `&&` 也能编译」，只是退化成拷贝或被复制消除
- [ ] **`const T&` 里不能 `std::move`**：`const` 让 move 失效，且违背「拷贝不动原件」的承诺；想搬必须用 `T&&`
- [ ] **只写移动构造 → 拷贝构造被隐式删除**，类变成 move-only，传左值直接编译失败
- [ ] **`std::move(临时对象)` 是多余且有害的**：触发 `-Wpessimizing-move`，反而阻止复制消除

**已借用但没正式教**（🔵 看过、不用会写，勿进「已掌握」）：

| 概念 | 在哪出现 | 正式教在哪 |
|---|---|---|
| `sizeof` | 第 10 课讲 `unique_ptr` 大小 | 第 19 课 |
| `std::move` / 移动构造 | 第 11 课发现 `push_back` 临时对象走的是移动 | 第 16 课 |
| `explicit` | 学生自己在 `practice11.cpp` 用了 | 未列入课表，用对了即可 |

> `const`、初始化列表、`auto`、range-for 已在第 11 课正式教并练习，不再是借用。

---

## 易错点

讲到这里时主动提醒。

| 错误 | 次数 | 说明 | 提醒时机 |
|---|---|---|---|
| `=` 当 `==` | 2 次 | `if (hp_enemy = 0)`、`if (confrim = 'n')` | 写任何 `if` 时 |
| 拼写错误 | 多次 | `ruturn`、`fales`、`confrim` | 报"未声明"时先查拼写 |
| 内层变量遮蔽外层 | 1 次 | 外层 `int hp` 没用上 | 见到 `unused variable` 时 |
| 参数多余 / 返回类型不满足 | 1 次 | `ask_confirm(char confirm)` 参数没用 | 设计函数时先问"传入什么、传出什么" |
| 依赖传递性包含 | 1 次 | 缺 `#include <limits>`，不带 `-std` 能编、带就失败 | 用到 `numeric_limits` 时 |
| 循环变量当编号用 | 1 次 | `while` 的 `i` 从 0 开始，输出成「第 0 回合」 | 循环里要显示序号时用 `i + 1` |
| 参数值传递大容器 | 1 次 | `apply_damage(Player&, std::vector<int>)` 每次复制整个 vector | 传入只读的 `vector`/`string`/`struct` 时用 `const &` |
| `&` 和 `*` 在不同位置意思不同 | 1 次 | `&` 在声明里是引用、在表达式里是取地址；`*` 在声明里是指针、在表达式里是解引用 | 每写一个 `&` 或 `*` 时先问「这是声明还是表达式」 |
| 改函数名漏改调用处 | 1 次 | `Do_Action` 改成 `do_action`，第 62 行调用没跟着改，编译失败 | 重命名用 `F2`，别手改 |
| 复制粘贴漏删旧文字 | 1 次 | 判空分支的两句输出粘错，「有对象」后面还跟着「指针为空」 | 复制整段代码后逐行读一遍 |
| 新建文件头注释写错文件名 | 2 次 | `practice09b.cpp` 写成 `practice09.cpp`；`practice10.cpp` 也写成 `practice09b.cpp` | 新建文件先写对第一行 |
| 改一半就交回 | 2 次 | `practice09b` 改了函数名没改调用处；`practice11` 上一轮 4 条建议只改了 1 条，还留 `unused variable` 警告 | **交作业前把上次的问题清单逐条打勾** |
| 该调的成员函数没调，用近似表达式代替 | 1 次 | `is_alive()` 写成了 `get_hp() ? true : false`，碰巧同义才没被发现 | 函数写出来了就一定要调到 |
| `operator<<` 里写死 `std::cout` | 未发生（预防） | 函数里该用参数 `os` 却用了 `std::cout`，导致 `cerr`、文件流全部输出到屏幕，且**编译不报错** | 写 `operator<<` 时通读一遍：有没有直接出现 `std::cout` |
| 忘了带括号调用函数 | 1 次 | `d.get_name` 少了 `()`，报 `<unresolved overloaded function type>` | 打印函数返回值时检查有没有 `()` |
| 字符串字面量当成 `std::string` 用 | 1 次 | `max_of("apple","pear")` 推导成 `const char*`，比较指针地址，结果 `apple` 而非 `pear`，**编译不报错** | 要比较内容就写 `std::string("...")` |

---

## 待办

- [ ] 第 18 课：未定义行为与防御性编程——课表要求：列出 4 种 UB，各写一个能触发的最小例子，并说出正确写法
