// 原型模式是一种创建型模式，使你能够复制已有对象，而又无需使代码依赖它们所属的类
#include <iostream>
#include <unordered_map>

using std::string;
using std::unordered_map;

class icloneable
{
public:
    virtual icloneable* clone() const = 0;
    virtual void log() const = 0;

    virtual ~icloneable() = default;
};

class concrete_prototype:
    public icloneable
{
public:
    concrete_prototype(const string& name)
                       : m_name_(name)
    {
    }

    concrete_prototype(const concrete_prototype&) = default;
    virtual ~concrete_prototype() = default;

    icloneable* clone() const override
    {
        return new concrete_prototype(*this);
    }

    void log() const override
    {
        using std::cout;
        cout << "name: " << m_name_;
    }
private:
    string m_name_;
};

class sub_concrete_prototype
    : public concrete_prototype
{
public:
    sub_concrete_prototype(const string& name,
                           float x,
                           float y)
                           : concrete_prototype(name),
                             m_x_(x),
                             m_y_(y)
    {
    }

    sub_concrete_prototype(const sub_concrete_prototype&) = default;

    icloneable* clone() const override
    {
        return new sub_concrete_prototype(*this);
    }

    void log() const override
    {
        using std::cout;

        concrete_prototype::log();
        cout << ", ";
        cout << "x: " << m_x_;
        cout << ", ";
        cout << "y: " << m_y_;
    }
private:
    float m_x_;
    float m_y_;
};

class prototype_factory
{
public:
    enum class TYPE
    {
        CP,
        SUBCP
    };

    prototype_factory()
    {
        m_map_[TYPE::CP] = new concrete_prototype("concrete prototype");
        m_map_[TYPE::SUBCP] = new sub_concrete_prototype("subclass concrete prototype-rect", 1.0, 1.0);
    }

    ~prototype_factory()
    {
        auto p = m_map_.begin();
        while (p != m_map_.end())
        {
            delete p->second;
            p++;
        }

        m_map_.clear();   
    }

    icloneable* create(TYPE t)
    {
        return m_map_[t]->clone();
    }

private:
    unordered_map<TYPE, icloneable*> m_map_;
};

void client(prototype_factory& pf)
{
    using std::cout;
    using t = prototype_factory::TYPE;

    cout << "clone cp:\n";
    icloneable* ic1 = pf.create(t::CP);
    ic1->log();
    cout << "\n";

    cout << "clone scp:\n";
    icloneable* ic2 = pf.create(t::SUBCP);
    ic2->log();
    cout << "\n";

    delete ic1;
    delete ic2;
}

int main()
{
    prototype_factory pf;
    client(pf);
    return 0;
}