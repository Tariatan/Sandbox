#pragma once

#include <memory>
#include <iostream>

class iOutputImpl
{
public:
    virtual void show() const = 0;
    virtual ~iOutputImpl() = default;
};

class TVOutputImpl : public iOutputImpl
{
public:
    void show() const override final
    {
        std::cout << "show on TV" << std::endl;
    }
};

class DisplayOutputImpl : public iOutputImpl
{
public:
    void show() const override final
    {
        std::cout << "show on Cinema" << std::endl;
    }
};

class iDevice
{
public:
    virtual void show() const = 0;
    virtual ~iDevice() = default;
};

class TV : public iDevice
{
public:
    TV(std::shared_ptr<iOutputImpl> impl) : m_outpuptImpl(impl) {}

    void show() const override final
    {
        m_outpuptImpl->show();
    }

private:
    std::shared_ptr<iOutputImpl> m_outpuptImpl;
};

class Display : public iDevice
{
public:
    Display(std::shared_ptr<iOutputImpl> impl) : m_outpuptImpl(impl) {}

    void show() const override final
    {
        m_outpuptImpl->show();
    }
private:
    std::shared_ptr<iOutputImpl> m_outpuptImpl;
};

class GraphicsCardBridge
{
public:
    void show()
    {
        TV tv(std::make_shared<TVOutputImpl>());
        tv.show();

        Display display(std::make_shared<DisplayOutputImpl>());
        display.show();
    }
};