/**
 * 观察者模式是一种行为模式,用于定义对象之间一种一对多的依赖关系.一旦一个对象的
 * 某种状态发生变化时,所有依赖它的对象都得到通知将被更新
*/

#include <iostream>
#include <unordered_set>

class Subject;

class Observer
{
public:
    virtual void Update() = 0;
};

class Subject
{
public:
    virtual void Attach(Observer *observer)
    {
        _observers.insert(observer);
    }

    virtual void Detach(Observer *observer)
    {
        _observers.erase(observer);
    }

    virtual void Notify()
    {
        for (auto &&ob : _observers)
        {
            ob->Update();
        }
    }

    virtual ~Subject() = default;
protected:
    std::unordered_set<Observer*> _observers;
};

class ConcreteSubject
    : public Subject
{
public:
    typedef std::string State;

    void SetState(const State& s)
    {
        _state = s;
        std::cout << "[subject] set state: " << s << "\n";
        Notify();
    }

    const State& GetState()
    {
        return _state;
    }
private:
    std::string _state;
};

class ConcreteObserver
    : public Observer
{
public:
    ConcreteObserver(const std::string &n, ConcreteSubject *subject)
        : _name(n),
          _subject(subject)
    {}

    void Update() override
    {
        std::cout << "[" << _name << "] I know that subject's state is "
                  << _subject->GetState() << "\n";
    }

private:
    const std::string _name;
    ConcreteSubject *_subject;
};

void Client()
{
    ConcreteSubject subject;
    ConcreteObserver observer1("observer1", &subject);
    ConcreteObserver observer2("observer2", &subject);
    ConcreteObserver observer3("observer3", &subject);


    subject.SetState("Hello World\n");
    subject.Attach(&observer1);

    subject.SetState("Hello XiaoMing\n");

    subject.Attach(&observer1);
    subject.Attach(&observer2);
    subject.Attach(&observer3);
    subject.SetState("Hello XiaoWangba\n");
}

int main()
{
    Client();
    return 0;
}