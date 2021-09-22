// 适配器模式是一种结构型设计模式，它能使不兼容的对象能够相互合作(多继承实现)

#include <iostream>

using std::string;
using std::cout;

class exist
{
public:
    virtual ~exist() = default;
    virtual void method(const string &cname) const
    {
        cout << cname << ":";
        cout << "exist method run !\n";
    }
};

class service
{
public:
    virtual ~service() = default;
    string smethod() const
    {
        return "service smethod run !\n";
    }
};

class service_adapter
    : public exist, public service
{
public:
    virtual ~service_adapter() = default;
    void method(const string &cname) const override
    {
        cout << cname << ":";
        cout << service::smethod();
    }
};

void client(exist *inst)
{
    inst->method("client");
}

int main()
{
    exist *inst = new service_adapter;
    client(inst);
    delete inst;
    return 0;
}