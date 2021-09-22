/**
 * 备忘录模式(momento)
 *  在不破坏对象封装性的前提下，捕获一个对象的内部状态，并在对象之外保存这个状态
*/

#include <iostream>

class Originator;

// 备忘录类
class Memento
{
private:
    friend class Originator;

    // 对外部类(除 Originator)隐藏构造方法
    Memento()
    {}

    // 对外部类(除 Originator)隐藏状态获取方法
    void SetState(const std::string& ns)
    {
        _state = ns;
    }

    const std::string& GetState()
    {
        return _state;
    }

private:
    // 与原发器对应的状态
    std::string _state;
};

// 原发器
class Originator
{
public:
    // 改变状态的方法
    void ChangeState()
    {

    }

    // 备份状态, 返回一个备忘录类的对象
    Memento *CreateMemento()
    {
        return new Memento;
    }

    // 根据备忘录的对象, 恢复状态
    void Restore(Memento *memento)
    {
        _state = memento->GetState();
    }

    // 保存状态到指定备忘录对象
    void Save(Memento *memento)
    {
        memento->SetState(_state);
    }

private:
    std::string _state;
};

// 管理
class CareTaker
{
public:
    CareTaker(Originator* originator)
        : _originator(originator),
          _history(originator->CreateMemento())
    {
    }

    // 管理方法: 备份
    void BackUp()
    {
        _originator->Save(_history);
    }

    // 管理方法： 撤销
    void Undo()
    {
        _originator->Restore(_history);
    }
private:
    // 受管理的原发器对象
    Originator *_originator;
    // 用于备份原发器的对象状态
    // 或使用 stack<Memento*> _historys记录一系列状态
    Memento *_history;
};

int main()
{
    return 0;
}