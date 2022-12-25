#pragma once
#include <iostream>

struct mem
{
    mem()
    {
        std::cout << "mem" << std::endl;
    }
    virtual ~mem() noexcept(false)
    {
        std::cout << "~mem" << std::endl;
        //         throw "error";
    }
};

struct A
{
    virtual void print()
    {
        std::cout << "A::print" << std::endl;
    }

    A() : m(new mem())
    {
        std::cout << "A" << std::endl;
    }

    virtual ~A() noexcept(false)
    {
        std::cout << "~A" << std::endl;
        //         throw "error";

        delete m;
    }

    mem* m;
};

struct B : A
{
    virtual void print() override final
    {
        std::cout << "B::print" << std::endl;
        throw "error";
    }
    B()
    {
        std::cout << "B" << std::endl;
    }

    ~B() noexcept(false)
    {
        std::cout << "~B" << std::endl;
    }
};

