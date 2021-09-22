/**
 *      命令模式是一种行为设计模式， 它可将请求转换为一个包含与
 * 请求相关的所有信息的独立对象。 
 * 
 */

#include <iostream>

using std::string;
using std::cout;

/**
 *      client
 *      | 
 *    app
 *     /
 *   command
 */
class app;

class command
{
public:
    virtual ~command() = default;
    command(app *a) : m_app_(a) {}
    virtual void execute() = 0;
protected:
    app *m_app_;
};

class app
{
    std::string m_selection_;
public:
    void invoke(command *cmd)
    {
        cmd->execute();
    }

    const string& get_selection() const
    {
        return m_selection_;
    }

    void set_selection(const string &selection)
    {
        m_selection_ = selection;
    }
};

class copy
    : public command
{
public:
    copy(app *a) : command(a) {}
    void execute() override
    {
        m_app_->set_selection("[from copy] hello world!");
    }
};

class paste
    : public command
{
public:
    paste(app *a) : command(a) {}
    void execute() override
    {
        std::cout << "[paste]:" << m_app_->get_selection() << "\n";
    }
};

void client(app *a)
{
    command *cmd = new copy(a);
    command *p = new paste(a);

    a->invoke(cmd);
    a->invoke(p);

    delete p;
    delete cmd;
}

int main()
{
    app a;
    client(&a);
    return 0;
}