/**
 * 状态模式允许一个对象在内部状态改变时改变它的行为 
 */
#include <iostream>

class Context;

class State
{
public:
    virtual void Do(Context* context) = 0;
    virtual ~State() = default;

protected:
    State() {}

protected:
    void ChangeState(Context *context, State* state);
};

class Context
{
public:
    Context(State *state)
        : _state(state)
    {}

    void CallStateDo()
    {
        std::cout << "[Context]Call State : " << typeid(*_state).name() << "\n";
        _state->Do(this);
    }

private:
    friend class State;
    void ChangeState(State *state)
    {
        _state = state;
    }

    State *_state;
};

void State::ChangeState(Context *context, State* state)
{
    context->ChangeState(state);
}

class ConcreteStateA
    : public State
{
public:
    void Do(Context* context) override;

    static ConcreteStateA* Instance()
    {
        if (!_inst)
        {
            _inst = new ConcreteStateA;
        }
        return _inst;
    }

    class GC
    {
    public:
        ~GC()
        {
            if (_inst)
            {
                delete _inst;
                _inst = nullptr;
            }
        }
    };
private:
    static ConcreteStateA *_inst;
    static GC _gc;
};

ConcreteStateA* ConcreteStateA::_inst = nullptr;
ConcreteStateA::GC ConcreteStateA::_gc;

class ConcreteStateB
    : public State
{
public:
    void Do(Context* context) override
    {
        std::cout << "[ConcreteStateB] run !\n";
        ChangeState(context, ConcreteStateA::Instance());
    }

    static ConcreteStateB* Instance()
    {
        if (!_inst)
        {
            _inst = new ConcreteStateB;
        }
        return _inst;
    }

    class GC
    {
    public:
        ~GC()
        {
            if (_inst)
            {
                delete _inst;
                _inst = nullptr;
            }
        }
    };
private:
    static ConcreteStateB *_inst;
    static GC _gc;
};

ConcreteStateB* ConcreteStateB::_inst = nullptr;
ConcreteStateB::GC ConcreteStateB::_gc;

void ConcreteStateA::Do(Context* context)
{
    std::cout << "[ConcreteStateA] run !\n";
    ChangeState(context, ConcreteStateB::Instance());
}

int main()
{
    Context context(ConcreteStateA::Instance());
    context.CallStateDo();
    context.CallStateDo();
    return 0;
}