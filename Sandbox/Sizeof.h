#pragma once
#include <string>
#include <iostream>


class I
{
public:
    virtual ~I(){};
    virtual void print() = 0;
};

class A : public I
{
public:
    ~A(){};
    void print() override final {};
};

struct S
{
//     double p{0.0};
    int i{0};
    bool b{0};
//     std::string s{""};
    char c{' '};

    A* a;

    S()
    {
        a = new A();
        std::cout << "struct S" << std::endl;
//         std::cout << "\tdouble p => " << sizeof(p) << std::endl;
        std::cout << "\tint i => " << sizeof(i) << std::endl;
        std::cout << "\tbool b => " << sizeof(b) << std::endl;
//         std::cout << "\tstd::string s => " << sizeof(s) << std::endl;
        std::cout << "\tchar c => " << sizeof(c) << std::endl;
        std::cout << "\tclass A a => " << sizeof(a) << std::endl;
    }
};

void showSizeof()
{
    S s;
    std::cout << sizeof(s) << std::endl;
}
