#pragma once

#include <iostream>
#include <map>
#include <memory>

// AKA Cache

class CachedObject
{
public:
    void render()
    {
        std::cout << "rendering big image " << m_heavyData << std::endl;
    }
private:
    int m_heavyData{0};
};

class FlyweightCommonFactory
{
public:
    static std::shared_ptr<CachedObject> getObject(int refId)
    {
        return m_idToObjectMap[refId];
    }

    static void setObject(int refId, std::shared_ptr<CachedObject> obj)
    {
        m_idToObjectMap[refId] = obj;
    }

private:
    using ObjectsMap = std::map<int, std::shared_ptr<CachedObject>>;
    static ObjectsMap m_idToObjectMap;
};

FlyweightCommonFactory::ObjectsMap FlyweightCommonFactory::m_idToObjectMap{};

class Flyweight
{
public:
    Flyweight(int refId)
    {
        m_cache = FlyweightCommonFactory::getObject(refId);
    }

    void render()
    {
        m_cache->render();
    }

private:
    std::shared_ptr<CachedObject> m_cache;
};

class CacheContainer
{
public:
    void renderObjects()
    {
        FlyweightCommonFactory::setObject(1, std::make_shared<CachedObject>());
        FlyweightCommonFactory::setObject(2, std::make_shared<CachedObject>());

        auto obj = FlyweightCommonFactory::getObject(1);
        obj->render();
    }
};