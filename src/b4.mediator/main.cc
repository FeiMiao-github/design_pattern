// 中介者是一种行为设计模式
// 让程序组件通过特殊的中介者对象进行间接沟通， 达到减少组件之间依赖关系的目的。
// 中介者能使得程序更易于修改和扩展， 而且能更方便地对独立的组件进行复用，
// 因为它们不再依赖于很多其他的类。
#include <iostream>

class Component;

class Mediator
{
public:
    virtual ~Mediator() {}
    virtual void notify(Component *component, std::string event) const = 0;
};

class Component
{
public:
    virtual ~Component() {}
    Component() : m_mediator_(nullptr) {}

    void setMediator(Mediator* mediator)
    {
        m_mediator_ = mediator;
    }
protected:
    Mediator* m_mediator_;
};

class ConcreateComponent1 : public Component
{
public:
    void doA()
    {
        std::cout << "ConcreateComponent1: doA !\n";
        m_mediator_->notify(this, "A");
    }
    void doB()
    {
        std::cout << "ConcreateComponent1: doB !\n";
        m_mediator_->notify(this, "B");
    }
};

class ConcreateComponent2 : public Component
{
public:
    void doC()
    {
        std::cout << "ConcreateComponent2: doC !\n";
        m_mediator_->notify(this, "C");
    }
    void doD()
    {
        std::cout << "ConcreateComponent2: doD !\n";
        m_mediator_->notify(this, "D");
    }
};

class ConcreateMediator : public Mediator
{
public:
    ConcreateMediator(ConcreateComponent1 *c1, ConcreateComponent2 *c2) : component1(c1),
                                                                          component2(c2) {}
    void notify(Component *, std::string event) const override
    {
        if (event == "A")
        {
            std::cout << "Mediator reacts on A and triggers following operations:\n";
            component2->doC();
        }
        else if (event == "D")
        {
            std::cout << "Mediator reacts on A and triggers following operations:\n";
            component1->doB();
        }
    }
private:
    ConcreateComponent1* component1;
    ConcreateComponent2* component2;
};

int main()
{
    ConcreateComponent1 component1;
    ConcreateComponent2 component2;
    ConcreateMediator mediator(&component1, &component2);
    component1.setMediator(&mediator);
    component2.setMediator(&mediator);

    std::cout << "trigger operation A.\n";
    component1.doA();

    std::cout << '\n';    
    std::cout << "trigger operation D.\n";
    component2.doD();

    return 0;
}