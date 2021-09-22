/**
 * 享元模式是一种结构型设计模式.
 * 运用共享技术来有效地支持大量细粒度对象的复用。
 * 
 */

#include <iostream>
#include <sstream>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::cout;
using std::make_pair;
using std::pair;
using std::stringstream;
using std::initializer_list;

class unsharable_state;

class flyweight
{
public:
    virtual void work(unsharable_state*) const = 0;
    virtual ~flyweight() = default;
};

class unsharable_state
{
public:
    virtual const string info() const = 0;
    virtual ~unsharable_state() = default;
};

class sharable_state
{
public:
    sharable_state(const string &n, int id)
        : m_name_(n),
          m_id_(id)
    {}

    sharable_state(const sharable_state &s) = default;

    const string info() const
    {
        stringstream ss;
        ss << "{name: " << m_name_ << ", id: " << m_id_ << "}";
        return ss.str();
    }

    const string& name() const
    {
        return m_name_;
    }
private:
    std::string m_name_;
    int m_id_;
};

class c_unsharable_state
    : public unsharable_state
{
public:
    const string info() const override
    {
        return "c_unsharable_state";
    }
};

class c_flyweight
    : public flyweight
{
public:
    c_flyweight(const sharable_state &ss)
        : m_share_state_(ss)
    {}

    virtual void work(unsharable_state *us) const override
    {
        cout << "c_flyweight "
             << m_share_state_.info() << ": " << us->info() << '\n';
    }

private:
    sharable_state m_share_state_;
};

class flyweight_factory
{
public:
    flyweight_factory(initializer_list<sharable_state> ss)
    {
        for (auto&& s : ss)
        {
            string k = key(s);
            m_flyweights_.insert(
                make_pair(k,new c_flyweight(s))
            );
        }   
    }

    ~flyweight_factory()
    {
        for (auto &&f : m_flyweights_)
        {
            flyweight *p = f.second;
            if (p != nullptr)
            {
                delete p;
            }
        }
        m_flyweights_.clear();
    }

    flyweight* get_flyweight(const sharable_state &s)
    {
        string k = key(s);
        cout << "flyweight_factory: ";
        if (m_flyweights_.find(k) != m_flyweights_.end())
        {
            cout << "Reusing existing flyweight.\n";
        }
        else
        {
            std::cout << "Can't find the flyweight " << k
                      << ", creating new one.\n";
            m_flyweights_.insert(
                make_pair(k, new c_flyweight(s))
            );
        }
        return m_flyweights_.at(k);
    }

    void list_flyweights() const
    {
        size_t size = m_flyweights_.size();
        cout << "flyweight_factory: I have " << size << " flyweights.\n";
        for (auto &i : m_flyweights_)
        {
            cout << "\t" << i.first << "\n";
        }
    }
private:
    const string& key(const sharable_state &ss) const
    {
        return ss.name();
    }
private:
    unordered_map<string,flyweight*> m_flyweights_;
};

void flyweight_test(
    flyweight_factory &factory,
    const sharable_state &s,
    unsharable_state &us
    )
{
    cout << "flyweight_test: ";
    const flyweight *pf = factory.get_flyweight(s);
    pf->work(&us);
}

int main()
{
    flyweight_factory factory({
        {"FengQinxue", 1},
        {"BailiTusu", 2},
        {"TaiziChangqing", 3},
        {"YingQianshan", 4}
    });
    c_unsharable_state us;

    factory.list_flyweights();

    flyweight_test(factory, {"FengQinxue", 1}, us);
    flyweight_test(factory, {"HangYunxi", 5}, us);
    return 0;
}