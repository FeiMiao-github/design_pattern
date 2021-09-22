/**
 * 访问者模式(visitor)是一种行为型模式
 *  它建议将新添加的行为放入一个名为访问者的新类中
 */

#include <iostream>
#include <array>

class ConcreteComponentA;
class ConcreteComponentB;

class Visitor
{
public:
    virtual ~Visitor() = default;

    /* 定义所有Component子类的新行为 */
    virtual void VisitConcreteComponentA(ConcreteComponentA *) = 0;
    virtual void VisitConcreteComponentB(ConcreteComponentB *) = 0;

    /* 或者 通过visit重载 */
    /*
    virtual void Visit(ConcreteComponentA *) = 0;
    virtual void Visit(ConcreteComponentB *) = 0;
    */
};

class Component
{
public:
    virtual ~Component() = default;
    virtual void Accept(Visitor *visitor) = 0;
};

class ConcreteComponentA
    : public Component
{
public:
    void Accept(Visitor *visitor)
    {
        visitor->VisitConcreteComponentA(this);
    }

    void MethodA()
    {
        std::cout << "[ConcreteComponentA] MethodA run !\n";
    }
};

class ConcreteComponentB
    : public Component
{
public:
    void Accept(Visitor *visitor)
    {
        visitor->VisitConcreteComponentB(this);
    }

    void MethodB()
    {
        std::cout << "[ConcreteComponentB] MethodB run !\n";
    }
};

/* 可以定义通过添加新的访问类添加新的行为 */
class ConcreteVisitor
    : public Visitor
{
public:
    /* 此处可以使用重载 */
    void VisitConcreteComponentA(ConcreteComponentA * component) override
    {
        component->MethodA();
    }

    void VisitConcreteComponentB(ConcreteComponentB * component) override
    {
        component->MethodB();
    }
};

class Context
{
public:
    void Run(Component *component, Visitor *visitor)
    {
        component->Accept(visitor);
    }
};

int main()
{
    Context context;
    ConcreteComponentA ca;
    ConcreteComponentB cb;
    ConcreteVisitor cv;

    std::array<Component*, 2> arr{&ca, &cb};
    for (auto &&p: arr)
    {
        context.Run(p, &cv);
    }

    return 0;
}