// 外观是一种结构型设计模式
// 能为复杂系统、 程序库或框架提供一个简单 （但有限） 的接口。

#include <iostream>

using std::cout;

class Subsystem1
{
public:
    std::string Operation1() const
    {
        return "Subsystem1: Ready!\n";
    }

    std::string OperationN() const
    {
        return "Subsystem1: GO!\n";
    }
};

class Subsystem2
{
public:
    std::string Operation1() const
    {
        return "Subsystem2: Ready!\n";
    }

    std::string OperationZ() const
    {
        return "Subsystem2: Fire!\n";
    }
};

class Facade
{
public:
    Facade(Subsystem1* subsystem1, Subsystem2* subsystem2) : m_subsystem1_(subsystem1),
                                                             m_subsystem2_(subsystem2)
    {}

    std::string Operation()
    {
        std::string result = "Facade initializes subsystem:\n";
        result += m_subsystem1_->Operation1();
        result += m_subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += m_subsystem1_->OperationN();
        result += m_subsystem2_->OperationZ();
        return result;
    }
private:
    Subsystem1* m_subsystem1_;
    Subsystem2* m_subsystem2_;
};

class Client
{
public:
    void Code(Facade* facade)
    {
        std::cout << facade->Operation() << '\n';
    }
};

int main()
{
    Subsystem1 subsystem1;
    Subsystem2 subsystem2;
    Facade facade(&subsystem1, &subsystem2);
    Client client;
    client.Code(&facade);
    return 0;
}