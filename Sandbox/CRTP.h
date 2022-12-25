#pragma once
#include <iostream>

template<typename DerivedT>
class Base
{
public:

    void f()
    {
        static_cast<DerivedT*>(this)->foo();
    }
};

class Derived : public Base<Derived>
{
public:

    void foo()
    {
        std::cout << "Derived" << std::endl;
    }
};
