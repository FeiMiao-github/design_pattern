// 适配器模式是一种结构型设计模式，它能使不兼容的对象能够相互合作

#include <iostream>

using std::string;
using std::cout;

class iclient
{
public:
    virtual void method(string &cname) const = 0;
    virtual ~iclient() = default;
};

class service
{
public:
    void smethod() const
    {
        cout << "service smethod run !\n";
    }
};

class service_adapter
    : public iclient
{
public:
    service_adapter()
        : m_service_()
    {
    }
    virtual ~service_adapter() = default;
    void method(string &name) const override
    {
        cout << name << ": ";
        m_service_.smethod(); 
    }
private:
    service m_service_;
};

void client(iclient *ic)
{
    string name = "client";
    ic->method(name);
}

void test()
{
    cout << "\n";
    cout << "\n";
    cout << "\n";

    float i = 21;
    cout << std::hexfloat << i << "\n";
}

int main()
{
    iclient *sadapter = new service_adapter;
    client(sadapter);
    delete sadapter;

    test();
    return 0;
}