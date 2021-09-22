#include <iostream>

class ProductA
{
public:
    virtual ~ProductA() {}
    virtual std::string NameA() const = 0;
};

class ProductB
{
public:
    virtual ~ProductB() {}
    virtual std::string NameB() const = 0;
};

class Factory
{
public:
    virtual ~Factory() {}
    virtual ProductA* CreateA() const = 0;
    virtual ProductB* CreateB() const = 0;
};

class CProductA1
    : public ProductA
{
public:
    virtual std::string NameA() const override
    {
        return "CProductA1";
    }
};

class CProductA2
    : public ProductA
{
public:
    virtual std::string NameA() const override
    {
        return "CProductA2";
    }
};

class CProductB1
    : public ProductB
{
public:
    virtual std::string NameB() const override
    {
        return "CProductB1";
    }
};

class CProductB2
    : public ProductB
{
public:
    virtual std::string NameB() const override
    {
        return "CProductB2";
    }
};

class CFactory1
    : public Factory
{
public:
    ProductA* CreateA() const override
    {
        return new CProductA1;
    }

    ProductB* CreateB() const override
    {
        return new CProductB1;
    }
};

class CFactory2
    : public Factory
{
public:
    ProductA* CreateA() const override
    {
        return new CProductA2;
    }

    ProductB* CreateB() const override
    {
        return new CProductB2;
    }
};

void ClientCode(Factory *facotry)
{
    ProductA *productA = facotry->CreateA();
    ProductB *productB = facotry->CreateB();

    std::cout << "factory create product : {\n"
              << "\t" << productA->NameA() << ",\n"
              << "\t" << productB->NameB() << ",\n"
              << "}\n";

    delete productA;
    delete productB;
}

int main()
{
    Factory *factory1 = new CFactory1;
    ClientCode(factory1);
    delete factory1;

    Factory *factory2 = new CFactory2;
    ClientCode(factory2);
    delete factory2;

    return 0;
}