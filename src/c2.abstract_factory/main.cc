// 抽象工厂模式是一种创建型设计模式， 它能创建一系列相关的对象， 而无需指定其具体类。

#include <iostream>

using std::string;
using std::cout;

class ProductA
{
public:
    virtual ~ProductA() {}
    virtual string NameA() const = 0;
};

template <int Tag>
class ConcreateProductA : public ProductA
{
public:
    virtual string NameA() const override
    {
        return "{ConcreateProductA" + std::to_string(Tag) + "}";
    }
};

class ProductB
{
public:
    virtual ~ProductB() {}
    virtual string NameB() const = 0;
};

template <int Tag>
class ConcreteProductB : public ProductB
{
public:
    virtual string NameB() const override
    {
        return "{ConcreateProductB" + std::to_string(Tag) + "}";
    }
};

class Factory
{
public:
    virtual ~Factory() {}
    virtual ProductA* CreateProductA() const = 0;
    virtual ProductB* CreateProductB() const = 0;
};

template <int Tag>
class ConcreteFactory : public Factory
{
public:
    ProductA* CreateProductA() const override
    {
        return new ConcreateProductA<Tag>;
    }

    ProductB* CreateProductB() const override
    {
        return new ConcreteProductB<Tag>;
    }
};

void ClientCode(const Factory* factory)
{
    ProductA* productA = factory->CreateProductA();
    ProductB* productB = factory->CreateProductB();
    std::cout << "[ClientCode: " << productA->NameA() << "]\n";
    std::cout << "[ClientCode: " << productB->NameB() << "]\n";
    delete productA;
    delete productB;
}

template <int Tag>
class Exe
{
public:
    void run()
    {
        cout << "Test ConcreteFactory " << Tag << ": \n";
        Factory* factory = new ConcreteFactory<Tag>;
        ClientCode(factory);
        delete factory;

        Exe<Tag - 1> e;
        e.run();
    }
};

template <>
class Exe<0>
{
public:
    void run()
    {
        cout << "Test ConcreteFactory " << 0 << ": \n";
        Factory* factory = new ConcreteFactory<0>;
        ClientCode(factory);
        delete factory;
    }
};

int main()
{
    Exe<3> e;
    e.run();
    return 0;
}