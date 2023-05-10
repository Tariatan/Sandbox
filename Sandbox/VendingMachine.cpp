#include "VendingMachine.h"

VendingMachine::VendingMachine()
    : m_state(std::make_shared<NoCoinState>(this))
    , m_HasCoinState(std::make_shared<HasCoinState>(this))
    , m_NoCoinState(std::make_shared<NoCoinState>(this))
    , m_SellState(std::make_shared<SellState>(this))
{

}
