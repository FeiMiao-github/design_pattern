// 责任链模式是一种行为模式,用于避免请求的发送者和接收者之间的耦合

#include <iostream>

using std::string;
using std::cout;

/**
 *  @brief define the request interface
 */
class request
{
public:
    enum class e_req : unsigned char {
        REQ_PRINT_NAME,
        REQ_PRINT_AGE,
    };

    virtual e_req tag() const = 0;
};

class request_name
    : public request
{
public:
    request_name(const string& s)
        : m_name_(s)
    {}

    e_req tag() const override
    {
        return e_req::REQ_PRINT_NAME;
    }

    const string &name() const
    {
        return m_name_;
    }
private:
    string m_name_;
};

class request_age
    : public request
{
public:
    request_age(unsigned age)
        : m_age_(age)
    {}

    e_req tag() const override
    {
        return e_req::REQ_PRINT_AGE;
    }

   unsigned age() const
   {
       return m_age_;
   } 
private:
    unsigned m_age_;
};

/**
 * @brief define an interface used to handle the request 
*/
class handler
{
public:
    handler(handler *s) : m_successor_(s) {}

    virtual void handle(request* req)
    {
        if (m_successor_)
        {
            m_successor_->handle(req);
        }
    }

    virtual void set_successor(handler *h)
    {
        m_successor_ = h;
    }

    virtual ~handler() = default;
private:
    handler *m_successor_;
};

class concrete_handler_name
    : public handler
{
public:
    concrete_handler_name(handler *s)
        : handler(s)
    {}

    void handle(request *req) override
    {
        switch (req->tag())
        {
        case request::e_req::REQ_PRINT_NAME:
            {
                request_name *rq = dynamic_cast<request_name*>(req);
                std::cout << "concrete_handler_name:{"
                        << "name:" << rq->name() << "}\n";
            }
            break;
        
        default:
            handler::handle(req);
            break;
        }
    }
};

class concrete_handler_age
    : public handler
{
public:
    concrete_handler_age(handler *s)
        : handler(s)
    {}

    void handle(request *req) override
    {
        switch (req->tag())
        {
        case request::e_req::REQ_PRINT_AGE:
            {
                request_age *rq = dynamic_cast<request_age*>(req);
                std::cout << "concrete_handler_age:{"
                    << "age:" << rq->age() << "}\n";
            }
            break;
        
        default:
            handler::handle(req);
            break;
        }
    }
};

/**
 * @brief The client is responsible for sending a request
 * which needs to be handled by handler.
 */
void client(handler *h)
{
    request_name a("XiaoWang");
    h->handle(&a);

    request_age b(32);
    h->handle(&b);
}

int main()
{
    concrete_handler_age a(nullptr);
    concrete_handler_name n(&a);
    client(&n);

    return 0;
}