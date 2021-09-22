// 命令模式是一种行为设计模式，
// 它可将请求转换为一个包含与请求相关的所有信息的独立对象。
// 该转换让你能根据不同的请求将方法参数化、 延迟请求执行或将其放入队列中，
// 且能实现可撤销操作

#include <iostream>
#include <vector>

class Command
{
public:
    virtual ~Command() {}
    virtual std::string execute() = 0;
};

template <int Tag>
class ConcreateCommand : public Command
{
public:
    std::string execute() override
    {
        std::string ret = "{ConcreateCommand-" + std::to_string((Tag)) + "}";
        return ret;
    }
};

class App
{
public:
    // [[deprecated("Using execute instead !")]]
    void exe(Command *pc)
    {
        std::string res = pc->execute();
        std::cout << "App: execute command" + res << '\n';
        delete pc;
    }
};

template <int N>
class Client
{
public:
    void run(App &app)
    {
        app.exe(new ConcreateCommand<N>);
        Client<N-1> client;
        client.run(app);
    }
};

template <>
class Client<0>
{
    public:
    void run(App &app)
    {
        app.exe(new ConcreateCommand<0>);
    }
};

int main()
{
    using std::cout;

    Client<3> client;
    App app;

    client.run(app);

    return 0;
}
