#include <iostream>
#include <vector>

class Product
{
public:
    virtual ~Product() {}
    virtual void Push(const std::string &str)
    {
        m_step_.push_back(str);
    }
    virtual void Disp() const
    {
        std::cout << "{\n";
        for (auto &&i : m_step_)
        {
            std::cout << "\t" << i << ",\n";
        }
        std::cout << "}\n";
    }
private:
    std::vector<std::string> m_step_;
};

class ProductA
    : public Product
{
public:
    virtual ~ProductA() {}
    virtual std::string NameA() const = 0;
    void Disp() const override
    {
        std::cout << NameA() << ":";
        Product::Disp();
    }
};

class ProductB
    : public Product
{
public:
    virtual ~ProductB() {}
    virtual std::string NameB() const = 0;
    void Disp() const override
    {
        std::cout << NameB() << ":";
        Product::Disp();
    }
};

class CProductA
    : public ProductA
{
public:
    std::string NameA() const override
    {
        return "CProductA";
    }
};

class CProductB
    : public ProductB
{
public:
    std::string NameB() const override
    {
        return "CProductB";
    }
};

class Builder
{
public:
    virtual ~Builder() {}
    virtual void BuildStep1() = 0;
    virtual void BuildStep2() = 0;
    virtual void BuildStep3() = 0;
    virtual void Reset() = 0;
};

class ConcreteBuilderA
    : public Builder
{
private:
    void Reset() override
    {
        if (m_product_ == nullptr)
        {
            m_product_ = new CProductA;
        }
    }
public:
    ConcreteBuilderA()
        : m_product_(new CProductA)
    {
    }
    ~ConcreteBuilderA()
    {
        delete m_product_;
    }
    ProductA *Get()
    {
        ProductA *ret = m_product_;
        m_product_ = nullptr;
        return ret;
    }
    void BuildStep1() override
    {
        m_product_->Push("ConcreteBuilderA Step1");
    }
    void BuildStep2() override
    {
        m_product_->Push("ConcreteBuilderA Step2");
    }
    void BuildStep3() override
    {
        m_product_->Push("ConcreteBuilderA Step3");
    }
private:
    ProductA *m_product_;
};

class ConcreteBuilderB
    : public Builder
{
private:
    void Reset() override
    {
        if (m_product_ == nullptr)
        {
            delete m_product_;
        }
    }
public:
    ConcreteBuilderB()
        : m_product_(new CProductB)
    {
    }
    ~ConcreteBuilderB()
    {
        delete m_product_;
    }
    ProductB *Get()
    {
        ProductB *ret = m_product_;
        m_product_ = nullptr;
        return ret;
    }
    void BuildStep1() override
    {
        m_product_->Push("ConcreteProductB Step1");
    }
    void BuildStep2() override
    {
        m_product_->Push("ConcreteProductB Step2");
    }
    void BuildStep3() override
    {
        m_product_->Push("ConcreteProductB Step3");
    }
private:
    ProductB *m_product_;
};

class Director
{
public:
    Director() = default;
    void SetBuilder(Builder *builder)
    {
        m_builder_ = builder;
    }
    void Build123()
    {
        if (m_builder_ == nullptr)
            return;

        m_builder_->BuildStep1();
        m_builder_->BuildStep2();
        m_builder_->BuildStep3();
    }
    void Build321()
    {
        if (m_builder_ == nullptr)
            return;

        m_builder_->BuildStep3();
        m_builder_->BuildStep2();
        m_builder_->BuildStep1();
    }
private:
    Builder *m_builder_;
};

void ClientCode(Director *director)
{
    ConcreteBuilderA cbuilderA;
    ConcreteBuilderB cbuilderB;

    director->SetBuilder(&cbuilderA);
    director->Build123();
    std::cout << "ConcreteBuilderA Build123:\n";
    ProductA *productA = cbuilderA.Get();
    productA->Disp();
    delete productA;

    director->SetBuilder(&cbuilderB);
    director->Build321();
    std::cout << "ConcreteBuilderB Build321:\n";
    ProductB *productB = cbuilderB.Get();
    productB->Disp();
    delete productB;
}

int main()
{
    Director director;
    ClientCode(&director);
    return 0;
}