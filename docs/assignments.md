# 作业单

> 每次作业的具体要求。写法规范见 [teaching-notes.md](teaching-notes.md) 规则 8。
> **示例输出就是验收标准，逐字对照。**

**目录**（点标题跳转）：

| 练习 | 主题 | 对应课次 |
|---|---|---|
| [练习 08](#练习-08打怪模拟器) | 打怪模拟器 | 第 8 课 struct |
| [练习 09](#练习-09引用与指针对照实验) | 引用与指针对照实验 | 第 9 课 引用 vs 指针 |
| [练习 09b](#练习-09b动作选择器) | 动作选择器 | 第 9.5 课 switch + enum |
| [练习 10](#练习-10三种存储方式对照) | 三种存储方式对照 | 第 10 课 栈/堆/unique_ptr |
| [练习 11](#练习-11把-player-改成-class) | 把 Player 改成 class | 第 11 课 类与封装 |
| [练习 12](#练习-12生命周期与输出) | 生命周期与输出 | 第 12 课 析构/拷贝/运算符重载 |
| [练习 13](#练习-13继承与多态) | 继承与多态 | 第 13 课 继承 + 虚函数 |
| [练习 14](#练习-14模板与-lambda) | 模板与 lambda | 第 14 课 模板 + lambda |
| [练习 14b](#练习-14b背包统计) | 背包统计 | 第 14.5 课 map |
| [练习 15](#练习-15拆成三个文件) | 拆成三个文件 | 第 15 课 多文件工程 |
| [练习 16](#练习-16敌人计数器) | 敌人计数器 | 第 16 课 static 成员 |
| [练习 17](#练习-17拷贝-vs-移动) | 拷贝 vs 移动 | 第 17 课 移动语义 |
| [练习 18](#练习-18ub-清单与防线) | UB 清单与防线 | 第 18 课 未定义行为 |
| [练习 19](#练习-19结课项目--回合制战斗) | **结课项目：回合制战斗** | 第 19 课 结课项目 |

**当前作业：练习 19（结课项目）**

---

## 练习 08：打怪模拟器

文件：`cpp-learning\practice08.cpp`

```
请输入玩家名：Dark Knight
请输入血量：30
请输入攻击力：12

=== 战斗开始 ===
Dark Knight 血量 30，攻击力 12
第 1 回合：Dark Knight 受到 15 伤害，HP 30 -> 15
第 2 回合：Dark Knight 受到 10 伤害，HP 15 -> 5
第 3 回合：Dark Knight 受到 10 伤害，HP 5 -> 0
=== 战斗结束 ===
Dark Knight 倒下了。
```

### 七条要求

1. 定义 `struct Player`，含 `name`（`std::string`）、`hp`（`int`）、`atk`（`int`）
2. 名字用 `getline` 读（可含空格）
3. 血量、攻击力用 `cin >>` 读
4. 写 `void apply_damage(Player &p, int dmg)`：扣血、`hp` 不许小于 0、打印一行
5. 读完血量立刻用 `cin.fail()` 检查，不是数字就报错 `return 1`
6. 连打 3 回合，伤害依次 `15`、`10`、`10`
7. `hp` 到 0 时输出「倒下了。」

### 提示

`getline` 读名字放在最前面，本作业不需要 `ignore`。

> 需要 `ignore` 的场景：先 `cin >>` 数字再 `getline`。

### 危险点

**1. 扣血必须钳制在 0**

第 3 回合只剩 5 血要挨 10 点，直接减会变成 **-5**，编译器一声不响。

**2. struct 定义后必须有分号**

```cpp
struct Player
{
    std::string name;
    int hp;
    int atk;
};        // <-- 漏了就报错指到下一行
```

**3. `cin.fail()` 必须读后立刻查**

`cin >> hp;` → `if (cin.fail())` → `return 1;`，不能拖到后面。

### 自测边界

| 输入 | 期望 |
|---|---|
| 血量 30，挨 15/10/10 | 第 3 回合停在 0，不是 -5 |
| 血量输 `abc` | 报错退出，`return` 非 0 |

### 进阶（可选）

把两个玩家放进 `std::vector<Player>`，先读数字再读名字，补练：

```cpp
std::cin.ignore(1000, '\n');
```

---

## 练习 09：引用与指针对照实验

文件：`cpp-learning\practice09.cpp`

```
=== 值传递 ===
传入前：hero.hp = 30
函数内：p.hp = 20
返回后：hero.hp = 30   ← 没变

=== 引用传递 ===
传入后：hero.hp = 20   ← 变了

=== 指针传递 ===
传入后：hero.hp = 15   ← 变了

=== 指针改指向 ===
p 指向 A
p 改指 B
p 现在指向 B，A 完好

=== 空指针检查 ===
nullptr 未使用
```

### 六条要求

1. 定义 `struct Player`，含 `name`、`hp`
2. 写三个函数 `by_value(Player p, int dmg)`、`by_ref(Player &p, int dmg)`、`by_ptr(Player *p, int dmg)`，各自扣血
3. 每次调用**前和调用后**打印 `hp`，亲眼看到差别
4. 演示指针改指向：`Player *p = &a;` 再 `p = &b;`，前后各打印 `p->name`
5. 演示空指针检查：`Player *p = nullptr;` 然后 `if (p == nullptr)` 打印提示，**不要解引用**
6. 最后输出「结论」三条，用自己的话说

### 提示

- 每段加一行 `=== xxx ===` 分隔，方便对照
- `by_value` 里改了 `p.hp`，返回后原对象应该**没变**，这是重点

### 危险点

**1. 空指针绝不能解引用**

```cpp
Player *p = nullptr;
p->hp = 5;     // ❌ 编译能过，运行崩溃（访问冲突 0xC0000005）
```

**2. 指针访问成员用 `->`，不用 `.`**

```cpp
p->hp      // ✅ 指针
(*p).hp    // ✅ 等价写法
p.hp       // ❌ "maybe you meant to use '->' ?"
```

**3. 引用声明时必须给初值**

```cpp
Player &r;          // ❌ error: 'r' declared as reference but not initialized
Player &r = hero;   // ✅
```

### 自测边界

| 试什么 | 期望 |
|---|---|
| `by_value` 改完 `hp` | 原对象**没变** |
| `by_ref` / `by_ptr` 改完 | 原对象**变了** |
| `p = nullptr` 后不检查就访问 | 崩溃，**不能出现乱码数字** |
| `r = b` 之后 | `a` 内容变成 `b` 的，`r` 仍指 `a` |

---

## 练习 09b：动作选择器

文件：`cpp-learning\practice09b.cpp`

```
请选择动作（1=攻击 2=防御 3=逃跑）：2

=== 回合结算 ===
玩家选择：防御
你的防御力提升，本回合受到的伤害减少。
```

### 五条要求

1. 用 `enum class Action` 定义三个值：`Attack`、`Defend`、`Flee`
2. 用 `cin >>` 读入 `int`，转换成 `Action`
3. 用 `switch` 分发，每个 `case` 结尾都要有 `break`
4. 必须有 `default` 分支处理未知输入
5. 每个动作输出一句不同的描述

### 提示

给枚举加 `Unknown` 值，让 `default` 有真实语义：

```cpp
enum class Action { Attack, Defend, Flee, Unknown };
```

### 危险点

**1. 每个 `case` 都要 `break`** —— 漏了会贯穿，编译只给警告，运行结果错误

**2. `enum class` 成员必须带前缀**

```cpp
case Action::Attack:   // ✅
case Attack:           // ❌
```

### 自测边界

| 输入 | 期望 |
|---|---|
| `1` / `2` / `3` | 三个分支各自正确 |
| `9` / `0` / 负数 | 走 `default`，输出「未知」 |
| 字母 `a` | `cin.fail()` 报错退出 |

---

## 练习 10：三种存储方式对照

文件：`cpp-learning\practice10.cpp`

```
=== 栈对象 ===
创建：hero hp=30
销毁时机：函数结束时自动
[销毁] hero

=== new / delete ===
创建：enemy hp=50
销毁时机：手动 delete
[销毁] enemy

=== unique_ptr ===
创建：boss hp=100
销毁时机：函数结束自动
[销毁] boss
```

### 六条要求

1. 定义 `struct Enemy`，含 `name`（string）、`hp`（int）
2. 给 `Enemy` 写构造（打印 `创建`）和析构（打印 `[销毁]`）
3. 写三个函数，分别用栈 / `new` / `make_unique` 创建对象
4. `main` 依次调用，**观察 `[销毁]` 打印的时机**
5. 演示 `unique_ptr` 判空：**默认构造一个空的**，`if (p)` 判断
6. 最后输出「结论」三行

### 提示

```cpp
Enemy e{"hero", 30};                                              // 栈
Enemy *p = new Enemy{"enemy", 50};  delete p;                     // new
std::unique_ptr<Enemy> up = std::make_unique<Enemy>("boss", 100); // 智能指针
```

注意 `new` 用花括号、`make_unique` 用圆括号。

### 危险点

**1. `new` 之后必须 `delete`** —— 漏了就是内存泄漏，**编译器完全不提示**

**2. 不要返回局部变量的地址**

```cpp
Enemy *f() { Enemy e{"x", 1}; return &e; }   // ❌ 悬垂指针
```

**3. `unique_ptr` 不能复制**

```cpp
std::unique_ptr<Enemy> b = a;   // ❌ 编译错误，所有权唯一
```

### 自测边界

| 试什么 | 期望 |
|---|---|
| 栈对象的 `[销毁]` | 函数 `}` 时打印 |
| `new` 的 `[销毁]` | **`delete` 那行才打印** |
| `unique_ptr` 的 `[销毁]` | 函数 `}` 时打印（没写 delete） |
| 默认构造的 `unique_ptr` 判空 | 打印「空」分支 |
| 删掉 `delete` 那一行 | 编译通过但**看不到 `[销毁]`** |

---

## 练习 11：把 Player 改成 class

文件：`cpp-learning\practice11.cpp`

```
=== struct 的弱点 ===
Orc 的 hp 被改成 -999 也没人管

=== class 的封装 ===
创建：Liam，初始 hp = 30
set_hp(-50) 后：hp = 0
set_hp(999) 后：hp = 30
is_alive() = true
set_hp(0) 后：is_alive() = false

=== const 演示 ===
const int MAX_LEVEL = 100;
MAX_LEVEL = 200;      ← 这行必须注释掉并写上原因
const Player boss 只能调 const 函数
```

### 八条要求

1. 保留 `struct RawPlayer{name, hp}`，演示直接改出负数没人管
2. 写 `class Player`，三个字段**全部 private**：`name`、`hp`、`max_hp`
3. 写构造函数，**必须用初始化列表**：

   ```cpp
   Player(std::string n, int h) : name(n), hp(h), max_hp(h) { }
   ```

   **不能用**函数体里赋值（`{ name = n; hp = h; }`）的写法
4. 写 `const int MAX_LEVEL = 100;`，**下面跟一行 `MAX_LEVEL = 200;`（注释掉）**并注明「const 变量不能修改」
5. 声明一个 **`const Player boss{...}`**，用它调用 getter 成功，并注释说明「const 对象只能调 const 成员函数」
6. 写 public 成员函数：`get_name() const`、`get_hp() const`、`get_max_hp() const`、`set_hp(int)`（<0 钳到 0，>max_hp 钳到上限）、`is_alive() const`
7. 演示 `set_hp(-50)` 和 `set_hp(999)` 都被钳住，再演示 `set_hp(0)` 后 `is_alive()` 变 `false`
8. 用 `std::vector<Player>` 装 2 个敌人，用 **range-for + `const auto &`** 遍历打印

### 提示

```cpp
// 初始化列表：冒号后面，用括号给成员赋初值
Player(std::string n, int h) : name(n), hp(h), max_hp(h) { }

// const 变量：值定了就不能改
const int MAX_LEVEL = 100;
// MAX_LEVEL = 200;   // ❌ 编译错误

// const 对象：只能调 const 成员函数
const Player boss{"Boss", 200};
boss.get_hp();   // ✅ get_hp 是 const 的

for (const auto &p : enemies)
{
    std::cout << p.get_name() << '\n';   // 用 getter，不是 p.hp
}
```

**`auto` 的类型推断**（顺带验证一下）：

```cpp
auto hp = hero.get_hp();        // int
auto name = hero.get_name();    // std::string
```

### 危险点

**1. 所有 getter 必须加 `const`** —— 否则在 `const auto &` 循环里、或 `const Player` 上调不了

**2. 初始化列表不能省** —— 写成 `{ name = n; hp = h; max_hp = h; }` 能编译，但成员先被默认构造再赋值，语义不同；**本作业要求用初始化列表**

**3. 钳制顺序**：先 `< 0`，再 `> max_hp`，两个独立 `if`

**4. 别在 `main` 里直接写 `hero.hp`** —— private，编译错误

### 自测边界

| 试什么 | 期望 |
|---|---|
| `set_hp(-50)` | 返回 0 |
| `set_hp(999)` | 返回 `max_hp` |
| `set_hp(0)` 后 `is_alive()` | `false` |
| `main` 里写 `hero.hp` | **编译错误** |
| getter 不加 `const` | range-for 里编译错误 |
| 去掉 `//` 放开 `MAX_LEVEL = 200;` | **编译错误**（const 变量不能改） |
| `const Player boss` 调 `set_hp` | **编译错误**（const 对象不能调非 const 函数） |

### 进阶（可选）

给 `Player` 加 `void take_damage(int dmg)`，内部调用 `set_hp(hp - dmg)`。

**你会看到一个结果**：负血保护不用重写，因为规则已经在 `set_hp` 里写好了。**这就是把门变成规矩的好处：规则只写一次，所有入口都受约束。**

---

## 练习 12：生命周期与输出

文件：`cpp-learning\practice12.cpp`

```
=== 1. 构造与析构 ===
[构造] Orc hp=30
  进入作用域
[析构] Orc
  离开作用域

=== 2. 拷贝构造 ===
[构造] Goblin hp=15
[拷贝构造] Goblin（来自 Goblin）
  b 地址与 c 地址不同
=== 3. 重载 << ===
  Goblin(hp=15)
  Goblin(hp=15) 和 Goblin(hp=15)

=== 4. 结束 ===
[析构] Goblin
[析构] Goblin
```

> 地址每次都不同，**只要两个地址不一样就算对**。

### 六条要求

1. 写 `class Enemy`，private 字段 `name`、`hp`
2. 写构造函数 `Enemy(std::string n, int h)`，**用初始化列表**，打印 `[构造] name hp=N`
3. 写**析构函数** `~Enemy()`，打印 `[析构] name`
4. 写**拷贝构造函数** `Enemy(const Enemy &other)`，用初始化列表复制成员，打印 `[拷贝构造] name（来自 other.name）`
5. 重载 `operator<<`，让 `std::cout << enemy` 输出 `name(hp=N)`
6. 在 `main` 里演示四段：
   - 用 `{}` 包住一个对象，观察 `[析构]` 出现在 `}` 时
   - `Enemy b{"Goblin", 15}; Enemy c = b;` 打印**两个对象的地址**，证明不同
   - `std::cout << b` 和 `std::cout << b << " 和 " << c`
   - 顺序观察：结束时析构是否是**逆序**

### 提示

```cpp
class Enemy
{
private:
    std::string name;
    int hp;
public:
    Enemy(std::string n, int h) : name(n), hp(h)
    {
        std::cout << "[构造] " << name << " hp=" << hp << '\n';
    }

    ~Enemy()
    {
        std::cout << "[析构] " << name << '\n';
    }

    Enemy(const Enemy &other) : name(other.name), hp(other.hp)
    {
        std::cout << "[拷贝构造] " << name << "（来自 " << other.name << "）\n";
    }
};

// 写在类外面
std::ostream &operator<<(std::ostream &os, const Enemy &e)
{
    os << e.get_name() << "(hp=" << e.get_hp() << ")";
    return os;      // 别忘了
}
```

**打印地址：** `std::cout << &b << '\n';`

### 危险点

**1. 析构函数不能有参数、不能有返回值**

```cpp
~Enemy(int x) { }   // ❌ error: destructors may not have parameters
```

**2. 拷贝构造的参数必须是 `const 类名 &`**

```cpp
Enemy(Enemy other) { }              // ❌ 无限递归，编译错误
Enemy(const Enemy &other) { }       // ✅
```

**3. `operator<<` 必须 `return os`**

**不写也能编译**（只有警告），**但运行时崩溃**。这是本课最容易忽略的一条。

**4. `operator<<` 写在类外面**

**别写成成员函数**，否则 `cout << p` 用不了。

### 自测边界

| 试什么 | 期望 |
|---|---|
| `{}` 里的对象 | `[析构]` 在 `}` 那行打印 |
| `Enemy c = b;` | 出现 `[拷贝构造]` |
| `&b` 和 `&c` | **两个不同的地址** |
| `cout << b << " 和 " << c` | 一行完整输出，不是只打出第一个 |
| 删掉 `return os;` | **编译只有警告，运行崩溃** |
| 三个对象依次建 | 析构顺序是**倒过来**的 |

### 进阶（可选）

在 `main` 里再加一句：

```cpp
Enemy d = b;      // 和 Enemy c = b 一样，都是拷贝构造
```

**验证 `=` 初始化和括号初始化都会调拷贝构造**，`[拷贝构造]` 会再打印一次。

---

## 练习 13：继承与多态

文件：`cpp-learning\practice13.cpp`

```
=== 1. 继承 ===
Dragon 的 hp = 200

=== 2. 虚函数 ===
普通敌人受 10 伤：10
Boss 受 10 伤：5

=== 3. 一次性打全体 ===
Orc(hp=10)
Dragon(hp=185)

=== 4. 通过基类引用 ===
ref.damage_taken(10) = 5
```

### 七条要求

1. 写 `class Enemy`（基类），含 `name`、`hp`，getter，和 **`virtual int damage_taken(int dmg) const`**（返回 `dmg`）
2. `Enemy` 必须有 **`virtual ~Enemy() = default;`**
3. 写 `class Boss : public Enemy`，额外有 `armor`
4. `Boss` 的构造函数用 `: Enemy(n, h), armor(a)` 调用基类构造
5. `Boss` 用 **`override`** 改写 `damage_taken`：返回 `dmg - armor`，**小于 0 时返回 0**
6. 重载 `operator<<`（参数是 `const Enemy &`），输出 `name(hp=N)`
7. 在 `main` 里演示四段：
   - 继承：`Boss` 对象调用继承来的 getter
   - 虚函数：普通敌人受 10 伤 = 10，Boss 受 10 伤 = 5
   - **多态**：`vector<unique_ptr<Enemy>>` 装 Orc 和 Dragon，遍历打 20 伤，输出各自剩余血量
   - 通过 `const Enemy &ref = boss;` 调用，确认返回 **5 而不是 10**

### 提示

```cpp
class Enemy
{
protected:
    std::string name;
    int hp;
public:
    Enemy(std::string n, int h) : name(n), hp(h) {}
    virtual ~Enemy() = default;
    std::string get_name() const { return name; }
    int get_hp() const { return hp; }
    virtual int damage_taken(int dmg) const { return dmg; }
};

class Boss : public Enemy
{
private:
    int armor;
public:
    Boss(std::string n, int h, int a) : Enemy(n, h), armor(a) {}
    int damage_taken(int dmg) const override
    {
        int r = dmg - armor;
        return r < 0 ? 0 : r;
    }
};
```

**容器写法：**

```cpp
std::vector<std::unique_ptr<Enemy>> enemies;
enemies.push_back(std::make_unique<Enemy>("Orc", 30));
enemies.push_back(std::make_unique<Boss>("Dragon", 200, 5));
for (const auto &e : enemies) { e->damage_taken(20); }
```

### 危险点

**1. 漏掉 `virtual`**

```cpp
int damage_taken(int dmg) const { return dmg; }        // ❌ 没 virtual
```
**结果：`Enemy &ref = boss; ref.damage_taken(10)` 返回 10，不是 5。编译不报错，行为悄悄错了。**

**2. `override` 签名必须和基类完全一致**

```cpp
int damage_taken(int dmg) override { }      // ❌ 漏了 const
// error: marked 'override', but does not override
```

**3. 派生类不能直接初始化基类的 private 成员**

```cpp
Boss(int h) : hp(h) {}          // ❌ 'hp' is private
Boss(int h) : Enemy(h) {}       // ✅
```

**4. 析构必须 `virtual`**

**否则 `delete` 一个 `Enemy*` 指向的 `Boss` 时，只调 `~Enemy()`，`Boss` 自己的析构不执行。**

### 自测边界

| 试什么 | 期望 |
|---|---|
| `Enemy e{...}; Boss b{...};` 都调 `damage_taken(10)` | 分别返回 10 和 5 |
| `const Enemy &ref = boss; ref.damage_taken(10);` | 返回 **5** |
| 去掉基类的 `virtual` | **同一行返回 10**（编译不报错） |
| `Boss` 的 `override` 漏写 `const` | **编译错误** |
| `enemies` 遍历 | Orc 和 Dragon 掉血数不同 |
| `boss.damage_taken(3)`（伤害 < 护甲） | 返回 **0**，不是负数 |

### 进阶（可选）

再加一个派生类 `Elite : public Enemy`，改写 `damage_taken` 为「只受一半伤害」（`dmg / 2`）。

**然后把它也 `push_back` 进同一个 `vector`**，遍历时三种敌人各自按自己的规则掉血——**同样是 `e->damage_taken(20)`，三种结果。**

---

## 练习 14：模板与 lambda

文件：`cpp-learning\practice14.cpp`

```
=== 1. 模板函数 ===
max_of(3, 7) = 7
max_of(2.5, 1.5) = 2.5
max_of(apple, pear) = pear

=== 2. lambda ===
square(6) = 36
add(3, 4) = 7

=== 3. 按 hp 排序 ===
排序前：
  Orc(hp=30)
  Dragon(hp=200)
  Goblin(hp=15)
排序后：
  Goblin(hp=15)
  Orc(hp=30)
  Dragon(hp=200)
```

### 六条要求

1. 写函数模板 `template <typename T> T max_of(T a, T b)`，返回较大者
2. 用 `int`、`double`、`std::string` 三种类型各调用一次 `max_of`
3. 写一个 lambda `square`，求一个 `int` 的平方，调用并打印 `square(6)`
4. 写一个 lambda `add`，两个 `int` 相加，调用并打印 `add(3, 4)`
5. 用 `class Enemy`（含 `name`、`hp`、getter、`virtual ~Enemy() = default`）和 `class Boss : public Enemy`
6. 用 `vector<unique_ptr<Enemy>>` 装 Orc(30)、Dragon(200)、Goblin(15)，用 **`std::sort` + lambda** 按 `hp` 从小到大排序，排序前后各打印一次

### 提示

```cpp
#include <algorithm>   // std::sort

template <typename T>
T max_of(T a, T b) { return a > b ? a : b; }

auto square = [](int x) { return x * x; };

std::sort(enemies.begin(), enemies.end(),
          [](const std::unique_ptr<Enemy> &a, const std::unique_ptr<Enemy> &b)
          {
              return a->get_hp() < b->get_hp();
          });
```

**用 `std::string` 调 `max_of` 时**，两个参数都是 `std::string` 才能推导成功：

```cpp
max_of(std::string("apple"), std::string("pear"));
```

### 危险点

**1. 比较器必须用 `<`，不能用 `<=`**

```cpp
return a->get_hp() < b->get_hp();       // ✅
return a->get_hp() <= b->get_hp();      // ❌ 小数据不报错，大数据崩溃
```

**实测：2000 个元素的 `vector<int>` 用 `<=` 排序 → 崩溃（`0xC0000374` 堆损坏）。**

**2. lambda 结尾要分号**

```cpp
auto f = [](int x) { return x * x; }     // ❌ 少分号
// error: expected ',' or ';' before 'std'
```

**3. `max_of` 两个参数类型必须一致**

```cpp
max_of(1, 2.5);      // ❌ no matching function
max_of<double>(1, 2.5);   // ✅
```

**4. `std::sort` 需要 `#include <algorithm>`**

**5. 排序 lambda 里用 `->` 不用 `.`**

`a` 是 `unique_ptr<Enemy>`，所以是 `a->get_hp()`。

### 自测边界

| 试什么 | 期望 |
|---|---|
| `max_of(3, 7)` | 7 |
| `max_of(2.5, 1.5)` | 2.5 |
| `max_of("apple","pear")` | pear |
| `square(6)` | 36 |
| 排序前打印 | Orc、Dragon、Goblin（插入顺序） |
| 排序后打印 | **Goblin、Orc、Dragon**（按 hp） |
| 比较器改成 `<=` | 三个元素时可能正常，**数据量大时才崩** |

### 进阶（可选）

把排序改成**按名字**排（`a->get_name() < b->get_name()`），观察结果不同。

**然后写第二个 lambda `desc`，把排序改成从大到小**（`a->get_hp() > b->get_hp()`），验证能否正确倒序。

---

## 练习 14b：背包统计

文件：`cpp-learning\practice14b.cpp`

```
=== 1. map 统计 ===
  bow : 1
  potion : 1
  shield : 2
  sword : 3

=== 2. 查找 ===
  sword 出现了 3 次
  axe 不存在

=== 3. operator[] 的陷阱 ===
  查 axe 之前 size = 4
  查 axe 之后 size = 5   <- 被插入了
  erase 之后 size = 4

=== 4. unordered_map 验证 ===
  u["sword"] = 3
  u.count("sword") = 1   <- count 问的是"有几个键"，不是"计数值"
```

### 五条要求

1. 用 `std::map<std::string, int>` 统计 `{"sword","shield","sword","potion","sword","shield","bow"}` 的词频
2. 用 **`find`** 查 `"sword"`，存在则打印次数；用 **`find`** 查 `"axe"`，不存在则打印「不存在」
3. 演示 **`operator[]` 的副作用**：查 `"axe"` 之前和之后各打印一次 `size()`，证明多了条目；然后 `erase` 掉，再打印 `size()`
4. 用 `std::unordered_map` 重新统计一遍，打印 `u["sword"]`（应为 3）和 `u.count("sword")`（应为 1）
5. 用 `const auto &[key, value]` 遍历打印 map 的内容

### 提示

```cpp
#include <map>
#include <unordered_map>

std::map<std::string, int> m;
for (const auto &w : words) ++m[w];

auto it = m.find("sword");
if (it != m.end()) std::cout << it->second;

if (m.count("axe") == 0) std::cout << "不存在";

for (const auto &[k, v] : m) std::cout << k << " : " << v << '\n';
```

### 危险点

**1. `operator[]` 查不存在的键会插入**

```cpp
int n = m["axe"];        // ⚠️ 插入了一个 0，size() 变大
```

**只想查询就用 `find` 或 `count`。**

**2. `find` 之后必须比较 `end()`**

```cpp
auto it = m.find("axe");
it->second;              // ❌ 没找到时是 end()，解引用未定义行为
if (it != m.end()) { it->second; }    // ✅
```

**3. `map` 和 `unordered_map` 需要不同的头文件**

```cpp
#include <map>
#include <unordered_map>
```

### 自测边界

| 试什么 | 期望 |
|---|---|
| 统计结果 | `sword:3, shield:2, bow:1, potion:1` |
| map 遍历顺序 | **按字母序**（bow, potion, shield, sword） |
| `find("axe")` | 返回 `end()`，不插入 |
| 查 `m["axe"]` 后 `size()` | **从 4 变成 5** |
| `erase("axe")` 后 `size()` | 回到 4 |
| `u["sword"]` | **3**（统计值） |
| `u.count("sword")` | **1**（表示"存在一个 sword 键"，不是次数） |

### 进阶（可选）

把统计用的容器换成 `std::vector<std::pair<std::string, int>>`，**手动实现“查找已有条目”**：

```cpp
for (auto &p : vec)
{
    if (p.first == w) { ++p.second; found = true; break; }
}
```

**你会发现代码变长了很多，而且每次查找都要遍历整条列表。** 这就是 `map` 存在的理由。

---

## 练习 15：拆成三个文件

新建目录：`cpp-learning\practice15\`，内含 **三个文件**：

```
practice15/
├── enemy.h
├── enemy.cpp
└── main.cpp
```

```
名字：Orc
血量：40
受到 15 伤害后：25
受到 100 伤害后：0
状态：已倒下
```

### 七条要求

1. `enemy.h` 第一行写 **`#pragma once`**
2. `enemy.h` 里定义 `class Enemy`，private 有 `name`（`std::string`）、`hp`（`int`）
3. `enemy.h` 里只写**函数声明**（不写函数体）：

   ```cpp
   Enemy(std::string n, int h);
   std::string get_name() const;
   int get_hp() const;
   void take_damage(int dmg);
   bool is_alive() const;
   ```

4. `enemy.cpp` **第一行** `#include "enemy.h"`，然后写所有函数的**实现**，每个都带 `Enemy::`
5. `take_damage` 把血量扣到 **0 为止**（不为负）
6. `main.cpp` 里 `#include "enemy.h"`，创建 `Enemy{"Orc", 40}`，按示例输出四段
7. 用下面的命令**一次编译两个 `.cpp`**（`.h` 不列）：

   ```
   g++ -std=c++17 -Wall -Wextra -o app.exe main.cpp enemy.cpp
   ```

### 提示

```cpp
// enemy.h
#pragma once
#include <string>

class Enemy
{
private:
    std::string name;
    int hp;

public:
    Enemy(std::string n, int h);
    int get_hp() const;
    void take_damage(int dmg);
};
```

```cpp
// enemy.cpp
#include "enemy.h"

Enemy::Enemy(std::string n, int h) : name(n), hp(h) {}

int Enemy::get_hp() const { return hp; }

void Enemy::take_damage(int dmg)
{
    hp -= dmg;
    if (hp < 0) hp = 0;
}
```

**注意 `.cpp` 里的 `Enemy::`——每个函数前面都要有。**

### 危险点

**1. `.cpp` 里忘了 `Enemy::`**

```cpp
int get_hp() const { return hp; }      // ❌
// error: non-member function 'int get_hp()' cannot have cv-qualifier
```

**看到 `cv-qualifier` 就查：是不是漏了 `类名::`。**

**2. 忘了 `#pragma once`**

同一份头文件被包含两次时：
```
error: redefinition of 'class Enemy'
```

**3. 编译时漏了 `enemy.cpp`**

编译能过，但**链接**失败：
```
undefined reference to `Enemy::Enemy(std::string, int)'
```

**`undefined reference` 是链接错误——说明某个 `.cpp` 没参与编译。**

**4. `.h` 里写了函数体**

```cpp
int get_hp() const { return hp; }    // ❌ 写在 .h 里
```

**如果两个 `.cpp` 都包含它，就是重复定义。修复方式要么把实现挪到 `.cpp`，要么加 `inline`。**

### 自测边界

| 试什么 | 期望 |
|---|---|
| 编译三个文件 | `g++ -std=c++17 -Wall -Wextra -o app.exe main.cpp enemy.cpp` 零警告 |
| 运行 | 四条输出与示例一致 |
| 受伤 100 后血量 | **0**，不是 -60 |
| 去掉 `#pragma once` 并让 `main.cpp` 两次 include | **`redefinition of 'class Enemy'`** |
| 编译时只给 `main.cpp` | **`undefined reference`** |
| `enemy.cpp` 里漏 `Enemy::` | **编译错误** |

### 进阶（可选）

再加第四个文件 `enemy_util.h`（只含一个函数声明 `int damage_roll(int min, int max);`），在 `main.cpp` 里包含它，**故意让它和 `enemy.h` 互相包含**，验证 `#pragma once` 能否挡住无限展开。

---

## 练习 16：敌人计数器

文件：`cpp-learning\practice16.cpp`

```
=== 1. 初始状态 ===
当前敌人数 = 0

=== 2. 创建三个 ===
创建 Orc，当前共 1 个
创建 Goblin，当前共 2 个
创建 Dragon，当前共 3 个
此时 count() = 3
销毁 Dragon，当前共 2 个

=== 3. 销毁一个 ===
销毁 Goblin，当前共 1 个
销毁 Orc，当前共 0 个

=== 4. 再创建一个 ===
创建 Slime，当前共 1 个
Slime 的名字是 Slime
Enemy::count() = 1   <- 所有对象共享
销毁 Slime，当前共 0 个
```

> 第 3 段的输出取决于你的 `{}` 嵌套方式。**关键是：Dragon 先销毁（内层作用域），剩 2 个；离开大括号时 Goblin、Orc 逆序销毁，回到 0。**

### 六条要求

1. `class Enemy`，private 有 `name`、`hp`，还有 **`static int total;`**
2. 构造函数和析构函数里分别 `++total` / `--total`，并打印当前总数
3. 写 **`static int count()`**，返回 `total`
4. **在类外定义** `int Enemy::total = 0;`
5. `main` 里用 `{}` 控制作用域，演示创建 3 个、销毁 1 个后的数量变化
6. 演示两件事：
   - `Enemy::count()` 用**类名**调用（不用对象）
   - 打印某个对象的 `get_name()`，对比「对象自己的」vs「共享的」

### 提示

```cpp
class Enemy
{
private:
    std::string name;
    int hp;
    static int total;                 // 声明

public:
    Enemy(std::string n, int h) : name(n), hp(h)
    {
        ++total;
        std::cout << "创建 " << name << "，当前共 " << total << " 个\n";
    }
    ~Enemy()
    {
        --total;
        std::cout << "销毁 " << name << "，当前共 " << total << " 个\n";
    }
    std::string get_name() const { return name; }
    static int count() { return total; }
};

int Enemy::total = 0;                 // 定义，必须有
```

**用 `{}` 控制生命周期：**

```cpp
{
    Enemy a{"Orc", 30};
    Enemy b{"Goblin", 15};
    {
        Enemy c{"Dragon", 200};       // 内层作用域，离开时销毁
    }
    // 这里 Dragon 已销毁，剩 2 个
}
```

### 危险点

**1. 忘了类外定义**

```cpp
class Enemy { static int total; };
// 少了 int Enemy::total = 0;
```
```
undefined reference to `Enemy::total'
```

**编译能过，链接失败。**

**2. 静态函数里访问普通成员**

```cpp
static int count() { return name.size(); }    // ❌
```
```
error: invalid use of member 'Enemy::name' in static member function
```

**静态函数没有 `this`，不知道是哪个对象的 `name`。**

**3. 用类名调非静态函数**

```cpp
Enemy::get_name();     // ❌
```
```
error: cannot call member function '...' without object
```

**4. `count` 和普通成员重名**

**如果类里既有一个 `int count;` 又有 `static int count()`，编译器会报错。** 起名时避开。

### 自测边界

| 试什么 | 期望 |
|---|---|
| 程序开始 | `Enemy::count() = 0` |
| 创建 3 个 | 每次打印的数字递增 1、2、3 |
| 内层 `{}` 结束 | 打印「销毁 Dragon」，总数回到 2 |
| 全部 `{}` 结束 | 总数回到 0 |
| `Enemy::count()` | **不用对象就能调** |
| 删掉 `int Enemy::total = 0;` | **`undefined reference`** |
| `static count()` 里访问 `name` | **编译错误** |

### 进阶（可选）

给 `Enemy` 加一个**静态成员函数** `static void reset_total()`，在 `main` 结束后手动清零，观察能否影响还在作用域里的对象计数。

**注意：这会让计数和真实对象数量不一致。** 想想为什么「静态成员变量最好只由构造函数和析构函数管理」。

---

## 练习 17：拷贝 vs 移动

文件：`cpp-learning\practice17.cpp`

```
=== 1. 左值：拷贝 ===
[构造] Orc
[拷贝构造] Orc
a="Orc"  b="Orc"

=== 2. 右值：移动 ===
[移动构造] Dragon          ← 用 std::move 才能稳定触发

=== 3. std::move 之后 ===
move 前 d.name="Dragon"
[移动构造] Dragon
e.name="Dragon"
d.name=""        <- 被搬空
d.hp=200         <- int 是复制的

=== 4. push_back 的区别 ===
左值：
[拷贝构造] Slime
临时对象：
[构造] Bat
[移动构造] Bat
```

### 八条要求

1. `class Enemy`，private 有 `name`（`std::string`）、`hp`（`int`）
2. **四个**特殊函数都写出来，每个都打印自己的名字：
   - `Enemy(const Enemy &other)` → 打印 `[拷贝构造]`
   - `Enemy(Enemy &&other)` → 打印 `[移动构造]`，用 `std::move(other.name)`
   - `Enemy &operator=(const Enemy &other)` → 打印 `[拷贝赋值]`
   - `Enemy &operator=(Enemy &&other)` → 打印 `[移动赋值]`
3. 加 `~Enemy()`，打印 `[析构]`
4. 演示 **左值 → 拷贝构造**（`Enemy b = a;`）
5. 演示 **`std::move` → 移动构造**：`Enemy c = std::move(b);`

   > **注意**：直接写 `Enemy c = Enemy{...};` 可能**不打印移动构造**——C++17 的**复制消除**会直接就地构造，连移动都省了。所以第 2 段用 `std::move` 才能稳定触发移动。
6. 演示 **`std::move` 前后**：打印 `d.name`、`e.name`、`d.name`（应为空）、`d.hp`（不变）
7. 演示 **`push_back`**：先传左值（拷贝），再传临时对象（移动）
8. 演示 **拷贝赋值 vs 移动赋值**（`h = g;` 和 `h = Enemy{...};`）

### 提示

```cpp
#include <utility>      // std::move

Enemy(Enemy &&other) : name(std::move(other.name)), hp(other.hp)
{
    std::cout << "[移动构造] " << name << '\n';
}

Enemy &operator=(const Enemy &other)
{
    name = other.name;
    hp = other.hp;
    std::cout << "[拷贝赋值] " << name << '\n';
    return *this;
}
```

**`operator=` 必须返回 `*this`**——否则 `a = b = c` 这种链式赋值会断。

### 危险点

**1. 移动构造的参数是 `Enemy &&`，不是 `const Enemy &`**

```cpp
Enemy(Enemy &&other)          // ✅ 右值引用
Enemy(const Enemy &&other)    // ⚠️ const 右值引用，通常不是你想要的
```

**加 `const` 之后就没法 `std::move(other.name)`** 了（`const` 阻止移动），移动构造会退化成拷贝。

**2. `std::move` 之后原对象不能假设还有值**

```cpp
Enemy d{"Dragon", 200};
Enemy e = std::move(d);
d.get_name();      // ⚠️ 返回空字符串，不是 "Dragon"
```

**`d` 仍然“有效”（能析构、能重新赋值），但内容已被搬走。**

**3. `int` 不要 `std::move`**

```cpp
hp(std::move(other.hp))    // ❌ 没意义，int 没有"移动"这回事
hp(other.hp)               // ✅
```

**4. `operator=` 忘了 `return *this`**

**编译器可能不报错（因为你要么用返回值，要么不用），但链式赋值会出错。**

**5. 只写了拷贝构造，没写移动构造**

**编译器就不会自动生成移动构造。** 结果：`std::move` 也会走拷贝（因为它能绑到 `const Enemy &`）。

**这正好是「Rule of Three」存在的原因——三个（五个）要么都写，要么都不写。**

### 自测边界

| 试什么 | 期望 |
|---|---|
| `Enemy b = a;`（a 是左值） | 打印 **`[拷贝构造]`** |
| `Enemy c = Enemy{...};`（右值） | 打印 **`[移动构造]`** |
| `Enemy e = std::move(d);` | 打印 `[移动构造]`，之后 `d.name` 是 **`""`** |
| `d.hp` 在 move 之后 | **不变**（int 是复制的） |
| `v.push_back(f)`（f 是左值） | 打印 `[拷贝构造]` |
| `v.push_back(Enemy{...})` | 打印 `[移动构造]` |
| `h = g;` | 打印 `[拷贝赋值]` |
| `h = Enemy{...};` | 打印 `[移动赋值]` |
| 删掉移动构造 | **`std::move` 也会走拷贝构造** |

### 进阶（可选）

写一个 `Enemy make_enemy()` 函数，`return Enemy{"Boss", 100};`，然后：

```cpp
Enemy x = make_enemy();
```

**观察打印了哪些构造。** C++17 起有「返回值优化」，可能什么都不打印——**这说明编译器直接在你需要的地方构造，连移动都省了。**

---

## 练习 18：UB 清单与防线

文件：`cpp-learning\practice18.cpp`

```
=== 1. 越界访问 ===
v.size() = 3
v[2] = 30  <- 合法
v[3] 危险：operator[] 不检查
at(3) 会抛异常

=== 2. 未初始化变量 ===
已初始化: y = 0
未初始化: x 的值不能依赖

=== 3. 悬垂指针 ===
*p = 42  <- local 活着时
作用域结束后 p 悬垂，不解引用

=== 4. 空指针 ===
p 是空指针，跳过

=== 5. assert ===
assert(hp >= 0) 通过

=== 6. 防线总结 ===
越界 -> 先检查或用 at()
未初始化 -> 一律给初值
悬垂 -> 不返回局部地址，用 unique_ptr
空指针 -> 解引用前判空
```

### 七条要求

1. 用 `std::vector<int>{10, 20, 30}` 演示：打印 `size()`、合法下标的读取、**说明 `v[3]` 是 UB**、说明 `at()` 会抛异常
2. 演示未初始化变量：写一个 `int x;` 和 `int y = 0;`，**只读取 `y`**，并注释说明为什么不读 `x`
3. 演示悬垂指针：在**内层作用域**取局部变量地址，打印一次，离开作用域后**不**解引用，并说明原因
4. 演示空指针：`int *p = nullptr;`，**用 `if` 判空后**才解引用
5. 用 `#include <cassert>` + `assert(hp >= 0)` 演示一次通过的断言
6. 写一段**安全检查函数**（见提示），对越界下标返回失败而不崩
7. 最后输出「防线总结」四行

### 提示

**安全检查函数：**

```cpp
bool safe_get(const std::vector<int> &v, int idx, int &out)
{
    if (idx < 0 || idx >= static_cast<int>(v.size()))
        return false;
    out = v[idx];
    return true;
}
```

**用 `int &out` 把结果传出——这是第 5、8 课学的引用参数。**

**`static_cast<int>(v.size())`** 是因为 `size()` 返回 `size_t`（无符号），和 `int` 比较会报警告（第 6 课讲过）。

### 危险点

**1. 不要真的去触发 UB**

**本作业要求你“说明”越界和悬垂是 UB，不是让你去读 `v[3]` 或解引用悬垂指针。** 真触发会崩溃——那学不到东西。

**2. 未初始化变量只声明、不读取**

```cpp
int x;                             // 可以声明
// std::cout << x;                 // ❌ 不要读
```

**3. `assert` 不要用来检查用户输入**

```cpp
assert(input > 0);      // ❌ 用户输错不该崩
if (input <= 0) { ... } // ✅
```

**4. 判空之后才能解引用**

```cpp
int *p = nullptr;
if (p != nullptr) { std::cout << *p; }   // ✅
```

### 自测边界

| 试什么 | 期望 |
|---|---|
| 程序运行 | **全程不崩溃，退出码 0** |
| `v[2]` | 打印 30 |
| `v[3]` | **只出现在注释或文字里，不真的执行** |
| 悬垂指针那段 | 打印 `*p = 42` 后，**不再解引用** |
| 空指针 | **走 else 分支**，不崩 |
| `assert(hp >= 0)` | 通过，程序继续 |
| `safe_get(v, 5, out)` | 返回 `false`，不崩 |
| 编译 | **零警告**（未初始化那段用 `(void)x;` 或注释规避） |

### 进阶（可选）

把 `assert` 换成「失败就打印并 return」的检查：

```cpp
if (hp < 0)
{
    std::cerr << "内部错误：hp 为负\n";
    return 1;
}
```

**想想什么时候该用 `assert`（bug），什么时候该用运行时检查（可恢复的错误）。**

---

## 练习 19：结课项目 —— 回合制战斗

目录：`cpp-learning\final\`

### 文件结构（必须）

```
final/
├── character.h      character.cpp      ← 基类
├── player.h         player.cpp         ← 玩家（含背包）
├── enemy.h          enemy.cpp          ← 敌人（Orc / Boss / Elite）
├── battle.h         battle.cpp         ← 战斗流程
└── main.cpp                            ← 只做输入输出
```

**编译：**

```
g++ -std=c++17 -Wall -Wextra -o app.exe main.cpp character.cpp player.cpp enemy.cpp battle.cpp
```

### 示例运行

```
==============================
        RPG 战斗演示
==============================
请输入你的名字：Hero
请输入血量（1-200）：100

=== 你的角色 ===
Hero  HP 100/100  ATK 15
背包：药水 x3  炸弹 x1

==============================
 第 1 回合
==============================
敌人：Orc(hp=40/40)  EliteGoblin(hp=30/30) [精英]  Dragon(hp=200/200) [Boss]

请选择动作：
  1. 攻击
  2. 防御
  3. 用药水
  4. 逃跑
> 1

请选择目标：
  1. Orc(hp=40/40)
  2. EliteGoblin(hp=30/30)
  3. Dragon(hp=200/200)
> 1

Hero 攻击 Orc，造成 15 伤害！
Orc 剩余 25 血。

Orc 反击 Hero，造成 8 伤害！
EliteGoblin 反击 Hero，造成 10 伤害！
Dragon 反击 Hero，造成 15 伤害！
Hero 剩余 67 血。
```

### 类设计

**`character.h` — 基类**

```cpp
class Character
{
protected:
    std::string name;
    int hp;
    int max_hp;
    int atk;

public:
    Character(std::string n, int h, int a);
    virtual ~Character() = default;

    std::string get_name() const;
    int get_hp() const;
    int get_max_hp() const;
    int get_atk() const;
    bool is_alive() const;
    void take_damage(int dmg);        // hp 不为负

    virtual int defense() const { return 0; }
    virtual std::string type_name() const { return "角色"; }
};

std::ostream &operator<<(std::ostream &os, const Character &c);
```

**`player.h`**

```cpp
class Player : public Character
{
private:
    std::map<std::string, int> bag_;
    bool defending_;

public:
    Player(std::string n, int h);
    void add_item(const std::string &item, int count);
    bool use_item(const std::string &item);
    int item_count(const std::string &item) const;
    void set_defending(bool d);
    int defense() const override;      // 防御时 5
    void print_bag() const;
};
```

**`enemy.h`**

```cpp
class Enemy : public Character { ... };           // 普通
class Boss : public Enemy { int armor_; ... };    // 护甲
class Elite : public Enemy { ... };               // 精英
```

**`battle.h`**

```cpp
enum class Action { Attack, Defend, Item, Flee, Unknown };

class Battle
{
private:
    Player &player_;
    std::vector<std::unique_ptr<Enemy>> enemies_;
    int round_;

public:
    Battle(Player &p);
    void add_enemy(std::unique_ptr<Enemy> e);
    bool all_dead() const;
    bool run_round(std::istream &in, std::ostream &out);
    int round() const;
};
```

### 游戏规则

| 项 | 规则 |
|---|---|
| 玩家初始 | HP 100，ATK 15，药水 3，炸弹 1 |
| Orc | 40 HP，8 ATK |
| EliteGoblin | 30 HP，10 ATK |
| Boss Dragon | 200 HP，20 ATK，护甲 5 |
| 攻击伤害 | `atk - 目标defense()`，**最小 1** |
| 防御 | 本回合受伤减 5 |
| 药水 | 回复 30（不超过 max_hp） |
| 逃跑 | 立即结束（算失败） |
| 胜利 | 所有敌人死亡 |
| 失败 | 玩家死亡 |

### 十二条要求

1. 至少 4 个 `.h` + 4 个 `.cpp`
2. 每个 `.h` 有 `#pragma once`
3. 基类有 **`virtual ~Character() = default;`**
4. 至少 **2 个派生类**
5. 用 **`std::vector<std::unique_ptr<Enemy>>`** 装敌人
6. 背包用 **`std::map<std::string, int>`**
7. 动作用 **`enum class` + `switch`**
8. 玩家输入用 **`cin` + `cin.fail()` 检查**
9. 血量**永不为负**
10. **零 UB**（不越界、不空指针解引用）
11. **≥200 行**（不含空行和注释）
12. 编译 **零警告**

### 危险点

**1. 头文件互相包含**

`battle.h` 需要 `player.h` 和 `enemy.h`。**都在 `.h` 里 `#include`，不要靠 `.cpp` 传递。**

**2. 循环里删除元素**

```cpp
for (auto &e : enemies_)
{
    if (!e->is_alive()) enemies_.erase(...);   // ❌ 迭代器失效（UB）
}
```

**正确做法：用 `std::remove_if` + `erase`，或者先收集再删。**

**3. `operator<<` 里写死 `std::cout`**

**必须用参数 `os`。** 这个坑我们从第 12 课说过。

**4. 敌人死亡后还会反击**

**需要检查 `is_alive()` 再让它攻击。**

**5. `vector` 扩容时 `unique_ptr` 移动**

**`unique_ptr` 是 move-only，`vector` 扩容会自动移动——没问题。但如果用 `Player` 对象直接存，要注意拷贝成本。**

### 自测边界

| 试什么 | 期望 |
|---|---|
| 运行 | 能完整玩一局到胜利或失败 |
| 血量受重击 | **归 0，不为负** |
| 输入 `abc` | **报错退出，不崩溃** |
| 输入 `9`（无效动作） | **提示无效，重新选择** |
| 已死亡的敌人 | **不再反击、不再出现在目标列表** |
| 药水用完后再用 | **提示没有药水** |
| 逃跑 | **立即结束战斗** |
| 行数 | `find /c /v ""` 或数一下，**≥200** |
| 编译 | **零警告** |

### 进阶（可选，做了加分）

1. **炸弹**：对**所有敌人**造成 15 伤害
2. **存档**：用 `std::ofstream` 把玩家状态写到 `save.txt`，下次启动自动读
3. **更聪明的 AI**：Boss 血量低于 30% 时攻击力翻倍
4. **`std::array`**：把三个敌人放进 `std::array<std::unique_ptr<Enemy>, 3>`

### 提交前自查

- [ ] 12 条要求逐条打勾
- [ ] 玩一遍完整流程
- [ ] 故意输错几次输入，程序不崩
- [ ] 零警告编译

**这个项目预计 3–6 小时。** 不用一次写完——先让程序能跑起来（哪怕只有"攻击"一个动作），再逐步加功能。
