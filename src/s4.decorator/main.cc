// 装饰模式是一种结构型设计模式
// 允许你通过将对象放入包含行为的特殊封装对象中来为原对象绑定新的行为

#include <iostream>

using std::cout;

class Component
{
public:
    virtual ~Component() = default;
    virtual std::string Operation() const = 0;
};

class ConcreteComponent : public Component
{
public:
    std::string Operation() const override
    {
        return "ConcreteComponent";
    }
};

class Decorator : public Component
{
public:
    Decorator(Component* component) : m_component_(component)
    {}

    std::string Operation() const override
    {
        return m_component_->Operation();
    }
private:
    Component* m_component_;    
};

class ConcreteDecoratorA : public Decorator
{
public:
    ConcreteDecoratorA(Component* component) : Decorator(component)
    {}

    std::string Operation() const override
    {
        return "ConcreteOperationA(" + Decorator::Operation() + ")";
    }
};

class ConcreteDecoratorB : public Decorator
{
public:
    ConcreteDecoratorB(Component* component) : Decorator(component)
    {}

    std::string Operation() const override
    {
        return "ConcreteOperationB(" + Decorator::Operation() + ")";
    }
};

class Client
{
public:
    void Code(Component* component)
    {
        std::cout << "RESULT: " << component->Operation() << '\n';
    }
};

int main()
{
    Client client;

    std::cout << "Client: I have got a simple component:\n";
    Component* simple = new ConcreteComponent;
    client.Code(simple);
    std::cout << '\n';

    Component* decoratorA = new ConcreteDecoratorA(simple);
    Component* decoratorB = new ConcreteDecoratorB(decoratorA);
    std::cout << "Client: I have got a decorated component:\n";
    client.Code(decoratorB);

    delete decoratorB;
    delete decoratorA;
    delete simple;

    return 0;
}