// 生成器模式是一种创建型设计模式， 使你能够分步骤创建复杂对象。
// 该模式允许你使用相同的创建代码生成不同类型和形式的对象。

#include <iostream>
#include <vector>

using std::cout;
using std::string;
using std::vector;

class Product
{
public:
    virtual ~Product() {}
    virtual void Disp() const
    {
        for (auto &&i : m_parts_)
        {
            cout << i << '|';            
        }
    }
    void Push(const string &str) 
    {
        m_parts_.push_back(str);
    }
private:
    vector<string> m_parts_;
};

class ProductA : public Product
{
public:
    virtual ~ProductA() {}
    virtual string NameA() const = 0;
    void Disp() const override
    {
        cout << NameA() << ":";
        Product::Disp();
    }
};

class ProductB : public Product
{
public:
    virtual ~ProductB() {}
    virtual string NameB() const = 0;
    void Disp() const override
    {
        cout << NameB() << ":";
        Product::Disp();
    }
};

class ConcreteProductA1 : public ProductA
{
public:
    string NameA() const override
    {
        return "{ConcreteProductA1}";
    }
};

class ConcreteProductB1 : public ProductB
{
public:
    string NameB() const override
    {
        return "{ConcreteProductB1}";
    }
};

class Builder
{
public:
    virtual ~Builder() {}
    virtual void Reset() = 0;
    virtual void BuildStep1() = 0;
    virtual void BuildStep2() = 0;
    virtual void BuildStep3() = 0;
};

class ConcreteBuilderA : public Builder 
{
private:
    void Reset() override
    {
        m_product_ = new ConcreteProductA1;
    }
public:
    ConcreteBuilderA()
    {
        Reset();
    }
    ~ConcreteBuilderA()
    {
        delete m_product_;
    }
    void BuildStep1() override
    {
        if (m_product_ != nullptr)
        {
            m_product_->Push("buildA step1");
        }
    }
    void BuildStep2()
    {
        if (m_product_ != nullptr)
        {
            m_product_->Push("buildA step2");
        }
    }
    void BuildStep3()
    {
        if (m_product_ != nullptr)
        {
            m_product_->Push("buildA step3");
        }
    }
    ProductA* GetResult()
    {
        ProductA* ret = m_product_;
        Reset();
        return ret;
    }
private:
    ProductA* m_product_;
};

class ConcreteBuilderB : public Builder 
{
private:
    void Reset() override
    {
        m_product_ = new ConcreteProductB1;
    }
public:
    ConcreteBuilderB()
    {
        Reset();
    }
    ~ConcreteBuilderB()
    {
        delete m_product_;
    }
    void BuildStep1() override
    {
        if (m_product_ != nullptr)
        {
            m_product_->Push("buildB step1");
        }
    }
    void BuildStep2()
    {
        if (m_product_ != nullptr)
        {
            m_product_->Push("buildB step2");
        }
    }
    void BuildStep3()
    {
        if (m_product_ != nullptr)
        {
            m_product_->Push("buildB step3");
        }
    }
    ProductB* GetResult()
    {
        ProductB* ret = m_product_;
        Reset();
        return ret;
    }
private:
    ProductB* m_product_;
};

class Director
{
public:
    Director(Builder* builder = nullptr) : m_builder_(builder)
    {}

    void SetBuilder(Builder* builder)
    {
        this->m_builder_ = builder;
    }

    void build12()
    {
        if (m_builder_ == nullptr)
        {
            return ;
        }
        this->m_builder_->BuildStep1();
        this->m_builder_->BuildStep2();
    }

    void build23()
    {
        if (m_builder_ == nullptr)
        {
            return ;
        }
        this->m_builder_->BuildStep2();
        this->m_builder_->BuildStep3();
    }
private:
    Builder* m_builder_;
};

void ClientCode(Director* director)
{
    ConcreteBuilderA* builderA = new ConcreteBuilderA;
    ConcreteBuilderB* builderB = new ConcreteBuilderB;

    cout << "\nBuild A12 Product: \n";
    director->SetBuilder(builderA);
    director->build12();

    ProductA* productA = builderA->GetResult();
    productA->Disp();
    cout << '\n';
    delete productA; 

    cout << "\nBuild B23 Product: \n";
    director->SetBuilder(builderB);
    director->build23();

    ProductB* productB = builderB->GetResult();
    productB->Disp();
    cout << '\n';
    delete productB;

    delete builderA;
    delete builderB;
}

int main()
{
    Director* director = new Director();
    ClientCode(director);
    delete director;
    return 0;
}