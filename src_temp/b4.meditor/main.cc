/**
 * 中介者模式是一种行为模式,用于抽象一组对象之间的交互,使这组对象相互解耦
 *   
 */

#include <iostream>

using namespace std;

class component;

class meditor
{
public:
    virtual void component_change(component*) = 0;
    virtual ~meditor() = default;
};

class component
{
public:
    component(meditor *m, bool enable = true)
        : m_meditor_(m),
          m_enable_(enable)
    {}

    bool& enable()
    {
        return m_enable_;
    }

    virtual void change()
    {
        m_meditor_->component_change(this);
    }

    virtual void showname() const = 0;
    virtual ~component() = default;
protected:
    meditor *m_meditor_;
    bool m_enable_;
};

class component_a
    : public component
{
public:
    component_a(meditor *m)
        : component(m)
    {}

    void showname() const override
    {
        std::cout << "from component:";
        if (m_enable_)
        {
            std::cout << "component-a\n";
        }
        else
        {
            std::cout << "(disable display)\n";
        }
    }
};

class concrete_meditor
    : public meditor
{
public:
    concrete_meditor()
    {
        m_c_a_ = new component_a(this);
        m_c_b_ = new component_a(this);
    }

    ~concrete_meditor()
    {
        delete m_c_a_;
        delete m_c_b_;
    }

    void component_change(component *c)
    {
        if (c == m_c_a_)
        {
            m_c_b_->enable() = !m_c_b_->enable();
        }
        else if (c == m_c_b_)
        {
            m_c_a_->enable() = !m_c_a_->enable();
        }
    }

    component *m_c_a_;
    component *m_c_b_;
};

void client(component *ca, component *cb)
{
    ca->showname();
    cb->change();
    ca->showname();
}

int main()
{
    concrete_meditor cm;
    client(cm.m_c_a_, cm.m_c_b_);
}