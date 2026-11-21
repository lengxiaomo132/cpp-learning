// enemy.cpp
#include "enemy.h"

std::ostream &operator<<(std::ostream &os, const Boss &c) // 打印Boss信息“[Boss].name(hp=.hp/.max_hp)”
{
    os << "[Boss]" << c.get_name() << "(hp=" << c.get_hp() << '/' << c.get_max_hp() << ')';
    return os;
};
