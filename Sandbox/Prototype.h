#pragma once
#include <memory>
#include <vector>
#include <string>

// Clone / Virtual Copy Constructor

class iClonable
{
public:
    virtual std::unique_ptr<iClonable> clone() const = 0;
    virtual ~iClonable() = default;
};

class Sunflower : public iClonable
{
public:
    Sunflower(int quality) : m_quality(quality) {};

    std::unique_ptr<iClonable> clone() const override final
    {
        return std::make_unique<Sunflower>(m_quality);
    }

private:
    int m_quality;
};

class Corn : public iClonable
{
public:
    Corn(int quality) : m_quality(quality) {};

    std::unique_ptr<iClonable> clone() const override final
    {
        return std::make_unique<Corn>(m_quality);
    }

private:
    int m_quality;
};

class Greenhouse
{
public:
    Greenhouse() : m_id(0) {}
    Greenhouse(int id) : m_id(id) {}

    void setPlant(std::shared_ptr<iClonable> plant)
    {
        m_plant.swap(plant);
    }

    std::shared_ptr<iClonable> yield() const
    {
        return m_plant->clone();
    }

private:
    std::shared_ptr<iClonable> m_plant;
    int m_id;
};

class Farm
{
public:
    void initializeGame()
    {
        Greenhouse g1(1);
        g1.setPlant(std::make_unique<Sunflower>(50));
        Greenhouse g2(2);
        g2.setPlant(std::make_unique<Corn>(80));

        m_greenhouses.emplace_back(g1);
        m_greenhouses.emplace_back(g2);
    }

    void yield()
    {
        for (const auto& greenhouse : m_greenhouses)
        {
            m_crops.emplace_back(greenhouse.yield());
        }
    }
private:
    std::vector<Greenhouse> m_greenhouses;
    std::vector<std::shared_ptr<iClonable>> m_crops;
};