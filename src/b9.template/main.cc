// 模版方法是一种行为设计模式
// 它在基类中定义了一个算法的框架， 允许子类在不修改结构的情况下重写算法的特定步骤。

// 抽象类 （Abstract­Class） 会声明作为算法步骤的方法， 以及依次调用它们的实际模板方法。 
//                  算法步骤可以被声明为 抽象类型， 也可以提供一些默认实现。
// 具体类 （Concrete­Class） 可以重写所有步骤， 但不能重写模板方法自身。

#include <iostream>

class AbstractClass
{
public:
    void TemplateMethod() const
    {
        this->BaseOperation1();
        this->RequiredOperations1();
        this->BaseOperation2();
        this->Hook1();
        this->RequiredOperations2();
        this->BaseOperation3();
        this->Hook2();
    }

private:
    void BaseOperation1() const
    {
        std::cout << "AbstractClass says: I am doing the bulk of the work.\n";
    }

    void BaseOperation2() const
    {
        std::cout << "AbstractClass says: But I let subclasses override some operations.\n";
    }

    void BaseOperation3() const
    {
        std::cout << "AbstractClass says: But I am doing the bulk of work anyway.\n";
    }

    virtual void RequiredOperations1() const = 0;
    virtual void RequiredOperations2() const = 0;

    virtual void Hook1() const {}
    virtual void Hook2() const {}
};

class ConcreteClass1 : public AbstractClass{
private:
    void RequiredOperations1() const override
    {
        std::cout << "ConcreteClass1 says: Implemented Operation1.\n";
    }

    void RequiredOperations2() const override
    {
        std::cout << "ConcreteClass1 says: Implemented Operation2.\n";
    }
};

class Client
{
public:
    void Code(AbstractClass *aclass)
    {
        aclass->TemplateMethod();
    }
};

class ConcreteClass2 : public AbstractClass
{
private:
    void RequiredOperations1() const override
    {
        std::cout << "ConcreteClass2 says: Implemented Operation1.\n";
    }

    void RequiredOperations2() const override
    {
        std::cout << "ConcreteClass2 says: Implemented Operations2.\n";
    }

    void Hook1() const override
    {
        std::cout << "ConcreteClass2 says: Overridden Hook1.\n";
    }
};

int main()
{
    Client client;

    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass1 cclass1;
    client.Code(&cclass1);
    std::cout << "\n";

    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass2 cclass2;
    client.Code(&cclass2);
    return 0;
}