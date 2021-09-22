// 访问者是一种行为设计模式
// 允许你在不修改已有代码的情况下向已有类层次结构中增加新的行为。
// 它能将算法与其所作用的对象隔离开来。

// visitor
// concrete visitor
// element
// concrete element

#include <iostream>
#include <array>

class ConcreteComponentA;
class ConcreteComponentB;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void VisitConcreteComponentA(const ConcreteComponentA *element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

class Component
{
public:
    virtual ~Component() = default;
    virtual void Accept(Visitor *visitor) const = 0;
};

class ConcreteComponentA : public Component
{
public:
    void Accept(Visitor *visitor) const override
    {
        visitor->VisitConcreteComponentA(this);
    }

    std::string ExclusiveMethodOfConcreteComponentA() const
    {
        return "ConcreteComponentA";
    }
};

class ConcreteComponentB : public Component
{
public:
    void Accept(Visitor *visitor) const override
    {
        visitor->VisitConcreteComponentB(this);
    }

    std::string SpecialMethodOfConcreteComponentB() const
    {
        return "ConcreteComponentB";
    }
};

class ConcreteVisitor1 : public Visitor
{
public:
    void VisitConcreteComponentA(const ConcreteComponentA *element) const override
    {
        std::cout << element->ExclusiveMethodOfConcreteComponentA()
                  << " + ConcreteVisitor1.\n";
    }

    void VisitConcreteComponentB(const ConcreteComponentB *element) const override
    {
        std::cout << element->SpecialMethodOfConcreteComponentB()
                  << " + ConcreteVisitor1.\n";
    }
};

class ConcreteVisitor2 : public Visitor
{
public:
    void VisitConcreteComponentA(const ConcreteComponentA *element) const override
    {
        std::cout << element->ExclusiveMethodOfConcreteComponentA()
                  << " + ConcreteVisitor2.\n";
    }

    void VisitConcreteComponentB(const ConcreteComponentB *element) const override
    {
        std::cout << element->SpecialMethodOfConcreteComponentB()
                  << " + ConcreteVisitor2.\n";
    }
};

void ClientCode(std::array<const Component *, 2> components, Visitor *visitor)
{
    for (const Component *component : components)
    {
        component->Accept(visitor);
    }
} 

int main()
{
    std::array<const Component *, 2> components =
    {
        new ConcreteComponentA,
        new ConcreteComponentB
    };
    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    std::cout << "\n";
    std::cout << "It allows the same client code to work with different types of visitors:\n";
    ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for(const Component *component : components)
    {
        delete component;
    }
    delete visitor1;
    delete visitor2;
    return 0;
}