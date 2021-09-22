#include <iostream>

class Product
{
public:
    virtual std::string Name() const = 0;
    virtual ~Product() {}
};

class Factory
{
public:
    virtual Product* create() const = 0;
    virtual ~Factory() {}
};

class CProductA
    : public Product
{
public:
    std::string Name() const override
    {
        return "CProductA";
    }
};

class CProductB
    : public Product
{
public:
    std::string Name() const override
    {
        return "CProductB";
    }
};

class CFactoryA
    : public Factory
{
public:
    Product* create() const override
    {
        return new CProductA;
    }
};

class CFactoryB
    : public Factory
{
public:
    Product* create() const override
    {
        return new CProductB;
    }
};

void ClientCode(Factory *factory)
{
    Product *product = factory->create();
    std::cout << "factory create product " << product->Name() << '\n';
    delete product;
}

int main()
{
    Factory *factoryA = new CFactoryA;
    ClientCode(factoryA);
    delete factoryA;

    Factory *factoryB = new CFactoryB;
    ClientCode(factoryB);
    delete factoryB;

    return 0;
}
