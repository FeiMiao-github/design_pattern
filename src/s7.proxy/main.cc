// 代理模式是一种结构型设计模式
// 让你能够提供对象的替代品或其占位符。
// 代理控制着对于原对象的访问， 并允许在将请求提交给对象前后进行一些处理。

// service interface
// service
// proxy
// client

#include <iostream>

using std::cout;

class Subject
{
public:
    virtual ~Subject() = default;
    virtual void Request() const = 0;
};

class RealSubject : public Subject
{
public:
    void Request() const override
    {
        std::cout << "RealSubject: Handling request.\n";
    }
};

/**
 * @brief The Proxy maintains a reference to an object of the
 * RealSubject class. It can be either lazy-loaded or passed to the
 * Proxy by client.
 */
class Proxy : public Subject
{
private:
    bool CheckAccess() const{
        std::cout <<"Proxy: Checking access prior to firing a real request.\n";
        return true;
    }

    void LogAccess() const
    {
        std::cout << "Proxy: Logging the time of request.\n";
    }
public:
    Proxy(RealSubject *real_subject)
          :  m_real_subject_(new RealSubject(*real_subject))
    {
    }

    ~Proxy()
    {
        delete m_real_subject_;
    }

    void Request() const override
    {
        if (CheckAccess())
        {
            this->m_real_subject_->Request();
            LogAccess();
        }
    }

private:
    RealSubject *m_real_subject_;
};

class Client
{
public:
    void Code(const Subject &subject)
    {
        subject.Request();
    }
};

int main()
{
    Client client;

    std::cout << "Client: Executing the client code with a real subject:\n";
    RealSubject *realSubject = new RealSubject;
    client.Code(*realSubject);

    std::cout << "\n";
    std::cout << "Client: Executing the same client code with a proxy:\n";
    Proxy *proxy = new Proxy(realSubject);
    client.Code(*proxy);

    delete proxy;
    delete realSubject;
    return 0;
}