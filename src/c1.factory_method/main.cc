// 工厂方法模式
// 亦称： 虚拟构造函数、Virtual Constructor、Factory Method
//    工厂方法模式是一种创建型设计模式, 其在父类中提供一个创建对象的方法,
//    允许子类决定实例化对象的类型。

#include <iostream>

using std::cout;
using std::string;

class Product
{
public:
    virtual ~Product() {}
    virtual string Name() const = 0;
};

class Creator
{
public:
    virtual ~Creator() {}
    virtual Product* CreateProduct() const = 0;
};

template <char ch>
class ConcreteProduct : public Product
{
public:
    string Name() const override
    {
        string ret = "{ConcreteProduct-";
        ret.push_back(ch);
        ret.push_back('}');
        return ret;
    }
};

template <char ch>
class ConcreteCreator : public Creator
{
public:
    Product* CreateProduct() const override
    {
        return new ConcreteProduct<ch>;
    }
};

void ClientCode(const Creator* c)
{
    Product* product = c->CreateProduct();
    std::cout << "[ClientCode: " << product->Name() << "]\n";
    delete product;
}

int main()
{
    cout << "Test ConcreteCreator A: \n";
    Creator* c = new ConcreteCreator<'A'>;
    ClientCode(c);
    delete c;
    return 0;
}