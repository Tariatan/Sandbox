#pragma once

#include <string>
#include <memory>
#include <iostream>

class iBuilder
{
public:
    virtual std::string buildWall() = 0;
    virtual std::string buildWindow() = 0;
    virtual std::string buildDoor() = 0;
    virtual ~iBuilder() = default;
};

class CottegeBuilder : public iBuilder
{
public:
    std::string buildWall()
    {
        return "cottage wall";
    }

    std::string buildWindow()
    {
        return "cottage window";
    }

    std::string buildDoor()
    {
        return "cottage door";
    }
};

class HutBuilder : public iBuilder
{
public:
    std::string buildWall()
    {
        return "hut wall";
    }

    std::string buildWindow()
    {
        return "hut window";
    }

    std::string buildDoor()
    {
        return "hut door";
    }
};

class Architector
{
public:
    Architector(std::shared_ptr<iBuilder> builder) : m_builder(builder) {}

    void changeBuilder(std::shared_ptr<iBuilder> builder)
    {
        m_builder = builder;
    }

    void buildHouse()
    {
        std::cout << m_builder->buildWall() << " " << m_builder->buildDoor() << " " << m_builder->buildWindow() << std::endl;
    }

private:
    std::shared_ptr<iBuilder> m_builder;
};

class Director
{
public:
    void establishTown()
    {
        Architector a(std::make_shared<HutBuilder>());
        a.buildHouse();

        a.changeBuilder(std::make_shared<CottegeBuilder>());
        a.buildHouse();
        a.buildHouse();
    }
};