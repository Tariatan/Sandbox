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

struct ExcClass
{
    virtual void print()
    {
        std::cout << "ExcClass::print" << std::endl;
    }

    ExcClass()
    try : m(new mem())
    {
        std::cout << "ExcClass" << std::endl;
    }
    catch (std::exception & /*e*/)
    {
        throw;
    }

    virtual ~ExcClass() noexcept(false)
    {
        std::cout << "~ExcClass" << std::endl;
        //         throw "error";

        delete m;
    }

    mem* m;
};

struct B : ExcClass
{
    void print() override final
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

