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

**当前作业：练习 13（已完成）**

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
