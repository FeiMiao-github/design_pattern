/**
 * 代理是一种结构型设计模式， 让你能提供真实服务对象的替代品给客户端使用。 
 */

#include <iostream>

using std::cout;

class subject
{
public:
    virtual void work() const = 0;
    virtual ~subject() = default;
};

class c_subject
    : public subject
{
public:
    void work() const
    {
        cout << "c_subject run !\n";
    }
};

class proxy
    : public subject
{
public:
    proxy(c_subject *s)
        : m_s_(s)
    {
    }

    void before() const
    {
        cout << "proxy: before ...\n";
    }

    void after() const
    {
        cout << "proxy: after ...\n";
    }

    void work() const override
    {
        before();
        m_s_->work();
        after();
    }
private:
    c_subject *m_s_;
};

void client(subject *s)
{
    s->work();
}

int main()
{
    c_subject *cs = new c_subject;
    subject *p = new proxy(cs);

    cout << "Real subject:";
    client(cs);
    cout << "Proxy subject: ";
    client(p);

    delete p;
    delete cs;
    return 0;
}