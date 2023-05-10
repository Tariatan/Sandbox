#pragma once

#include <memory>
#include <iostream>

class VendingMachine;

class iState
{
public:
    using VMPtr = VendingMachine*;

    virtual void insertCoin() = 0;
    virtual void ejectCoin() = 0;
    virtual void trigger() = 0;
    virtual void dispence() = 0;
};

class VendingMachine
{
public:
    using StatePtr = std::shared_ptr<iState>;

    VendingMachine();

    void Start(unsigned int items)  { m_items = items; }
    void setState(StatePtr state)   { m_state = state; }

    StatePtr getHasCoinState()      { return m_HasCoinState; }
    StatePtr getNoCoinState()       { return m_NoCoinState; }
    StatePtr getSellState()         { return m_SellState; }
    StatePtr getEmptyState()        { return m_EmptyState; }

    void insertCoin()               { m_state->insertCoin(); }
    void ejectCoin()                { m_state->ejectCoin(); }
    void trigger()
                                    {
                                        m_state->trigger();
                                        m_state->dispence();
                                    }

    void sell()                     { --m_items; }
    unsigned int getCount() const   { return m_items; }
    void refill(unsigned int items)
                                    {
                                        m_items = items;
                                        m_state = m_NoCoinState;
                                    }

private:
    unsigned int m_items{ 0 };
    StatePtr m_state;
    StatePtr m_HasCoinState;
    StatePtr m_NoCoinState;
    StatePtr m_SellState;
    StatePtr m_EmptyState;
};

class SellState : public iState
{
    VMPtr m_VM;
public:
    SellState(VMPtr vm) : m_VM(vm) {}
    void insertCoin() override
    {
        std::cout << "Item is being sold" << std::endl;
    }
    void ejectCoin() override
    {
        std::cout << "Item is being sold" << std::endl;
    }
    void trigger() override
    {
        std::cout << "Item is being sold" << std::endl;
    }
    void dispence() override
    {
        std::cout << "Selling item" << std::endl;
        m_VM->sell();
        if (m_VM->getCount() > 0)
        {
            m_VM->setState(m_VM->getNoCoinState());
        }
        else
        {
            m_VM->setState(m_VM->getEmptyState());
        }
    }
};
class EmptyState : public iState
{
public:
    void insertCoin() override
    {
        std::cout << "Empty" << std::endl;
    }
    void ejectCoin() override
    {
        std::cout << "Empty" << std::endl;
    }
    void trigger() override
    {
        std::cout << "Empty" << std::endl;
    }
    void dispence() override
    {
        std::cout << "Empty" << std::endl;
    }
};
class NoCoinState : public iState
{
    VMPtr m_VM;
public:
    NoCoinState(VMPtr vm) : m_VM(vm) {}
    void insertCoin() override
    {
        std::cout << "Received Coin" << std::endl;
        m_VM->setState(m_VM->getHasCoinState());
    }
    void ejectCoin() override
    {
        std::cout << "No coin" << std::endl;
    }
    void trigger() override
    {
        std::cout << "No coin" << std::endl;
    }
    void dispence() override
    {
        std::cout << "No coin" << std::endl;
    }
};
class HasCoinState : public iState
{
    VMPtr m_VM;
public:
    HasCoinState(VMPtr vm) : m_VM(vm) {}
    void insertCoin() override
    {
        std::cout << "Already has Coin" << std::endl;
    }
    void ejectCoin() override
    {
        std::cout << "Eject Coin" << std::endl;
        m_VM->setState(m_VM->getNoCoinState());
    }
    void trigger() override
    {
        std::cout << "Sell item" << std::endl;
        m_VM->setState(m_VM->getSellState());
    }
    void dispence() override
    {
        std::cout << "You need to push the trigger" << std::endl;
    }
};

