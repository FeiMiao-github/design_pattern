// 适配器模式是一种结构型设计模式， 它能使接口不兼容的对象能够相互合作。

#include <iostream>

using std::cout;

class Target
{
public:
    virtual ~Target() = default;

    virtual std::string Request() const 
    {
        return "Target: the default target's behavior.";
    }
};

class Adaptee
{
public:
    std::string SpecificRequest() const
    {
        return "Adaptee: the adaptee's behavior.";
    }
};

class Adapter: public Target
{
public:
    Adapter(Adaptee* adaptee) : m_adaptee_(adaptee)
    {
    }

    std::string Request() const override
    {
        return "Adapter:" + m_adaptee_->SpecificRequest();
    }
private:
    Adaptee* m_adaptee_;
};

void ClientCode(Target* target)
{
    std::cout << "[ClientCode]" << target->Request() << '\n';
}

int main()
{
    std::cout << "client call Target: \n";
    Target* target = new Target;
    ClientCode(target);
    delete target; 

    std::cout << "\n";
    std::cout << "client call Adaptee:\n";
    Adaptee* adaptee = new Adaptee;
    Adapter* adapter = new Adapter(adaptee);
    ClientCode(adapter);
    delete adapter;
    delete adaptee;

    return 0;
}
