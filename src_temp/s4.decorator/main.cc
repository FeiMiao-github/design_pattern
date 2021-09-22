// 装饰模式是一种结构型设计模式，允许你将对象放入包含行为的特殊封装对象中为原对象绑定
// 新的行为

#include <iostream>

using std::string;
using std::cout;

class Component
{
public:
    virtual ~Component() = default;
    virtual void doSomething() const = 0;
};

class Decorator
    : public Component
{
public:
    virtual ~Decorator() = default;

    Decorator(Component *component)
        : m_component_(component)
    {}

    void doSomething() const override
    {
        m_component_->doSomething();
    }

private:
    Component *m_component_;
};

class ConcreteCompoent
    : public Component
{
public:
    void doSomething() const override
    {
        cout << "ConcreteCompoent";
    }
};

class ConcreteDecoratorA
    : public Decorator
{
public:
    ConcreteDecoratorA(Component *component)
        : Decorator(component)
    {}

    void doSomething() const override
    {
        cout << "ConcreteDecoratorA(";
        Decorator::doSomething();
        cout << ")";
    }
};

class ConcreteDecoratorB
    : public Decorator
{
public:
    ConcreteDecoratorB(Component *component)
        : Decorator(component)
    {}

    void doSomething() const override
    {
        cout << "ConcreteDecoratorB(";
        Decorator::doSomething();
        cout << ")";
    }
};

void Client(Component *component)
{
    component->doSomething();
}

int main()
{
    Component *component = new ConcreteCompoent;
    cout << "ConcreteCompoent ---> \n";
    Client(component);
    cout << "\n";

    Component *concreteDecoratorA = new ConcreteDecoratorA(component);
    cout << "ConcreteDecoratorA ---> \n";
    Client(concreteDecoratorA);
    cout << "\n";
 
    Component *concreteDecoratorB = new ConcreteDecoratorB(concreteDecoratorA);
    cout << "CncreteDecoratorB ---> \n";
    Client(concreteDecoratorB);
    cout << "\n";

    delete concreteDecoratorB;
    delete concreteDecoratorA;
    delete component;
    return 0;
}