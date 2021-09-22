// 策略模式是一种行为设计模式
// 它能让你定义一系列算法， 并将每种算法分别放入独立的类中， 以使算法的对象能够相互替换。

// 上下文 （Context） 维护指向具体策略的引用， 且仅通过策略接口与该对象进行交流。
// 策略 （Strategy） 接口是所有具体策略的通用接口， 它声明了一个上下文用于执行策略的方法。
// 具体策略 （Concrete Strategies） 实现了上下文所用算法的各种不同变体。
//          当上下文需要运行算法时， 它会在其已连接的策略对象上调用执行方法。 上下文不清楚其所涉及的策略类型与算法的执行方式。
// 客户端 （Client） 会创建一个特定策略对象并将其传递给上下文。 上下文则会提供一个设置器以便客户端在运行时替换相关联的策略。

#include <iostream>
#include <vector>
#include <algorithm>

class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual std::string DoAlgorithm(const std::vector<std::string> &data) const = 0;
};

class Context
{
public:
    Context(Strategy *strategy) : m_strategy_(strategy)
    {
    }

    ~Context()
    {
        delete m_strategy_;
    }

    void SetStrategy(Strategy *strategy)
    {
        delete m_strategy_;
        this->m_strategy_ = strategy;
    }

    void DoSomeBusinessLogic() const
    {
        std::cout << "Context: sorting data using the strategy (not sure how it'll do it)\n";
        std::string result = this->m_strategy_
                                 ->DoAlgorithm(std::vector<std::string>{"a", "e", "c", "b", "d"});
        std::cout << result << '\n';
    }
private:
    Strategy *m_strategy_;
};

class ConcreteStrategyA : public Strategy
{
public:
    std::string DoAlgorithm(const std::vector<std::string> &data) const override
    {
        std::string result;
        for (auto &&pstr : data)
        {
            result += pstr;
        }
        
        std::sort(result.begin(), result.end());
        return result;
    }
};

class ConcreteStrategyB : public Strategy
{
public:
    std::string DoAlgorithm(const std::vector<std::string> &data) const override
    {
        std::string result;
        for (auto &&str : data)
        {
            result += str;
        }
        
        std::sort(result.begin(), result.end(), std::greater<char>());
        return result;
    }
};

class Client
{
public:
    void Code()
    {
        Context *context = new Context(new ConcreteStrategyA);
        std::cout << "Client: Strategy is set normal sorting.\n";
        context->DoSomeBusinessLogic();

        std::cout << "\n";
        std::cout << "Client Strategy is set reverse sorting.\n";
        context->SetStrategy(new ConcreteStrategyB);
        context->DoSomeBusinessLogic();
        delete context;
    }
};

int main()
{
    Client client;
    client.Code();
    return 0;
}