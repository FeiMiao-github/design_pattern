
// 单例模式是一种创建型设计模式
// 让你能够保证一个类只有一个实例， 并提供一个访问该实例的全局节点。

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using std::string;
using std::cout;
using std::mutex;
using namespace std::chrono_literals;

class SingletTon
{
public:
    SingletTon(const SingletTon&) = delete;
    SingletTon operator=(const SingletTon&) = delete;

    ~SingletTon()
    {
    }

    static SingletTon* GetInstance(const string &name)
    {
        std::lock_guard<mutex> lock(s_mutex_);
        if (s_inst_ == nullptr)
        {
            s_inst_ = new SingletTon(name);
            cout << "construct singleton !" << s_inst_ << '\n';
        }

        return s_inst_;
    }

    void Show() const
    {
        cout << "thread: " << m_name_ << '\n';
    }
private:
    // 自动回收资源
    class GC
    {
    public:
        ~GC()
        {
            cout << "deconstruct singleton !" << s_inst_ << '\n';
            delete SingletTon::s_inst_;
        }
    };
protected:
    SingletTon(const string& td_name) : m_name_(td_name)
    {}

    static GC s_gc_;
    static SingletTon* s_inst_;
    static mutex s_mutex_;

    string m_name_;
};

SingletTon* SingletTon::s_inst_ = nullptr;
mutex SingletTon::s_mutex_;
SingletTon::GC SingletTon::s_gc_;

void ThreadA()
{
    std::this_thread::sleep_for(1s);
    SingletTon* td = SingletTon::GetInstance("Thread-A");
    td->Show();
}

void ThreadB()
{
    std::this_thread::sleep_for(1s);
    SingletTon* td = SingletTon::GetInstance("Thread-B");
    td->Show();
}

int main()
{
    std::thread threadA(ThreadA);
    std::thread threadB(ThreadB);

    threadA.join();
    threadB.join();

    return 0;
}