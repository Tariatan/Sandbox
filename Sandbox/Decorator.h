#pragma once

#include <iostream>

// AKA Wrapper
// Extends existing functionality without inheritance

class iDrawable
{
public:
    virtual void draw() = 0;
    virtual ~iDrawable() = default;
};

class Button : public iDrawable
{
public:
    void draw() override final  { std::cout << "Draw button" << std::endl; }
};

class ButtonWrapper : public iDrawable
{
public:
    ButtonWrapper(std::shared_ptr<iDrawable> drawable) : m_drawable(drawable) {}
    std::shared_ptr<iDrawable> m_drawable;
};

class BorderedButton : public ButtonWrapper
{
public:
    BorderedButton(std::shared_ptr<iDrawable> drawable) : ButtonWrapper(drawable){}
    void draw()
    {
        std::cout << "Draw border" << std::endl;
        m_drawable->draw();
    }
};

class FormPanel
{
public:
    void show()
    {
        std::shared_ptr<iDrawable> btn{std::make_shared<Button>()};
        BorderedButton borderedBtn(btn);
        borderedBtn.draw();
    }
};