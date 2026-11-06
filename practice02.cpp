//practise02.cpp
#include<iostream>

int main(){
    int a,b;
    std::cout<<"请输入第一个数字：";
    std::cin>>a;

    std::cout<<"请输入第二个数字：";
    std::cin>>b;
    std::cout<<"sum = "<<(a+b)<<"\n";
    
    std::cout<<"average = "<<(a+b)/2.0<<"\n";
    
    if (a > b) {
        std::cout << a << " is bigger\n";
    } else if (a < b) {
        std::cout << b << " is bigger\n";
    } else {
        std::cout << a<<" and "<<b<<" are equal\n";
    }
    return 0;
}