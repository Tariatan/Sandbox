#pragma once

#include <list>
#include <memory>

// Common Interface for both Items and Composite Items
class iComponent
{
public:
    virtual unsigned int get() const = 0;
    virtual ~iComponent() = default;
};

// Concrete Item is derived from Component Interface
class Leaf : public iComponent
{
public:
    unsigned int get() const override final
    {
        return 1u;
    }
};

// Composite Item is also derived from Component Interface
class Branch : public iComponent
{
public:
    void addItem(std::shared_ptr<iComponent> item)
    {
        m_items.emplace_back(item);
    }

    unsigned int get() const override final
    {
        unsigned int total = 0u;
        for (const auto& item : m_items)
        {
            total += item->get();
        }

        return total;
    }

private:
    std::list<std::shared_ptr<iComponent>> m_items;
};

class Tree
{
public:
    Tree() : m_CompositeItems(std::make_shared<Branch>()){}

    void pack()
    {
        // Pack Items
        m_CompositeItems->addItem(std::make_shared<Leaf>());
        m_CompositeItems->addItem(std::make_shared<Leaf>());

        // Pack Item of Items
        std::shared_ptr<Branch> ci{ std::make_shared<Branch>() };
        ci->addItem(std::make_shared<Leaf>());
        ci->addItem(std::make_shared<Leaf>());

        m_CompositeItems->addItem(ci);
    }

    unsigned int calculate()
    {
        return m_CompositeItems->get();
    }

private:
    std::shared_ptr<Branch> m_CompositeItems;
};