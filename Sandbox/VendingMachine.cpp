#include "VendingMachine.h"

VendingMachine::VendingMachine()
    : m_state(std::make_shared<NoCoinState>(this))
    , m_HasCoinState(std::make_shared<HasCoinState>(this))
    , m_NoCoinState(std::make_shared<NoCoinState>(this))
    , m_SellState(std::make_shared<SellState>(this))
    , m_EmptyState()
{

}

void VendingMachine::Start(unsigned int items)
{
    m_items = items;
}
void VendingMachine::setState(StatePtr state)
{
    m_state = state;
}
VendingMachine::StatePtr VendingMachine::getHasCoinState()
{
    return m_HasCoinState;
}
VendingMachine::StatePtr VendingMachine::getNoCoinState()
{
    return m_NoCoinState;
}
VendingMachine::StatePtr VendingMachine::getSellState()
{
    return m_SellState;
}
VendingMachine::StatePtr VendingMachine::getEmptyState()
{
    return m_EmptyState;
}
void VendingMachine::insertCoin()
{
    m_state->insertCoin();
}
void VendingMachine::ejectCoin()
{
    m_state->ejectCoin();
}
void VendingMachine::trigger()
{
    m_state->trigger();
    m_state->dispence();
}
void VendingMachine::sell()
{
    --m_items;
}
unsigned int VendingMachine::getCount() const
{
    return m_items;
}
void VendingMachine::refill(unsigned int items)
{
    m_items = items;
    m_state = m_NoCoinState;
}
