// enemy.h
#pragma once

#include <string>
#include "character.h"

class Enemy : public Character// 普通
{
public:
    Enemy(std::string n, int h, int a) : Character(n, h, a) {}
    std::string type_name() const override { return "Enemy"; }
}; 


class Boss : public Enemy
{
private:
    int armor_;// 护甲
public:
    Boss(std::string n, int h, int a, int armor): Enemy(n,h,a), armor_(armor) {}
    int defense() const override{return armor_;}
    std::string type_name() const override{return "Boss";}
}; 

class Elite : public Enemy 
{
    Elite(std::string n, int h, int a):Enemy(n,h,a){}
    std::string type_name() const override{return "Elite";}
};               // 精英