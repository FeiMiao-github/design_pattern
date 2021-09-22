/**
 * 策略模式(Strategy)是一种行为型模式
 *  用于封装一系列的算法，并且使它们可以替换
 * 
 */

#include <iostream>
#include <memory>

class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual void Execute() = 0;
};

class ConcreteStrategyA
    : public Strategy
{
public:
    void Execute()
    {
        std::cout << "ConcreteStrategyA Execute !\n";
    }
};

class ConcreteStrategyB
    : public Strategy
{
public:
    void Execute()
    {
        std::cout << "ConcreteStrategyB Execute !\n";
    }
};

class Context
{
public:
    Context(Strategy *strategy)
        : _strategy(strategy)
    {
    }

    void SetStrategy(Strategy *strategy)
    {
        _strategy = strategy;
    }

    void Do()
    {
        std::cout << "[Context] Call Strategy:";
        _strategy->Execute();
    }

private:
    Strategy *_strategy;
};

int main()
{
    std::shared_ptr<Strategy> strategyA = std::make_unique<ConcreteStrategyA>();
    std::shared_ptr<Strategy> strategyB = std::make_unique<ConcreteStrategyB>();
    std::shared_ptr<Context> context = std::make_shared<Context>(strategyA.get());
    context->Do();
    context->SetStrategy(strategyB.get());
    context->Do();
    return 0;
}