// 状态模式是一种行为设计模式，
// 让你能在一个对象的内部状态变化时改变其行为， 使其看上去就像改变了自身所属的类一样。

#include <iostream>

using std::cout;

class Context;

class State
{
public:
    virtual ~State() = default;
    void SetContext(Context *context)
    {
        m_context_ = context;
    }

    virtual void Handler1() = 0;
    virtual void Handler2() = 0;
protected:
    Context *m_context_;
};

class Context
{
public:
    Context(State *state) : m_state_(nullptr)
    {
        this->TransitionTo(state);
    }

    ~Context()
    {
        delete m_state_;
    }

    void TransitionTo(State *state)
    {
        std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        if (this->m_state_ != nullptr)
            delete this->m_state_;
        
        this->m_state_ = state;
        this->m_state_->SetContext(this);
    }

    void Request1()
    {
        this->m_state_->Handler1();
    }

    void Request2()
    {
        this->m_state_->Handler2();
    }
private:
    State *m_state_;
};

class ConcreteStateA : public State
{
public:
    void Handler1() override;

    void Handler2() override
    {
        std::cout << "ConcreteStateA handles request2.\n";
    }
};

class ConcreteStateB : public State
{
public:
    void Handler1() override
    {
        std::cout << "ConcreteStateB handles request1.\n";
    }

    void Handler2() override
    {
        std::cout << "ConcreteStateB handles request2.\n";
        std::cout << "ConcreteStateB wants to change the state of the context.\n";
        this->m_context_->TransitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::Handler1()
{
    std::cout << "ConcreteStateA handles request1.\n";
    std::cout << "ConcreteStateA wants to change the state of the context.\n";
    this->m_context_->TransitionTo(new ConcreteStateB);
}

void ClientCode()
{
    Context *context = new Context(new ConcreteStateA);
    context->Request1();
    context->Request1();
    context->Request2();
    context->Request2();
    delete context;
}

int main()
{
    ClientCode();
    return 0;
}