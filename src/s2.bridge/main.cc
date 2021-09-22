// 桥接模式是一种结构型设计模式， 
// 可将一个大类或一系列紧密相关的类拆分为抽象和实现两个独立的层次结构， 从而能在开发时分别使用。

#include <iostream>

using std::cout;
using std::string;

class Implementation
{
public:
    virtual ~Implementation() = default;
    virtual string OperationImplementation() const = 0;
};

class ConcreteImplementationA : public Implementation
{
public:
    string OperationImplementation() const override
    {
        return "ConcreteImplementationA: Here's the result on the platform A.";
    }
};

class ConcreteImplementationB : public Implementation
{
public:
    string OperationImplementation() const override
    {
        return "ConcreteImplementationB: Here's the result on the platform B.";
    }
};

class Abstraction
{
public:
    Abstraction(Implementation* implementation) : m_implementation_(implementation)
    {
    }

    virtual ~Abstraction() = default;

    virtual string Operation() const
    {
        return "Abstraction: Base operation with: \n"
            + m_implementation_->OperationImplementation();
    }
protected:
    Implementation* m_implementation_;
};

class ExtendedAbstraction : public Abstraction
{
public:
    ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation)
    {
    }

    string Operation() const override
    {
        return "Extendedbstraction: Extended operation with: \n"
            + this->m_implementation_->OperationImplementation();
    }
};

void ClientCode(const Abstraction* abstraction)
{
    cout << abstraction->Operation() << '\n';
}

int main()
{
    Implementation* implementationA = new ConcreteImplementationA;
    Implementation* implementationB = new ConcreteImplementationB;
    Abstraction* abstractionA = new Abstraction(implementationA);
    ClientCode(abstractionA);
    std::cout << '\n';

    Abstraction* abstractionB = new ExtendedAbstraction(implementationB);
    ClientCode(abstractionB);

    delete abstractionB;
    delete abstractionA;
    delete implementationA;
    delete implementationB;
    return 0;
}