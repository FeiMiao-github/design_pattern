// 备忘录模式是一种行为设计模式
// 允许在不暴露对象实现细节的情况下保存和恢复对象之前的状态。

#include <iostream>

template <typename T>
void safe_release(T* &t)
{
    if (t != nullptr)
    {
        delete t;
        t = nullptr;
    }
}

/**
 * @brief 备忘录 （Memento） 是原发器状态快照的值对象 （value object）。
 * 通常做法是将备忘录设为不可变的， 并通过构造函数一次性传递数据
 * 
 */
class Memento
{
public:
    virtual std::string state() const = 0;
    virtual ~Memento() = default;
};

/**
 * @brief 用于保存Originator的snapshot状态
 * 
 */
class ConcreateMemento : public Memento
{
public:
    ConcreateMemento(std::string state) : m_state_(state) {}
    std::string state() const
    {
        return m_state_;
    }
private:
    std::string m_state_;
};

/**
 * @brief 原发器 （Originator） 类可以生成自身状态的快照，
 * 也可以在需要时通过快照恢复自身状态。
 * 
 */
class Originator
{
public:
    Memento* save()
    {
        return new ConcreateMemento(m_state_);
    }

    /**
     * @brief restore state from a Memento object
     * 
     * @param m The Memento object which saves the state of Originator
     */
    void restore(Memento* m)
    {
        m_state_ = m->state();
        std::cout << "Originator: my state has restored to : "
                  << m_state_
                  << '\n';
    }

    void set_state(const std::string &new_state)
    {
        m_state_ = new_state;
    }

    const std::string& get_state()
    {
        return m_state_;
    }
private:
    std::string m_state_;
};

/**
 *  @brief 负责人（Caretaker） 
 * 仅知道 “何时” 和 “为何” 捕捉原发器的状态， 以及何时恢复状态。
 * 负责人通过保存备忘录栈来记录原发器的历史状态。 当原发器需要回溯历史状态时， 
 * 负责人将从栈中获取最顶部的备忘录， 并将其传递给原发器的恢复 （restoration） 方法
 * 
 */
class Caretaker
{
public:
    Caretaker(Originator* originator)
        : m_originator(originator),
          m_history(nullptr)
    {
    }

    void backup() {
        safe_release(m_history);
        m_history = m_originator->save();
    }

    void undo() {
        if (!m_history)
        {
            return;
        }

        m_originator->restore(m_history);
        safe_release(m_history);
    }

    ~Caretaker()
    {
        safe_release(m_history);
    }
private:
    Originator* m_originator;
    Memento* m_history;
};

void client()
{
    Originator originator;
    originator.set_state("Hello world!");
    std::cout << "[originator]: " << originator.get_state() << "\n";

    Caretaker caretaker(&originator);
    caretaker.backup();

    originator.set_state("Hello XiaoMing!");
    std::cout << "[originator]: " << originator.get_state() << "\n";

    caretaker.undo();
    std::cout << "[originator]: " << originator.get_state() << "\n";
}

int main()
{
    client();
    return 0;
}