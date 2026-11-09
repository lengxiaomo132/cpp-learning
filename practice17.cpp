// practice17.cpp

#include <iostream>
#include <string>
#include <utility> // std::move
#include <vector>

class Enemy
{
private:
    std::string name;
    int hp;

public:
    Enemy(std::string n, int h) : name(n), hp(h) { std::cout << "[构造] " << name << '\n'; }
    ~Enemy() { std::cout << "[析构] " << name << '\n'; }

    Enemy(const Enemy &other) : name(other.name), hp(other.hp) // 负责拷贝一个已有名字的对象来创建一个新的对象
    {
        std::cout << "[拷贝构造] " << name << '\n';
    }

    Enemy(Enemy &&other) : name(std::move(other.name)), hp(other.hp) // 负责移动一个右值(且只允许右值输入)来创建一个新的对象,如果单独存在会隐式删除拷贝构造,此时不写拷贝构造在输入左值时会报错,编译失败
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

    Enemy &operator=(Enemy &&other)
    {
        name = std::move(other.name);
        hp = other.hp;
        std::cout << "[移动赋值] " << name << '\n';
        return *this;
    }

    const std::string &get_name() const { return name; }
    int get_hp() const { return hp; }
};

int main()
{
    {
        std::cout << "\n=== 1. 左值：拷贝 ===\n";
        Enemy a{"Orc", 10};
        Enemy b = a;
        std::cout << "a=\"" << a.get_name() << '\"' << "  b=\"" << b.get_name() << '\"' << '\n';
    }
    {
        std::cout << "\n=== 2. 右值：移动 ===\n";
        Enemy d = std::move(Enemy{"Dragon", 200});
        std::cout << "临时变量先构造,在被移动构造给c,最后name为 \"\" 的临时变量结束生命周期析构\n";
    
    
        std::cout << "\n=== 3. std::move 之后 ===\n";
        std::cout << "move 前 d.name=\"" << d.get_name() << '\"' << '\n';
        Enemy e = std::move(d);
        std::cout << "e.name=\"" << e.get_name() << '\"' << '\n';
        std::cout << "d.name=\"" << d.get_name() << '\"' << "        <- 被搬空" << '\n';
        std::cout << "d.hp=\"" << d.get_hp() << '\"' << "         <- int 是复制的" << '\n';
    }
    {
        std::cout << "\n=== 4. push_back 的区别 ===\n";
        std::vector<Enemy> v;
        Enemy s{"Slime", 5};
        std::cout << "左值：\n";
        v.push_back(s);
        std::cout << "临时对象：\n";
        v.push_back(Enemy{"Bat", 5});
    }
    return 0;
}