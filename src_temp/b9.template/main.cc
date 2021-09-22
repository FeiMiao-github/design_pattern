/**
 * 模板方法(template)是一种行为型模式
 *  它定义一个操作中算法的骨架,而将一些步骤延迟到子类中实现
 */
#include <iostream>

class AbastractClass
{
public:
    /* 外部调用方法 */
    
    virtual ~AbastractClass() = default;

    void TemplateMethod()
    {
        BaseOperation();
        RequireOperation();
        Hook();
    }

private:
    /* 不需要子类实现*/

    void BaseOperation()
    {

    }

protected:
    /* 需要子类实现 */

    virtual void RequireOperation() = 0;

    /* 子类可选实现 */

    virtual void Hook()
    {
    }
};

class ConcreteClassA
    : public AbastractClass
{
public:
    virtual void RequireOperation()
    {
        std::cout << "[ConcreteClassA] run RequireOperation.\n";
    }
};

class ConcreteClassB
    : public AbastractClass
{
public:
    virtual void RequireOperation()
    {
        std::cout << "[ConcreteClassB] run RequireOperation.\n";
    }

    virtual void Hook()
    {
        std::cout << "[ConcreteClassB] run Hook.\n";
    }
};

class Client
{
public:
    void Run(AbastractClass *as)
    {
        as->TemplateMethod();
    }
};

int main()
{
    ConcreteClassA ca;
    ConcreteClassB cb;
    Client client;

    client.Run(&ca);
    client.Run(&cb);

    return 0;
}