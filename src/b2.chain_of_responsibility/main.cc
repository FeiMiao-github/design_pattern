// 责任链模式
// 责任链模式是一种行为设计模式，
// 允许你将请求沿着处理者链进行发送。
// 收到请求后， 每个处理者均可对请求进行处理， 或将其传递给链上的下个处理者。

#include <iostream>
#include <vector>

// 处理者 （Handler） 声明了所有具体处理者的通用接口。
// 该接口通常仅包含单个方法用于请求处理， 但有时其还会包含一个设置链上下个处理者的方法。
class Handler
{
public:
    virtual ~Handler() {}
    typedef const std::string Tag;
    virtual std::string handle(Tag &tag) = 0;
};

// 基础处理者 （Base Handler） 是一个可选的类，
// 你可以将所有处理者共用的样本代码放置在其中。
// 通常情况下， 该类中定义了一个保存对于下个处理者引用的成员变量。
// 客户端可通过将处理者传递给上个处理者的构造函数或设定方法来创建链。
// 该类还可以实现默认的处理行为： 确定下个处理者存在后再将请求传递给它。
class BaseHandler : public Handler
{
public:
    virtual ~BaseHandler() {}
    virtual std::string handle(Tag &tag) override = 0;
    BaseHandler* setNext(BaseHandler* handler)
    {
        m_next_ = handler;
        return handler; 
    }
    std::string sendToNext(Tag &tag)
    {
        if (m_next_)
        {
            return m_next_->handle(tag);
        }
        else
        {
            return "{None}";
        }
    }
protected:
    Handler* m_next_;
};

// 具体处理者 （Concrete Handlers） 包含处理请求的实际代码。
// 每个处理者接收到请求后， 都必须决定是否进行处理， 以及是否沿着链传递请求。
// 处理者通常是独立且不可变的， 需要通过构造函数一次性地获得所有必要地数据。
class ConcreteHandler1 : public BaseHandler
{
public:
    std::string handle(Tag &tag) override
    {
        if (tag != "c_handler_1")
        {
            return sendToNext(tag);
        }
        else
        {
            return "{ConcreteHandler1}";
        }
    }
};

class ConcreteHandler2 : public BaseHandler
{
public:
    std::string handle(Tag &tag) override
    {
        if (tag != "c_handler_2")
        {
            return sendToNext(tag);
        }
        else
        {
            return "{ConcreteHandler2}";
        }
    }
};

class ConcreteHandler3 : public BaseHandler
{
public:
    std::string handle(Tag &tag) override
    {
        if (tag != "c_handler_3")
        {
            return sendToNext(tag);
        }
        else
        {
            return "{ConcreteHandler3}";
        }
    }
};

// 客户端 （Client） 可根据程序逻辑一次性或者动态地生成链。
// 值得注意的是， 请求可发送给链上的任意一个处理者， 而非必须是第一个处理者。
class Client
{
public:
    void run(Handler* handler)
    {
        std::vector<std::string> arr = 
        {
            "c_handler_1",
            "c_handler_2",
            "c_handler_3",
            "c_handler_4"
        };

        for (auto p = arr.begin(); p != arr.end(); p++)
        {
            auto ret = handler->handle(*p);
            std::cout << "Client: "
                      << *p
                      << " -> "
                      << ret
                      << "\n";
        }
    }
};

int main() {
    ConcreteHandler1* ch1 = new ConcreteHandler1;
    ConcreteHandler2* ch2 = new ConcreteHandler2;
    ConcreteHandler3* ch3 = new ConcreteHandler3;

    ch1->setNext(ch2)->setNext(ch3);
    std::cout << "Chain: "
              << "ConcreteHandler1 >> ConcreteHandler2 >> ConcreteHandler3\n";

    Client c;
    c.run(ch1);

    delete ch1;
    delete ch2;
    delete ch3;

    return 0;
}