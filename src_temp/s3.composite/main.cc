// 组合模式是一种结构型设计模式，你可以使用它将对象组合成树状模式

#include <iostream>
#include <list>

using std::string;
using std::cout;

class Component
{
public:
    virtual ~Component() = default;

    void SetParent(Component *parent)
    {
        m_parent_ = parent;
    }

    Component *GetParent() const
    {
        return m_parent_;
    }

    virtual void Add(Component *) {}
    virtual void Remove(Component *) {}
    virtual bool IsComposite() const
    {
        return false;
    }
    virtual string operator()() const = 0;
private:
    Component *m_parent_;
};

class Leaf
    : public Component
{
public:
    virtual ~Leaf() = default;
    string operator()() const override
    {
        return "Leaf";
    }
};

class Composite
    : public Component
{
public:
    virtual ~Composite() = default;
    void Add(Component *c) override
    {
        m_c_.push_back(c);
        c->SetParent(this);
    }

    void Remove(Component *c) override
    {
        m_c_.remove(c);
        c->SetParent(nullptr);
    }

    bool IsComposite() const override
    {
        return true;
    }

    string operator()() const override
    {
        string result;
        for (const Component *c: m_c_)
        {
            if (c == m_c_.back())
            {
                result += (*c)();
            }
            else
            {
                result += (*c)() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
private:
    std::list<Component*> m_c_;
};

void Client(Component *c)
{
    cout << "Result: " << (*c)() << "\n";
}

int main()
{
    Composite root, pl, pr;
    Leaf a, b, c, d;

    root.Add(&pl);
    root.Add(&pr);
    pl.Add(&a);
    pl.Add(&b);
    pr.Add(&c);
    pr.Add(&d);

    Client(&root);

    return 0;
}