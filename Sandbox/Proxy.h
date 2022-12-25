#pragma once

#include <iostream>

class ServiceInterface
{
public:
    virtual void init() = 0;
    virtual void store() = 0;
    virtual ~ServiceInterface() = default;
};

class SaveService : public ServiceInterface
{
public:
    void init() override final
    {
        std::cout << "Init service" << std::endl;
    }

    void store() override final
    {
        std::cout << "Save to file" << std::endl;
    }
};

class LazySaveServiceProxy : public ServiceInterface
{
public:
    void init() override final
    {
        static bool bInitizlized = false;
        if (bInitizlized)
        {
            return;
        }

        bInitizlized = true;
        m_service.init();
    }
    void store() override final
    {
        init();
        m_service.store();
    }

private:
    SaveService m_service;
};

class Client
{
public:
    void save()
    {
        LazySaveServiceProxy proxy;
        proxy.store();
    }
};